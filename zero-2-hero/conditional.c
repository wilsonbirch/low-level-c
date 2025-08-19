#include <stdio.h>

int main(){

    int temp;
    printf("What is the temperature?");
    scanf("%d", &temp);

    if (temp >= 70) {
        printf("dang it's hot!\n");
    } else if (temp >= 30) {
        printf("dang it's mild!\n");
    } else {
        printf("dang it's cold!\n");
    }

    return 0;

}