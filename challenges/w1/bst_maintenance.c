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
    int left_weight, right_weight, top_weight;
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
    printf("%d ", data->val);
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

/* 0 is parent, 1 is child left, 2 is child right */
static void bst_update(node *node, int origin) {
    if (node == NULL) {
        return;
    }

    if (origin == 0) {
        node *parent = node->parent;
        struct node_info *current_node_info = parent->data;
        assert(current_node_info != NULL);
        struct node_info *parent_node_info = parent->data;
        assert(parent_node_info != NULL);
        current_node_info->top_count = 1 + parent_node_info->top_count;
        current_node_info->top_weight = 1 + parent_node_info->top_count + parent_node_info->top_weight;

        if (node == parent->left) {
            current_node_info->top_count += parent_node_info->right_count;
            current_node_info->top_weight += parent_node_info->right_count + parent_node_info->right_weight;
        } else {
            assert(node == parent->right);
            current_node_info->top_count += parent_node_info->left_count;
            current_node_info->top_weight += parent_node_info->left_count + parent_node_info->left_weight;
        }

        bst_update(node->left, 0);
        bst_update(node->right, 0);
    } 
}

int main(int argc, char *argv[]) {
    int n = read_int();
    struct node_info *node_array = calloc(n, sizeof(struct node_info));
    bst_init(node_comp);
    for (int i = 0; i < n; ++i) {
        node_array[i].val = read_int();
        node * _node = bst_feed(node_array + i);
        bst_print();
    }

    bst_finish();
    free(node_array);
    return 0;
}
