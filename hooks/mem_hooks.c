#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "common.h"


int get_m3d_pipe_write_end() {
    char* fdstr = getenv(ENV_M3D_PIPE_WRITE_FILENO);
    if (!fdstr) {
        char* err_msg = "error: mem3d pipe write-end file descriptor not found.\n";
        write(STDERR_FILENO, err_msg, strlen(err_msg));
    }
    return atoi(fdstr);
}

void* malloc(size_t size) {
    static void* (*orig_malloc)(size_t) = NULL;
    if (!orig_malloc) {
        orig_malloc = dlsym(RTLD_NEXT, "malloc");
    }

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    void* ptr = orig_malloc(size);

    char msg_buf[ALLOC_DESCRIPTOR_STRLEN];
    int len = snprintf(msg_buf, ALLOC_DESCRIPTOR_STRLEN, "alloc_type:A,address:%p,timestamp:%010ld.%09ld,size:%010zu", ptr, ts.tv_sec, ts.tv_nsec, size);

    int write_fd = get_m3d_pipe_write_end();
    if (len) write(write_fd, msg_buf, sizeof(msg_buf));

    return ptr;
}

void free(void* ptr) {
    static void (*orig_free)(void*) = NULL;
    if (!orig_free) {
        orig_free = dlsym(RTLD_NEXT, "free");
    }

    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);    
    orig_free(ptr);

    char msg_buf[ALLOC_DESCRIPTOR_STRLEN];
    int len = snprintf(msg_buf, ALLOC_DESCRIPTOR_STRLEN, "alloc_type:F,address:%p,timestamp:%010ld.%09ld-----------------", ptr, ts.tv_sec, ts.tv_nsec);

    int write_fd = get_m3d_pipe_write_end();
    if (len) write(write_fd, msg_buf, sizeof(msg_buf));
}