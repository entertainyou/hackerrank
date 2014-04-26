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

struct node_info {
    int left_count, right_count, top_count;
    long long int left_weight, right_weight, top_weight;
    int val;
};

static int node_comp(const void *v1, const void *v2) {
    struct node_info *ni1 = (struct node_info *)v1;
    struct node_info *ni2 = (struct node_info *)v2;
    return ni1->val - ni2->val;
}

typedef struct _node {
    struct _node *left, *right, *parent;
    void *data;
} node;

typedef int (*comp_func)(const void *, const void *);
static node *root;
static comp_func data_comp;

static void bst_init(comp_func comp) {
    root = NULL;
    data_comp = comp;
}

static node * bst_insert(void *data, node *parent) {
    node *_node = malloc(sizeof(node));
    _node->left = NULL;
    _node->right = NULL;
    _node->parent = parent;
    _node->data = data;
    return _node;
}

static node * bst_find_insert_point(void *data, node *parent) {
    assert(parent != NULL);
    int result = data_comp(parent->data, data);
    if (result > 0) {
        /* should go to left */
        if (parent->left != NULL) {
            return bst_find_insert_point(data, parent->left);
        } else {
            parent->left = bst_insert(data, parent);
            return parent->left;
        }
    } else {
        /* go to right */
        if (parent->right != NULL) {
            return bst_find_insert_point(data, parent->right);
        } else {
            parent->right = bst_insert(data, parent);
            return parent->right;
        }
    }
}

/* return the inserted node */
static node * bst_feed(void *data) {
    if (!root) {
        root = bst_insert(data, NULL);
        return root;
    }

    return bst_find_insert_point(data, root);
}

static void bst_print_internal(node *parent) {
    assert(parent != NULL);
    const struct node_info *data = (const struct node_info *)parent->data;
    if (parent->left) {
        bst_print_internal(parent->left);
    }
    printf("%d(%d,%d,%d  %lld,%lld,%lld) ", data->val, data->left_count, data->right_count, data->top_count,
           data->left_weight, data->right_weight, data->top_weight);
    if (parent->right) {
        bst_print_internal(parent->right);
    }
}

static void bst_print() {
    printf("--------------------------------------------------\n");
    if (!root) {
        printf("EMPTY BST\n");
    } else {
        bst_print_internal(root);
        printf("\n");
    }
    printf("--------------------------------------------------\n");
}

/* TODO: free memory */
static void bst_finish() {
}

/* 0 is parent, 1 is left child, 2 is right child */
static void bst_update(node *current, int origin) {
    if (current == NULL) {
        return;
    }

    node *other_node;

    if (origin == 0) {
        other_node = current->parent;
    } else if (origin == 1) {
        other_node = current->left;
    } else if (origin == 2) {
        other_node = current->right;
    } else {
        assert(0);
    }

    struct node_info *current_node_info = current->data;
    assert(current_node_info != NULL);
    struct node_info *other_node_info = other_node->data;
    assert(other_node_info != NULL);

    /* printf("bst_update %d origin: %d\n", current_node_info->val, origin); */
    if (origin == 0) {
        current_node_info->top_count = 1 + other_node_info->top_count;
        current_node_info->top_weight = 1 + other_node_info->top_count + other_node_info->top_weight;

        if (current == other_node->left) {
            current_node_info->top_count += other_node_info->right_count;
            current_node_info->top_weight += other_node_info->right_count + other_node_info->right_weight;
        } else {
            assert(current == other_node->right);
            current_node_info->top_count += other_node_info->left_count;
            current_node_info->top_weight += other_node_info->left_count + other_node_info->left_weight;
        }

        current_node_info->top_weight %= 1000000007;
        bst_update(current->left, 0);
        bst_update(current->right, 0);
    } else if (origin == 1) {
        current_node_info->left_count = 1 + other_node_info->left_count;
        current_node_info->left_weight = 1 + other_node_info->left_count + other_node_info->left_weight;

        current_node_info->left_count += other_node_info->right_count;
        current_node_info->left_weight += other_node_info->right_count + other_node_info->right_weight;

        current_node_info->top_weight %= 1000000007;
        if (current->parent) {
            bst_update(current->parent, current->parent->left == current ? 1 : 2);
        }
        bst_update(current->right, 0);
    } else if (origin == 2) {
        current_node_info->right_count = 1 + other_node_info->left_count;
        current_node_info->right_weight = 1 + other_node_info->left_count + other_node_info->left_weight;

        /* printf("A\n"); */
        /* bst_print(); */
        /* printf("B\n"); */
        current_node_info->right_count += other_node_info->right_count;
        current_node_info->right_weight += other_node_info->right_count + other_node_info->right_weight;

        current_node_info->top_weight %= 1000000007;
        /* printf("C\n"); */
        /* bst_print(); */
        /* printf("D\n"); */

        if (current->parent) {
            bst_update(current->parent, current->parent->left == current ? 1 : 2);
        }
        bst_update(current->left, 0);
    }

    /* current_node_info->top_count = 1 + parent_node_info->top_count; */
    /* current_node_info->top_weight = 1 + parent_node_info->top_count + parent_node_info->top_weight; */

    /* if (node == parent->left) { */
    /*     current_node_info->top_count += parent_node_info->right_count; */
    /*     current_node_info->top_weight += parent_node_info->right_count + parent_node_info->right_weight; */
    /* } else { */
    /*     assert(node == parent->right); */
    /*     current_node_info->top_count += parent_node_info->left_count; */
    /*     current_node_info->top_weight += parent_node_info->left_count + parent_node_info->left_weight; */
    /* } */

    /* bst_update(node->left, 0); */
    /* bst_update(node->right, 0); */
}

int main(int argc, char *argv[]) {
    int n = read_int();
    struct node_info *node_array = calloc(n, sizeof(struct node_info));
    bst_init(node_comp);
    long long answer = 0;
    for (int i = 0; i < n; ++i) {
        node_array[i].val = read_int();
        node *_node = bst_feed(node_array + i);
        node *parent = _node->parent;
        struct node_info *current_info = _node->data;
        /* printf("ALICE\n"); */
        /* bst_print(); */
        /* update _node info */
        if (parent != NULL) {
            struct node_info *parent_info = parent->data;
            current_info->top_count = parent_info->top_count + 1;
            /* printf("BOB\n"); */
            /* bst_print(); */
            /* printf("%d %d %d\n", parent_info->top_count, 1, parent_info->top_weight); */
            current_info->top_weight = parent_info->top_count + 1 + parent_info->top_weight;
            if (_node == parent->left) {
                current_info->top_count += parent_info->right_count;
                current_info->top_weight += parent_info->right_weight + parent_info->right_count;
            } else {
                current_info->top_count += parent_info->left_count;
                current_info->top_weight += parent_info->left_weight + parent_info->left_count;
            }

            bst_update(parent, _node == parent->left ? 1 : 2);
        }
        /* bst_print(); */
        answer += (current_info->top_weight);
        answer %= 1000000007;

        /* assert(answer % 2 == 0); */
        printf("%lld\n", answer);
        /* bst_print(); */
    }

    bst_finish();
    free(node_array);
    return 0;
}
