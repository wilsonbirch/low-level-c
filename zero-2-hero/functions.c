#include <stdio.h>

int add(int x, int y)
{
    int z = x+y;
    return z;
}

int main(int argc, char *argv[])
{
    int other_int = add(1,2);

    printf("%d\n", other_int);

    return 0;
}