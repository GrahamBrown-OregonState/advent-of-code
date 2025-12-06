/*
Author: Graham Brown

Author's Note: Yes, this is obviously overkill. I chose to do it this way because I was bored.
*/

#include <stdio.h>
#include <sys/types.h>

void read_rotations() {
    FILE* rotations_file = fopen("./rotations.txt", "r");
    int current_pos = 50;
    while (!feof(rotations_file)) {
        char* line = NULL;
        size_t buffer_size = 0;
        ssize_t line_len = getline(&line, &buffer_size, rotations_file);
        current_pos = calculate_code(line, current_pos);
        printf("The answer is: %d \n", current_pos);
    }
    printf("The answer is: %d \n", current_pos);

}

int calculate_code(char* instruction, int current_pos) {
    char num_instr[100];
    copy_until_null(num_instr, instruction);
    int num = atoi(num_instr);
    if (instruction[0] == 'L') {
        current_pos -= num;
        while (current_pos < 0) {
            current_pos += 100;
        }
    } else {
        current_pos += num;
        while (current_pos > 99) {
            current_pos -= 100;
        }

    }
}

void copy_until_null(char* dest, const char* src_start) {
    int i = 0;
    while (src_start[i] != '\0') {
        dest[i] = src_start[i];
        i++;
    }
    dest[i] = '\0';
}

void main() {
    read_rotations();
}