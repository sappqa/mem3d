#pragma once
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

typedef struct _memory_event {
    char alloc;
    void* address;
    struct timespec timestamp;
    size_t size;
} memory_event;

typedef struct _memory_event_bounds {
    void* min_address;
    void* max_address;
    struct timespec start_timestamp;
    struct timespec end_timestamp;
} memory_event_bounds;

static const memory_event_bounds memory_event_bounds_min_max_init = {
    (void*)(uintptr_t)(~0ULL), (void*)(uintptr_t)0
};

void parse_memory_event(char* const event_str, size_t len, memory_event* event);
