#include "mouse_input_handler.h"


void _left_press() {

}

void _left_release() {

}

void _right_press() {

}

void _right_release() {

}

void _middle_press() {

}

void _middle_release() {

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

void handle_mouse_scroll_input(GLFWwindow* window, double xoffset, double yoffset) {
    
}