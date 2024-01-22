#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int fd = open("./q2.output", O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        const char *text = "written from child process!";
        write(fd, text, strlen(text));
        int w = wait(NULL);
        printf("%d", w);
    } else {
        // parent goes down this path (original process)
        const char *text = "written from parent process!";
        write(fd, text, strlen(text));
    }
    return 0;
}