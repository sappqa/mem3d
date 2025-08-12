#pragma once
#include <stdlib.h>
#include <stdint.h>

typedef struct _memory_event {
    bool alloc;
    void* ptr;
    size_t size;
    uint64_t timestamp;
} memory_event;