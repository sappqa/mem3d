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

void parse_memory_event(char* const event_str, size_t len, memory_event* event);