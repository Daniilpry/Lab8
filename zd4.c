#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();

    if (pid == 0) {
        dup2(pipefd[0], STDIN_FILENO);
        close(pipefd[0]);
        execlp("cat", "cat", NULL);
        perror("execlp");
        exit(1);

    } else {
        close(pipefd[0]);
        wait(NULL);
    }

    return 0;
}
