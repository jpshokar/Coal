#include "../include/coal_gl_gfx.h"
#include "../include/coal_matrices.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../external/stb_image.h"

COALTYPE_PREFIX(Renderer)
COAL_PREFIX(CreateRenderer)(I32 Width, I32 Height, I32 RendererFlags)
{ 
    COALTYPE_PREFIX(Renderer) rnd =
    {
        .VertexBufferSize = 2048,
        .VertexColor = (Color){.r=1,.g=1,.b=1,.a=1}
    };
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    
    String8 VertexShader;
    if (RendererFlags & COALENUM_PREFIX(RENDERER_3D)){
        
        
        VertexShader = 
            "#version 330 core\n"
            "layout (location=0) in vec3 Position;\n"
            "layout (location=1) in vec4 Color;\n"
            "layout (location=2) in vec2 Texture;\n"
            "layout (location=3) in float  texEnabled;\n"
            "out vec4 FColor;\n"
            "out vec2    TC;\n"
            "out float   TE;\n"
            "uniform mat4 orthographic;\n"
            "uniform mat4 perspective;\n"
            "uniform mat4 translation;\n"
            "uniform mat4 rotate;\n"
            "void main() {\n"
            "FColor = Color;\n"
            "TE = texEnabled;\n"
            "TC = Texture;\n"
            "gl_Position =  perspective *  orthographic * translation * rotate * vec4(Position.xyz, 1.0) ;\n"
            "}\n\0";
        rnd.Is3D = 1;
        glEnable(GL_DEPTH_TEST);  
        
    } else
    {
        VertexShader = 
            "#version 330 core\n"
            "layout (location=0) in vec3 Position;\n"
            "layout (location=1) in vec4 Color;\n"
            "layout (location=2) in vec2 Texture;\n"
            "layout (location=3) in float  texEnabled;\n"
            "out vec4 FColor;\n"
            "out vec2    TC;\n"
            "out float   TE;\n"
            "uniform mat4 orthographic;\n"
            "uniform mat4 translation;\n"
            "uniform mat4 rotate;\n"
            "void main() {\n"
            "FColor = Color;\n"
            "TE = texEnabled;\n"
            "TC = Texture;\n"
            "gl_Position = translation * rotate * orthographic * vec4(Position, 1.0) ;\n"
            "}\n\0";
    }
    
    String8 FragmentShader = 
        "#version 330 core\n"
        "out vec4 Color;\n"
        "in vec4 FColor;\n"
        "in vec2   TC;\n"
        "in float  TE;\n"
        "uniform sampler2D Tex;\n"
        "void main() {\n"
        "if (TE == 1){\n"
        "Color = texture(Tex, TC) * FColor;\n"
        "}\n"
        "else if (TE == 2){\n"
        "vec4 Sampled = vec4(1.0,1.0,1.0,texture(Tex, TC).r);"
        "Color =  vec4(FColor) * Sampled;\n"
        "}\n"  
        "else {"
        "Color = FColor;\n"
        "}\n"
        "}\n\0";
    
    
    rnd.FragmentShader = FragmentShader;
    rnd.VertexShader = VertexShader;
    
    rnd.Shader = COAL_PREFIX(CreateShader)(VertexShader, FragmentShader);
    
    
    
    glGenBuffers(1, &rnd.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, rnd.VBO);
    glBufferData(GL_ARRAY_BUFFER, rnd.VertexBufferSize, (void*)0, GL_DYNAMIC_DRAW);
    
    
    COAL_PREFIX(CreateVertexFormat)(&rnd.Shader, COALENUM_PREFIX(VERTEX_POSITION) | COALENUM_PREFIX(VERTEX_COLOR) | COALENUM_PREFIX(VERTEX_TEXTURE) | COALENUM_PREFIX(VERTEX_TEXTURE_ENABLED));
    
    glBindVertexArray(0);
    
    rnd.View.FOV = 45;
    /*
    int buffer_size;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffer_size);
    printf("Buffer Size%i\n", buffer_size);
    */
    
    COAL_PREFIX(PushViewMatrices)(rnd.Shader, rnd, Width, Height) ;
    
    return rnd;
}

