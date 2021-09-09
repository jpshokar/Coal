
/* NOTE: This isn't the win32 stuff, this is just the base class for the windows stuff.
Windows stuff will be prefixed with a  win32 tag. */

#ifndef COALFOUNDATION_WINDOWS_H
#define COALFOUNDATION_WINDOWS_H
#include "../coal_types.h"
#define COAL_USE_DEFAULT 1 << 2

typedef enum COALTYPE_PREFIX(CoalMouseMessages) COALTYPE_PREFIX(CoalMouseMessages);
enum COALTYPE_PREFIX(CoalMouseMessages) 
{
    COALENUM_PREFIX(MESSAGE_MOUSE_LEFT_PRESSED) = 1 << 6,
    COALENUM_PREFIX(MESSAGE_MOUSE_RIGHT_PRESSED) = 1 << 7,
    COALENUM_PREFIX(MESSAGE_MOUSE_MIDDLE_PRESSED) = 1 << 8,
    COALENUM_PREFIX(MESSAGE_MOUSE_SCROLL_UP)  = 1 << 9,
    COALENUM_PREFIX(MESSAGE_MOUSE_SCROLL_DOWN)  = 1 << 10,
    COALENUM_PREFIX(MESSAGE_MOUSE_MOVED)  = 1 << 11,
    COALENUM_PREFIX(MESSAGE_MOUSE_ENTER) = 1 << 12,
    COALENUM_PREFIX(MESSAGE_MOUSE_LEAVE)  = 1 << 13,
    COALENUM_PREFIX(MESSAGE_MOUSE_LEFT_RELEASED) = 1 << 14,
    COALENUM_PREFIX(MESSAGE_MOUSE_RIGHT_RELEASED) = 1 << 15,
    COALENUM_PREFIX(MESSAGE_MOUSE_MIDDLE_RELEASED) = 1 << 16,
};
typedef enum COALTYPE_PREFIX(Messages) COALTYPE_PREFIX(Messages);
enum COALTYPE_PREFIX(Messages)
{
    COALENUM_PREFIX(MESSAGE_NONE) = 1 << 0,
    COALENUM_PREFIX(MESSAGE_KEY_PRESS) = 1 << 1,
    COALENUM_PREFIX(MESSAGE_KEY_RELEASE) = 1 << 2,
    COALENUM_PREFIX(MESSAGE_WINDOW_CLOSE) = 1 << 3,
    COALENUM_PREFIX(MESSAGE_MOUSE_PRESSED) = 1 << 4,
    COALENUM_PREFIX(MESSAGE_MOUSE_RELEASE) = 1 << 5,
    COALENUM_PREFIX(MESSAGE_WINDOW_RESIZE) = 1 << 6
        
};
typedef enum COALTYPE_PREFIX(Style) COALTYPE_PREFIX(Style);
enum COALTYPE_PREFIX(Style)
{
    COALENUM_PREFIX(STYLE_RESIZABLE) = 1 << 1
};
typedef struct COALTYPE_PREFIX(Event) COALTYPE_PREFIX(Event);
struct COALTYPE_PREFIX(Event)
{
    
    COALTYPE_PREFIX(Messages) Type;
    /* Keyboard events. */
    I8           KeyPressed;
    I8           KeyReleased;
    /* Mouse Events */
    I32 MouseX;
    I32 MouseY;
    COALTYPE_PREFIX(CoalMouseMessages) Mouse;
    /* Window events */
    I32 WindowResizeSizeW;
    I32 WindowResizeSizeH;
};

typedef struct COALTYPE_PREFIX(Window) COALTYPE_PREFIX(Window);
struct COALTYPE_PREFIX(Window)
{
    String8 Title;
    F32 w;
    F32 h;
    COALTYPE_PREFIX(Style) Style;
    
};
B32
COAL_PREFIX(KeyPressed)(I8 Key);
void 
COAL_PREFIX(ConfigurateGLXVersion)(F32 Major, F32 Minor);
F32 
COAL_PREFIX(GetTime)(void);
void
COAL_PREFIX(InitWindow)(void);
COALTYPE_PREFIX(Window)
COAL_PREFIX(CreateWindow)(String8 Title, F32 Width, F32 Height, COALTYPE_PREFIX(Style) Style);


void
COAL_PREFIX(PollEvents)(COALTYPE_PREFIX(Window)* window, COALTYPE_PREFIX(Event)* events);

void 
COAL_PREFIX(DeleteWindow)(COALTYPE_PREFIX(Window)* Window);

void
COAL_PREFIX(MakeContextCurrent)(COALTYPE_PREFIX(Window)* Window);

void
COAL_PREFIX(SwapBuffers)(COALTYPE_PREFIX(Window)* Window);
#endif
