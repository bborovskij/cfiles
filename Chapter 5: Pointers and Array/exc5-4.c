/*
 * Chapter5: Pointers and array
 *
 * Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the end of the string s,
 * and zero otherwise.
 */
#include <stdio.h>


int strend(char *s, char *t) {
    int t_idx = 0;
    while (*s != '\0') { s++; }
    while (*t != '\0') {
        t++;
        ++t_idx;
    }
    for (; t_idx; --t_idx) {
        if (*(--t) != *(--s)) {
            return 0;
        }
    }
    return 1;
}


int main() {
    char *s = "Hello";
    char *t = "o";
    int res = strend(s, t);
    printf("%d\n", res);
}
