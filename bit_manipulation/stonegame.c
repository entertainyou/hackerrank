#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

static int solve(int *array, int n) {
    int xored = 0;
    for (int i = 0; i < n; ++i) {
        xored ^= array[i];
    }

    /* printf("xorded %d\n", xored); */

    for (int i = 0; i < n; ++i) {
        if ()
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int n = read_int();
    int *array = read_int_array(n);

    printf("%d\n", solve(array, n));
    free(array);
    return 0;
}
