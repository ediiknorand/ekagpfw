#ifndef H_GL_FBO_H
#define H_GL_FBO_H

#include <GL/glew.h>
#include "../window/window.h"

typedef struct {
  GLuint fbo;
  GLuint tex;
  GLuint rbo;
} FBO;

int fbo_create_w(FBO *fbo, Window *w);
void fbo_destroy(FBO *fbo);
void fbo_draw(FBO *fbo, GLuint vbo, GLint attr_coord, GLint unif_tex);

#define FBO_BINDTEXTURE(fbo) glBindTexture(GL_TEXTURE_2D, fbo->tex)
#define FBO_BINDRENDERBUFFER(fbo) glBindRenderbuffer(GL_RENDERBUFFER, fbo->rbo)
#define FBO_BINDFRAMEBUFFER(fbo) glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo)

#endif
