#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main() {
    const char *filename = "data.bin";
    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};

    int fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open (write)");
        return 1;
    }

    write(fd, data, sizeof(data));
    close(fd);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open (read)");
        return 1;
    }

    lseek(fd, 3, SEEK_SET);

    unsigned char buffer[4];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer));

    if (bytesRead == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Buffer contains: ");
    for (int i = 0; i < bytesRead; ++i) {
        printf("%d ", buffer[i]);
    }
    printf("\n");

    close(fd);
    return 0;
}
