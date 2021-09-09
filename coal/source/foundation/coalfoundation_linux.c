#include "../../include/foundation/coalfoundation_windows.h"


/*
Current window system supported. 
    * X11


TODO: 
 
*/
#ifdef __linux__
#ifdef  COAL_WINDOW_X11

#include <sys/time.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysymdef.h>
#include <stddef.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <string.h>
typedef struct CoalX11 CoalX11;
struct CoalX11
{
    Window Win;
    Display* Display;
    XEvent Events;
    Screen* Screen;
    XVisualInfo* XVisual;
    I32 ScreenID;
    F32 MajorGLX, MinorGLX;
    GLXContext Context;
    double offset;
    KeySym KSym;
    XWindowAttributes XWA;
};
static CoalX11 X11Window;
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display*, GLXFBConfig, GLXContext, Bool, const I32*);
static B32 /* Helper function, adapted from https://www.khronos.org/opengl/wiki/Tutorial:_OpenGL_3.0_Context_Creation_(GLX) */
Coal_OpenGLExtensionSupported(String8  ExtList, String8  Extension){
    String8 Start;
    String8 Where;
    String8 Terminator;
    
    Where = strchr(Extension, ' ');
    if (Where || *Extension == '\0')
        return 0;
    for (Start=ExtList;;)
    {
        Where = strstr(Start, Extension);
        if (!Where)
            break;
        
        Terminator = Where + strlen(Extension);
        
        if (Where == Start || *(Where-1) == ' ')
            if (*Terminator == ' ' || *Terminator == '\0')
            return 1;
        Start = Terminator;
    }
    return 0;
};

B32
COAL_PREFIX(KeyPressed)(I8 Key)
{
    I8 key[32];
    XQueryKeymap(X11Window.Display, key);
    KeyCode keys = XKeysymToKeycode(X11Window.Display, Key);
    return (key[keys>>3] & 1 << (keys & 7));
    
}
void 
COAL_PREFIX(ConfigurateGLXVersion)(F32 Major, F32 Minor)
{
    X11Window.MajorGLX = Major;
    X11Window.MinorGLX = Minor;
}

