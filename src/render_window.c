#include "render_window.h"
#include "KHR/khrplatform.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "render_graphics.h"
#include "mouse_input_handler.h"
#include "animation_timer.h"
#include <stdio.h>


static void _key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

static void _mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    handle_mouse_button_input(window, button, action, mods);
}

static void _mouse_move_callback(GLFWwindow* window, double xpos, double ypos) {
    handle_mouse_move_input(window, xpos, ypos);
}

static void _mouse_scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    handle_mouse_scroll_input(window, xoffset, yoffset);
}

static GLFWwindow* _glfw_window_init() {
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
    glfwSetCursorPosCallback(window, _mouse_move_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        perror("error: failed to initialize GLAD\n");
        return NULL;
    }

    return window;
}

int render_window(memory_event* memory_events, size_t num_memory_events, memory_event_bounds* bounds) {
    GLFWwindow* window = _glfw_window_init();

    animation_timer_set_startup_delay(1);
    animation_timer_set_animation_duration_ms(8 * 1000);
    
    graphics_init(memory_events, num_memory_events, bounds);

    animation_timer_start();

    while(!glfwWindowShouldClose(window)) {
        render_graphics();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    animation_timer_stop();
    render_graphics_dispose();

    glfwTerminate();
    return 0;
}