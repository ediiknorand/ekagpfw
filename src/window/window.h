#ifndef H_WINDOW_WINDOW_H
#define H_WINDOW_WINDOW_H

#include <GLFW/glfw3.h>

#define Window GLFWwindow
#define window_closed(w) glfwWindowShouldClose(w)
#define window_close(w) glfwSetWindowShouldClose(w, GL_TRUE)
#define window_context(w) glfwMakeContextCurrent(w)
#define window_destroy(w) glfwDestroyWindow(w)
#define window_update(w) glfwSwapBuffers(w)
#define window_get_size(w, wi, he) glfwGetWindowSize(w, wi, he)
#define window_get_fbsize(w, wi, he) glfwGetFramebufferSize(w, wi, he)
#define window_set_fbsize_callback(w, callback) glfwSetFramebufferSizeCallback(w, callback)

Window *window_create(const char *title, int width, int height);

#endif
