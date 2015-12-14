#include <GL/glew.h>
#include <stdio.h>
#include "program.h"
#include "shader.h"

GLint program_attribute(GLuint program_id, const char* name)
{
  GLint attrib = glGetAttribLocation(program_id, name);
  if(attrib == -1) {
    fprintf(stderr, "Could not bind attribute %s\n", name);
    return -1;
  }
  return attrib;
}

GLint program_uniform(GLuint program_id, const char* name)
{
  GLint uniform = glGetUniformLocation(program_id, name);
  if(uniform == -1) {
    fprintf(stderr, "Could not bind uniform %s\n", name);
    return -1;
  }
  return uniform;
}

GLuint program_create(const char *vshader, const char *fshader)
{
  GLint vs = shader_create(vshader, GL_VERTEX_SHADER);
  if(!vs)
    return (GLuint)0;
  GLint fs = shader_create(fshader, GL_FRAGMENT_SHADER);
  if(!fs)
    return (GLuint)0;
  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glDeleteShader(vs);
  glDeleteShader(fs);
  GLint ok;
  glGetProgramiv(program, GL_LINK_STATUS, &ok);
  if(!ok) {
    glDeleteProgram(program);
    return (GLuint)0;
  }
  return program;
}
