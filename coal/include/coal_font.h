#ifndef COAL_FONT_H
#define COAL_FONT_H
#include "coal_types.h"
#include "../external/stb_truetype.h"
#include "coal_gl_gfx.h"
#include "../include/coal_shapes.h"


typedef struct COALTYPE_PREFIX(Text) COALTYPE_PREFIX(Text);
struct COALTYPE_PREFIX(Text)
{
    String8           Font;
    String8           Text;
    F32               x;
    F32               y;
    F32               nx;
    F32               ny;
    F32               GlyphSize;
    Color             Color;
    stbtt_packedchar* GlyphInfo;
    COALTYPE_PREFIX(Texture)       Texture;
    COALTYPE_PREFIX(Rectangle)     Rect;
};

COALAPI COALTYPE_PREFIX(Text)
COAL_PREFIX(CreateText)(String8 Font, String8 Text, F32 x, F32 y, F32 GlyphSize);

COALAPI void
COAL_PREFIX(DrawText)(COALTYPE_PREFIX(Text)* Text, COALTYPE_PREFIX(Renderer)* renderer);


#endif 
