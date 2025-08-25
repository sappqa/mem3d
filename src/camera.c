#include "camera.h"
#include "common.h"
#include <stdio.h>

static vec3 _starting_position = {0};
static vec3 _position = {0};
static vec3 _target = {0};
static vec3 _up = {0};
static quat _rotation;
static mat4x4 _projection;
static float _zoom = 0.0f;

static float _distance = 30.0f;
static float _azimuth = 0.0f;
static float _altitude = 0.0f;

static const vec3 X_AXIS = {1, 0, 0};
static const vec3 Y_AXIS = {0, 1, 0};


void camera_init() {
    vec3 target = {10, 10, 0};
    vec3 up = {0, 1, 0};
    vec3 position = {10, 10, _distance};

    memcpy(_position, position, sizeof(vec3));
    memcpy(_target, target, sizeof(vec3));
    memcpy(_up, up, sizeof(vec3));
}

void camera_get_position(vec3 position) {
    memcpy(position, _position, sizeof(vec3));
}

void camera_set_position(vec3 position) {
    memcpy(_position, position, sizeof(vec3));
}

void camera_get_target(vec3 target) {
    memcpy(target, _target, sizeof(vec3));
}

void camera_set_target(vec3 target) {
    memcpy(_target, target, sizeof(vec3));
}

void camera_get_projection(mat4x4 proj) {
    mat4x4 view, perspective;
    mat4x4_look_at(view, _position, _target, _up);
    mat4x4_perspective(perspective, RADIANS(45.0f), RENDER_WINDOW_ASPECT, 0.01f, 100.0f);
    mat4x4_mul(proj, perspective, view);
}

float camera_get_zoom() {
    return _zoom;
}

void camera_set_zoom(float zoom) {
    _zoom = zoom;
    // vec3_sub(_position_offset, _target, _position);
    // vec3_scale(_position_offset, _position_offset, zoom);
}

void camera_rotate(float dx, float dy) {
    quat pitch, yaw;

    _azimuth -= dx * 0.01f;
    _altitude -= dy * 0.01f;

    if (_azimuth >= (M_PI / 2.0f) - 0.001)
        _azimuth = (M_PI / 2.0f) - 0.001;
    else if (_azimuth <= -(M_PI / 2.0f) + 0.001)
        _azimuth = -(M_PI / 2.0f) + 0.001;

    if (_altitude >= (M_PI / 2.0f) - 0.001)
        _altitude = (M_PI / 2.0f) - 0.001;
    else if (_altitude <= -(M_PI / 2.0f) + 0.001)
        _altitude = -(M_PI / 2.0f) + 0.001;

    quat_rotate(yaw, _azimuth, Y_AXIS);

    vec3 right;
    quat_mul_vec3(right, yaw, X_AXIS);
    quat_rotate(pitch, _altitude, right);

    quat rot;
    quat_mul(rot, pitch, yaw);

    vec3 offset = {0, 0, _distance};
    quat_mul_vec3(offset, rot, offset);

    vec3_add(_position, _target, offset);    
}

