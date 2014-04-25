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

#define SIZE 100000
static int *buffer = NULL;
static int cached = 3;

static int init_world(int n) {
    buffer = calloc((n + 1), sizeof(int));
    assert(buffer);
    buffer[0] = 0;
    buffer[1] = 1;
    buffer[2] = 2;
    buffer[3] = 4;
    return 0;
}

static int tear_down_world() {
    free(buffer);
    return 0;
}

static long long int solve(int d) {
    assert(d >= 0 && d <= SIZE);
    if (d <= cached) {
        return buffer[d];
    }

    long long int result = 0;
    for (int i = cached + 1; i <= d; ++i) {
        result = (buffer[i - 1] + buffer[i - 2] + buffer[i - 3]) % 1000000007;
        buffer[i] = result;
    }

    cached = d;
    return result;
}

int main(int argc, char *argv[])
{
    init_world(SIZE);
    int n = read_int();
    for (int i = 0; i < n; ++i) {
        printf("%lld\n", solve(read_int()));
    }
    tear_down_world();
    return 0;
}
