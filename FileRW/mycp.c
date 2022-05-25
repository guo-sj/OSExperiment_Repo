#include <stdio.h>
#include <fcntl.h> /* for open() */
#include <error.h> /* for error() */
#include <unistd.h> /* for write(), read() */
#include <stdlib.h> /* for exit() */
#define MAXLEN 1024

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("Usage: %s [src] [dst]\n", argv[0]);
        exit(-1);
    }

    int fds, fdt, rn, wn;
    char s[MAXLEN];

    if ((fds = open(argv[1], O_RDONLY, 0)) == -1) {
        perror("open file: ");
        exit(-1);
    }
    if ((fdt = open(argv[2], O_CREAT | O_RDWR, 0644)) == -1) {
        perror("open file: ");
        exit(-1);
    }
    while ((rn = read(fds, s, MAXLEN)) > 0)
        if ((wn = write(fdt, s, rn)) == -1) {
                perror("write file: ");
                close(fds);
                close(fdt);
                exit(-1);
        }
    if (rn == -1) {
        perror("read file: ");
        close(fds);
        close(fdt);
        exit(-1);
    }

    close(fds);
    close(fdt);
    exit(0);
}
