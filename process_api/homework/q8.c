#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipe_fd[2];

    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t child1_pid = fork();

    if (child1_pid == -1) {
        perror("fork");
        return 1;
    }

    if (child1_pid == 0) {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);

        execlp("ls", "ls", (char *)NULL);

        perror("execlp");
        return 1;
    }

    pid_t child2_pid = fork();

    if (child2_pid == -1) {
        perror("fork");
        return 1;
    }

    if (child2_pid == 0) {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);

        execlp("wc", "wc", "-l", (char *)NULL);

        perror("execlp");
        return 1;
    }

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(child1_pid, NULL, 0);
    waitpid(child2_pid, NULL, 0);

    return 0;
}
