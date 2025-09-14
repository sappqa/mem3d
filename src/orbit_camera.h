#pragma once
#include "linmath.h"

void orbit_camera_init();
void orbit_camera_set_view(vec3 position, vec3 target, vec3 up);
void orbit_camera_get_projection(mat4x4 proj);
float orbit_camera_get_distance();
void orbit_camera_set_distance(float distance);
void orbit_camera_rotate(float dx, float dy);