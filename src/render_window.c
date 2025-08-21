#include "render_window.h"
#include "KHR/khrplatform.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "render_graphics.h"
#include "mouse_input_handler.h"
#include <stdio.h>


void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    handle_mouse_button_input(window, button, action, mods);
}

void _mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    handle_mouse_scroll_input(window, xoffset, yoffset);
}

GLFWwindow* _glfw_window_init() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "", NULL, NULL);
    if (window == NULL) {
        perror("error: failed to create GLFW window\n");
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, _key_callback);
    glfwSetMouseButtonCallback(window, _mouse_button_callback);
    glfwSetScrollCallback(window, _mouse_scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("error: failed to initialize GLAD\n");
        return NULL;
    }

    return window;
}

int render_window() {
    GLFWwindow* window = _glfw_window_init();
    graphics_init();

    while(!glfwWindowShouldClose(window)) {
        render_graphics();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}