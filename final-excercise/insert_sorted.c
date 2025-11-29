#include <stdio.h>
#include <stdlib.h>

/*
 * Insert 'value' into a dynamically allocated sorted list.
 * arr      : pointer to the dynamic array pointer
 * size     : pointer to current element count
 * capacity : pointer to current allocated size
 */
void insert_sorted(int **arr, int *size, int *capacity, int value) {

    // ---------- Grow array if needed ----------
    if (*size == *capacity) {
        int new_capacity = (*capacity == 0) ? 4 : (*capacity * 2);
        int *new_arr = realloc(*arr, new_capacity * sizeof(int));
        if (!new_arr) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(1);
        }
        *arr = new_arr;
        *capacity = new_capacity;
    }

    int *a = *arr;

    // ---------- Binary search for insertion point: O(log n) ----------
    int left = 0, right = *size - 1, pos = *size;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (a[mid] < value)
            left = mid + 1;
        else {
            pos = mid;
            right = mid - 1;
        }
    }

    // ---------- Shift elements: O(n) ----------
    for (int i = *size; i > pos; i--) {
        a[i] = a[i - 1];
    }

    // ---------- Insert ----------
    a[pos] = value;
    (*size)++;
}

int main() {
    int *arr = NULL;
    int size = 0;
    int capacity = 0;

    int x;
    printf("Enter integers (Ctrl+D to end):\n");

    while (scanf("%d", &x) == 1) {
        insert_sorted(&arr, &size, &capacity, x);

        // Print sorted list
        printf("List: ");
        for (int i = 0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\n");
    }

    free(arr);
    return 0;
}
