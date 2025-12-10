# Actual Documentation:

Advent of Code 2025

--- Day 1: Secret Entrance ---

The Elves have good news and bad news.

The good news is that they've discovered [project management](https://en.wikipedia.org/wiki/Project_management)! This has given them the tools they need to prevent their usual Christmas emergency. For example, they now know that the North Pole decorations need to be finished soon so that other critical tasks can start on time.

The bad news is that they've realized they have a **different** emergency: according to their resource planning, none of them have any time left to decorate the North Pole!

To save Christmas, the Elves need **you** to **finish decorating the North Pole by December 12th**.

Collect stars by solving puzzles. Two puzzles will be made available on each day; the second puzzle is unlocked when you complete the first. Each puzzle grants *one star*. Good luck!

You arrive at the secret entrance to the North Pole base ready to start decorating. Unfortunately, the password seems to have been changed, so you can't get in. A document taped to the wall helpfully explains:

"Due to new security protocols, the **password** is locked in the safe below. Please see the attached document for the new combination."

The safe has a dial with only an arrow on it; around the dial are the numbers `0` through `99` in order. As you turn the dial, it makes a small click noise as it reaches each number.

The attached document (your puzzle input) contains a sequence of **rotations**, one per line, which tell you how to open the safe. A rotation starts with an `L` or `R` which indicates whether the rotation should be to the **left** (toward lower numbers) or to the **right** (toward higher numbers). Then, the rotation has a **distance** value which indicates how many clicks the dial should be rotated in that direction.

So, if the dial were pointing at `11`, a rotation of R8 would cause the dial to point at `19`. After that, a rotation of `L19` would cause it to point at `0`.

Because the dial is a circle, turning the dial left from `0` one click makes it point at 99. Similarly, turning the dial right from `99` one click makes it point at `0`.

So, if the dial were pointing at `5`, a rotation of `L10` would cause it to point at `95`. After that, a rotation of `R5` could cause it to point at `0`.

The dial starts by pointing at `50`.

You could follow the instructions, but your recent required official North Pole secret entrance security training seminar taught you that the safe is actually a decoy. The actual password is the number of times the dial is left pointing at 0 after any rotation in the sequence.

For example, suppose the attached document contained the following rotations:
```
L68
L30
R48
L5
R60
L55
L1
L99
R14
L82
```
Following these rotations would cause the dial to move as follows:

 - The dial starts by pointing at 50.
 - The dial is rotated L68 to point at 82.
 - The dial is rotated L30 to point at 52.
 - The dial is rotated R48 to point at 0.
 - The dial is rotated L5 to point at 95.
 - The dial is rotated R60 to point at 55.
 - The dial is rotated L55 to point at 0.
 - The dial is rotated L1 to point at 99.
 - The dial is rotated L99 to point at 0.
 - The dial is rotated R14 to point at 14.
 - The dial is rotated L82 to point at 32.

Because the dial points at `0` a total of three times during this process, the password in this example is `3`.

Analyze the rotations in your attached document. **What's the actual password to open the door?**
To begin, [get your puzzle input](./01.txt)

Time Start: 2:13AM, 12/2
First Time Out: 2:25AM 12/2
Time In: 1:07 12/11
First Submission: 2:25 12/11
Time End: 2:56 12/11

## Design Think
Ok, so for this one, its like the CS50's Caesar cipher algo. Here's what we do:

1. Open file
2. Set counter to 0, everytime it goes to 0, we add it to counter, which is the final answer
3. To left, minus, to right, add

### Code
### Code Exhibit A
```c
#include <stdio.h>
int main() {
    int counter = 0;
}
```
### Code Exhibit B
12/11
```c
#include <stdio.h>

int main() {
    FILE *fptr;
    fptr = fopen("01.txt", "r");
    int count = 10;
    // for (int i = 0; i<count; i++) {
    // supposed to get one line after the other in here
    char string[100];
    fgets(string, 100, fptr);
    printf("%s", string);
    // }
    //
    // int counter = 0;
    // printf("%i\n", counter);
}
```
### Code Exhibit C
Blockpoints:
- output becomes this:
```
R23
 82 50 51 0
L16
 76 49 54 0
R39
 82 51 57 0
```
```c
#include <stdio.h>
#include <string.h>

char* remove_char(char* str, char find) {
    char *current_pos = strchr(str, find);
    while (current_pos) {
        memmove(current_pos, current_pos + 1, strlen(current_pos));
        current_pos = strchr(str, find);
    }
    return str;
}

int main() {
    FILE *fptr = fopen("01.txt", "r"); //open file for read

    char pointer[5];
    char num[4];

    while (fgets(pointer, sizeof(pointer), fptr)) {

        memcpy(num, pointer, 3);
        num[3] = '\0';

        remove_char(num, '\n');

        printf("%s %d %d %d %d\n", pointer, num[0], num[1], num[2], num[3]);
    }
    return 0;

}
```
### Code Exhibit D
well, output is now this:
```
52 	52
84 	84
79 	79
102 	2
-14 	86
125 	25
```
Update: its wrong
```c
int main() {
    FILE *fptr = fopen("01.txt", "r"); //open file for read

    char instruction[5];
    int counter = 0;

    while (fgets(instruction, sizeof(instruction), fptr)) {
        instruction[strcspn(instruction, "\n")] = '\0';
        switch (instruction[0]) {
            case 'L':
                counter -= atoi(&instruction[1]) % 100;
                break;
            case 'R':
                counter += atoi(&instruction[1]) % 100;
                break;
        }
        printf("%d \t", counter);
        // should have pointer as 0-99
        if (counter < 1) {
            counter += 100;
        } else if (counter > 99) {
            counter -= 100;
        }
        counter = counter % 100; // after checking, this ain't needed
        printf("%d \n", counter);

        // printf("%s %d \n", instruction, counter);
    }
    return 0;

}
```

### Code Example E (final code)
```c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int cleanse_num(int num) {
    int wrapped = (num % 100 + 100) % 100;
    return wrapped;
}

int main() {
    FILE *fptr = fopen("01.txt", "r"); //open file for read

    char instruction[7];
    int lock_pos = 50; // bro forgot to read the instructions
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

```


[Reference 1](https://www.w3schools.com/c/c_files_read.php)

Takeaways:
- `fopen` gives a pointer
- `fgets` gets the first line
12/11
- `fgets` can be passed to while and it gives EOF and NULL when end of file happens.
- `memcpy` to slice text, `p[2:3]` doesnt work here
- having hardcoded fgets and char... will cause off-by-one errors
- welp
- `switch` helps... a lot. also, never knew there's `strcspn` (vim find command to a newb programmer)
