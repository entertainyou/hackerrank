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

static char *A = NULL, *B = NULL, *C = NULL;
static int N = 0;

static void init(char *a, char *b, int n) {
    A = malloc(n * sizeof(char));
    B = malloc(n * sizeof(char));
    C = malloc((n + 1) * sizeof(char));
    N = n;

    /* printf("a = %s b = %s\n", a, b); */
    int previous = 0;
    for (int i = n - 1; i >= 0; --i) {
        assert(a[i] == '0' || a[i] == '1');
        assert(b[i] == '0' || b[i] == '1');
        A[n - 1 - i] = a[i] - '0';
        B[n - 1 - i] = b[i] - '0';
        C[n - 1 - i] = (A[n - 1 - i] + B[n - 1 - i] + previous) % 2;
        previous = (A[n - 1 - i] + B[n - 1 - i] + previous) / 2;
    }

    C[n] = previous;

    /* for (int i = 0; i < n; i++) { */
    /*     printf("%d", A[i]); */
    /* } */
    /* printf("\n"); */

    /* for (int i = 0; i < n; i++) { */
    /*     printf("%d", B[i]); */
    /* } */
    /* printf("\n"); */

    /* for (int i = 0; i < n + 1; i++) { */
    /*     printf("%d", C[i]); */
    /* } */
    /* printf("\n"); */
}

/* the idx has added x */
static void c_op(int idx, int x) {
    /* for (int i = idx; i < N + 1; ++i) { */
    /* } */
    assert(x >= -1 && x <= 1);
    if (x == 0) {
        return;
    }
    int current = C[idx];
    if (x == 1) {
        if (current == 1) {
            C[idx] = 0;
            c_op(idx + 1, 1);
        } else {
            C[idx] = 1;
        }
    } else {
        if (current == 1) {
            C[idx] = 0;
        } else {
            C[idx] = 1;
            c_op(idx + 1, -1);
        }
    }
}

static void handle_cmd(char *cmd, int idx, int x) {
    /* printf("idx: %d x: %d\n", idx, x); */
    /* assert(idx < N + 1 && (x == 0 || x == 1)); */
    if (strcmp(cmd, "set_a") == 0) {
        int previous = A[idx];
        A[idx] = x;
        c_op(idx, x - previous);
    } else if (strcmp(cmd, "set_b") == 0) {
        int previous = B[idx];
        B[idx] = x;
        c_op(idx, x - previous);
    } else if (strcmp(cmd, "get_c") == 0) {
        /* printf("RESULT: %d\n", C[idx]); */
        printf("%d", C[idx]);
    }

    /* for (int i = 0; i < N; i++) { */
    /*     printf("%d", A[i]); */
    /* } */
    /* printf("\n"); */

    /* for (int i = 0; i < N; i++) { */
    /*     printf("%d", B[i]); */
    /* } */
    /* printf("\n"); */

    /* for (int i = 0; i < N + 1; i++) { */
    /*     printf("%d", C[i]); */
    /* } */
    /* printf("\n"); */
}

static void finish() {
    free(A);
    free(B);
    free(C);
}

int main(int argc, char *argv[])
{
    int n = read_int(), q = read_int();
    char a[100001], b[100001];

    scanf(" %s", a);
    scanf(" %s", b);

    init(a, b, n);
    for (int i = 0; i < q; ++i) {
        char cmd[20];
        int idx, x;

        scanf(" %s %d %d", cmd, &idx, &x);
        /* idx = n - 1 - idx; */
        /* printf("%s %d %d\n", cmd, idx, x); */
        handle_cmd(cmd, idx, x);
    }
    finish();
    return 0;
}