void 
COAL_PREFIX(ResizeRenderer)(COALTYPE_PREFIX(Renderer)* renderer, I32 w, I32 h)
{
    COAL_PREFIX(PushViewMatrices)(renderer->Shader, *renderer, w, h) ;
}
void 
COAL_PREFIX(PushViewMatrices)(COALTYPE_PREFIX(Shader) shd, COALTYPE_PREFIX(Renderer) Renderer, F32 W, F32 H)
{
    M4 orthographic = {0};
    
    COAL_PREFIX(M4Orthographic)(orthographic, 0, W, H, 0, -1.0f, 1.0f);
    COAL_PREFIX(UniformMatrix4fv)(shd, "orthographic", 1, 0, (F32*)orthographic);
    
    
    if (Renderer.Is3D){
        M4 perspective = {0};
        COAL_PREFIX(M4Perspective)(perspective, COAL_DEG2RAD(Renderer.View.FOV), (F32)W/(F32)H, 1.0f, 200.0f );
        COAL_PREFIX(UniformMatrix4fv)(shd, "perspective", 1, 0, (F32*)perspective);
    }
    
    
    
    
    COAL_PREFIX(UseView)(Renderer.View,&Renderer);
    COAL_PREFIX(PushShader)(Renderer.Shader);
}
void
COAL_PREFIX(ClearColor)(Color color)
{
    glClearColor(color.r / 255, color.g / 255, color.b / 255, color.a /255);
}
void 
COAL_PREFIX(Clear)()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void 
COAL_PREFIX(UseView)(COALTYPE_PREFIX(CoalView) view,struct COALTYPE_PREFIX(Renderer)* renderer)
{
    COAL_PREFIX(UseViewShader)(view, renderer->Shader);
    
}

void 
COAL_PREFIX(UseViewShader)(COALTYPE_PREFIX(CoalView) view, COALTYPE_PREFIX(Shader) Shader)
{
    M4 Translation = {0};
    COAL_PREFIX(M4Translation)(Translation, view.x,view.y,view.z);
    COAL_PREFIX(UniformMatrix4fv)(Shader, "translation", 1, 0, (F32*)Translation);
    
    M4 Rotate = {0};
    COAL_PREFIX(M4Rotate)(Rotate, COAL_DEG2RAD(view.Rotate), 1.0f, 1.0f,1.0f);
    COAL_PREFIX(UniformMatrix4fv)(Shader, "rotate", 1, 0, (F32*)Rotate);
}
COALTYPE_PREFIX(Texture) 
COAL_PREFIX(LoadTexture)(String8 File, I32 TextureFmt)
{
    COALTYPE_PREFIX(Texture) tex = {0};
    
    U8* Data = stbi_load(File, &tex.Width, &tex.Height, 0,0);
    if (Data == NULL)
    {
        COAL_PRINTF("Failed to load image: \"%s\"\n", File);  
    }
    
    
    glGenTextures(1, &tex.Id);
    glBindTexture(GL_TEXTURE_2D, tex.Id);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (TextureFmt & COALENUM_PREFIX(TEXTURE_JPG))
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.Width, tex.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
        
    } else if (TextureFmt & COALENUM_PREFIX(TEXTURE_PNG))
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.Width, tex.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
        
    }
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    tex.LoadedTexture = 1;;
    stbi_image_free(Data);
    return tex;
}


void
COAL_PREFIX(Wireframe)()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void
COAL_PREFIX(Filled)()
{
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


COALTYPE_PREFIX(Texture) 
COAL_PREFIX(CreateTexture)(F32 Width, F32 Height, I32 TextureFmt)
{
    COALTYPE_PREFIX(Texture) texture;
    glGenTextures(1, &texture.Id);
    glBindTexture(GL_TEXTURE_2D, texture.Id);
    
    texture.LoadedTexture = 1;
    if (TextureFmt & COALENUM_PREFIX(TEXTURE_JPG))
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
        
    } else if (TextureFmt & COALENUM_PREFIX(TEXTURE_PNG))
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        
    }
    else if (TextureFmt & COALENUM_PREFIX(TEXTURE_FRAMEBUFFER))
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
        
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    return texture;
}
COALTYPE_PREFIX(Texture) 
COAL_PREFIX(CreateSpecficTexture)(F32 Width, F32 Height, I32 TextureFmt, const void* Data)
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8);
    COALTYPE_PREFIX(Texture) texture;
    glGenTextures(1, &texture.Id);
    glBindTexture(GL_TEXTURE_2D, texture.Id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    
    texture.LoadedTexture = 1;
    if (TextureFmt & COALENUM_PREFIX(TEXTURE_JPG))
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
        
    } else if (TextureFmt & COALENUM_PREFIX(TEXTURE_PNG))
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
        
    }
    else if (TextureFmt & COALENUM_PREFIX(TEXTURE_FRAMEBUFFER))
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
        
    }else if (TextureFmt & COALENUM_PREFIX(TEXTURE_TEXT))
    {
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RED, GL_UNSIGNED_BYTE, Data);
        
		
		
    }
    glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    glGenerateMipmap(GL_TEXTURE_2D);
    return texture;
}
void 
COAL_PREFIX(DisableTextures)(COALTYPE_PREFIX(Renderer)* renderer)
{
    renderer->IsTextureDisabled = 1;
}
void 
COAL_PREFIX(EnableTextures)(COALTYPE_PREFIX(Renderer)* renderer)
{
    renderer->IsTextureDisabled = 0;
}