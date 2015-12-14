#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"
#include "../util/file.h"

static void print_log(GLuint object)
{
  GLint log_length = 0;
  if(glIsShader(object))
    glGetShaderiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else if(glIsProgram(object))
    glGetProgramiv(object, GL_INFO_LOG_LENGTH, &log_length);
  else {
    fprintf(stderr, "printlog: Not a shader or program.\n");
    return;
  }

  char *log = malloc(log_length);
  if(glIsShader(object))
    glGetShaderInfoLog(object, log_length, NULL, log);
  else if(glIsProgram(object))
    glGetProgramInfoLog(object, log_length, NULL, log);

  fprintf(stderr, "%s\n", log);
  free(log);
}

GLuint shader_create(const char *filename, GLenum type)
{
  const GLchar *source = file_read(filename);
  if(source == NULL) {
    fprintf(stderr, "Error: opening %s: ", filename);
    perror("");
    return 0;
  }
  GLuint res = glCreateShader(type);
  const GLchar *sources[] = {
  /* GLSL Version */
#ifdef GL_ES_VERSION_2_0
    "#version 100\n"
    "#define GLES2\n"
#else
    "#version 120\n"
#endif
    ,
  /* GLES2 precision specifiers */
#ifdef GL_ES__VERSION_2_0
    (type == GL_FRAGMENT_SHADER)?
    "#ifdef GL_FRAGMENT_PRECISION_HIGH\n"
    "precision highp float;\n"
    "#else\n"
    "precision mediump float;\n"
    "#endif\n"
    : ""
#else
    "#define lowp\n"
    "#define mediump\n"
    "#define highp\n"
#endif
    ,
    source };
  glShaderSource(res, 3, sources, NULL);
  free((void*)source);

  glCompileShader(res);
  GLint compile_ok = GL_FALSE;
  glGetShaderiv(res, GL_COMPILE_STATUS, &compile_ok);
  if(compile_ok == GL_FALSE) {
    fprintf(stderr, "%s:", filename);
    print_log(res);
    glDeleteShader(res);
    return 0;
  }
  return res;
}
