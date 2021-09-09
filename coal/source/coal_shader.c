#include "../include/coal_gl_shader.h"




COALTYPE_PREFIX(Shader)
COAL_PREFIX(CreateShader)(String8 VertexShader, String8 FragmentShader)
{
    COALTYPE_PREFIX(Shader) shd = {
        .VertexShader = VertexShader,
        .FragmentShader = FragmentShader
    };
    
    glGenVertexArrays(1, &shd.VAO);
    
    I8 ShaderLog[512] = {0};
    I32      Success = 0;
    
    shd.VertexShaderProgram = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shd.VertexShaderProgram, 1, &shd.VertexShader, 0);
    glCompileShader(shd.VertexShaderProgram);
    
    glGetShaderiv(shd.VertexShaderProgram, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        /* TODO[@jss]: Logging. */
        glGetShaderInfoLog(shd.VertexShaderProgram, 512, 0, ShaderLog);
        COAL_PRINTF("coalgl_vertex_shader: %s\n",  ShaderLog);
        
    }
    
    
    shd.
        FragmentShaderProgram = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shd.FragmentShaderProgram, 1, &shd.FragmentShader, 0);
    glCompileShader(shd.FragmentShaderProgram);
    
    glGetShaderiv(shd.FragmentShaderProgram, GL_COMPILE_STATUS, &Success);
    if (!Success)
    {
        /* TODO[@jss]: Logging. */
        glGetShaderInfoLog(shd.FragmentShaderProgram, 512, 0, ShaderLog);
        COAL_PRINTF("coalgl_fragment_shader: %s\n",  ShaderLog);
        
    }
    
    
    shd.Program = glCreateProgram();
    glAttachShader(shd.Program, shd.VertexShaderProgram);
    glAttachShader(shd.Program, shd.FragmentShaderProgram);
    glLinkProgram(shd.Program);
    
    glGetProgramiv(shd.Program, GL_LINK_STATUS, &Success);
    if (!Success)
    {
        /* TODO[@jss]: Logging. */
        glGetShaderInfoLog(shd.Program, 512, 0, ShaderLog);
        COAL_PRINTF("coalgl_program_shader: %s\n",  ShaderLog);
        
    }
    
    
    return shd;
    
}

void
COAL_PREFIX(PushShader)(COALTYPE_PREFIX(Shader) Shd)
{
    glUseProgram(Shd.Program);
}
void
COAL_PREFIX(PopShader)(void)
{
    glUseProgram(0);
}

void
COAL_PREFIX(CreateVertexFormat)(COALTYPE_PREFIX(Shader)* shader, I32 VertexFormat)
{
    
    I32 offset = 0;
    I32 vertex_loc = 0;
    glBindVertexArray(shader->VAO);
    
    
    
    if (VertexFormat & COALENUM_PREFIX(VERTEX_POSITION))
    {
        glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, sizeof(F32)*10, (void*)(sizeof(F32) * offset));
        glEnableVertexAttribArray(vertex_loc);
        offset += 3;
        vertex_loc += 1;
    }
    if (VertexFormat & COALENUM_PREFIX(VERTEX_COLOR))
    {
        
        glVertexAttribPointer(vertex_loc, 4, GL_FLOAT, GL_FALSE, sizeof(F32)*10, (void*)(sizeof(F32) * offset));
        glEnableVertexAttribArray(vertex_loc);
        offset += 4;
        vertex_loc += 1;
    }
    if (VertexFormat & COALENUM_PREFIX(VERTEX_TEXTURE))
    {
        
        glVertexAttribPointer(vertex_loc, 2, GL_FLOAT, GL_FALSE, sizeof(F32)*10, (void*)(sizeof(F32) * offset));
        glEnableVertexAttribArray(vertex_loc);
        offset += 2;
        vertex_loc += 1;
    }
    if (VertexFormat & COALENUM_PREFIX(VERTEX_TEXTURE_ENABLED))
    {
        
        glVertexAttribPointer(vertex_loc, 1, GL_FLOAT, GL_FALSE, sizeof(F32)*10, (void*)(sizeof(F32) * offset));
        glEnableVertexAttribArray(vertex_loc);
        offset += 1;
        vertex_loc += 1;
    }
    glBindVertexArray(0);
    shader->VAO_Offset = offset;
}


