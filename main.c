#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    int pipe_fd[2];
    if (pipe(&pipe_fd) == -1) {
        exit(1);
    }

    pid_t pid = fork();
    if (pid == 0) {
        close(pipe_fd[0]);

        execv(argv[1], NULL);
        
    }
    else {
        close(pipe_fd[1]);
        int status;
        waitpid(0, &status, NULL);
    }

    exit(0);
}