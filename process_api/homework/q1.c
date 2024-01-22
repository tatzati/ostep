#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int x = 100;
    printf("hello world (pid:%d) (x:%d)\n", (int) getpid(), x);
    int rc = fork();
    if (rc < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        // child (new process)
        x++;
        printf("hello, I am child (pid:%d) (x:%d)\n", (int) getpid(), x);
    } else {
        // parent goes down this path (original process)
        x = 1;
        int wc = wait(NULL);
        printf("hello, I am parent of %d (x:%d) (pid:%d)\n",
	       rc, x, (int) getpid());
    }
    return 0;
}