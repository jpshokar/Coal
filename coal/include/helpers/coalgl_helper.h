/*~~~~~~~~~~~~~~~~~~~~~~~~~~
Coal
- OpenGL helper.
Author: @jss
~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#ifndef COALGL_HELPER_H
#define COALGL_HELPER_H
typedef enum COALTYPE_PREFIX(DrawingMode) COALTYPE_PREFIX(DrawingMode);
enum COALTYPE_PREFIX(DrawingMode)
{
    COALENUM_PREFIX(TRIANGLES)     = GL_TRIANGLES,
    COALENUM_PREFIX(TRIANGLES_FAN) = GL_TRIANGLE_FAN
};
void
COAL_PREFIX(PushDrawing)(COALTYPE_PREFIX(Renderer)* coal_renderer);

void
COAL_PREFIX(PushTexture)(COALTYPE_PREFIX(Texture) texture);

void 
COAL_PREFIX(Vertex3f)(F32 x, F32 y, F32 z);
void 
COAL_PREFIX(Vertex2f)(F32 x, F32 y);
void 
COAL_PREFIX(Color4f)(F32 r, F32 g, F32 b, F32 a);

void 
COAL_PREFIX(TexCoord2d)(F32 x, F32 y);

void
COAL_PREFIX(PopTexture)();

void
COAL_PREFIX(PopDrawing)(COALTYPE_PREFIX(DrawingMode) mode);

#ifdef COAL_GL_IMPL


static COALTYPE_PREFIX(Renderer)* renderer;

void
COAL_PREFIX(PushDrawing)(COALTYPE_PREFIX(Renderer)* coal_renderer)
{
    renderer = coal_renderer;
    glBindVertexArray(renderer->Shader.VAO);
    
}


void
COAL_PREFIX(PushTexture)(COALTYPE_PREFIX(Texture) texture)
{
    if (!renderer->IsTextureDisabled){
        glBindTexture(GL_TEXTURE_2D, texture.Id);
        
        glActiveTexture(GL_TEXTURE0); 
        renderer->TextureEnabled = 1;
    }
}
void
COAL_PREFIX(PopTexture)()
{
    if (!renderer->IsTextureDisabled){
        glBindTexture(GL_TEXTURE_2D, 0);
        renderer->TextureEnabled = 0;
    }
}
void 
COAL_PREFIX(Vertex3f)(F32 x, F32 y, F32 z)
{
    
    F32 tmp_vertex[] = 
    {
        x,y,z,renderer->VertexColor.r,renderer->VertexColor.g,renderer->VertexColor.b,renderer->VertexColor.a, 
        renderer->VertexUV.x,renderer->VertexUV.y, renderer->TextureEnabled
    };
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(F32) * renderer->Shader.VAO_Offset * renderer->VertexOccupied, sizeof(tmp_vertex), &tmp_vertex); 
    renderer->VertexOccupied += 1;
}


void 
COAL_PREFIX(Vertex2f)(F32 x, F32 y)
{
    
    renderer->Is3D == 1 ?  COAL_PREFIX(Vertex3f)(x,y,0.0f) :  COAL_PREFIX(Vertex3f)(x,y,0.f);
    
}

void 
COAL_PREFIX(Color4f)(F32 r, F32 g, F32 b, F32 a)
{
    renderer->VertexColor = (Color){.r=r/255,.g=g/255,.b=b/255,.a=a/255};
}

void
COAL_PREFIX(PopDrawing)(COALTYPE_PREFIX(DrawingMode) mode)
{
    COAL_PREFIX(Color4f)(255,255,255,255);
    
    glDrawArrays(mode, 0 ,renderer->VertexOccupied );
    /* NOTE[@jss]: We zero this out because, if we don't do that. We'll reach a issue where we use new VBO offsets then use the pre-existing one. Something you don't want to delete.*/ 
    
    renderer->VertexOccupied = 0;
    
}



void 
COAL_PREFIX(TexCoord2d)(F32 x, F32 y)
{
    renderer->VertexUV.x = x;
    renderer->VertexUV.y = y;
}


#endif


#endif 

