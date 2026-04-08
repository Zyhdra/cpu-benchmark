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
    return -ops;  // not found, return negative ops
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
    return -ops;  // not found, return negative ops
}

/*
 * get_random_value - returns a random value from the dataset
 * Picks a random index and returns the element at that position.
 */
int get_random_value(int *arr, int n) {
    return arr[rand() % n];
}

int main(void) {
    int *original = alloc_dataset();
    int *arr = malloc(DATASET_SIZE * sizeof(int));

    struct timespec t0, t1;  // wall clock timestamps
    uint64_t c0, c1;         // cycle counter timestamps

    print_bench_header("SEARCH", DATASET_SIZE);

    // --- Linear Search (Not Found) ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    long long lops = linear_search(arr, DATASET_SIZE, -1);  // search for value not in dataset
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    char lname[64];
    sprintf(lname, "Linear Search%s", lops < 0 ? " (Not Found)" : "");
    print_bench_row(lname, elapsed_ms(t0, t1), c1 - c0, llabs(lops));

    // --- Binary Search (Not Found) ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    long long bops = binary_search(arr, DATASET_SIZE, -1);  // search for value not in dataset
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    char bname[64];
    sprintf(bname, "Binary Search%s", bops < 0 ? " (Not Found)" : "");
    print_bench_row(bname, elapsed_ms(t0, t1), c1 - c0, llabs(bops));

    // --- Linear Search (Random Value) ---
    int target = get_random_value(original, DATASET_SIZE);
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    lops = linear_search(arr, DATASET_SIZE, target);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    sprintf(lname, "Linear Search (Random)%s", lops < 0 ? " (Not Found)" : "");
    print_bench_row(lname, elapsed_ms(t0, t1), c1 - c0, llabs(lops));

    // --- Binary Search (Random Value) ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    bops = binary_search(arr, DATASET_SIZE, target);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    sprintf(bname, "Binary Search (Random)%s", bops < 0 ? " (Not Found)" : "");
    print_bench_row(bname, elapsed_ms(t0, t1), c1 - c0, llabs(bops));

    free(original);
    free(arr);
    return 0;
}