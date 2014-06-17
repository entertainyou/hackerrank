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

/* 0 if 0, 1 if odd, 2 is even(beside 0) */
static char **cache;

static void build_cache(int *array, int size) {
    cache = malloc((size + 1) * sizeof(char *));
    for (int i = 0; i < size + 1; ++i) {
        cache[i] = malloc(size * sizeof(char));
    }

    /* for (int i = 0; i < size + 1; ++i) { */
    /*     for (int j = 0; j < size; ++j) { */
    /*         cache[i][j] = 42; */
    /*     } */
    /* } */
    for (int i = 0; i < size; ++i) {
        cache[size][i] = 1;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < i; ++j) {
            cache[i][j] = 1;
        }
    }

    for (int j = 0; j < size; ++j) {
        for (int i = j; i >= 0; --i) {
            int result;
            /* (i + 1, j) is safe */
            if (cache[i + 1][j] == 0) {
                result = 1;
            } else if (array[i] % 2 == 0) {
                result = array[i] == 0 ? 0 : 2;
            } else {
                result = 1;
            }

            cache[i][j] = result;
        }
    }
    /* for (int i = 0; i < size + 1; ++i) { */
    /*     for (int j = 0; j < size; ++j) { */
    /*         printf("%d ", cache[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */
}

int main(int argc, char *argv[]) {
    int n = read_int();
    int *array = read_int_array(n);
    build_cache(array, n);
    int q = read_int();
    for (int i = 0; i < q; ++i) {
        int x, y;
        x = read_int();
        y = read_int();

        printf("%s\n", cache[x - 1][y - 1] == 1 ? "Odd" : "Even");
    }
    return 0;
}
