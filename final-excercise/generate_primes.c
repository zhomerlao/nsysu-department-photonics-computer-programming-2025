#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Check if a number is prime
bool is_prime(int n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;

    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }

    return true;
}

// Generate a list of the first 'count' prime numbers
int* generate_primes(int count) {
    int* primes = malloc(sizeof(int) * count);
    if (!primes) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int found = 0;
    int number = 2;

    while (found < count) {
        if (is_prime(number)) {
            primes[found] = number;
            found++;
        }
        number++;
    }

    return primes;
}

int main() {
    int n;

    printf("Enter how many prime numbers to generate: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    int* list = generate_primes(n);

    printf("Prime numbers:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    free(list);
    return 0;
}
