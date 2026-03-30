#include <stdio.h>
#include <stdlib.h>
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
