
#ifndef COAL_SHADER_H
#define COAL_SHADER_H
#include "coal_types.h"


typedef enum COALTYPE_PREFIX(VertexFmt) COALTYPE_PREFIX(VertexFmt);
enum COALTYPE_PREFIX(VertexFmt)
{
    COALENUM_PREFIX(VERTEX_POSITION)          = 1 << 1,
    COALENUM_PREFIX(VERTEX_COLOR)             = 1 << 2,
    COALENUM_PREFIX(VERTEX_TEXTURE)           = 1 << 3,
    COALENUM_PREFIX(VERTEX_TEXTURE_ENABLED)   = 1 << 4
};


typedef struct COALTYPE_PREFIX(Shader) COALTYPE_PREFIX(Shader);
struct COALTYPE_PREFIX(Shader)
{
    String8 VertexShader;
    String8 FragmentShader;
    I32     VertexFormat;
    U32     Program;
    U32     VertexShaderProgram;
    U32     FragmentShaderProgram;
    U32     VAO;
    U32     VAO_Offset;
    
};

COALTYPE_PREFIX(Shader)
COAL_PREFIX(CreateShader)(String8 VertexShader, String8 FragmentShader);
COALAPI void
COAL_PREFIX(CreateVertexFormat)(COALTYPE_PREFIX(Shader)* shader, I32 VertexFormat);
COALAPI void
COAL_PREFIX(PushShader)(COALTYPE_PREFIX(Shader) Shd);
COALAPI void
COAL_PREFIX(PopShader)(COALAPI void);


COALAPI void 
COAL_PREFIX(Uniform1f)(COALTYPE_PREFIX(Shader) Shd, String8 Location, F32 v0);
COALAPI void
COAL_PREFIX(Uniform2f)(COALTYPE_PREFIX(Shader) Shd, String8 Location, F32 v0, F32  v1);
COALAPI void
COAL_PREFIX(Uniform3f)(COALTYPE_PREFIX(Shader) Shd, String8 Location, F32 v0, F32  v1, F32  v2);
COALAPI void
COAL_PREFIX(Uniform4f)(COALTYPE_PREFIX(Shader) Shd, String8 Location, F32 v0, F32 v1, F32 v2, F32 v3);
COALAPI void
COAL_PREFIX(Uniform1i)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32 v0);
COALAPI void 
COAL_PREFIX(Uniform2i)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32 v0, I32 v1);
COALAPI void
COAL_PREFIX(Uniform3i)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32 v0, I32 v1, I32 v2);
COALAPI void
COAL_PREFIX(Uniform4i)(COALTYPE_PREFIX(Shader) Shd, String8 Location,I32  v0,I32  v1,I32  v2,I32  v3);
COALAPI void
COAL_PREFIX(Uniform1ui)(COALTYPE_PREFIX(Shader) Shd, String8 Location, U32 v0);
COALAPI void
COAL_PREFIX(Uniform2ui)(COALTYPE_PREFIX(Shader) Shd, String8 Location,U32 v0,U32 v1);
COALAPI void
COAL_PREFIX(Uniform3ui)(COALTYPE_PREFIX(Shader) Shd, String8 Location,U32 v0,U32 v1,U32 v2);
COALAPI void
COAL_PREFIX(Uniform4ui)(COALTYPE_PREFIX(Shader) Shd, String8 Location,U32 v0,U32 v1,U32 v2,U32 v3);
COALAPI void 
COAL_PREFIX(Uniform1fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const F32 * value);
COALAPI void
COAL_PREFIX(Uniform2fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const F32 * value);
COALAPI void 
COAL_PREFIX(Uniform3fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const F32 * value);
COALAPI void
COAL_PREFIX(Uniform4fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const F32 * value);
COALAPI void
COAL_PREFIX(Uniform1iv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const I32 * value);
COALAPI void
COAL_PREFIX(Uniform2iv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const I32 * value);
COALAPI void
COAL_PREFIX(Uniform3iv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const I32 * value);
COALAPI void
COAL_PREFIX(Uniform4iv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const I32 * value);
COALAPI void
COAL_PREFIX(Uniform1uiv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const U32 * value);
COALAPI void
COAL_PREFIX(Uniform2uiv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const U32 * value);
COALAPI void
COAL_PREFIX(Uniform3uiv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const U32 * value);
COALAPI void
COAL_PREFIX(Uniform4uiv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const U32 * value);
COALAPI void
COAL_PREFIX(UniformMatrix2fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose,const F32 * value);
COALAPI void 
COAL_PREFIX(UniformMatrix3fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value);
COALAPI void 
COAL_PREFIX(UniformMatrix4fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value);
COALAPI void 
COAL_PREFIX(UniformMatrix2x3fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value);
COALAPI void 
COAL_PREFIX(UniformMatrix3x2fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32* value);
COALAPI void 
COAL_PREFIX(UniformMatrix2x4fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32* value);
COALAPI void 
COAL_PREFIX(UniformMatrix4x2fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value);
COALAPI void 
COAL_PREFIX(UniformMatrix3x4fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value);
COALAPI void 
COAL_PREFIX(UniformMatrix4x3fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value);

#endif 
