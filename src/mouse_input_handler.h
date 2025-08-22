#pragma once
#include "GLFW/glfw3.h"

static int left_mouse_button_down = 0;
static int right_mouse_button_down = 0;
static int middle_mouse_button_down = 0;

static float zoom;

void handle_mouse_button_input(GLFWwindow* window, int button, int action, int mods);
void handle_mouse_move_input(GLFWwindow* window, double xpos, double ypos);
void handle_mouse_scroll_input(GLFWwindow* window, double xoffset, double yoffset);