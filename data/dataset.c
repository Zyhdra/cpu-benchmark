#include <stdlib.h>
#include "../util/util.h"
#include "dataset.h"

/*
 * alloc_dataset - allocates an array of DATASET_SIZE ints, loads values
 * from data/sorting_data.txt, and returns a pointer to it.
 * The caller is responsible for calling free() on the returned pointer.
 */
int *alloc_dataset(void) {
    int *data = malloc(DATASET_SIZE * sizeof(int));
    load_from_file(data, DATASET_SIZE, "data/sorting_data.txt");
    return data;
}