void 
COAL_PREFIX(Uniform1f)(COALTYPE_PREFIX(Shader) Shd, String8 Location, F32 v0)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform1f(location, v0);
    
}
void
COAL_PREFIX(Uniform2f)(COALTYPE_PREFIX(Shader) Shd, String8 Location, F32 v0, F32  v1)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform2f(location, v0, v1);
    
}
void
COAL_PREFIX(Uniform3f)(COALTYPE_PREFIX(Shader) Shd, String8 Location, F32 v0, F32  v1, F32  v2)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform3f(location, v0, v1, v2);
}
void
COAL_PREFIX(Uniform4f)(COALTYPE_PREFIX(Shader) Shd, String8 Location, F32 v0, F32 v1, F32 v2, F32 v3)

{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform4f(location, v0, v1, v2, v3);
}
void
COAL_PREFIX(Uniform1i)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32 v0)
{
    
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform1i(location, v0);
    
}
void 
COAL_PREFIX(Uniform2i)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32 v0, I32 v1)
{
    
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform2i(location, v0, v1);
    
}
void
COAL_PREFIX(Uniform3i)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32 v0, I32 v1, I32 v2)
{
    
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform3i(location, v0,v1,v2);
    
}
void
COAL_PREFIX(Uniform4i)(COALTYPE_PREFIX(Shader) Shd, String8 Location,I32  v0,I32  v1,I32  v2,I32  v3)
{
    
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform4i(location, v0,v1,v2,v3);
    
}
void
COAL_PREFIX(Uniform1ui)(COALTYPE_PREFIX(Shader) Shd, String8 Location, U32 v0)
{
    
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform1ui(location, v0);
    
}
void
COAL_PREFIX(Uniform2ui)(COALTYPE_PREFIX(Shader) Shd, String8 Location,U32 v0,U32 v1)
{
    
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform2ui(location, v0,v1);
    
}
void
COAL_PREFIX(Uniform3ui)(COALTYPE_PREFIX(Shader) Shd, String8 Location,U32 v0,U32 v1,U32 v2)
{
    
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform3ui(location, v0,v1,v2);
    
}
void
COAL_PREFIX(Uniform4ui)(COALTYPE_PREFIX(Shader) Shd, String8 Location,U32 v0,U32 v1,U32 v2,U32 v3)
{
    
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform4ui(location, v0,v1,v2,v3);
    
}


void 
COAL_PREFIX(Uniform1fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform1fv(location, count, value);
}
void
COAL_PREFIX(Uniform2fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform2fv(location, count, value);
}
void 
COAL_PREFIX(Uniform3fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform3fv(location, count, value);
}
void
COAL_PREFIX(Uniform4fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform4fv(location, count, value);
}
void
COAL_PREFIX(Uniform1iv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const I32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform1iv(location, count, value);
}
void
COAL_PREFIX(Uniform2iv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const I32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform2iv(location, count, value);
}
void
COAL_PREFIX(Uniform3iv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const I32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform3iv(location, count, value);
}
void
COAL_PREFIX(Uniform4iv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const I32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform4iv(location, count, value);
}
void
COAL_PREFIX(Uniform1uiv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const U32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform1uiv(location, count, value);
}
void
COAL_PREFIX(Uniform2uiv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const U32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform2uiv(location, count, value);
}
void
COAL_PREFIX(Uniform3uiv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const U32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform3uiv(location, count, value);
}
void
COAL_PREFIX(Uniform4uiv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, const U32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniform4uiv(location, count, value);
}


void
COAL_PREFIX(UniformMatrix2fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose,const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix2fv(location, count, transpose, value);
}
void 
COAL_PREFIX(UniformMatrix3fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix3fv(location, count, transpose, value);
}
void 
COAL_PREFIX(UniformMatrix4fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix4fv(location, count, transpose, value);
}
void 
COAL_PREFIX(UniformMatrix2x3fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix2x3fv(location, count, transpose, value);
}
void 
COAL_PREFIX(UniformMatrix3x2fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32* value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix3x2fv(location, count, transpose, value);
}
void 
COAL_PREFIX(UniformMatrix2x4fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32* value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix2x4fv(location, count, transpose, value);
}
void 
COAL_PREFIX(UniformMatrix4x2fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix4x2fv(location, count, transpose, value);
}
void 
COAL_PREFIX(UniformMatrix3x4fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix3x4fv(location, count, transpose, value);
}
void 
COAL_PREFIX(UniformMatrix4x3fv)(COALTYPE_PREFIX(Shader) Shd, String8 Location, I32  count, B32  transpose, const F32 * value)
{
    COAL_PREFIX(PushShader)(Shd);
    U32 location = glGetUniformLocation(Shd.Program, Location);
    glUniformMatrix4x3fv(location, count, transpose, value);
}