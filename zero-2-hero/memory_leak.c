#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
    static memory or variables, is the best way to use global-ish variables, yet still contain the scope to where it is required, 
    less dangerous declaring completely global vars
*/

struct employee_t {
    int id;
    int income;
    bool staff;
};

int initialize_employee(struct employee_t *e) {
    static int numEmployees = 0;
    numEmployees++;

    e->id = numEmployees;
    e-> income = 0;
    e->staff = false;

    return numEmployees;
}


int main(){

    int n=4;

    struct employee_t *employees = malloc(sizeof(struct employee_t)*n);
    if(employees == NULL){
        printf("the allocator failed\n");
        return -1;
    }
    for(int i=0; i<n; i++){
        int id = initialize_employee(&employees[i]);
        printf("New employee ID: %d\n", id);
    }

    free(employees);
    employees = NULL;

};

// valgrind ubuntu tool to check leaks