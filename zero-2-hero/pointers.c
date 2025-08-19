#include <stdio.h>
#include <stdbool.h>

/*
    Pointers allow access for functions where a variable may be out of scope.

    When passing the pointer or adress of where a variable (Ralph) in this case exists, that function that has access to the pointer, now is able to edit
    that value directly, in this case a struct or a variable with a larger memory this makes sense to do.
*/

struct employee_t {
    int id;
    int income;
    bool staff;
};

void initialize_employee(struct employee_t *e) {
    e->id = 0;
    e-> income = 0;
    e->staff = false;

    return;
}


int swap(int * a, int * b) {    // int * a -> can be stated as "a is a pointer to an int", these params are initialized again for the scope of the function, 
                                //  the variables are not "passed" try reading the declaration right to left
    // initialize new temp int variable to store a
    int temp;
    // dereference a to get int value, assign to temp
    temp = *a;
    // set the value of a to the value of b
    *a = *b;
    // set the value of b to the temp int we assigned at the beginning (value of a)
    *b = temp;
}

int main(){

    int x = 3;

    int *pX = &x;

    printf("value of x: %d \n", x);
    printf("address of x: %p \n", pX);

    struct employee_t Ralph;
    initialize_employee(&Ralph);

    printf("%d\n", Ralph.income);

    
    int z = 5, y = 10;
    printf("Before swap: x = %d, y = %d\n", z, y);
    swap(&z, &y);
    printf("After swap: x = %d, y = %d\n", z, y);

};
