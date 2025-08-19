#include <stdio.h>

#define MAX_IDS 32

int main(){

    int ids[MAX_IDS] = {0,1,2};

    char mystr[] = {'h','e','l','l','o', 0}; // a string is actualy an array of characters, null limited, C will print memory until it finds a null/zero value

    printf("Hello World\n"); // Hello World
    printf("%s\n", mystr); // hello

    // strcpy(dest, src);
    // strncpy(dest,src,n);

}