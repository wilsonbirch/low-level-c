#include <stdio.h>

union myunion_u {
    int x;
    char c;
    short s;
};

int main(){

    union myunion_u u;
    u.x = 0x41424344;

    printf("%hx %hhx\n", u.s, u.c); //  output: 4344 44, u.s is the internal short and u.c is the internal character of that larger int x that we set
    
};