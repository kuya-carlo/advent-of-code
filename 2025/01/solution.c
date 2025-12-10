#include <stdio.h>



void main() {
    FILE *fptr;
    fptr = fopen("01.txt", "r");
    int count = 10;
    // for (int i = 0; i<count; i++) {
    char string[100];
    fgets(string, 100, fptr);
    printf("%s", string);
    // }
    //
    // int counter = 0;
    // printf("%i\n", counter);
}
