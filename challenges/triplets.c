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

struct info {
    int val;
    int lower_than, higher_than;
    int duplicate_pos;
};

struct val_with_index {
    int val;
    int index;
};

/* UGLY.... */
static struct val_with_index *myfind(const int *key, struct val_with_index *base, int count, int *insert_index) {
    assert(count >= 0);
    if (count == 0) {
        *insert_index = 0;
        return NULL;
    }

    int low = 0, high = count - 1;
    while (high > low + 1) {
        int half = (low + high) / 2;
        if (*key == base[half].val) {
            return base + half;
        } else if (*key > base[half].val) {
            low = half;
        } else if (*key < base[half].val) {
            high = half;
        }
    }

    if (base[high].val == *key) {
        return base + high;
    } else if (base[low].val == *key) {
        return base + low;
    } else {
        int larger = *key > base[high].val;
        int lower = *key < base[low].val;
        if (lower) {
            *insert_index = low;
        } else if (larger) {
            *insert_index = high + 1;
        } else {
            *insert_index = high;
        }
        return NULL;
    }
}

int main(int argc, char *argv[]) {
    int n = read_int();

    int *array = read_int_array(n);

    struct info *infos = malloc(n * sizeof(struct info));
    struct val_with_index *temp_array = malloc(n * sizeof(struct val_with_index));
    int temp_count = 0;
    struct val_with_index *temp_array2 = malloc(n * sizeof(struct val_with_index));
    int temp_count2 = 0;

    for (int i = 0; i < n; ++i) {
        infos[i].val = array[i];
        infos[i].lower_than = 0;
        infos[i].higher_than = 0;
        infos[i].duplicate_pos = -1;
    }

    for (int i = 0; i < n; ++i) {
        int insert_index = -1;
        struct val_with_index *loc;
        loc = myfind(&array[i], temp_array, temp_count, &insert_index);
        /* printf("LOC: %p\n", loc); */
        if (!loc) {
            memmove(temp_array + insert_index + 1, temp_array + insert_index, (temp_count - insert_index) * sizeof(struct val_with_index));
            temp_array[insert_index].val = array[i];
            temp_array[insert_index].index = i;
            temp_count ++;
        } else {
            infos[i].duplicate_pos = loc->index;
        }
        infos[i].lower_than = loc ? loc - temp_array : insert_index;
    }

    for (int i = n - 1; i >= 0; --i) {
        int insert_index = -1;
        struct val_with_index *loc;
        loc = myfind(&array[i], temp_array2, temp_count2, &insert_index);

        if (!loc) {
            memmove(temp_array2 + insert_index + 1, temp_array2 + insert_index, (temp_count2 - insert_index) * sizeof(struct val_with_index));
            temp_array2[insert_index].val = array[i];
            temp_array2[insert_index].index = i;
            temp_count2 ++;
        } else {
            infos[i].duplicate_pos = loc->index;
        }
        infos[i].higher_than = loc ? temp_count2 - (loc - temp_array2) - 1 : temp_count2 - insert_index - 1;
    }

    long long int result = 0;
    for (int i = 0; i < n; ++i) {
        result += infos[i].lower_than * infos[i].higher_than;
        if (infos[i].duplicate_pos != -1 && infos[i].duplicate_pos > i) {
            result -= infos[i].lower_than * infos[infos[i].duplicate_pos].higher_than;
        }
    }
    printf("%lld\n", result);
    free(temp_array);
    free(temp_array2);
    free(infos);
    free(array);
    return 0;
}
