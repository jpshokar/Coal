#include "../include/coal_gl_framebuffer.h"


COALTYPE_PREFIX(Framebuffer)
COAL_PREFIX(CreateFramebuffer)(F32 W, F32 H)
{
    COALTYPE_PREFIX(Framebuffer) fb= {0};
    glGenFramebuffers(1, &fb.FBO);
    glBindFramebuffer(GL_FRAMEBUFFER , fb.FBO);
    
    fb.TextureAttachment = COAL_PREFIX(CreateTexture)(W,H,COALENUM_PREFIX(TEXTURE_PNG));
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,fb.TextureAttachment.Id, 0);
    
    glGenRenderbuffers(1, &fb.RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, fb.RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, W,H);
    /* ATTACHING THE RENDERBUFFER! */
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb.RBO);
    
#if 0
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, W,H,0,GL_DEPTH_STENCIL,GL_UNSIGNED_INT_24_8, 0);
    
    
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, fb.TextureAttachment.Id, 0);
#endif /* This is for the stencil shader. */
    
    
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        COAL_PRINTF("[Coal.gl] Framebuffer did not complete.\n\t+ [Coal.glFramebuffer] Error code Generated: %i\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    return fb;
}

void
COAL_PREFIX(PushFramebuffer)(COALTYPE_PREFIX(Framebuffer) FB)
{
    
    
    glBindFramebuffer(GL_FRAMEBUFFER, FB.FBO);
    
}
void
COAL_PREFIX(PopFramebuffer)(void) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
}/* Reverts back to default framebuffer. */

void 
COAL_PREFIX(AttachTextureToFramebuffer)(COALTYPE_PREFIX(Framebuffer) Framebuffer,  COALTYPE_PREFIX(Texture) Texture )
{
    COAL_PREFIX(PushFramebuffer)(Framebuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, Texture.Id, 0);
    U32 Attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(2, Attachments);
    
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        COAL_PRINTF("[Coal.gl] Framebuffer did not complete.\n\t+ [Coal.glFramebuffer] Error code Generated: %i\n", glCheckFramebufferStatus(GL_FRAMEBUFFER));
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
}

