#ifndef DATASET_H
#define DATASET_H

#define DATASET_SIZE 50000  // Number of elements in sorting_data.txt

/*
 * alloc_dataset - allocates an array of DATASET_SIZE ints, loads values
 * from data/sorting_data.txt, and returns a pointer to it.
 * The caller is responsible for calling free() on the returned pointer.
 */
int *alloc_dataset(void);

#endif /* DATASET_H */
