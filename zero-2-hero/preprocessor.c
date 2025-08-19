#include <stdio.h>

#define MAX_PERSONS 1024

#define DEBUG

int main()
{
    #ifdef DEBUG
        printf("WE ARE IN DEBUG MODE: %s:%d", __FILE__,__LINE__); // WE ARE IN DEBUG MODE: C:\Users\birchw2\Repos\low-level-c\preprocessor.c:10
    #endif

    return 0;
}