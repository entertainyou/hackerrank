#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* reverse  */
int intcomp(const void *v1, const void *v2) {
    return *(const int *)v2 - *(const int *)v1;
}

/* array is a descending array */
static int find_max_length_internal(const int *array, int length, int max_diff) {
    if (length == 0) {
        return 0;
    }
    int diff = array[0] - array[length - 1];
    if (diff <= max_diff) {
        return length - ((array[length - 1] == 0 || max_diff > diff) ? 0 : 1);
        /* return length - ((array[length - 1] == 0) ? 0 : 1); */
    }

    int look_for_value = array[0] - max_diff;
    int *search = bsearch(&look_for_value, array, length, sizeof(int), intcomp);

    /* printf("SEARCH: %p look_for_value: %d\n", search, look_for_value); */
    if (!search) {
        return 0;
    }
    /* go to the rightest one */
    while (search != array + length - 1) {
        if (*(search + 1) == *search)
            search ++;
        else
            break;
    }
    /* printf("search: %p array: %p search - array %d\n", search, array, search - array); */
    return search - array;
}

/* TODO: optimize */
static int find_max_length(const int *array, int length, int max_diff) {
    int result = 0;
    assert(length != 0);
    for (int i = 0; i < length - max_diff; ++i) {
        int temp = find_max_length_internal(array + i, length - i, max_diff);
        if (temp != 0 && temp >= result)
            result = temp;
    }
    return result;
}

static int solve(int k, const char *string1, const char *string2) {
    int len = strlen(string1);
    assert(len == strlen(string2));

    if (k >= len) {
        return len;
    }

    int **M = malloc((len + 1) * sizeof(int *));

    for (int i = 0; i < len + 1; i++) {
        /* M[] */
        M[i] = calloc(len + 1, sizeof(int));
    }

    for (int i = len - 1; i >= 0; --i) {
        for (int j = len - 1; j >= 0; --j) {
            int equal = string1[i] == string2[j];
            M[i][j] = M[i + 1][j + 1] + (equal ? 0 : 1);
            /* M[i][j] = (equal ? 0 : 1); */
        }
    }

    /* for (int i = 0; i < len; ++i) { */
    /*     for (int j = 0; j < len; ++j) { */
    /*         printf("%d ", M[i][j]); */
    /*     } */
    /*     printf("\n"); */
    /* } */

    /* printf("K = %d len = %d\n", k, len); */
    int result = -1, found = 0;
    int *found_array = malloc((len + 1) * sizeof(int *));
    int found_count = 0;
    for (int i = 0; i < len; ++i) {
        for (int j = 0; j < len - i; ++j) {
            /* printf("INDEX %d %d\n", j, i + j); */
            found_array[j] = M[j][i + j];
        }
        found_count = len - i;
        /* printf("I %d\n", i); */
        /* for (int l = 0; l < found_count; ++l) { */
        /*     printf("%d ", found_array[l]); */
        /* } */
        /* printf("\n"); */

        int temp = find_max_length(found_array, found_count, k);
        /* printf("FIRST I: %d temp %d\n", i, temp); */
        if (temp != -1) {
            found = 1;
            if (temp > result)
                result = temp;
        }
    }

    for (int i = 1; i < len; ++i) {
        for (int j = i; j < len; ++j) {
            /* printf("INDEX %d %d\n", j, i + j); */
            found_array[j - i] = M[j][j - i];
        }
        found_count = len - i;

        /* printf("I %d\n", i); */
        /* for (int l = 0; l < found_count; ++l) { */
        /*     printf("%d ", found_array[l]); */
        /* } */
        /* printf("\n"); */
        int temp = find_max_length(found_array, found_count, k);
        /* printf("SECOND I: %d temp %d\n", i, temp); */
        if (temp != 0) {
            found = 1;
            if (temp > result)
                result = temp;
        }
    }
    if (!found) {
        result = -1;
    }
    return result;
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char string1[1501], string2[1501];
        int k;
        scanf("%d %s %s", &k, string1, string2);
        printf("%d\n", solve(k, string1, string2));
    }
    return 0;
}
