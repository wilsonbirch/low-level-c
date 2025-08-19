#include <stdio.h>
#include <stdlib.h>

/*
    Pointers allow access for functions where a value may be out of scope.

    Pointer to a pointer is the address of an address

    the following foo function tries to reallocate a 64 bit memory address size to 128, this will "fail" if something goes wrong trying to do that
*/

typedef enum {
    STATUS_GOOD,
    STATUS_BAD,
} status_t;

status_t foo(int **data, int len) {
    int *temp = NULL;                   // create a temporary pointer
    temp = realloc(*data, len);         // try to reallocate the data pointer to this new size.

    if(temp == NULL){                   // if temp returns NULL, then we could not realloc this data pointer, return status bad
        *data = NULL;
        return STATUS_BAD;
    };

    *data = temp;                       // If we succeed, then set the original data pointer to this new address
    return STATUS_GOOD;
}

int main(){



    int i;              // value
    int *pi = &i;       // pointer to value
    int **ppi = &pi;    // pointer to pointer to value

    int *first = malloc(64);            // 64 bytes allocated for this integer.
    if(STATUS_BAD == foo(&first,128)){  // foo takes in the address of a pointer (double) & a new amount to allocate
        printf("Uh oh\n");
    };

    return 0;

};

/*
    This challenge requires you to fix the code to the right. The function takes a pointer to a pointer. 
    Write a valid heap allocated memory address to that parameter. 
    Before the function returns, write the number 10 to that location.
*/

int foo(int **ptr) {
    int *temp = realloc(*ptr, sizeof(int));

    if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return -1;
    }

    *temp = 10;
    *ptr = temp; 
    return 0;
}