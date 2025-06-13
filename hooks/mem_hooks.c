#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/*
TODO:

ipc options:

- writing to a file would incur file-io overhead every malloc/free..
- I should use a pipe with fork/exec and setenv to configure the ld_preload hooks. in here would need to use getenv for the pipe fd and write to write to the pipe... maybe something like this
typedef struct {
    char type; // 'A' or 'F'
    void* ptr;
    size_t size;
    uint64_t timestamp;
} __attribute__((packed)) MemEvent;

void log_alloc(void* ptr, size_t size) {
    MemEvent evt = { 'A', ptr, size, get_timestamp() };
    write(log_fd, &evt, sizeof(evt));
}


rendering solution 1
- create array of memory events: ALLOC or FREE, timestamp, ptr, size. This array must be in timestamp sequential order
- if we set the animation length to 10s at 60fps, we'll have 600 frames total. we're mapping the real-time memory event timestamps to be between 0-10 seconds
- for each frame, find the closest memory event and update the vertex buffer to match the current allocations
    - the naive solution would be to recompute the current allocations by reading up to the current memory event from the start of the array, every frame
    - if we only had to worry about the animation going in sequential order, we would only need the next memory event in the timeline to see what has changed and update the vertex buffer, but we want to be able to recompute the 
            current allocations list for any frame n.
    - so, one way we can speed this up is to create evenly spaced "memory state snapshots" along our timeline. Then, whenever we need to figure out the current allocations list for a given frame n, we fall back to the closest snapshot and 
        just use the allocation deltas from there. 

rendering solution 2
- use segment tree to find all allocations that have start-end ranges containing a given frame n

*/



void* malloc(size_t size) {
    static void* (*orig_malloc)(size_t) = NULL;
    if (!orig_malloc) {
        orig_malloc = dlsym(RTLD_NEXT, "malloc");
    }

    void* ptr = orig_malloc(size);

    char msg_buf[128];
    int len = snprintf(msg_buf, sizeof(msg_buf), "malloc'd %zu bytes @ %p\n", size, ptr);
    if (len) write(STDOUT_FILENO, msg_buf, len);

    return ptr;
}

void free(void* ptr) {
    static void (*orig_free)(void*) = NULL;
    if (!orig_free) {
        orig_free = dlsym(RTLD_NEXT, "free");
    }

    orig_free(ptr);

    char msg_buf[64];
    int len = snprintf(msg_buf, sizeof(msg_buf), "freed @ %p\n", ptr);
    if (len) write(STDOUT_FILENO, msg_buf, len);
}