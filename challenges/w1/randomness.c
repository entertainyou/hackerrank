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

#define MAX_SIZE 75000

static char buffer[MAX_SIZE + 1];
static char *suffixes[MAX_SIZE];
static int suffix_count;

static void init(char *string, int n) {
    suffix_count = n;
    for (int i = 0; i < n; ++i) {
        suffixes[i] = string + i;
    }
}

static int charp_cmp(const void *v1, const void *v2) {
    const char *p1 = *(const char **)v1;
    const char *p2 = *(const char **)v2;
    return strcmp(p1, p2);
}

static int get_count(const char *s1, const char *s2) {
    char *iter1, *iter2;
    for (iter1 = s1, iter2 = s2; *iter1 && *iter2; ++iter1, ++iter2) {
        if (*iter1 != *iter2)
            break;
    }

    assert((*iter1 || *iter2));
    return buffer + suffix_count - iter2;
}

static void handle_cmd(int idx, char ch) {
    buffer[idx] = ch;
    qsort(suffixes, suffix_count, sizeof(char *), charp_cmp);

    /* for (int i = 0; i < suffix_count; ++i) { */
    /*     printf("%s\n", suffixes[i]); */
    /* } */
    /* int result = 1; */
    long long int result = buffer + suffix_count - suffixes[0];
    for (int i = 0; i < suffix_count - 1; ++i) {
        result += get_count(suffixes[i], suffixes[i + 1]);
        /* printf("result: %d\n", result); */
    }
    /* return result; */
    printf("%lld\n", result);
}

int main(int argc, char *argv[])
{
    int n = read_int(), q = read_int();
    scanf(" %s", buffer);

    init(buffer, n);

    for (int i = 0; i < q; ++i) {
        int a;
        char c;
        scanf("%d %c", &a, &c);

        handle_cmd(a - 1, c);
    }
    return 0;
}
