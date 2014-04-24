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

typedef char CHUNK;

struct bits {
    CHUNK *bit;
    /* should not change after first set */
    int n;
};

static void set_bit(struct bits *number, int idx, int x) {
    int section = idx / sizeof(CHUNK);
    int position_in_section = idx % sizeof(CHUNK);

    int val = number->bit[section];
    val &= ~(1 << position_in_section);
    if (x == 1) {
        val |= (1 << position_in_section);
    }
    number->bit[section] = val;
}

static int get_bit(struct bits *number, int idx) {
    int section = idx / sizeof(CHUNK);
    int position_in_section = idx % sizeof(CHUNK);

    int val = number->bit[section];
    return (val >> position_in_section) & 1;
}

int main(int argc, char *argv[])
{
    int n = read_int(), q = read_int();
    char a[100001], b[100001];

    scanf(" %s", a);
    scanf(" %s", b);

    for (int i = 0; i < q; ++i) {
        char cmd[20];
        int idx, x;

        scanf(" %s %d %d", cmd, &idx, &x);
    }
    return 0;
}
