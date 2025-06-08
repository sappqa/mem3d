#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void* malloc(size_t size) {
    static void* (*orig_malloc)(size_t) = NULL;
    if (!orig_malloc) {
        orig_malloc = dlsym(RTLD_NEXT, "malloc");
    }

    void* ptr = orig_malloc(size);

    char msg_buf[128];
    int len = snprintf(msg_buf, sizeof(msg_buf), "malloc'd %zu bytes @ %p\n", size, ptr);
    if (len) write(STDIN_FILENO, msg_buf, len);

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