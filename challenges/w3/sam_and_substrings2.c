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

static long long int power_mod(int i, int n, int m) {
    if (n == 0)
        return 1;

    long long int half = power_mod(i, n / 2, m);
    long long int result = (half * half) % m;
    int rem = n % 2;
    return rem ? (result * i) % m : result;
}

static void make_cache(long long int *cache, int size, int base, int m) {
    memset(cache, 0, size * sizeof(long long int));
    assert(size >= 1);
    cache[0] = 1;
    for (int i = 1; i < size; ++i) {
        cache[i] = (cache[i - 1] * base) % m;
    }
}

static long long int solve(const char *buffer, int mod) {
    int size = strlen(buffer);
    int *sum = calloc(size, sizeof(long long int));

    long long int sum_now = 0;
    for (int i = 0; i < size; ++i) {
        sum_now += (i + 1) * (buffer[i] - '0');
        sum_now %= mod;
        sum[size - 1 - i] = sum_now;
    }

    long long int *cache = malloc(size * sizeof(long long int));
    make_cache(cache, size, 10, mod);
    /* for (int i = 0; i < size; ++i) { */
    /*     printf("%d sum: %d cache: %d\n", i, sum[i], cache[i]); */
    /* } */

    long long int result = 0;
    for (int i = 0; i < size; ++i) {
        result += cache[i] * sum[i];
        result %= mod;
    }

    return result;
}

int main(int argc, char *argv[]) {
    char buffer[200001];
    scanf("%s", buffer);
    printf("%lld\n", solve(buffer, 1000000007));
    return 0;
}
