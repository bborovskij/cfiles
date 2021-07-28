/*
Exercise 5-13. Write the program tail, which prints the last n lines of its input.
 By default, n is 10, let us say, but it can be changed by an optional argument, so that

$ tail -n

prints the last n lines. The program should behave rationally no matter how unreasonable 
the input or the value of n. Write the program so it makes the best use of available storage; 
 lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional 
 array of fixed size.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN (100000)

int read_and_add_to_buffer(char *buffer) {
    ssize_t bytes_read = 1;
    int lineno = 0;
    size_t size = 100;
    char *string;

    while (bytes_read > 0) {
        string = NULL;
        bytes_read = getline(&string, &size, stdin);
        if (bytes_read <= 0) {
            break;
        }
        for (; *string != '\0'; string++, buffer++) {
            *buffer = *string;
        }
        *buffer = *string;
        lineno++;
    }
    return lineno;
}

int parse_line_nums(const int *argc, char *argv[]) {
    int linenum;
    if (*argc == 1) {
        return 0;
    } else if (*argc != 2 && *argc != 3) {
        printf("Accepts only -n=<number> or -n <number>");
        return 0;
    }
    if (!strcmp(argv[1], "-n")) {
        linenum = (int) strtod(argv[2], NULL);
    } else {
        for (; *argv[1] != '='; ++argv[1]) {};
        ++argv[1];
        linenum = (int) strtod(argv[1], NULL);
    }
    return linenum;
}

void print_last_lines(char *buffer, const int *lines, const int *total_lines) {
    int i = *total_lines - *lines;

    for (int j = 0; j < i; ++j) {
        while (*buffer != '\n') { buffer++; }
        buffer++;
    }
    printf("%s", buffer);
}


int main(int argc, char *argv[]) {
    char main_buffer[MAX_LEN];
    int total_lines;
    int lines_num;

    total_lines = read_and_add_to_buffer(main_buffer);
    lines_num = parse_line_nums(&argc, argv);

    if (!lines_num) {
        printf("%s", main_buffer);
    } else {
        print_last_lines(main_buffer, &lines_num, &total_lines);
    }
}
