#include <stdio.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 1000

/*
    different systems may add different padding characters to a struct, so behaviour may not be completely the same if needed to talk/communicate between the 2

*/

__attribute__((__packed__)) struct employee_t {
    int id;
    char firstname[64];
    char lastname[64];
    float income;
    bool ismanager;
};

int main(){
    struct employee_t employees[MAX_EMPLOYEES];

    printf("Size of employee: %d\n", sizeof(struct employee_t)); // 140

};