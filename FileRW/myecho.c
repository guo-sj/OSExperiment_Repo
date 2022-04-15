#include <stdio.h>
#define MAXLEN  1024

int main(int argc, char *argv[])
{
    /* command arguments */
    while (--argc)
        printf("%s ", *(++argv));
    printf("\n");
    return 0;
}
