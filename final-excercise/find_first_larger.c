#include <stdio.h>

/*
 * Function: find_first_larger
 * ---------------------------
 * Given a sorted integer array (ascending order) and a target integer,
 * this function returns the index of the first element that is strictly
 * larger than the target.
 *
 * Behavior Summary:
 *
 *   Array               | Target | Result Index | Reason
 *   --------------------|--------|--------------|-------------------------------
 *   {1, 3, 5, 7, 9}     |   5    |      3       | arr[3] = 7 > 5
 *   {1, 3, 5, 7, 9}     |   0    |      0       | arr[0] = 1 > 0
 *   {1, 3, 5, 7, 9}     |   10   |      5       | No element > 10 → return n = 5
 *
 * Notes:
 * - If no number in the array is larger than target, returns n.
 * - Time complexity: O(log n) using binary search.
 */

int find_first_larger(int *arr, int n, int target) {
    int left = 0, right = n;  // search in [0, n)

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] > target)
            right = mid;      // candidate found, continue left side
        else
            left = mid + 1;   // all values <= target are skipped
    }

    return left;  // index of the first value > target, or n if none
}



int main() {
    int arr[] = {1, 3, 5, 7, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 5;

    int idx = find_first_larger(arr, n, target);
    printf("Index = %d\n", idx);  // Output: 3 (since arr[3] = 7 > 5)

    return 0;
}
