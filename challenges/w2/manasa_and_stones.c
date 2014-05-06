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

int main(int argc, char *argv[]) {
    int t = read_int();

    for (int i = 0; i < t; ++i) {
        int n = read_int(), a = read_int(), b = read_int();
        int high = a > b ? a : b;
        int low = a + b - high;

        if (high != low) {
            for (int j = 0; j < n; ++j) {
                printf("%d ", (n - 1 - j) * low + j * high);
            }
            printf("\n");
        } else {
            /* high == low */
            printf("%d\n", (n - 1) * low);
        }
    }
    return 0;
}
