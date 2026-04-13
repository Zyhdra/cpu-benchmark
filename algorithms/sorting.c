#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../util/util.h"
#include "../data/dataset.h"

/*
 * bubble_sort - O(n^2) sorting algorithm
 * Repeatedly steps through the array, compares adjacent elements,
 * and swaps them if they are in the wrong order.
 * Very slow for large arrays — included to show worst-case performance.
 * Returns the total number of comparisons + swaps performed.
 */
long long bubble_sort(int* arr, int n) {
    long long ops = 0;
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) {
            ops++;  // count each comparison
            if (arr[j] > arr[j + 1]) {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                ops++;  // count each swap
            }
        }
    return ops;
}

/*
 * merge - helper for merge_sort
 * Merges two sorted halves of an array back into one sorted array.
 * Allocates temporary arrays for the two halves, then merges them
 * back in sorted order.
 */
static long long merge_ops = 0;  // global op counter for merge sort

void merge(int* arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;

    int* L = malloc(n1 * sizeof(int));
    int* R = malloc(n2 * sizeof(int));
    memcpy(L, arr + l, n1 * sizeof(int));
    memcpy(R, arr + m + 1, n2 * sizeof(int));

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        merge_ops++;  // count each comparison
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }

    while (i < n1) {
        arr[k++] = L[i++];
        merge_ops++;
    }

    while (j < n2) {
        arr[k++] = R[j++];
        merge_ops++;
    }

    free(L);
    free(R);
}

/*
 * merge_sort - O(n log n) divide and conquer sorting algorithm
 * Recursively splits the array in half, sorts each half,
 * then merges them back together in sorted order.
 */
void merge_sort(int* arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

/*
 * partition - helper for quick_sort
 * Picks the last element as the pivot and rearranges the array so
 * all elements smaller than the pivot come before it, and all
 * elements greater come after it.
 * Returns the final position of the pivot.
 */
static long long quick_ops = 0;  // global op counter for quick sort

int partition(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        quick_ops++;  // count each comparison
        if (arr[j] <= pivot) {
            int tmp = arr[++i];
            arr[i] = arr[j];
            arr[j] = tmp;
            quick_ops++;  // count each swap
        }
    }

    int tmp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = tmp;

    return i + 1;
}

/*
 * quick_sort - O(n log n) average case sorting algorithm
 * Picks a pivot element and partitions the array around it,
 * then recursively sorts the sub-arrays on each side.
 */
void quick_sort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

/*
 * linear_search - O(n) search algorithm
 * Scans the array from left to right until target is found.
 * Returns the index if found, otherwise returns -1.
 * ops counts the number of comparisons made.
 */
int linear_search(int* arr, int n, int target, long long* ops) {
    *ops = 0;

    for (int i = 0; i < n; i++) {
        (*ops)++;  // count each comparison
        if (arr[i] == target) {
            return i;
        }
    }

    return -1;
}

/*
 * binary_search - O(log n) search algorithm
 * Works only on a sorted array.
 * Repeatedly checks the middle element and cuts the search range in half.
 * Returns the index if found, otherwise returns -1.
 * ops counts the number of comparisons made.
 */
int binary_search(int* arr, int n, int target, long long* ops) {
    *ops = 0;

    int left = 0;
    int right = n - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        (*ops)++;  // count comparing arr[mid] to target

        if (arr[mid] == target) {
            return mid;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return -1;
}

int main(void) {
    int* original = alloc_dataset();
    int* arr = malloc(DATASET_SIZE * sizeof(int));
    int* sorted_arr = malloc(DATASET_SIZE * sizeof(int));

    struct timespec t0, t1;
    uint64_t c0, c1;

    long long search_ops;
    int target;
    int found_index;

    /*
     * Pick a target that is guaranteed to exist in the dataset.
     * Using the middle element from the original dataset is a simple choice.
     */
    target = original[DATASET_SIZE / 2];

    print_bench_header("SORTING + SEARCHING", DATASET_SIZE);

    // --- Bubble Sort ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    long long bops = bubble_sort(arr, DATASET_SIZE);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    print_bench_row("Bubble Sort", elapsed_ms(t0, t1), c1 - c0, bops);

    // --- Merge Sort ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    merge_ops = 0;
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    merge_sort(arr, 0, DATASET_SIZE - 1);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    print_bench_row("Merge Sort", elapsed_ms(t0, t1), c1 - c0, merge_ops);

    // --- Quick Sort ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    quick_ops = 0;
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    quick_sort(arr, 0, DATASET_SIZE - 1);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    print_bench_row("Quick Sort", elapsed_ms(t0, t1), c1 - c0, quick_ops);

    // --- Linear Search ---
    memcpy(arr, original, DATASET_SIZE * sizeof(int));
    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    found_index = linear_search(arr, DATASET_SIZE, target, &search_ops);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    print_bench_row("Linear Search", elapsed_ms(t0, t1), c1 - c0, search_ops);

    // --- Binary Search ---
    /*
     * Binary search requires a sorted array.
     * We sort a copy first, but do NOT include that sorting time in the
     * binary search benchmark, since we only want to measure the search itself.
     */
    memcpy(sorted_arr, original, DATASET_SIZE * sizeof(int));
    quick_sort(sorted_arr, 0, DATASET_SIZE - 1);

    c0 = rdtsc();
    clock_gettime(CLOCK_MONOTONIC, &t0);
    found_index = binary_search(sorted_arr, DATASET_SIZE, target, &search_ops);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    c1 = rdtsc();
    print_bench_row("Binary Search", elapsed_ms(t0, t1), c1 - c0, search_ops);


    free(original);
    free(arr);
    free(sorted_arr);
    return 0;
}