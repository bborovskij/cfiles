/**
 * Sort integers using a bubble sort algorithm.
 *
 * Requirements:
 * 1. Accept any number of integers to sort.
 * 2. Fail if input element is not integer.
 * 3. Pritn help message if called without an argument.
 *
 * Usage exmaple:
 * $ ./bubble_sort 1 5 2 4 3  # OK
 * 1 2 3 4 5
 *
 * $ ./bubble_sort 1          # OK
 * 1
 *
 * $ ./bubble_sort            # OK
 * Usage:
 * $ ./bubble_sort 1 98 54 76 31 3 54 76 98
 *
 * $ ./bubble_sort one 2      # Error
 * Error occurred: Invalid argument
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>

#define ZERO_STR "0"

/**
 * @brief Sort array of integers using a bubble sort algorithm.
 * @param arr     pointer to target array
 * @param arr_len number of elements in the array
 */
void bubble_sort(long *arr, const int *arr_len) {
    long first = arr[0];
    int changed = false;

    for (int i = 1; i < *arr_len; ++i) {
        if (first > arr[i]) {
            arr[i - 1] = arr[i];
            arr[i] = first;
            first = arr[i - 1];
            changed = true;
        } else
            first = arr[i];
    }
    if (changed) {
        bubble_sort(arr, arr_len);
    }
}


/**
 * @brief Print elements from the result array.
 * @param arr     pointer to results array
 * @param arr_len number of elements in the results array
 */
void output_result_array(long *arr, int arr_len) {
    for (; arr_len; --arr_len, ++arr) printf("%lu ", *arr);
    printf("\n");
}


/**
 * @brief Print help message about cmd usage.
 */
void output_help_msg() {
    char *help_msg = "Usage:\n"
                     "$ ./bubble_sort 1 98 54 76 3"
                     "1 3 54 76 98";
    printf("%s\n", help_msg);
}


/**
 * @brief Parse elements from the input into the results buffer.
 * @details
 * Steps are:
 * 1. Retrieve element from the input one by one;
 * 2. If element is not an integer, exit with an error.
 *
 * @param argv Argument vector of this program.
 */
int parse_input(const int *argc, char *argv[], long *res_buffer) {
    long value;

    for (int i = 1; i < *argc; ++i) {
        // Handle "0" in argv input
        if (!strcmp(argv[i], ZERO_STR)) {
            res_buffer[i - 1] = 0;
            continue;
        }
        if (!(value = strtol(argv[i], NULL, 10))) {
            return 1;
        }
        res_buffer[i - 1] = value;
    }
    return 0;
}


void report_error() {
    if (errno) perror("Error occurred");
}


int main(int argc, char *argv[]) {
    atexit(report_error);
    errno = 0;
    const int elem_count = argc - 1;
    long result_buffer[elem_count];

    if (argc == 1) {
        output_help_msg();
        return errno;
    }

    if (parse_input(&argc, argv, result_buffer)) {
        return errno;
    }
    bubble_sort(result_buffer, &elem_count);
    output_result_array(result_buffer, elem_count);

    return errno;
}
