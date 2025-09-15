#pragma once
#include "memory_event.h"

void render_init();
int render_window(memory_event* memory_events, size_t num_memory_events, memory_event_bounds* bounds);