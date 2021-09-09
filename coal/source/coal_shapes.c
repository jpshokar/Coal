#include "../include/coal_shapes.h"
#include "../include/helpers/coalgl_helper.h"


COALTYPE_PREFIX(Rectangle) 
COAL_PREFIX(CreateRectangle)(F32 x, F32 y, F32 w, F32 h)
{
    COALTYPE_PREFIX(Rectangle) rectangle =
    {
        .x = x,
        .y = y,
        .w = w,
        .h = h,
        .Color = (Color){255,255,255,255},
        .Orgin = (V2){x+w/2, y+h/2},
        .TextureCoordinates = {
            (V2){0,0}, 
            (V2){1,0},
            (V2){0,1},
            (V2){1,1}
        }
        
    };
    
    return rectangle;
}
void 
COAL_PREFIX(SetRectangleTexture)(COALTYPE_PREFIX(Rectangle)* rectangle, COALTYPE_PREFIX(Texture) texture)
{
    rectangle->Texture = texture;
}
void 
COAL_PREFIX(DrawRectangle)(COALTYPE_PREFIX(Rectangle)* rectangle,  COALTYPE_PREFIX(Renderer) renderer)
{
     COAL_PREFIX(PushDrawing)(&renderer); {
        if (rectangle->Texture.LoadedTexture == 1 )
             COAL_PREFIX(PushTexture)(rectangle->Texture);
        
         COAL_PREFIX(Color4f)(rectangle->Color.r,rectangle->Color.g,rectangle->Color.b,rectangle->Color.a);
         COAL_PREFIX(TexCoord2d)(rectangle->TextureCoordinates.BottomLeft.x, rectangle->TextureCoordinates.BottomLeft.y);  COAL_PREFIX(Vertex2f)(rectangle->x , rectangle->y+rectangle->h);
         COAL_PREFIX(TexCoord2d)(rectangle->TextureCoordinates.TopLeft.x,rectangle->TextureCoordinates.TopLeft.y);  COAL_PREFIX(Vertex2f)(rectangle->x,  rectangle->y);
         COAL_PREFIX(TexCoord2d)(rectangle->TextureCoordinates.TopRight.x,rectangle->TextureCoordinates.TopRight.y);  COAL_PREFIX(Vertex2f)(rectangle->x+rectangle->w, rectangle->y);
         COAL_PREFIX(TexCoord2d)(rectangle->TextureCoordinates.BottomRight.x,rectangle->TextureCoordinates.BottomRight.y);  COAL_PREFIX(Vertex2f)(rectangle->x+rectangle->w , rectangle->y+rectangle
                                                                                                                                    ->h);
    }  COAL_PREFIX(PopDrawing)(GL_TRIANGLE_FAN); 
    if (rectangle->Texture.LoadedTexture == 1)
         COAL_PREFIX(PopTexture)();
}


void 
COAL_PREFIX(DrawRectangleRotated)(COALTYPE_PREFIX(Rectangle)* rectangle, F32 Degree,COALTYPE_PREFIX(Renderer) renderer)
{
     COAL_PREFIX(PushDrawing)(&renderer); {
        if (rectangle->Texture.LoadedTexture == 1)
             COAL_PREFIX(PushTexture)(rectangle->Texture);
        
        
        V2 Position01 = (V2){rectangle->x , rectangle->y+rectangle->h};
        V2 Position02 = (V2){rectangle->x,  rectangle->y};
        V2 Position03 = (V2){rectangle->x+rectangle->w, rectangle->y};
        V2 Position04 = (V2){rectangle->x+rectangle->w , rectangle->y+rectangle->h};
        Degree = COAL_DEG2RAD(Degree);
        
        {
            Position01.x -= rectangle->Orgin.x;
            Position01.y -= rectangle->Orgin.y;
            F32 AngleX = Position01.x * COAL_COS(Degree) - Position01.y * COAL_SIN(Degree);
            F32 AngleY = Position01.x * COAL_SIN(Degree) + Position01.y* COAL_COS(Degree);
            Position01.x = AngleX + rectangle->Orgin.x;
            Position01.y = AngleY + rectangle->Orgin.y;
        }
        
        {
            Position02.x -= rectangle->Orgin.x;
            Position02.y -= rectangle->Orgin.y;
            F32 AngleX = Position02.x * COAL_COS(Degree) - Position02.y * COAL_SIN(Degree);
            F32 AngleY = Position02.x * COAL_SIN(Degree) + Position02.y * COAL_COS(Degree);
            Position02.x = AngleX + rectangle->Orgin.x;
            Position02.y = AngleY + rectangle->Orgin.y;
        }
        {
            Position03.x -= rectangle->Orgin.x;
            Position03.y -= rectangle->Orgin.y;
            F32 AngleX = Position03.x * COAL_COS(Degree) - Position03.y * COAL_SIN(Degree);
            F32 AngleY = Position03.x * COAL_SIN(Degree) + Position03.y * COAL_COS(Degree);
            Position03.x = AngleX + rectangle->Orgin.x;
            Position03.y = AngleY + rectangle->Orgin.y;
        }
        {
            Position04.x -= rectangle->Orgin.x;
            Position04.y -= rectangle->Orgin.y;
            F32 AngleX = Position04.x * COAL_COS(Degree) - Position04.y * COAL_SIN(Degree);
            F32 AngleY = Position04.x * COAL_SIN(Degree) + Position04.y * COAL_COS(Degree);
            Position04.x = AngleX + rectangle->Orgin.x;
            Position04.y = AngleY + rectangle->Orgin.y;
        }
         COAL_PREFIX(Color4f)(rectangle->Color.r,rectangle->Color.g,rectangle->Color.b,rectangle->Color.a);
         COAL_PREFIX(TexCoord2d)(rectangle->TextureCoordinates.BottomLeft.x, rectangle->TextureCoordinates.BottomLeft.y); 
         COAL_PREFIX(Vertex2f)(Position01.x, Position01.y);
         COAL_PREFIX(TexCoord2d)(rectangle->TextureCoordinates.TopLeft.x,rectangle->TextureCoordinates.TopLeft.y);  COAL_PREFIX(Vertex2f)(Position02.x, Position02.y);
         COAL_PREFIX(TexCoord2d)(rectangle->TextureCoordinates.TopRight.x,rectangle->TextureCoordinates.TopRight.y);  COAL_PREFIX(Vertex2f)(Position03.x, Position03.y);
         COAL_PREFIX(TexCoord2d)(rectangle->TextureCoordinates.BottomRight.x,rectangle->TextureCoordinates.BottomRight.y); 
         COAL_PREFIX(Vertex2f)(Position04.x, Position04.y);
    }  COAL_PREFIX(PopDrawing)(GL_TRIANGLE_FAN); 
    if (rectangle->Texture.LoadedTexture == 1)
         COAL_PREFIX(PopTexture)();
}

void
COAL_PREFIX(DrawLine)(F32 x0, F32 y0, F32 x1, F32 y1, Color Color, COALTYPE_PREFIX(Renderer) Renderer)
{
     COAL_PREFIX(PushDrawing)(&Renderer); {
         COAL_PREFIX(Color4f)(Color.r,Color.g,Color.b,Color.a);
         COAL_PREFIX(Vertex2f)(x0, y0);
         COAL_PREFIX(Vertex2f)(x1, y1);
        
    }  COAL_PREFIX(PopDrawing)(GL_LINES); 
    
    
}
