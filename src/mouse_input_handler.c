#include "mouse_input_handler.h"
#include "camera.h"
#include <stdio.h>

static void _left_press() {

}

static void _left_release() {

}

static void _right_press() {

}

static void _right_release() {

}

static void _middle_press() {

}

static void _middle_release() {

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

}

void handle_mouse_scroll_input(GLFWwindow* window, double xoffset, double yoffset) {
    camera_set_zoom(camera_get_zoom() + yoffset * .025);
}