#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "util.h"

/*
 * load_from_file - reads integers from a text file into an array
 * The first line of the file is the count, followed by one integer per line.
 */
void load_from_file(int *arr, int n, const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) { fprintf(stderr, "Could not open %s\n", filename); exit(1); }
    int count;
    fscanf(f, "%d", &count);  // read the first line (50000)
    for (int i = 0; i < n; i++)
        fscanf(f, "%d", &arr[i]);
    fclose(f);
}

/* elapsed_ms - calculates time difference between two timestamps in milliseconds */
double elapsed_ms(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) * 1000.0
        + (end.tv_nsec - start.tv_nsec) / 1e6;
}

/*
 * print_bench_header - prints the benchmark title and column header/separator rows
 */
void print_bench_header(const char *title, int n) {
    printf("=== %s BENCHMARK (n=%d) ===\n\n", title, n);
    printf("%-20s %12s %15s %15s\n", "Algorithm", "Time (ms)", "Cycles", "Operations");
    printf("%-20s %12s %15s %15s\n", "---------", "---------", "------", "----------");
}

/*
 * print_bench_row - prints one result row in the benchmark table
 */
void print_bench_row(const char *name, double ms, uint64_t cycles, long long ops) {
    printf("%-20s %12.2f %15lu %15lld\n", name, ms, cycles, ops);
}
