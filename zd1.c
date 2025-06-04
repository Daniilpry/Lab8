#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    int flags = fcntl(pipefd[1], F_GETFL);
    fcntl(pipefd[1], F_SETFL, flags | O_NONBLOCK);

    char buffer[65536]; // великий буфер
    memset(buffer, 'A', sizeof(buffer));

    ssize_t count = write(pipefd[1], buffer, sizeof(buffer));
    
    if (count == -1) {
        perror("write");
    } else {
        printf("Requested to write %zu bytes, actually wrote %zd bytes\n", sizeof(buffer), count);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    return 0;
}
