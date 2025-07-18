#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define PIPE_WRITE_FILENO 100
#define ALLOC_DESCRIPTOR_STRLEN 88

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
        snprintf(ld_preload_hook_path, sizeof(ld_preload_hook_path), "%s/../hooks/libhooks.so", cwd);
        setenv("LD_PRELOAD", ld_preload_hook_path, 1);
        setenv("M3D_PIPE_WRITE_FILENO", "100", 1);
        execv(argv[1], &argv[1]);

        // for (int i = 0; i < 11; i++) {
        //     char message[64];
        //     snprintf(message, sizeof(message), "this is message %d\n", i);
        //     write(PIPE_WRITE_FILENO, message, strlen(message));
        // }

        // const char* done = "leaving child process";
        // write(STDOUT_FILENO, done, strlen(done));
        // close(PIPE_WRITE_FILENO);
    }
    else {        
        close(pipe_fd[1]);

        char buf[ALLOC_DESCRIPTOR_STRLEN];
        ssize_t bytes_read;

        while ((bytes_read = read(pipe_fd[0], buf, sizeof(buf))) > 0) {
            // need to loop read until we've definitely read the message size
            write(STDOUT_FILENO, buf, bytes_read);
        }

        close(pipe_fd[0]);

        int status;
        waitpid(pid, &status, 0);
    }

    exit(0);
}