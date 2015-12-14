#ifndef H_GL_POSTPROC_H
#define H_GL_POSTPROC_H

#include <GL/glew.h>
#include "../window/window.h"

typedef struct {
  GLuint fbo;
  GLuint tex;
  GLuint rbo_depth;

  GLuint vbo;
  GLuint program;

  GLint attr_coord;
  GLint unif_tex;
  //GLint unif_offset;
} PostProcessor;

int postproc_init(PostProcessor *pp, Window *window, const char *vshader, const char *fshader);
void postproc_finish(PostProcessor *pp);

void postproc_begin(PostProcessor *pp);
void postproc_end(PostProcessor *pp);

#endif
