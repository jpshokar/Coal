
#ifndef COAL_GFX_H
#define COAL_GFX_H
#include "coal_types.h"
#include "../include/coal_gl_shader.h"

typedef enum COALTYPE_PREFIX(TextureFmt) COALTYPE_PREFIX(TextureFmt);
enum COALTYPE_PREFIX(TextureFmt)
{
    COALENUM_PREFIX(TEXTURE_PNG)          = 1 << 1,
    COALENUM_PREFIX(TEXTURE_JPG)          = 1 << 2,
    COALENUM_PREFIX(TEXTURE_FRAMEBUFFER)  = 1 << 3,
    COALENUM_PREFIX(TEXTURE_TEXT)         = 1 << 4
};
typedef enum COALTYPE_PREFIX(RendererFlags) COALTYPE_PREFIX(RendererFlags);
enum COALTYPE_PREFIX(RendererFlags)
{
    COALENUM_PREFIX(RENDERER_3D)  = 1 << 1,
    COALENUM_PREFIX(RENDERER_2D)  = 1 << 2
};
typedef struct COALTYPE_PREFIX(CoalView) COALTYPE_PREFIX(CoalView);
struct COALTYPE_PREFIX(CoalView)
{
    F32 x;
    F32 y;
    F32 z;
    F32 FOV;
    F32 Rotate;
};


typedef struct COALTYPE_PREFIX(Renderer) COALTYPE_PREFIX(Renderer);
struct COALTYPE_PREFIX(Renderer)
{
    COALTYPE_PREFIX(Shader) Shader;
    COALTYPE_PREFIX(CoalView)   View;
    U32        VBO;
    U32        VertexBufferSize;
    Color      VertexColor;
    V2         VertexUV;
    I32        VertexOccupied;
    I32        TextureEnabled;
    I32        Is3D;
    I32        IsTextureDisabled;
    String8    FragmentShader;
    String8    VertexShader;
};

typedef struct COALTYPE_PREFIX(Texture) COALTYPE_PREFIX(Texture);
struct COALTYPE_PREFIX(Texture)
{
    String8  FileName;
    I32      Width;
    I32      Height;
    U32      Id;
    U32      LoadedTexture;
    
};

COALAPI void 
COAL_PREFIX(ResizeRenderer)(COALTYPE_PREFIX(Renderer)* renderer, I32 w, I32 h);

COALAPI void 
COAL_PREFIX(UseView)(COALTYPE_PREFIX(CoalView) view,struct  COALTYPE_PREFIX(Renderer)* renderer);
COALAPI void 
COAL_PREFIX(UseViewShader)(COALTYPE_PREFIX(CoalView) view, COALTYPE_PREFIX(Shader) Shader);

COALAPI void
COAL_PREFIX(ClearColor)(Color color);
COALAPI void 
COAL_PREFIX(DisableTextures)(COALTYPE_PREFIX(Renderer)* renderer);
COALAPI void 
COAL_PREFIX(EnableTextures)(COALTYPE_PREFIX(Renderer)* renderer);
COALAPI void 
COAL_PREFIX(Clear)();
COALAPI void 
COAL_PREFIX(PushViewMatrices)(COALTYPE_PREFIX(Shader) shd, COALTYPE_PREFIX(Renderer) Renderer, F32 W, F32 H);
COALAPI COALTYPE_PREFIX(Texture) 
COAL_PREFIX(LoadTexture)(String8 File, I32 TextureFmt);


COALAPI COALTYPE_PREFIX(Texture) 
COAL_PREFIX(CreateTexture)(F32 Width, F32 Height, I32 TextureFmt);
COALAPI COALTYPE_PREFIX(Texture) 
COAL_PREFIX(CreateSpecficTexture)(F32 Width, F32 Height, I32 TextureFmt, const void* Data);


COALAPI COALTYPE_PREFIX(Renderer)
COAL_PREFIX(CreateRenderer)(I32 Width, I32 Height, I32 RendererFlags);

COALAPI void
COAL_PREFIX(Wireframe)();

COALAPI void
COAL_PREFIX(Filled)();

#endif 


