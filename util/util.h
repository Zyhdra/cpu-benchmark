#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>
#include <time.h>

/*
 * rdtsc - Read Time Stamp Counter
 * Uses an x86 assembly instruction to read the CPU's internal cycle counter.
 * Returns the number of clock cycles since the processor was last reset.
 * We use this to measure how many CPU cycles each algorithm takes.
 */
static inline uint64_t rdtsc() {
    uint32_t lo, hi;
    __asm__ __volatile__ ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((uint64_t)hi << 32) | lo;
}

/*
 * load_from_file - reads integers from a text file into an array
 * The first line of the file is the count, followed by one integer per line.
 */
void load_from_file(int *arr, int n, const char *filename);

/* elapsed_ms - calculates time difference between two timestamps in milliseconds */
double elapsed_ms(struct timespec start, struct timespec end);

/*
 * print_bench_header - prints the benchmark title and column header/separator rows
 * title: short label for the benchmark (e.g. "SORTING", "SEARCH")
 * n:     the problem size printed in the title line
 */
void print_bench_header(const char *title, int n);

/*
 * print_bench_row - prints one result row in the benchmark table
 * name:   algorithm name
 * ms:     wall-clock time in milliseconds
 * cycles: CPU cycle count from rdtsc
 * ops:    operation count reported by the algorithm
 */
void print_bench_row(const char *name, double ms, uint64_t cycles, long long ops);

#endif /* UTIL_H */
