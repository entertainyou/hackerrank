#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct info {
    char c;
    int index;
};

static int infocmp(const void *v1, const void *v2) {
    /* return *(const char *)v1 - *(const char *)v2; */
    const struct info *i1 = (const struct info *)v1;
    const struct info *i2 = (const struct info *)v2;
    if (i1->c != i2->c) {
        return i1->c - i2->c;
    } else {
        return i1->index - i2->index;
    }
}

static int solve(char *buffer) {
    int count[26];

    /* memset */
    for (int i = 0; i < 26; ++i) {
        count[i] = 0;
    }
    /* for (int i = 0; i < 26; ++i) { */
    for (char *iter = buffer; *iter; ++iter) {
        /* char c = buffer[*]; */
        assert(*iter >= 'a' && *iter <= 'z');

        count[*iter - 'a'] ++;
    }

    for (int i = 0; i < 26; ++i) {
        int num = count[i];
        /* printf("i: %d num: %d\n", i, num); */
        assert(num % 2 == 0);
        count[i] = num / 2;
    }

    size_t len = strlen(buffer);
    size_t half = len / 2;
    assert(len % 2 == 0);

    struct info *infos = malloc(len * sizeof(struct info));
    for (size_t i = 0; i < len; ++i) {
        infos[i].c = buffer[i];
        infos[i].index = i;
    }

    /* for (int i = 0; i < len; ++i) { */
    /*     printf("SORT1: %d %c[%d]\n", i, infos[i].c, infos[i].index); */
    /* } */

    qsort(infos, len, sizeof(struct info), infocmp);

    /* for (int i = 0; i < len; ++i) { */
    /*     printf("SORT2: %d %c[%d]\n", i, infos[i].c, infos[i].index); */
    /* } */
    char *result = calloc(len + 1, sizeof(char));
    for (int index = len - 1; index >= 0;) {
        char c = infos[index].c;
        int number = count[c - 'a'];
        /* printf("c: %c %d\n", c, number); */
        /* for (int j = index - 2 * number; j < index - number; ++j) { */
        /*     result[infos[j].index] = c; */
        /* } */
        for (int j = index; j > index - number; --j) {
            result[infos[j].index] = c;
        }

        /* printf("index before: %d\n", index); */
        index -= 2 * number;
        /* printf("index after: %d\n", index); */
        /* for (int i = 0; i < len; ++i) { */
        /*     printf("%c", result[i] ? result[i] : '!'); */
        /* } */
        /* printf("\n"); */
    }

    for (int i = 0; i < len; ++i) {
        if (result[i]) {
            printf("%c", result[i]);
        }
    }
    printf("\n");
    return 0;
}

int main(int argc, char *argv[]) {
    char buffer[10001];
    scanf("%s", buffer);
    solve(buffer);
    return 0;
}
