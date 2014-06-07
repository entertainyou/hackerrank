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

#define BASE 801
static char powers[BASE][250];
static int power_nums[801];

static void build_powers() {
    powers[0][0] = '1';
    powers[0][1] = '\0';
    power_nums[0] = 1;

    for (int i = 1; i <= 800; ++i) {
        int previous = power_nums[i - 1];
        char *ppower  = powers[i - 1];
        int start_pos = previous;
        if (ppower[0] >= '5') {
            start_pos ++;
        }

        power_nums[i] = start_pos;

        char *current = powers[i];
        current[start_pos] = '\0';
        int rem = 0;
        for (int j = previous - 1; j >= 0; --j) {
            int val = (ppower[j] - '0') * 2 + rem;
            rem = val / 10;
            current[start_pos - 1] = '0' + (val % 10);
            start_pos --;
        }

        if (rem != 0) {
            /* assert(start_pos == 1); */
            current[0] = '0' + rem;
        }
    }
}

struct node {
    struct node *childs;
    char child_count;
    /* 1 if this is end */
    char end;
};

static struct node *build_node() {
    struct node *root = calloc(1, sizeof(struct node));

    for (int i = 0; i < BASE; ++i) {
        struct node *n = root;

        for (const char *iter = powers[i]; *iter; iter++) {
            if (!n->childs) {
                n->childs = calloc(10, sizeof(struct node));
                n->child_count = 10;
            }

            n = n->childs + (*iter - '0');
        }
        n->end = 1;
    }
    return root;
}

static long long int solve(char *buffer, struct node *root) {
    long long result = 0;
    for (char *iter = buffer; *iter; ++iter) {
        struct node *n = root;
        for (char *iter2 = iter; *iter2; ++iter2) {
            if (!n->childs) {
                /* previous is the end */
                break;
            } else {
                n = &n->childs[*iter2 - '0'];
                if (n->end) {
                    result++;
                }
            }
        }
    }
    return result;
}

int main(int argc, char *argv[]) {

    build_powers();

    struct node *root = build_node();

    int t = read_int();

    char buffer[100001];
    for (int i = 0; i < t; ++i) {
        scanf(" %s", buffer);
        printf("%lld\n", solve(buffer, root));
    }
    return 0;
}
