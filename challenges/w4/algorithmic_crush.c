#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limits.h"

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

int main(int argc, char *argv[]) {
    int n = read_int(), m = read_int();
    long long int *data = calloc(n, sizeof(long long int));

    long long int offset = 0;

    for (int i = 0; i < m; ++i) {
        int a = read_int(), b = read_int(), k = read_int();

        if (b - a + 1 >= n / 2) {
            offset += k;
            for (int j = 0; j < a - 1; ++j) {
                data[j] -= k;
            }

            for (int j = b; j < n; ++j) {
                data[j] -= k;
            }
        } else {
            for (int j = a - 1; j <= b - 1; ++j) {
                data[j] += k;
            }
        }
    }

    long long int max = -INT_MAX;
    for (int i = 0; i < n; ++i) {
        if (data[i] > max) {
            max = data[i];
        }
    }

    /* printf("%d\n", INT_MAX); */
    printf("%lld\n", max + offset);
    return 0;
}
