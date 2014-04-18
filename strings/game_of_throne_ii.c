#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int charcmp(const void *v1, const void *v2) {
    return *(const char *)v1 - *(const char *)v2;
}

const int solve(char *s) {
    size_t len = strlen(s);
    int count[26];
    /* qsort(s, len, sizeof(char), charcmp); */

    /* for (char *iter = s; *iter; ++iter) { */
    /*     int count = 1; */
    /*     while (*(iter + 1) == *iter) { */
    /*         iter ++; */
    /*         count ++; */
    /*     } */

    /*     printf("count: %d\n", count); */
    /* } */

    for (int i = 0; i < 26; ++i) {
        count[i] = 0;
    }

    for (char *iter = s; *iter; ++iter) {
        count[*iter - 'a'] ++;
    }

    size_t half = len / 2;
    for (int i = 0; i < 26; ++i) {
        count[i] /= 2;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    char buffer[100001];
    scanf("%s", buffer);

    printf("%d\n", solve(buffer));
    return 0;
}