F32 
COAL_PREFIX(GetTime)(void)
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    I32 time = (uint64_t) tv.tv_sec * (uint64_t) 1000000 + (uint64_t) tv.tv_usec;
    return (time - X11Window.offset)/ 1000000;
}
void
COAL_PREFIX(InitWindow)(void)
{
    struct timeval tv;
    gettimeofday(&tv, 0);
    I32 time = (uint64_t) tv.tv_sec * (uint64_t) 1000000 + (uint64_t) tv.tv_usec;
    X11Window.offset = time;
}
COALTYPE_PREFIX(Window)
COAL_PREFIX(CreateWindow)(String8 Title, F32 Width, F32 Height, COALTYPE_PREFIX(Style) Style)
{
    
    COALTYPE_PREFIX(Window) Window = (COALTYPE_PREFIX(Window))
    {
        .Title = Title,
        .Style = Style
    };
    X11Window.Display = XOpenDisplay(0);
    if (X11Window.Display ==  NULL)
    {
        COAL_PRINTF("[COALX11]: Failed to open display.\n");
    }
    X11Window.Screen = DefaultScreenOfDisplay(X11Window.Display);
    X11Window.ScreenID = DefaultScreen(X11Window.Display);
    
    I32 Attributes[] = 
    {
        GLX_X_RENDERABLE    , True,
		GLX_DRAWABLE_TYPE   , GLX_WINDOW_BIT,
		GLX_RENDER_TYPE     , GLX_RGBA_BIT,
		GLX_X_VISUAL_TYPE   , GLX_TRUE_COLOR,
		GLX_RED_SIZE        , 8,
		GLX_GREEN_SIZE      , 8,
		GLX_BLUE_SIZE       , 8,
		GLX_ALPHA_SIZE      , 8,
		GLX_DEPTH_SIZE      , 24,
		GLX_STENCIL_SIZE    , 8,
		GLX_DOUBLEBUFFER    , True,
		None
    };
    I32 FramebufferCount;
    GLXFBConfig* FramebufferConfig = glXChooseFBConfig(X11Window.Display, DefaultScreen(X11Window.Display), Attributes, &FramebufferCount);
    if (FramebufferCount == 0)
        COAL_PRINTF("[COALX11]: Couldn't retrieve framebuffer for drawing...\n");
    
    I32 BestFramebuffer = 0, WorstFramebuffer = -1, BestSamplers = -1, WorstSamplers = 999;
    for (I32 i=0;i<FramebufferCount;i++)
    {
        XVisualInfo* Temp = glXGetVisualFromFBConfig(X11Window.Display, FramebufferConfig[i]);
        if (Temp != 0)
        {
            I32 Samplers;
            I32 SamplerBuffer;
            glXGetFBConfigAttrib( X11Window.Display, FramebufferConfig[i], GLX_SAMPLE_BUFFERS, &SamplerBuffer );
			glXGetFBConfigAttrib( X11Window.Display, FramebufferConfig[i], GLX_SAMPLES       , &Samplers  );
            if ( BestFramebuffer < 0 || (SamplerBuffer && Samplers > BestSamplers))
            {
                BestFramebuffer = i;
                BestSamplers = Samplers;
            }
            if (WorstFramebuffer <0 || !SamplerBuffer || Samplers < WorstSamplers)
                WorstFramebuffer = i;
            WorstSamplers = Samplers;
            
        }
        XFree(Temp);
    }
    
    GLXFBConfig FBC = FramebufferConfig[BestFramebuffer];
    XFree(FramebufferConfig);
    
    
    X11Window.XVisual  = glXGetVisualFromFBConfig(X11Window.Display, FBC);
    if (X11Window.XVisual == 0)
        COAL_PRINTF("[COALX11]: Failed to create visual.\n");
    XSetWindowAttributes Attr;
    Attr.override_redirect = True;
    Attr.border_pixel = BlackPixel(X11Window.Display, X11Window.ScreenID);
    Attr.background_pixel = WhitePixel(X11Window.Display, X11Window.ScreenID);
    Attr.colormap = XCreateColormap(X11Window.Display, RootWindow(X11Window.Display, X11Window.ScreenID), X11Window.XVisual->visual, AllocNone);
    Attr.event_mask = ExposureMask | KeyPressMask;
    
    
    if (Width == COAL_USE_DEFAULT) 
        Width = X11Window.Screen->width/3;
    if (Height == COAL_USE_DEFAULT)
        Height = X11Window.Screen->height/2;
    Window.w = Width;
    Window.h = Height;
    
    X11Window.Win = XCreateWindow(X11Window.Display, RootWindow(X11Window.Display, X11Window.ScreenID), 0,0,Width,Height,0, X11Window.XVisual->depth, InputOutput, X11Window.XVisual->visual, CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &Attr);
    if (!(Style & COALENUM_PREFIX(STYLE_RESIZABLE))){
        XSizeHints* hints = XAllocSizeHints();
        hints->flags = PMinSize |  PMaxSize;
        hints->min_width = Width;
        hints->min_height = Height;
        hints->max_width = Width;
        hints->max_height = Height;
        XSetWMNormalHints(X11Window.Display, X11Window.Win , hints);
        XFree(hints);
        
    }
    
    
    
    XSelectInput(X11Window.Display, X11Window.Win, PointerMotionMask | ButtonPressMask | ButtonReleaseMask | EnterWindowMask | LeaveWindowMask| KeyPressMask | KeyReleaseMask | KeymapStateMask| ExposureMask);
    
    
    
    XClearWindow(X11Window.Display, X11Window.Win);
    XMapRaised(X11Window.Display, X11Window.Win);
    XStoreName(X11Window.Display, X11Window.Win, Title);
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB = (glXCreateContextAttribsARBProc) glXGetProcAddressARB( (const GLubyte *) "glXCreateContextAttribsARB");
    
    I32 CAttribs[] = {
        GLX_CONTEXT_MAJOR_VERSION_ARB, X11Window.MajorGLX == 0 ? 3 : X11Window.MajorGLX,
        GLX_CONTEXT_MINOR_VERSION_ARB,  X11Window.MinorGLX == 0 ? 3 : X11Window.MinorGLX,
        GLX_CONTEXT_FLAGS_ARB, GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
        None
    };
    String8 exts = glXQueryExtensionsString(X11Window.Display, X11Window.ScreenID);
    if (!Coal_OpenGLExtensionSupported( exts, "GLX_ARB_create_context"))
        X11Window.Context= glXCreateNewContext( X11Window.Display, FBC, GLX_RGBA_TYPE, 0, True );
    else 
        X11Window.Context= glXCreateContextAttribsARB( X11Window.Display, FBC, 0, 1, CAttribs);
    XSync(X11Window.Display, False);
    if (!glXIsDirect(X11Window.Display, X11Window.Context))
    {
        COAL_PRINTF("[COALX11GL] : Indirect GLX Rendering context obtained.");
    } 
    
    
    
    return Window;
}

