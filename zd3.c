#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#define MAX_SIZE 100000

int compare_ints(const void *a, const void *b) {
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;
    return (int_a > int_b) - (int_a < int_b);
}

bool is_sorted(int *arr, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        if (arr[i - 1] > arr[i]) return false;
    }
    return true;
}

void fill_sorted(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) arr[i] = (int)i;
}

void fill_reverse(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) arr[i] = (int)(size - i);
}

void fill_equal(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) arr[i] = 42;
}

void fill_random(int *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) arr[i] = rand();
}

void test_case(const char *desc, void (*filler)(int*, size_t), size_t size) {
    int *arr = malloc(size * sizeof(int));
    if (!arr) {
        fprintf(stderr, "Allocation failed\n");
        exit(1);
    }

    filler(arr, size);

    clock_t start = clock();
    qsort(arr, size, sizeof(int), compare_ints);
    clock_t end = clock();

    double duration = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%-20s | size: %-6zu | time: %.6fs | sorted: %s\n",
           desc, size, duration, is_sorted(arr, size) ? "yes" : "NO!");

    free(arr);
}

int main() {
    srand(time(NULL));

    size_t sizes[] = {10, 1000, 10000, 50000, 100000};
    size_t num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (size_t i = 0; i < num_sizes; ++i) {
        size_t size = sizes[i];

        test_case("Sorted",    fill_sorted,  size);
        test_case("Reversed",  fill_reverse, size);
        test_case("Equal",     fill_equal,   size);
        test_case("Random",    fill_random,  size);
    }

    return 0;
}
