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

static long long int read_int_module(const char *buffer, long long int mod) {
    long long int result = 0;
    for (const char *iter = buffer; *iter; ++iter) {
        /* result *= 10; */
        /* result += *iter; */
        /* result %= mod; */
        /* printf("ITER: %c\n", *iter); */
        result = (10 * result + (*iter - '0')) % mod;
    }
    return result;
}

#define MODULE 1000000007

static long long int pow_module(long long int a, long long int b, long long int module) {
    /* long long int result = 1; */
    if (b == 0) {
        return 1;
    }

    int rem = b % 2;
    long long int half = pow_module(a, b / 2, module);
    long long int result = half * half % module;
    return rem ? result * a % module : result;
}

int main(int argc, char *argv[]) {
    int n = read_int();
    for (int i = 0; i < n; ++i) {
        char buffer[100001];
        scanf(" %s", buffer);
        /* printf("BUFFER1: %s\n", buffer); */
        long long int a = read_int_module(buffer, MODULE);
        scanf(" %s", buffer);
        /* printf("BUFFER2: %s\n", buffer); */
        long long int b = read_int_module(buffer, MODULE - 1);
        /* printf("A: %lld B: %lld\n", a, b); */
        printf("%lld\n", pow_module(a, b, MODULE));
    }
    return 0;
}
