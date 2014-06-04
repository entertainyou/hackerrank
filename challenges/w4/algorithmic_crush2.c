#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

struct node {
    /* long long int val; */
    long long int offset;
    int start;
    int end;
};

#define PARENT(i) ((i - 1) / 2)
#define LCHILD(i) (2 * i + 1)
#define RCHILD(i) (2 * i + 2)

/* prerequire: node has start and end set */
static void init_node(struct node *nodes, int index) {
    struct node *current = nodes + index;
    int start = current->start;
    int end   = current->end;
    int lindex = LCHILD(index);
    int rindex = RCHILD(index);
    struct node *left = nodes + lindex;
    struct node *right = nodes + rindex;

    left->start  = start;
    left->end    = start + (end - start + 1) / 2 - 1;
    right->start = start + (end - start + 1) / 2;
    right->end   = end;
    if (left->start < left->end) {
        init_node(nodes, lindex);
    }

    if (right->start < right->end) {
        init_node(nodes, rindex);
    }
}

static struct node *setup(int size) {
    struct node *ret = calloc(2 * size - 1, sizeof(struct node));

    ret->start = 1;
    ret->end   = size;
    init_node(ret, 0);
    return ret;
}

static void dump(struct node *nodes, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d %d %d val: %lld\n", i, nodes[i].start, nodes[i].end, nodes[i].offset);
    }
}

/* static void child_updated(struct node *nodes, int index) { */
/*     int pindex = PARENT(index); */

/*     while (pindex != index) { */
/*         struct node* c = nodes + index; */
/*         struct node* p = nodes + pindex; */
/*         if (p->val < c->val) { */
/*             p->val = c->val; */
/*         } */

/*         index = pindex; */
/*     } */
/* } */

static void feed(struct node *nodes, int index, int start, int end, int val) {
    struct node *current = nodes + index;
    /* printf("feed index: %d c: [%d, %d] f: [%d, %d]\n", index, current->start, current->end, start, end); */
    assert(current->start <= start);
    assert(current->end   >= end);

    if (current->start == start && current->end == end) {
        /* not propagate to childs */
        current->offset += val;
        /* current->val    += val; */
        /* child_updated(nodes, index); */
        return;
    }

    /* no child! */
    if (current->start == current->end) {
        current->offset += val;
        /* current->val += val; */
        /* child_updated(nodes, index); */
        return;
    }

    int lend = current->start + (current->end - current->start + 1) / 2 - 1;


    /* the left half */
    if (start <= lend) {
        int lindex = LCHILD(index);
        int cend = end >= lend ? lend : end;
        feed(nodes, lindex, start, cend, val);
    }

    /* the right half */
    if (end > lend) {
        int rindex = RCHILD(index);
        int cstart = start >= lend + 1 ? start : lend + 1;
        feed(nodes, rindex, cstart, end, val);
    }
}

static long long int get_val(struct node *nodes, int index) {
    struct node *current = nodes + index;
    if (current->start == current->end) {
        return current->offset;
    }

    int lindex = LCHILD(index);
    int rindex = RCHILD(index);

    long long int lval = get_val(nodes, lindex);
    long long int rval = get_val(nodes, rindex);

    return current->offset + (lval > rval ? lval : rval);
}

int main(int argc, char *argv[]) {
    int n = read_int(), m = read_int();

    int size = (int)pow(2, ceil(log2(n)));
    /* printf("n %d size: %d\n", n, size); */
    struct node* nodes = setup(size);

    for (int i = 0; i < m; ++i) {
        int a = read_int(), b = read_int(), k = read_int();

        feed(nodes, 0, a, b, k);
    }
    /* dump(nodes, 2 * size - 1); */

    printf("%lld\n", get_val(nodes, 0));
    return 0;
}
