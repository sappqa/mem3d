#include "mouse_input_handler.h"
#include "orbit_camera.h"
#include <stdio.h>

static int _left_down = 0;
static int _right_down = 0;
static int _middle_down = 0;
static double _last_xpos;
static double _last_ypos;

static void _left_press() {
    _left_down = 1;
}

static void _left_release() {
    _left_down = 0;
}

static void _right_press() {
    _right_down = 1;
}

static void _right_release() {
    _right_down = 0;
}

static void _middle_press() {
    _middle_down = 1;
}

static void _middle_release() {
    _middle_down = 0;
}

void handle_mouse_button_input(GLFWwindow* window, int button, int action, int mods) {
    void (*callback)() = NULL;

    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        callback = action ? &_left_press : &_left_release;
    } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        callback = action ? &_right_press : &_right_release;
    } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        callback = action ? &_middle_press : &_middle_release;
    }

    if (callback != NULL) {
        callback();
    }
}

void handle_mouse_move_input(GLFWwindow* window, double xpos, double ypos) {
    double dx = xpos - _last_xpos;
    double dy = ypos - _last_ypos;

    if (_left_down) {
        orbit_camera_rotate(dx, dy);
    }
    
    _last_xpos = xpos;
    _last_ypos = ypos;
}

void handle_mouse_scroll_input(GLFWwindow* window, double xoffset, double yoffset) {
    orbit_camera_set_distance(orbit_camera_get_distance() + yoffset * .025);
}