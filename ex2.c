#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define FIFO_SERVER "./fifoserver"
#define BUFFERSIZE 80
int main() {
    int fd, ret;
    if (access(FIFO_SERVER, F_OK) == -1) {
        if (mkfifo(FIFO_SERVER, 0666) < 0 && (errno != EEXIST)) {
            printf("Create fifoserver error\n");
            exit(0);
        }
    }
    printf("Create fifoserver successfully\n");
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        char bufw[BUFFERSIZE];
        printf("Please input a string：");
        gets(bufw);
        fd = open(FIFO_SERVER, O_WRONLY);
        if (fd < 0) {
            printf("child: Open fifoserver error\n");
            exit(0);
        }
        ret = write(fd, bufw, strlen(bufw));
        if (ret < 0) {
            printf("fifoserver write error\n");
            exit(0);
        }
        printf("fifoserver write successfully\n");
        close(fd);
    } else if (pid > 0) {
        char bufr[BUFFERSIZE];
        memset(bufr, 0, sizeof(bufr));
        fd = open(FIFO_SERVER, O_RDONLY);
        if (fd < 0) {
            printf("parent: Open fifoserver error\n");
            exit(0);
        }
        printf("Before: %s\n", bufr);
        ret = read(fd, bufr, BUFFERSIZE);
        if (ret < 0) {
            printf("fifoserver read error\n");
            exit(0);
        }
        printf("After: %s\n", bufr);
        close(fd);
    } else if (pid < 0) {
        printf("Fork error\n");
        exit(0);
    }
    return 0;
}
