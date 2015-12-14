#include "postproc.h"
#include "program.h"
#include "vbo.h"

static PostProcessor *global_pp; /*The gods won't be pleased */

static void postproc_resize(Window *window, int width, int height)
{
  PostProcessor *pp = global_pp;
  glBindTexture(GL_TEXTURE_2D, pp->tex);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindRenderbuffer(GL_RENDERBUFFER, pp->rbo_depth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glViewport(0, 0, width, height);
}

int postproc_init(PostProcessor *pp, Window *window, const char *vshader, const char *fshader)
{
  int width, height;
  window_get_fbsize(window, &width, &height);

  glActiveTexture(GL_TEXTURE0);
  glGenTextures(1, &pp->tex);
  glBindTexture(GL_TEXTURE_2D, pp->tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  glBindTexture(GL_TEXTURE_2D, 0);

  glGenRenderbuffers(1, &pp->rbo_depth);
  glBindRenderbuffer(GL_RENDERBUFFER, pp->rbo_depth);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, (GLsizei)width, (GLsizei)height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glGenFramebuffers(1, &pp->fbo);
  glBindFramebuffer(GL_FRAMEBUFFER, pp->fbo);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pp->tex, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, pp->rbo_depth);

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status != GL_FRAMEBUFFER_COMPLETE) {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //fprintf(stderr, "glCheckFramebufferStatus: error %p", &status);
    glDeleteRenderbuffers(1, &pp->rbo_depth);
    glDeleteTextures(1, &pp->tex);
    glDeleteFramebuffers(1, &pp->fbo);
    return 0;
  }
  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  vbo_quadf(&pp->vbo, 1.0f); /* make it global? */
  pp->program = program_create(vshader, fshader);
  if(!pp->program) {
    glDeleteRenderbuffers(1, &pp->rbo_depth);
    glDeleteTextures(1, &pp->tex);
    glDeleteFramebuffers(1, &pp->fbo);
    glDeleteBuffers(1, &pp->vbo);
    return 0;
  }
  pp->attr_coord = program_attribute(pp->program, "coord");
  pp->unif_tex = program_uniform(pp->program, "texture");

  global_pp = pp;
  window_set_fbsize_callback(window, postproc_resize);
  return 1;
}

void postproc_finish(PostProcessor *pp)
{
  glDeleteRenderbuffers(1, &pp->rbo_depth);
  glDeleteTextures(1, &pp->tex);
  glDeleteFramebuffers(1, &pp->fbo);
  glDeleteBuffers(1, &pp->vbo);
  glDeleteProgram(pp->program);
}

void postproc_begin(PostProcessor *pp)
{
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glUseProgram(pp->program);
}

void postproc_end(PostProcessor *pp)
{
  glBindTexture(GL_TEXTURE_2D, pp->tex);
  glUniform1i(pp->unif_tex, 0);
  glEnableVertexAttribArray(pp->attr_coord);
  glBindBuffer(GL_ARRAY_BUFFER, pp->vbo);
  glVertexAttribPointer(
    pp->attr_coord,
    2,
    GL_FLOAT,
    GL_FALSE,
    0,
    0);

  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableVertexAttribArray(pp->attr_coord);
}
