#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "common.h"
#include "render_window.h"
#include "memory_event.h"

int main(int argc, char** argv) {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], PIPE_WRITE_FILENO);
        close(pipe_fd[1]);

        char cwd[512];
        getcwd(cwd, sizeof(cwd));
        char ld_preload_hook_path[640];
        int length = snprintf(ld_preload_hook_path, sizeof(ld_preload_hook_path), "%s/hooks/libhooks.so", cwd);

        setenv("LD_PRELOAD", ld_preload_hook_path, 1);
        setenv(ENV_M3D_PIPE_WRITE_FILENO, "100", 1);

        execv(argv[1], &argv[1]);
    }
    else {        
        close(pipe_fd[1]);

        char buf[ALLOC_DESCRIPTOR_STRLEN];
        ssize_t bytes_read;

        memory_event memory_events[16];
        memory_event_bounds bounds = memory_event_bounds_min_max_init;
        struct timespec last_timestamp;
        int i = 0;
        while ((bytes_read = read(pipe_fd[0], buf, sizeof(buf))) > 0) {
            // write(STDOUT_FILENO, buf, bytes_read);
            // memory_event* event = (memory_event*)malloc(sizeof(memory_event));
            parse_memory_event(buf, bytes_read, &memory_events[i]);

            if (i == 0) bounds.start_timestamp = memory_events[i].timestamp;
            if (memory_events[i].address < bounds.min_address) bounds.min_address = memory_events[i].address;
            if (memory_events[i].address > bounds.max_address) bounds.max_address = memory_events[i].address;
            last_timestamp = memory_events[i].timestamp;
            i++;
            // printf("alloc type: %c\n", event->alloc);
            // printf("alloc address: %p\n", event->address);
            // printf("alloc timestamp: %ld.%ld\n", event->timestamp.tv_sec, event->timestamp.tv_nsec);
            // printf("alloc size: %zu\n", event->size);
            // free(event);
        }

        printf("min address %p\n", bounds.min_address);
        printf("max address %p\n", bounds.max_address);

        close(pipe_fd[0]);

        int status;
        waitpid(pid, &status, 0);

        render_window();
    }

    exit(0);
}