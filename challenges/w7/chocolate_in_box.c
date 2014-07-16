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

static int nim_sum(int *array, int n, int op) {
    int result = op;
    for (int i = 0; i < n; ++i) {
        result ^= array[i];
    }

    return result;
}

static int solve(int *array, int n) {
    int ns = nim_sum(array, n, 0);

    if (ns == 0)
        return 0;

    int result = 0;
    for (int i = 0; i < n; ++i) {
        int ns_i = nim_sum(array + i, 1, ns);
        if (ns_i < array[i]) {
            result ++;
        }
    }

    assert(result >= 1);
    return result;
}

int main(int argc, char *argv[]) {
    int n = read_int();
    int *array = read_int_array(n);

    printf("%d\n", solve(array, n));
    return 0;
}
