#define _POSIX_C_SOURCE 199309L

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "math.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

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

#define MOD 1000000007

static int gcd(int x, int y) {
    if (x == 0 || y == 0) {
        return x + y;
    }

    int rem = x % y;
    x = y;
    y = rem;
    return gcd(x, y);
}

#define PRIME_COUNT 400000

struct prime_info {
    int value;
    long long int count;
};

static long long int power_mod(int i, int n, int m) {
    if (n == 0)
        return 1;

    long long int half = power_mod(i, n / 2, m);
    long long int result = (half * half) % m;
    int rem = n % 2;
    return rem ? (result * i) % m : result;
}

/* note: left should not be used */
static int prime(int n, int m, struct prime_info *primes, int *size, long long int *value, int *left, int mod) {
    long long int result = 1;
    int nn = n;
    for (int i = 0; i < *size; ++i) {
        if (nn % primes[i].value == 0) {
            int base = 0;
            int mul = m / primes[i].value;
            while (nn % primes[i].value == 0) {
                nn /= primes[i].value;
                base += mul;
                mul /= primes[i].value;
            }

            /* result *= power_mod(primes[i].value, base, mod); */
            /* result %= mod; */
            /* printf("Add %d for %d count: %lld n: %d\n", base, primes[i].value, primes[i].count, n); */
            assert(primes[i].count >= 0);
            /* assert(primes[i].count < 0); */
            primes[i].count += base;
            if (nn == 1) {
                /* return */
                *value = result;
                *left = 1;
                return 0;
            }
        }
    }

    /* insert */
    /* printf("INSERT %d at pos %d\n", n, *size); */
    /* *value = power_mod(n, m / n, mod); */
    assert(*size < PRIME_COUNT);
    primes[*size].value = n;
    primes[*size].count = m / n;
    *size += 1;
    *left = 1;
    return 1;
}

static long long int solve(int n, int m) {
    struct prime_info *primes = malloc(PRIME_COUNT * sizeof(struct prime_info));
    int prime_count = 0;
    long long int result = 1;
    for (int i = 2; i <= n; ++i) {
        long long int r;
        int left;
        prime(i, m, primes, &prime_count, &r, &left, MOD);
        /* result *= r; */
        /* result %= MOD; */
    }

    for (int i = 0; i < prime_count; ++i) {
        assert(primes[i].value > 0);
        /* printf("%d %d\n", primes[i].value, primes[i].count); */
        assert(primes[i].count >= 0);
        result *= power_mod(primes[i].value, primes[i].count, MOD);
        result %= MOD;
    }
    free(primes);
    return result;
}

static long long int solve2(int n, int m) {
    long long int result = 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            result *= gcd(i, j);
            result %= MOD;
        }
    }
    return result;
}

#define COUNT 1000000
static int primes[COUNT];
static int prime_count;

static int is_prime(int n) {
    int s = (int)floor(sqrt(n));
    for (int i = 2; i < prime_count && primes[i] <= s; ++i) {
        if (n % primes[i] == 0) {
            return 0;
        }
    }
    return 1;
}

static long long int solve3(int n, int m) {
    int low, high;
    low = MIN(n, m);
    high = MAX(n, m);

    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    prime_count = 3;
    /* build primes */
    for (int i = 1; i <= (low + 5) / 6; ++i) {
        if (is_prime(6 * i + 1)) {
            /* printf("%d %d %d\n", prime_count, i, 0); */
            primes[prime_count ++] = 6 * i + 1;
        }
        if (is_prime(6 * i + 5)) {
            /* printf("%d %d %d\n", prime_count, i, 0); */
            primes[prime_count ++] = 6 * i + 5;
        }
    }
    /* for (int i = 7; i <= low; i += 2) { */
    /*     if (is_prime(i)) { */
    /*         primes[prime_count ++] = i; */
    /*     } */
    /* } */

    /* printf("N: %d M: %d prime_count: %d\n", n, m, prime_count); */
    long long int result = 1;
    for (int i = 0; i < prime_count; ++i) {
        int prime = primes[i];
        long long int acc = prime;
        long long int nn = low, nm = high;
        long long int base = 0;
        while (nn >= acc && nm >= acc) {
            base += (nn / acc) * (nm / acc);
            acc *= prime;
        }
        result *= power_mod(prime, base, MOD);
        result %= MOD;
        /* printf("i: %d %d base: %lld\n", i, prime, base); */
    }

    return result;
}

