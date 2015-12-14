#ifndef H_GAME_TEST_DISPLAY_H
#define H_GAME_TEST_DISPLAY_H

#include <GL/glew.h>
#include "../../loop/state.h"
#include "../../gl/fbo.h"

typedef struct {
  GLuint program;
  GLint attr_coord;
  GLint unif_tex;
  GLint unif_offset;
  /* not exactly from glsl program */
  double time;
  GLuint vbo;
} PostProcProgram;

typedef struct {
  GLuint glslProgram;
  GLuint vbo;
  GLint attr;

  FBO fbo;
  PostProcProgram ppp;
} TestDisplay;

void *display_init(Window *window, void *ddata);
void *display_end(Window *window, void *ddata);
int display_update(Window *window, void *ddata, void *data, double delta, Display_t *display);

#endif
