#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "gl.h"

static void error_callback(int error, const char *description)
{
  fputs(description, stderr);
}

int gl_init()
{
  if(!glfwInit())
    return 0;
  glfwSetErrorCallback(error_callback);

  return 1;
}
