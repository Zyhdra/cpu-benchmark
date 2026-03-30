#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

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

#endif /* UTIL_H */
