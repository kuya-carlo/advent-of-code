#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cleanse_num(int num) {
    int wrapped = (num % 100 + 100) % 100;
    // if (num != wrapped) printf("%d -> %d\n", num, wrapped);
    return wrapped;
}

int main() {
    FILE *fptr = fopen("01.txt", "r"); //open file for read

    char instruction[7];
    int lock_pos = 50;
    int counter = 0;

    while (fgets(instruction, sizeof(instruction), fptr)) {
        // remove newlines
        instruction[strcspn(instruction, "\n")] = '\0';
        int change_num = instruction[0]== 'L'? -atoi(&instruction[1]): atoi(&instruction[1]);
        lock_pos = cleanse_num(lock_pos + change_num);
        if (lock_pos == 0) counter += 1;
    }
    printf("%d \n", counter);
    return 0;

}
