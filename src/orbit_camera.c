#include "orbit_camera.h"
#include "common.h"
#include <stdio.h>

static float _azimuth = 0.0f;
static float _altitude = (M_PI / 2.0f) - 0.01f;
static mat4x4 _view;
static float _distance = 40.0f;


static void _update_view() {
    float x = _distance * cosf(_altitude) * cosf(_azimuth);
    float y = _distance * cosf(_altitude) * sinf(_azimuth);
    float z = _distance * sinf(_altitude);

    vec3 target = {0, 0, 0};
    vec3 new_position;
    vec3_add(new_position, (vec3) {x, y, z}, target);
    vec3 up = {0, 0, 1};
    mat4x4_look_at(_view, new_position, target, up);
}

void orbit_camera_init() {
    _update_view();
}

void orbit_camera_get_projection(mat4x4 proj) {
    mat4x4 perspective;
    mat4x4_perspective(perspective, RADIANS(45.0f), RENDER_WINDOW_ASPECT, 0.01f, 100.0f);
    mat4x4_mul(proj, perspective, _view);
}

float orbit_camera_get_distance() {
    return _distance;
}

void orbit_camera_set_distance(float distance) {
    _distance = distance;
    // vec3_sub(_position_offset, _target, _position);
    // vec3_scale(_position_offset, _position_offset, zoom);
}

void orbit_camera_rotate(float dx, float dy) {
    float dx_rad = -(M_PI / (float)RENDER_WINDOW_WIDTH) * dx;
    float dy_rad = (2 * M_PI / (float)RENDER_WINDOW_HEIGHT) * dy;

    _azimuth += dx_rad;
    _altitude += dy_rad;

    if (_altitude >= (M_PI / 2.0f) - 0.01f) {
        _altitude = (M_PI) / 2.0f - 0.01f;
    }

    if (_altitude <= 0.01f) {
        _altitude = 0.01f;
    }

    _update_view();
}
