#include <stdio.h>

// Global scope
int g_NumPersons = 0;

void another_function ()
{
    int personID = 1;
}

int main()
{
    // type name = initial value;
    // in scope of main
    int personID = 0;
    personID = personID += 1;

    // in scope of this fn
    {
        int personID = 0;
        personID +=1;
    };
}