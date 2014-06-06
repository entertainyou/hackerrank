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

#define MOD 1000000009

struct node {
    long long int odd;
    long long int even;
    long long int count;
};

static long long int solve(int *array, int size, int alpha, int beta) {
    qsort(array, size, sizeof(int), intcomp);

    struct node **data = malloc(size * sizeof(struct node *));

    for (int i = 0; i < size; ++i) {
        data[i] = calloc(size, sizeof(struct node));
    }
    for (int s = 0; s <= size; ++s) {
        for (int i = 0; i < size - s; ++i) {
            /* i to i + s */
            for (int j = i; j <= i + s; ++j) {
                long long int left_count = 1, right_count = 1;
                long long int left_part_even = 0, right_part_even = 0;
                long long int left_part_odd = 0, right_part_odd = 0;

                /* left i to j */
                if (j != i) {
                    assert(i + s < size);
                    assert(i <= j - 1);
                    left_part_even = data[i][j - 1].odd;
                    left_part_odd  = data[i][j - 1].even;
                    assert(left_part_even < MOD && left_part_odd < MOD);
                    left_count = data[i][j - 1].count;
                }

                /* right j + 1 to i + s */
                if (j != i + s) {
                    assert(i + s < size);
                    assert(j + 1 <= i + s);
                    right_part_even = data[j + 1][i + s].odd;
                    right_part_odd  = data[j + 1][i + s].even;
                    assert(right_part_even < MOD && right_part_odd < MOD);
                    right_count = data[j + 1][i + s].count;
                }

                long long int count = left_count * right_count;
                count %= MOD;
                data[i][i + s].count += count;
                data[i][i + s].count %= MOD;

                long long int root = count * array[j];
                root %= MOD;
                data[i][i + s].even += root;
                data[i][i + s].even %= MOD;

                right_part_even *= left_count;
                right_part_even %= MOD;
                right_part_odd  *= left_count;
                right_part_odd  %= MOD;

                left_part_even  *= right_count;
                left_part_even  %= MOD;
                left_part_odd   *= right_count;
                left_part_odd   %= MOD;

                data[i][i + s].even += (right_part_even + left_part_even);
                data[i][i + s].even %= MOD;

                data[i][i + s].odd += (right_part_odd + left_part_odd);
                data[i][i + s].odd %= MOD;

                /* printf("J: FINAL count: %lld val: %d\n", count, array[j]); */
                /* printf("J: FINAL %d i: %d i + s: %d val: %lld %lld\n", j, i, i + s, data[i][i + s].even, data[i][i + s].odd); */
            }
            /* printf("i: %d i + s: %d val: %lld %lld count: %lld\n", i, i + s, data[i][i + s].even, data[i][i + s].odd, data[i][i + s].count); */
        }
    }
    long long int even = data[0][size - 1].even;
    long long int odd  = data[0][size - 1].odd;
    long long int val = 0;
    val += even * alpha;
    val %= MOD;
    val -= odd * beta;
    val %= MOD;
    for (int i = 0; i < size; ++i) {
        free(data[i]);
    }
    free(data);

    return (val + MOD) % MOD;
}

int main(int argc, char *argv[]) {
    int t = read_int();
    for (int i = 0; i < t; ++i) {
        int n = read_int();
        int alpha = read_int(), beta = read_int();

        int *array = read_int_array(n);

        printf("%lld\n", solve(array, n, alpha, beta));
        free(array);
    }
    return 0;
}
