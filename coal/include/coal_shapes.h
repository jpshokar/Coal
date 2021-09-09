
#ifndef COAL_SHAPES_H
#define COAL_SHAPES_H
#include "coal_types.h"
#include "coal_gl_gfx.h"
typedef struct COALTYPE_PREFIX(Rectangle) COALTYPE_PREFIX(Rectangle);
struct COALTYPE_PREFIX(Rectangle)
{
    F32 x;
    F32 y;
    F32 w;
    F32 h;
    Color Color;
    V2 Orgin;
    COALTYPE_PREFIX(Texture) Texture;
    struct 
    {
        V2 TopLeft;
        V2 TopRight;
        V2 BottomLeft;
        V2 BottomRight;
    } TextureCoordinates;
};

COALAPI COALTYPE_PREFIX(Rectangle) 
COAL_PREFIX(CreateRectangle)(F32 x, F32 y, F32 w, F32 h);
COALAPI void 
COAL_PREFIX(SetRectangleTexture)(COALTYPE_PREFIX(Rectangle)* rectangle, COALTYPE_PREFIX(Texture) texture);
COALAPI void 
COAL_PREFIX(DrawRectangle)(COALTYPE_PREFIX(Rectangle)* rectangle,  COALTYPE_PREFIX(Renderer) renderer);
COALAPI void 
COAL_PREFIX(DrawRectangleRotated)(COALTYPE_PREFIX(Rectangle)* rectangle, F32 Degree,COALTYPE_PREFIX(Renderer) renderer);

COALAPI void
COAL_PREFIX(DrawLine)(F32 x0, F32 y0, F32 x1, F32 y1, Color Color,COALTYPE_PREFIX(Renderer) Renderer);

#endif 
