#include "fbo.h"

int fbo_create_w(FBO *fbo, Window *w)
{
  int width, height;
  window_get_fbsize(w, &width, &height);

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &fbo->tex);
  glBindTexture(GL_TEXTURE_2D, fbo->tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenRenderbuffers(1, &fbo->rbo);
  glBindRenderbuffer(GL_RENDERBUFFER, fbo->rbo);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, (GLsizei)width, (GLsizei)height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glGenFramebuffers(1, &fbo->fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, fbo->fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo->tex, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo->rbo);

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status != GL_FRAMEBUFFER_COMPLETE) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //fprintf(stderr, "glCheckFramebufferStatus: error %p", &status);
    glDeleteRenderbuffers(1, &fbo->rbo);
    glDeleteTextures(1, &fbo->tex);
    glDeleteFramebuffers(1, &fbo->fbo);
    return 0;
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  return 1;
}

void fbo_destroy(FBO *fbo)
{
  glDeleteRenderbuffers(1, &fbo->rbo);
  glDeleteTextures(1, &fbo->tex);
  glDeleteFramebuffers(1, &fbo->fbo);
}

void fbo_draw(FBO *fbo, GLuint vbo, GLint attr_coord, GLint unif_tex)
{
  glBindTexture(GL_TEXTURE_2D, fbo->tex);
  glUniform1i(unif_tex, 0);
  glEnableVertexAttribArray(attr_coord);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(
    attr_coord,
    2,
    GL_FLOAT,
    GL_FALSE,
    0,
    0);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableVertexAttribArray(attr_coord);
}
