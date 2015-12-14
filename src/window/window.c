#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "window.h"

static void resize_callback(Window *window, int width, int height)
{
  glViewport(0,0, width, height);
}

Window *window_create(const char *title, int width, int height)
{
  Window *window = glfwCreateWindow(width, height, title, NULL, NULL);
  if(!window)
    return NULL;
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glfwSetFramebufferSizeCallback(window, resize_callback);
  glfwSetWindowSizeCallback(window, resize_callback);

  GLenum glew_status = glewInit();
  if(glew_status != GLEW_OK) {
    fprintf(stderr, "%s\n", glewGetErrorString(glew_status));
    window_destroy(window);
    return NULL;
  }
  if(!GLEW_VERSION_2_0) {
    fprintf(stderr, "Error: your graphic card does not suppoer OpenGL 2.0\n");
    window_destroy(window);
    return NULL;
  }
  glViewport(0,0, width, height);
  return window;
}