/* static long long int solve4(int n, int m) { */
/*     int low, high; */
/*     low = MIN(n, m); */
/*     high = MAX(n, m); */

/*     int *array = calloc(low, sizeof(int)); */
/*     int *primes = malloc((low / 2) * sizeof(int)); */
/*     int prime_count = 1; */
/*     primes[0] = 2; */

/*     for (int i = 2; i < low; ++i) { */
/*         if (array[i] == 0) { */
/*             /\* prime *\/ */
/*             return 0; */
/*         } */
/*     } */

/*     return 1; */
/* } */

static int do_int(int comp_start, int *a, int *b, int size) {
    /* printf("do_int comp_start: %d size: %d a: %p b: %p\n", comp_start, size, a, b); */
    /* printf("BEFORE\n"); */
    /* printf("A\n"); */
    /* for (int i = 0; i < size; ++i) { */
    /*     printf("%d %d\n", i, a[i]); */
    /* } */
    /* printf("B\n"); */
    /* for (int i = 0; i < size; ++i) { */
    /*     printf("%d %d\n", i, b[i]); */
    /* } */

    int index = 0;
    /* b[0] = a[0]; */

    /* for (int i = 0; i <= comp_start; ++i) { */
    /*     b[i] = a[i]; */
    /* } */
    memcpy(b, a, (comp_start + 1) * sizeof(int));
    index = comp_start + 1;
    for (int i = comp_start + 1; i < size; ++i) {
        if (a[i] % a[comp_start] != 0) {
            b[index ++] = a[i];
        }
    }

    /* printf("AFTER size: %d index: %d\n", size, index); */
    /* printf("A\n"); */
    /* for (int i = 0; i < size; ++i) { */
    /*     printf("%d %d\n", i, a[i]); */
    /* } */
    /* printf("B\n"); */
    /* for (int i = 0; i < index; ++i) { */
    /*     printf("%d %d\n", i, b[i]); */
    /* } */
    return index;
}

static long long int fill_primes(int **primes, int size) {
    int **a, **b;
    int *A = malloc(size * sizeof(int));
    int *B = malloc(size * sizeof(int));

    a = &A;
    b = &B;
    for (int i = 2; i <= size; ++i) {
        (*a)[i - 2] = i;
    }

    int start = 2, index = 0;
    int _size = size - 1;
    int limit = (int)floor(sqrt(size));
    while (start <= limit) {
        /* printf("start %d size: %d limit: %d\n", start, size, limit); */
        int count = do_int(index, *a, *b, _size);
        /* memcpy(a, b, count * sizeof(int)); */
        /* exchange a and b */
        int **temp = a;
        a = b;
        b = temp;
        /* printf("WHILE a: %p b: %p\n", *a, *b); */
        index ++;
        start = (*a)[index];
        _size = count;
    }

    *primes = *a;
    /* printf("A: %p B: %p a: %p b: %p\n", A, B, *a, *b); */
    free(*b);
    return _size;
}

static long long int solve4(int n, int m) {
    int low, high;
    low = MIN(n, m);
    high = MAX(n, m);
    int *primes;
    int prime_count = fill_primes(&primes, low);

    /* printf("count: %d primes: %p\n", prime_count, primes); */
    /* for (int i = 0; i < prime_count; ++i) { */
    /*     printf("%d\n", primes[i]); */
    /* } */

    long long int result = 1;
    for (int i = 0; i < prime_count; ++i) {
        int prime = primes[i];
        long long int acc = prime;
        long long int nn = low, nm = high;
        long long int base = 0;
        while (nn >= acc && nm >= acc) {
            base += (nn / acc) * (nm / acc);
            acc *= prime;
        }
        result *= power_mod(prime, base, MOD);
        result %= MOD;
        /* printf("i: %d %d base: %lld\n", i, prime, base); */
    }

    free(primes);
    return result;
}

