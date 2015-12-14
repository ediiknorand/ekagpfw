#include <GL/glew.h>
#include "vbo.h"

GLuint vbo_quadf(GLuint *vbo_p, GLfloat f)
{
  GLfloat quad[] = {
    -f, -f,
     f, -f,
    -f,  f,
     f,  f,
  };
  glGenBuffers(1, vbo_p);
  glBindBuffer(GL_ARRAY_BUFFER, *vbo_p);
  glBufferData(GL_ARRAY_BUFFER, sizeof(quad), quad, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  return *vbo_p;
}
