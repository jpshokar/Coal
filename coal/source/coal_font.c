
#include "../include/coal_font.h"
#define COAL_GL_IMPL
#include "../include/helpers/coalgl_helper.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "../external/stb_truetype.h"
COALTYPE_PREFIX(Text)
COAL_PREFIX(CreateText)(String8 Font, String8 Text, F32 x, F32 y, F32 GlyphSize)
{
    COALTYPE_PREFIX(Text) Fnt = 
    {
        .Font       = Font,
        .x          = x,
        .y          = y,
        .nx         = x,
        .ny         = y,
        .GlyphSize  = GlyphSize,
        .Color      = (Color){255,255,255,255},
        .Text       = Text
    };
    
    FILE* file = fopen(Font, "rb");
    if (file == NULL){
        COAL_PRINTF("[Coal] \"%s\" failed to read.\n", Font);
        
    }
    long Bytes;
    
    fseek(file, 0L, SEEK_END);
    Bytes = ftell(file);
    fseek(file, 0L, SEEK_SET);
    
    U8* FontData = COAL_MALLOC(sizeof(char)*Bytes+1);
    if (FontData == NULL ) COAL_PRINTF("[Coal] Mem error");
    
    if (fread(FontData, 1, Bytes, file) != Bytes) COAL_PRINTF("[Coal] Reading error");
    FontData[Bytes] = '\0';
    
    
    U8* AtlasData = COAL_MALLOC(sizeof(U8) * 1024 * 1024);
    
    
    Fnt.GlyphInfo = COAL_MALLOC(sizeof(stbtt_packedchar) * ( '~' - ' ' ));
    
    stbtt_pack_context PC;
    if (!stbtt_PackBegin(&PC, AtlasData, 1024, 1024, 0 , 1, 0))
        COAL_PRINTF("[Coal]: Failed to begin font packing. \n");
    
    stbtt_PackSetOversampling(&PC, 2,2);
    
    if (!stbtt_PackFontRange(&PC, FontData, 0, GlyphSize, ' ', '~' - ' ', Fnt.GlyphInfo))
        COAL_PRINTF("[Coal]: Failed to end font packing.");
    stbtt_PackEnd(&PC);
    
    Fnt.Texture = COAL_PREFIX(CreateSpecficTexture)(1024,1024, COALENUM_PREFIX(TEXTURE_TEXT), AtlasData);
    Fnt.Rect = COAL_PREFIX(CreateRectangle)(x,y,1024,1024);
    Fnt.Rect.Texture = Fnt.Texture;
    return Fnt;
}


void
COAL_PREFIX(DrawText)(COALTYPE_PREFIX(Text)* Text, COALTYPE_PREFIX(Renderer)* renderer)
{
    
    
    
    F32 OffsetX = 0;
    F32 OffsetY = 0;
    for (I32 i=0;i<Coal_GetLengthStr(Text->Text);i++)
    {
        
        U8 ActiveCharacter = (U8)Text->Text[i];
        
        if (!(ActiveCharacter == '\n' || ActiveCharacter == '\0' || ActiveCharacter == '\t')){
            stbtt_aligned_quad quad = {0};
            stbtt_GetPackedQuad(Text->GlyphInfo, 1024, 1024, ActiveCharacter - ' ', &OffsetX, &OffsetY, &quad, 0);
            F32 XMin = quad.x0+Text->nx;
            F32 XMax = quad.x1+Text->nx; 
            F32 YMin = quad.y1 + Text->ny;
            F32 YMax = quad.y0 + Text->ny;
            
             COAL_PREFIX(PushDrawing)(renderer); {
                
                 COAL_PREFIX(PushTexture)(Text->Texture);
                renderer->TextureEnabled = 2;
                 COAL_PREFIX(Color4f)(Text->Color.r,Text->Color.g,Text->Color.b,Text->Color.a);
                
                 COAL_PREFIX(TexCoord2d)(quad.s0, quad.t1);
                 COAL_PREFIX(Vertex2f)(XMin , YMin);
                 COAL_PREFIX(TexCoord2d)(quad.s0, quad.t0);
                 COAL_PREFIX(Vertex2f)(XMin, YMax);
                 COAL_PREFIX(TexCoord2d)(quad.s1, quad.t0);
                 COAL_PREFIX(Vertex2f)(XMax, YMax);
                 COAL_PREFIX(TexCoord2d)(quad.s1, quad.t1);
                 COAL_PREFIX(Vertex2f)(XMax, YMin);
                
            }  COAL_PREFIX(PopDrawing)(GL_TRIANGLE_FAN); 
             COAL_PREFIX(PopTexture)();
        }
        if (ActiveCharacter == '\n'){
            
            OffsetX = 0;
            OffsetY += Text->GlyphSize;
            
        }
        
        if (ActiveCharacter == '\t'){
            OffsetX += Text->GlyphSize*2;
            
        }
    };
    
    
}