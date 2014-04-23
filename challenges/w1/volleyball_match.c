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

static int valid_case(int a, int b) {
    int high = a > b ? a : b;
    int low = a + b - high;

    if (low <= 23)
        return high == 25;
    else
        return high - low == 2;
}

static long long int solve_internal(int a, int b) {
    long long int **array = malloc((a + 1) * sizeof(long long int *));
    /* assert(a <= 24 && b <= 24); */
    for (int i = 0; i < a + 1; ++i) {
        /* array[i] = malloc((b + 1) * sizeof(int)); */
        array[i] = calloc(b + 1, sizeof(long long int));
    }

    for (int i = 1; i < b + 1; ++i) {
        array[0][i] = 1;
    }

    for (int i = 1; i < a + 1; ++i) {
        array[i][0] = 1;
    }

    for (int i = 1; i < a + 1; ++i) {
        for (int j = 1; j < b + 1; ++j) {
            array[i][j] = (array[i][j - 1] + array[i - 1][j]) % 1000000007;
        }
    }

    /* for (int i = 0; i < a + 1; ++i) { */
    /*     for (int j = 0; j < b + 1; ++j) { */
    /*         /\* array[i][j] = array[i][j - 1] + array[i - 1][j]; *\/ */
    /*         printf("%4lld ", array[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    int ret = array[a][b];
    for (int i = 0; i < a + 1; ++i) {
        free(array[i]);
    }
    free(array);
    return ret;
}

static long long int solve(int a, int b) {
    if (!valid_case(a, b)) {
        return 0;
    } else {
        /* return solve_internal(a, b); */
        int low = a < b ? a : b;
        if (low >= 24) {
            /* return solve_internal(24, 24) + 2 * (low - 24); */
            long long int point = solve_internal(24, 24);
            for (int i = 0; i < low - 24; ++i) {
                point = (point * 2) % 1000000007;
            }
            return point;
        } else {
            return solve_internal(low, a + b - low - 1);
        }
    }
}

int main(int argc, char *argv[])
{
    int a = read_int(), b = read_int();
    printf("%lld\n", solve(a, b));
    return 0;
}
