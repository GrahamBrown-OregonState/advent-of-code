/*
Author: Graham Brown

Author's Note: Yes, this is obviously overkill. I chose to do it this way because I was bored.
*/

#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

void copy_until_null(char* dest, char* src_start) {
    int i = 0;
    while (src_start[i] != '\0' && src_start[i] != '\n') {
        dest[i] = src_start[i];
        i++;
    }
    dest[i] = '\0';
}

int calculate_code(char* instruction, int current_pos, int* count) {
    char num_instr[100];
    copy_until_null(num_instr, instruction + 1);
    int num = atoi(num_instr);
    int start_on_zero = 0;
    if (instruction[0] == 'L') {
        if (current_pos == 0) {
            start_on_zero = 1;
        }
        current_pos -= num;
        while (current_pos < 0) {
            current_pos += 100;
            if (current_pos != 0 && start_on_zero == 0) {
                *count += 1;
            }
            start_on_zero = 0;
        }
    } else {
        if (current_pos == 0) {
            start_on_zero = 1;
        }
        current_pos += num;
        while (current_pos > 99) {
            current_pos -= 100;
            if (current_pos != 0 && start_on_zero == 0) {
                *count += 1;
            }
        }
    }
    return current_pos;
}

void read_rotations() {
    FILE* rotations_file = fopen("./rotations.txt", "r");
    int current_pos = 50;
    char* line = NULL;
    size_t buffer_size = 0;
    ssize_t line_len = 0;
    int* count = malloc(sizeof(int));
    *count = 0;
    while ((line_len = getline(&line, &buffer_size, rotations_file)) != -1) {
        current_pos = calculate_code(line, current_pos, count);
        if (current_pos == 0) {
            *count += 1;
        }
    }
    printf("The answer is: %d \n", *count);

}

void main() {
    read_rotations();
}