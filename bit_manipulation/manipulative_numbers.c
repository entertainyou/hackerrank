#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COUNT 100
static int read_int() {
    int ret;
    scanf("%d", &ret);
    return ret;
}

/* caller should free the memory */
static int *read_int_array(int n) {
    int *ret = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", ret + i);
    }
    return ret;
}

static int intcomp(const void *v1, const void *v2) {
    return *(const int *)v1 - *(const int *)v2;
}

/* array is sorted */
static int solve_internal(int *array, int n) {
    int mask = 0x7fffffff;
    int larger[MAX_COUNT], larger_count, smaller_count, previous = 0;
    int result = 31;

    while (result != 0) {
        /* printf("mask: %08x result: %d K: %d\n", mask, result, mask + 1); */
        memset(larger, 0, sizeof(larger));
        larger_count = 0;
        smaller_count = 0;
        previous = 0;
        for (int i = 0; i < n; ++i) {
            if (!(array[i] & ~mask)) {
                /* printf("SMALL: %d\n", array[i]); */
                smaller_count ++;
            } else {
                int high_part = array[i] & ~mask;
                if (previous == high_part) {
                    larger[larger_count - 1] ++;
                } else {
                    larger[larger_count]++;
                    larger_count ++;
                    previous = high_part;
                }
                /* printf("UPDATE LARGE count: %d\n", larger_count); */
                /* for (int j = 0; j < larger_count; ++j) { */
                /*     printf("UPDATE LARGE: %d val: %d\n", larger[j], array[i]); */
                /* } */
            }
        }

        /* printf("smaller_count: %d\n", smaller_count); */
        /* if (smaller_count == n / 2) { */
        /*     return result; */
        /* } else */
        if (smaller_count > n / 2) {
            /* do nothing */
        } else {
            int pair_in_high_count = -1;
            /* for (int i = 0; i < larger_count; ++i) { */
            /*     printf("LARGE: %d\n", larger[i]); */
            /* } */

            for (int i = 0; i < larger_count; ++i) {
                if (larger[i] > (n - smaller_count) / 2) {
                    pair_in_high_count = 2 * (n - smaller_count - larger[i]);
                    break;
                }
            }

            /* printf("pair_in_high_count 1: %d\n", pair_in_high_count); */
            if (pair_in_high_count == -1) {
                pair_in_high_count = n - smaller_count;
            }
            /* printf("pair_in_high_count 2: %d\n", pair_in_high_count); */
            if (pair_in_high_count >= n - 2 * smaller_count) {
                return result;
            }
        }
        result --;
        mask = mask >> 1;
    }

    return -1;
}

static int solve(int *array, int n) {
    qsort(array, n, sizeof(int), intcomp);
    return solve_internal(array, n);
}

int main(int argc, char *argv[])
{
    int n = read_int();
    int *array = read_int_array(n);

    printf("%d\n", solve(array, n));
    free(array);
    return 0;
}
