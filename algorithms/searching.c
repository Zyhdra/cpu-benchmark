#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../util/util.h"
#include "../data/dataset.h"

long long linear_search(int *arr, int n, int target) {
    long long ops = 0;
    for (int i = 0; i < n; i++) {
        ops++;
        if (arr[i] == target) return ops;  // found target
    }
    return ops;
}

long long binary_search(int *arr, int n, int target) {
    int left = 0, right = n - 1;
    long long ops = 0;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        ops++;
        if (arr[mid] == target) return ops;  // found target
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return ops;
}

int main(void) {
    int *original = alloc_dataset();
    int *arr = malloc(DATASET_SIZE * sizeof(int));

    struct timespec t0, t1;  // wall clock timestamps
    uint64_t c0, c1;         // cycle counter timestamps

    print_bench_header("SEARCH", DATASET_SIZE);

    // --- Linear Search ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    long long lops = linear_search(arr, DATASET_SIZE, -1);  // search for value not in dataset
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    print_bench_row("Linear Search", elapsed_ms(t0, t1), c1 - c0, lops);

    // --- Binary Search ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    long long bops = binary_search(arr, DATASET_SIZE, -1);  // search for value not in dataset
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    print_bench_row("Binary Search", elapsed_ms(t0, t1), c1 - c0, bops);

    free(original);
    free(arr);
    return 0;
}