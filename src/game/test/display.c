#include <stdlib.h>
#include "display.h"
#include "scene.h"
#include "../../gl/shader.h"
#include "../../gl/program.h"
#include "../../gl/vbo.h"
#include "../../loop/state.h"

void *display_init(Window *window, void *ddata)
{
  TestDisplay *td = malloc(sizeof(TestDisplay));
  td->glslProgram = program_create("v.glsl","f.glsl");
  if(!td->glslProgram)
    exit(1);

  
  GLfloat triangle[] = {
     0.0,  0.8,
    -0.8, -0.8,
     0.8, -0.8,
  };
  glGenBuffers(1, &(td->vbo));
  glBindBuffer(GL_ARRAY_BUFFER, td->vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
  
  //vbo_quadf(&td->vbo, 0.8f);

  td->attr = program_attribute(td->glslProgram, "coord");

  glEnable(GL_DEPTH_TEST);
  if(!fbo_create_w(&td->fbo, window))
    exit(1);
  td->ppp.program = program_create("postproc.v.glsl", "postproc.f.glsl");
  td->ppp.attr_coord = program_attribute(td->ppp.program, "coord");
  td->ppp.unif_tex = program_uniform(td->ppp.program, "texture");
  td->ppp.unif_offset = program_uniform(td->ppp.program, "offset");
  td->ppp.time = 0.0;
  vbo_quadf(&td->ppp.vbo, 1.0f);

  return td;
}

void *display_end(Window *window, void *ddata)
{
  TestDisplay *td = (TestDisplay*) ddata;
  glDeleteProgram(td->glslProgram);
  glDeleteBuffers(1, &(td->vbo));

  fbo_destroy(&td->fbo);
  glDeleteProgram(td->ppp.program);
  glDeleteBuffers(1, &(td->ppp.vbo));

  free(ddata);
  return NULL;
}

int display_update(Window *window, void *ddata, void *data, double delta, Display_t *display)
{
  TestDisplay *td = (TestDisplay*) ddata;
  TestScene *t = (TestScene*)data;

  if(t->quit)
    return STATE_END;

  glBindFramebuffer(GL_FRAMEBUFFER, td->fbo.fbo);

  glClearColor(1.0, 1.0, 1.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(td->glslProgram);
  glBindBuffer(GL_ARRAY_BUFFER, td->vbo);
  glEnableVertexAttribArray(td->attr);
  glVertexAttribPointer(
    td->attr,
    2,
    GL_FLOAT,
    GL_FALSE,
    0,
    0);

  glDrawArrays(GL_TRIANGLES, 0, 3);
  //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableVertexAttribArray(td->attr);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

  glUseProgram(td->ppp.program);
  td->ppp.time += delta;
  GLfloat move = td->ppp.time*2*3.14159265*0.75;
  glUniform1f(td->ppp.unif_offset, move);
  fbo_draw(&td->fbo, td->ppp.vbo, td->ppp.attr_coord, td->ppp.unif_tex);

  return STATE_NOP;
}
