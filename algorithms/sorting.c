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
long long bubble_sort(int *arr, int n) {
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

void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;

    // allocate temp arrays for left and right halves
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    memcpy(L, arr + l, n1 * sizeof(int));
    memcpy(R, arr + m + 1, n2 * sizeof(int));

    // merge the two halves back into arr
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        merge_ops++;  // count each comparison
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    // copy any remaining elements
    while (i < n1) { arr[k++] = L[i++]; merge_ops++; }
    while (j < n2) { arr[k++] = R[j++]; merge_ops++; }

    free(L); free(R);
}

/*
 * merge_sort - O(n log n) divide and conquer sorting algorithm
 * Recursively splits the array in half, sorts each half,
 * then merges them back together in sorted order.
 */
void merge_sort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;  // find midpoint (avoids integer overflow)
        merge_sort(arr, l, m);     // sort left half
        merge_sort(arr, m + 1, r); // sort right half
        merge(arr, l, m, r);       // merge the two sorted halves
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

int partition(int *arr, int low, int high) {
    int pivot = arr[high];  // use last element as pivot
    int i = low - 1;        // index of smaller element
    for (int j = low; j < high; j++) {
        quick_ops++;  // count each comparison
        if (arr[j] <= pivot) {
            // swap arr[j] with arr[i+1] to move smaller element left
            int tmp = arr[++i]; arr[i] = arr[j]; arr[j] = tmp;
            quick_ops++;  // count each swap
        }
    }
    // place pivot in its correct position
    int tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

/*
 * quick_sort - O(n log n) average case sorting algorithm
 * Picks a pivot element and partitions the array around it,
 * then recursively sorts the sub-arrays on each side.
 * Generally faster than merge sort in practice due to better cache behavior.
 */
void quick_sort(int *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);  // partition and get pivot index
        quick_sort(arr, low, pi - 1);        // sort elements before pivot
        quick_sort(arr, pi + 1, high);       // sort elements after pivot
    }
}

int main(void) {
    int *original = alloc_dataset();
    int *arr = malloc(DATASET_SIZE * sizeof(int));

    struct timespec t0, t1;  // wall clock timestamps
    uint64_t c0, c1;         // cycle counter timestamps

    print_bench_header("SORTING", DATASET_SIZE);

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

    free(original);
    free(arr);
    return 0;
}