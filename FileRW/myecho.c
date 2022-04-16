#include <stdio.h>

int main(int argc, char *argv[])
{
    while (--argc)
        printf("%s ", *(++argv));
    printf("\n");
    return 0;
}
