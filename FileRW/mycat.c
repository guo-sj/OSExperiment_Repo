#include <stdio.h>
#include <fcntl.h> /* for open() */
#include <error.h> /* for error() */
#include <unistd.h> /* for write(), read() */
#include <stdlib.h> /* for exit() */
#define MAXLEN 1024

int mygetline(char s[], int len);

int main(int argc, char *argv[])
{
    char s[MAXLEN];
    if (argc == 1) {
        while (mygetline(s, MAXLEN))
            printf("%s", s);
        exit(0);
    }

    int fd, rn, wn;
    while (--argc) {
        if ((fd = open(*(++argv), O_RDONLY, 0)) == -1) {
            fprintf(stderr, "cat: %s: No such file or directory\n", *argv);
            continue;
        }
        while ((rn = read(fd, s, MAXLEN)) > 0)
            if ((wn = write(1, s, rn)) == -1) {
                perror("write file: ");
                close(fd);
                exit(1);
            }
        if (rn == -1) {
            perror("read file: ");
            close(fd);
            exit(1);
        }
        close(fd);
    }
    exit(0);
}

/* mygetline:  get one line from stdin */
int mygetline(char s[], int len)
{
    int i, c;

    for (i = 0; i < len-1 && (c=getchar()) != EOF && c != '\n'; i++)
        s[i] = c;
    if (c == '\n')
        s[i++] = c;
    s[i] = '\0';
    return i;
}
