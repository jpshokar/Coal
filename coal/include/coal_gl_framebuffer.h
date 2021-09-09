

#ifndef COAL_GL_FRAMEBUFFER_H
#define COAL_GL_FRAMEBUFFER_H

#include "coal_types.h"
#include "coal_gl_gfx.h"

typedef struct COALTYPE_PREFIX(Framebuffer) COALTYPE_PREFIX(Framebuffer);
struct COALTYPE_PREFIX(Framebuffer) {
    U32         FBO;
    U32         RBO;
    COALTYPE_PREFIX(Texture) TextureAttachment;
    COALTYPE_PREFIX(Texture) OutputTexture;
};


COALAPI void 
COAL_PREFIX(AttachTextureToFramebuffer)(COALTYPE_PREFIX(Framebuffer) Framebuffer,  COALTYPE_PREFIX(Texture) Texture );
COALAPI COALTYPE_PREFIX(Framebuffer)
COAL_PREFIX(CreateFramebuffer)(F32 W, F32 H);
COALAPI void
COAL_PREFIX(PushFramebuffer)(COALTYPE_PREFIX(Framebuffer) FB);
COALAPI void
COAL_PREFIX(PopFramebuffer)(void); /* Reverts back to default framebuffer. */
#endif
