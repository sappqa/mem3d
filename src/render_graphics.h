#pragma once
#include "memory_event.h"

void graphics_init(memory_event* memory_events, size_t num_memory_events, memory_event_bounds* bounds);
void render_graphics();
void render_graphics_dispose();