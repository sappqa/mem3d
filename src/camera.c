#include "camera.h"
#include "common.h"

static vec3 _position = {0};
static vec3 _position_offset = {0};
static vec3 _target = {0};
static vec3 _up = {0};
static mat4x4 _projection;
static float _zoom = 0.0f;


void camera_init() {
    vec3 position = {10.1, -7.0, 30};
    vec3 target = {10, 10, 0};
    vec3 up = {0, 0, 1};

    memcpy(_position, position, sizeof(vec3));
    memcpy(_target, target, sizeof(vec3));
    memcpy(_up, up, sizeof(vec3));
}

void camera_get_position(vec3 position) {
    position = _position;
}

void camera_set_position(vec3 position) {
    memcpy(_position, position, sizeof(vec3));
}

void camera_get_target(vec3 target) {
    target = _target;
}

void camera_set_target(vec3 target) {
    memcpy(_target, target, sizeof(vec3));
}

void camera_get_projection(mat4x4 proj) {
    vec3 position;
    vec3_add(position, _position, _position_offset);

    mat4x4 view, perspective;
    mat4x4_look_at(view, position, _target, _up);
    mat4x4_perspective(perspective, RADIANS(45.0f), RENDER_WINDOW_ASPECT, 0.01f, 100.0f);
    mat4x4_mul(proj, perspective, view);
}

float camera_get_zoom() {
    return _zoom;
}

void camera_set_zoom(float zoom) {
    _zoom = zoom;
    vec3_sub(_position_offset, _target, _position);
    vec3_scale(_position_offset, _position_offset, zoom);
}