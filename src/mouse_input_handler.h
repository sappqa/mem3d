#pragma once
#include "GLFW/glfw3.h"

void handle_mouse_button_input(GLFWwindow* window, int button, int action, int mods);
void handle_mouse_scroll_input(GLFWwindow* window, double xoffset, double yoffset);