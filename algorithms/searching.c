#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../util/util.h"
#include "../data/dataset.h"

static long long linear_ops = 0;
void linear_search(int *arr, int n, int target) {
    for (int i = 0; i < n; i++) {
        linear_ops++;
        if (arr[i] == target) return;  // found target
    }
}

static long long binary_ops = 0;
void binary_search(int *arr, int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        binary_ops++;
        if (arr[mid] == target) return;  // found target
        else if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
}