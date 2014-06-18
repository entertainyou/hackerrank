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

/* static long long int power_mod(int i, long long int n, int m) { */
/*     if (n == 0) */
/*         return 1; */

/*     long long int half = power_mod(i, n / 2, m); */
/*     long long int result = (half * half) % m; */
/*     int rem = n % 2; */
/*     return rem ? (result * i) % m : result; */
/* } */

static long long int power(int i, long long int n) {
    if (n == 0)
        return 1;

    long long int half = power(i, n / 2);
    long long int result = (half * half);
    int rem = n % 2;
    return rem ? (result * i) : result;
}

static long long int solve(int a, int b, int x) {
    if (a == 1) {
        return x == 1 ? 1 : 0;
    } else if (b >= 0) {
        long long int pow = power(a, b);
        long long int rem = pow % x;
        /* return pow - rem; */
        if (rem <= x - rem) {
            return pow - rem;
        } else {
            return pow - rem + x;
        }
    } else {
        /* b < 0 */
        return 0;
    }
}

int main(int argc, char *argv[]) {
    int t = read_int();
    for (int i = 0; i < t; ++i) {
        int a = read_int();
        int b = read_int();
        int x = read_int();
        printf("%lld\n", solve(a, b, x));
    }

    return 0;
}
