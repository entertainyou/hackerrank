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

#define MIN(a, b) (a < b ? a : b)
#define MAX(a, b) (a > b ? a : b)

/* long long int factorial(int n) { */
/*     return (n <= 1) ? 1 : factorial(n - 1) * n; */
/* } */

/* long long int comb(int n, int r){ */
/*     return factorial(n) / (factorial(n - r) * factorial(r)); */
/* } */

#define MOD 1000000009

static void build_factorial_cache(long long int *result, int size) {
    assert(size >= 1);
    result[0] = 0;
    result[1] = 1;

    for (int i = 2; i <= size; ++i) {
        result[i] = result[i - 1] * i;
        result[i] %= MOD;
        /* printf("FACT CACHE i: %d val: %lld prev: %lld\n", i, result[i], result[i - 1]); */
    }
}

static long long int power_mod(int i, long long int n, int m) {
    if (n == 0)
        return 1;

    long long int half = power_mod(i, n / 2, m);
    long long int result = (half * half) % m;
    int rem = n % 2;
    return rem ? (result * i) % m : result;
}

static long long int power_mod2(long long int i, long long int n, int m) {
    long long int res = 1;
    while (n)
    {
        if (n & 1) {
            res = (res * i) % m;
        }

        i = (i * i) % m;
        n >>= 1;
    }

    return res;
}

static void build_power_mod_cache(long long int *result, int size) {
    assert(size >= 1);
    result[0] = 0;
    result[1] = 1;
    for (int i = 2; i <= size; ++i) {
        result[i] = power_mod2(i, MOD - 2, MOD);
    }
}

static long long int C(long long int *fac, int i, int j, long long int *ccache, long long int *pm_cache, int pm_cache_size) {
    long long int result = 0;
    if (j != 1) {
        /* assert(prev_j + 1 == j); */
        if (i - j < j) {
            /* use previous result */
            result = ccache[i - j];
        } else {
            result = ccache[j - 1] * (i - j + 1);
            result %= MOD;
            assert(j <= pm_cache_size);
            result *= pm_cache[j];
            result %= MOD;
        }
    } else {
        /* printf("J %d\n", j); */
        /* assert(j == 1); */
        result = i;
    }

    ccache[j] = result;
    return result;
}

static void build_bst_number_cache(long long int *result, int size) {
    assert(size >= 2);

    result[0] = 1;
    result[1] = 1;

    for (int i = 2; i <= size; ++i) {
        result[i] = 0;
        for (int k = 1; k <= i; ++k) {
            result[i] += result[k - 1] * result[i - k];
            result[i] %= MOD;
        }
    }
}

static void build_cache(long long int *result, int size) {
    assert(size >= 1);

    result[0] = 1;
    long long int *bst = malloc((size + 1) * sizeof(long long int));
    build_bst_number_cache(bst, size);

    long long int *fac = malloc((size + 1) * sizeof(long long int));
    build_factorial_cache(fac, size);

    long long int *ccache = malloc((size + 1) * sizeof(long long int));
    ccache[0] = 1;

    long long int *power_mod_cache = malloc(((size + 1) / 2 + 1) * sizeof(long long int));
    build_power_mod_cache(power_mod_cache, (size + 1) / 2);
    /* for (int i = 1; i <= size; ++i) { */
    /*     printf("BST: %d %lld ratio: %f\n", i, bst[i], bst[i] * 1.0 / bst[i - 1]); */
    /* } */
    for (int i = 1; i <= size; ++i) {
        result[i] = 0;
        /* j size */
        for (int j = 1; j <= i; ++j) {
            result[i] += C(fac, i, j, ccache, power_mod_cache, (size + 1) / 2) * bst[j];
            result[i] %= MOD;
        }
    }
}

static long long int solve(long long int *cache, int n) {
    return cache[n];
}

int main(int argc, char *argv[]) {

    int size = 5000;
    long long int *cache = malloc((size + 1) * sizeof(long long int));

    build_cache(cache, size);

    /* for (int i = 1; i < size; ++i) { */
    /*     printf("i: %d %lld ratio: %f\n", i, cache[i], cache[i] * 1.0 / cache[i - 1]); */
    /* } */
    int t = read_int();
    for (int i = 0; i < t; ++i) {
        int n = read_int();
        printf("%lld\n", solve(cache, n));
    }
    return 0;
}
