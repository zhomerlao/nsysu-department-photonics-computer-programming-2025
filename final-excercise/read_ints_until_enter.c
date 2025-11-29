#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/* ---------------------------------------------------------
   Function: read_ints_until_enter
   Reads characters from stdin one-by-one.
   Stops immediately when Enter ('\n') is pressed.
   Stores parsed integers into a dynamic array.

   Returns: number of integers stored
   Output:  *out_list = allocated array of ints
   --------------------------------------------------------- */
size_t read_ints_until_enter(int **out_list) {
    int *list = NULL;
    size_t size = 0, capacity = 0;

    char *tok = NULL;
    size_t tok_len = 0, tok_cap = 0;

    int ch;

    while ((ch = getchar()) != EOF) {

        if (ch == '\n') {  // terminate immediately
            if (tok_len > 0) {
                tok[tok_len] = '\0';
                errno = 0;
                char *endp;
                long val = strtol(tok, &endp, 10);
                if (endp != tok && *endp == '\0' && errno == 0) {
                    if (size == capacity) {
                        size_t new_cap = (capacity == 0) ? 8 : capacity * 2;
                        int *tmp = realloc(list, new_cap * sizeof(int));
                        if (!tmp) { perror("realloc"); free(list); free(tok); return 0; }
                        list = tmp; capacity = new_cap;
                    }
                    list[size++] = (int) val;
                }
            }
            break;  // input ends immediately
        }

        if (ch == ' ' || ch == '\t') {
            if (tok_len > 0) {
                tok[tok_len] = '\0';
                errno = 0;
                char *endp;
                long val = strtol(tok, &endp, 10);
                if (endp != tok && *endp == '\0' && errno == 0) {
                    if (size == capacity) {
                        size_t new_cap = (capacity == 0) ? 8 : capacity * 2;
                        int *tmp = realloc(list, new_cap * sizeof(int));
                        if (!tmp) { perror("realloc"); free(list); free(tok); return 0; }
                        list = tmp; capacity = new_cap;
                    }
                    list[size++] = (int) val;
                }
                tok_len = 0;
            }
            continue;
        }

        /* Append character to token buffer */
        if (tok_len + 1 >= tok_cap) {
            size_t new_cap = (tok_cap == 0) ? 32 : tok_cap * 2;
            char *tmp = realloc(tok, new_cap);
            if (!tmp) { perror("realloc"); free(list); free(tok); return 0; }
            tok = tmp; tok_cap = new_cap;
        }
        tok[tok_len++] = (char)ch;
    }

    /* Handle token if input ended with EOF (not Enter) */
    if (ch == EOF && tok_len > 0) {
        tok[tok_len] = '\0';
        errno = 0;
        char *endp;
        long val = strtol(tok, &endp, 10);
        if (endp != tok && *endp == '\0' && errno == 0) {
            if (size == capacity) {
                size_t new_cap = (capacity == 0) ? 8 : capacity * 2;
                int *tmp = realloc(list, new_cap * sizeof(int));
                if (!tmp) { perror("realloc"); free(list); free(tok); return 0; }
                list = tmp; capacity = new_cap;
            }
            list[size++] = (int) val;
        }
    }

    free(tok);
    *out_list = list;
    return size;
}


/* -----------------------------
   Main program
   ----------------------------- */
int main(void) {
    int *numbers = NULL;

    printf("Input integers. Press Enter alone to end input immediately.\n");

    size_t count = read_ints_until_enter(&numbers);

    printf("\nStored %zu integer(s):\n", count);
    for (size_t i = 0; i < count; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    free(numbers);
    return 0;
}
