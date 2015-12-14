#ifndef H_WINDOW_INPUT_H
#define H_WINDOW_INPUT_H

#include <GLFW/glfw3.h>

#define KEY(key) GLFW_KEY_##key
#define MOUSE_BUTTON(button) GLFW_MOUSE_BUTTON_##button

#define INPUT_PRESS GLFW_PRESS
#define INPUT_RELEASE GLFW_RELEASE
#define INPUT_REPEAT GLFW_REPEAT

#define input_gettime() glfwGetTime()
#define input_getkey(window, key) glfwGetKey(window, key)

#define input_update() glfwPollEvents()
#define input_callback(window, InputMethod, callback) glfwSet##InputMethod##Callback(window, callback)

#endif