static double timespec_diff(struct timespec *t1, struct timespec *t2) {
    return (t2->tv_sec - t1->tv_sec) + (t2->tv_nsec - t1->tv_nsec) / 1000000000.0;
}

static long long int solve5(int n, int m) {
    int low, high;
    low = MIN(n, m);
    high = MAX(n, m);

    int *sieve = calloc((low + 1), sizeof(int));

    for (int j = 2; j <= low / 2; ++j) {
        sieve[2 * j] = 1;
    }

    for (int i = 3; i <= (int)floor(sqrt(low)); i += 2) {
        if (sieve[i] == 0) {
            for (int j = 2; j <= low / i; ++j) {
                sieve[i * j] = 1;
            }
        }
    }

    /* for (int i = 1; i <= low; ++i) { */
    /*     if (sieve[i] == 0) { */
    /*         printf("I: %d\n", i); */
    /*     } */
    /* } */
    /* return 0; */

    long long int result = 1;
    for (int i = 2; i <= low; ++i) {
        if (sieve[i] != 0) {
            continue;
        }
        int prime = i;
        long long int acc = prime;
        long long int nn = low, nm = high;
        long long int base = 0;
        while (nn >= acc && nm >= acc) {
            base += (nn / acc) * (nm / acc);
            acc *= prime;
        }
        result *= power_mod(prime, base, MOD);
        result %= MOD;
        /* printf("i: %d %d base: %lld\n", i, prime, base); */
    }
    return result;
}

int main(int argc, char *argv[]) {
    /* assert(gcd(10, 5) == 5); */
    /* assert(gcd(42, 24) == 6); */

    /* for (int i = 1; i < 20; ++i) { */
    /*     for (int j = 1; j < 30; ++j) { */
    /*         printf("TEST %d %d %lld %lld %lld\n", i, j, solve3(i, j), solve4(i, j), solve5(i, j)); */
    /*         assert(solve3(i, j) == solve5(i, j)); */
    /*         assert(solve4(i, j) == solve5(i, j)); */
    /*     } */
    /* } */

    int n = read_int(), m = read_int();

    printf("%lld\n", solve5(n, m));
    /* struct timespec start, end; */
    /* clock_gettime(CLOCK_REALTIME, &start); */
    /* printf("%lld\n", solve3(n, m)); */
    /* clock_gettime(CLOCK_REALTIME, &end); */
    /* printf("3 took %f secs\n", timespec_diff(&start, &end)); */

    /* clock_gettime(CLOCK_REALTIME, &start); */
    /* printf("%lld\n", solve4(n, m)); */
    /* clock_gettime(CLOCK_REALTIME, &end); */
    /* printf("4 took %f secs\n", timespec_diff(&start, &end)); */

    /* clock_gettime(CLOCK_REALTIME, &start); */
    /* printf("%lld\n", solve5(n, m)); */
    /* clock_gettime(CLOCK_REALTIME, &end); */
    /* printf("4 took %f secs\n", timespec_diff(&start, &end)); */

    /* solve4(4, 4); */
    /* for (int i = 10000; i < 20000; ++i) { */
    /*     for (int j = 10000; j < 20000; ++j) { */
    /*         printf("%d %d\n", i, j); */
    /*         assert(solve3(i, j) == solve4(i, j)); */
    /*     } */
    /* } */
    /* struct timespec start, end; */

    /* int base = 1000; */
    /* int mul = 2; */
    /* for (int i = 0; i < 10; ++i) { */
    /*     int cur = base * mul; */
    /*     mul *= 2; */
    /*     clock_gettime(CLOCK_REALTIME, &start); */
    /*     printf("%lld\n", solve4(cur, cur)); */
    /*     clock_gettime(CLOCK_REALTIME, &end); */

    /*     double t1 = start.tv_sec + (start.tv_nsec / 1000000000.0); */
    /*     double t2 = end.tv_sec + (end.tv_nsec / 1000000000.0); */
    /*     printf("cur: %d TIME: %f\n", cur, t2 - t1); */
    /* } */
    return 0;
}