void
COAL_PREFIX(MakeContextCurrent)(COALTYPE_PREFIX(Window)* Window)
{
    glXMakeCurrent(X11Window.Display, X11Window.Win, X11Window.Context);
}
void
COAL_PREFIX(PollEvents)(COALTYPE_PREFIX(Window)* window, COALTYPE_PREFIX(Event)* events)
{
    
    while (XPending (X11Window.Display) > 0)
        XNextEvent(X11Window.Display, &X11Window.Events);
    switch (X11Window.Events.type) 
    {
        case KeymapNotify:
        {
            XRefreshKeyboardMapping(&X11Window.Events.xmapping);
        } break;
        case KeyPress:
        {
            XLookupString(&X11Window.Events.xkey, &events->KeyPressed, 1, &X11Window.KSym, 0);
            events->Type = COALENUM_PREFIX(MESSAGE_KEY_PRESS);
        } break;
        case KeyRelease:
        {
            XLookupString(&X11Window.Events.xkey, &events->KeyReleased, 1, &X11Window.KSym, 0);
            events->Type = COALENUM_PREFIX(MESSAGE_KEY_RELEASE);
        } break;
        case Expose:
        {
            events->Type = COALENUM_PREFIX(MESSAGE_WINDOW_RESIZE);
            XGetWindowAttributes(X11Window.Display, X11Window.Win, &X11Window.XWA); 
            events->WindowResizeSizeH = X11Window.XWA.width;
            events->WindowResizeSizeW = X11Window.XWA.width;
            COAL_PREFIX(SwapBuffers)(window);
        }break;
        case EnterNotify:
        {
            events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_ENTER);
        } break;
        case LeaveNotify:
        {
            events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_LEAVE);
        } break;
        /* Mouse events */
        case ButtonPress:
        {
            events->Type = COALENUM_PREFIX(MESSAGE_MOUSE_PRESSED);
            switch (X11Window.Events.xbutton.button)
            {
                case 1:
                {
                    events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_LEFT_PRESSED);
                } break;
                case 2:
                {
                    events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_MIDDLE_PRESSED);
                } break;
                case 3:
                {
                    events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_RIGHT_PRESSED);
                } break;
                case 4:
                {
                    events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_SCROLL_UP);
                } break;
                case 5:
                {
                    events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_SCROLL_DOWN);
                } break;
            }
        } break;
        
        case ButtonRelease:
        {
            events->Type = COALENUM_PREFIX(MESSAGE_MOUSE_RELEASE);
            switch (X11Window.Events.xbutton.button)
            {
                case 1:
                {
                    events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_LEFT_RELEASED);
                } break;
                case 2:
                {
                    events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_MIDDLE_RELEASED);
                } break;
                case 3:
                {
                    events->Mouse = COALENUM_PREFIX(MESSAGE_MOUSE_RIGHT_RELEASED);
                } break;
            }
        } break;
        case MotionNotify:{
            events->MouseX = X11Window.Events.xmotion.x;
            events->MouseY = X11Window.Events.xmotion.y;
            events->Mouse  = COALENUM_PREFIX(MESSAGE_MOUSE_MOVED);
        }break;
        case DestroyNotify:
        {
            events->Type = COALENUM_PREFIX(MESSAGE_WINDOW_CLOSE);
        } break;
        
    };
}



void
COAL_PREFIX(SwapBuffers)(COALTYPE_PREFIX(Window)* Window)
{
    glXSwapBuffers(X11Window.Display, X11Window.Win);
}
void 
COAL_PREFIX(DeleteWindow)(COALTYPE_PREFIX(Window)* Window)
{
    XCloseDisplay(X11Window.Display);
    XDestroyWindow(X11Window.Display, X11Window.Win);
    XCloseDisplay(X11Window.Display);
}
#else
#error Coal: This window system is not supported.
#endif
#endif