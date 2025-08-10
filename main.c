#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include "common.h"

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

        while ((bytes_read = read(pipe_fd[0], buf, sizeof(buf))) > 0) {
            write(STDOUT_FILENO, buf, bytes_read);
        }

        close(pipe_fd[0]);

        int status;
        waitpid(pid, &status, 0);
    }

    exit(0);
}