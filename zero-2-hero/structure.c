#include <stdio.h>
#include <stdbool.h>

#define MAX_EMPLOYEES 1000

struct employee_t {
    int id;
    char firstname[64];
    char lastname[64];
    float income;
    bool ismanager;
};

int main(){
    struct employee_t employees[MAX_EMPLOYEES];

    int i = 0;
    for(i=0; i < MAX_EMPLOYEES; i++){
        employees[i].income = 0;
        employees[i].ismanager = false;
    }

    printf("%d\n", employees[4].income);

};