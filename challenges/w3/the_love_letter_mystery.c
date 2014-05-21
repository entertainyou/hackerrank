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

static int solve(const char *buffer) {
    int result = 0;
    const char *start = buffer, *end = buffer;
    while (*(end + 1))
        end ++;

    while (end - start >= 1) {
        result += abs(*start - *end);
        start ++;
        end --;
    }

    return result;
}

int main(int argc, char *argv[]) {
    int t = read_int();
    char buffer[10001];
    for (int i = 0; i < t; ++i) {
        scanf(" %s", buffer);
        printf("%d\n", solve(buffer));
    }
    return 0;
}
