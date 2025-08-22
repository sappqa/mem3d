#pragma once
#include "linmath.h"


void camera_init();
void camera_get_position(vec3 position);
void camera_set_position(vec3 position);
void camera_get_target(vec3 target);
void camera_set_target(vec3 target);
void camera_get_projection(mat4x4 proj);
float camera_get_zoom();
void camera_set_zoom(float zoom);