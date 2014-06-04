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

static int is_palindrome(const char *s, int len) {
    /* assert(len > 0); */
    /* assert(s); */
    if (!s || len <= 0) {
        return 0;
    }
    for (const char *start = s, *end = s + len - 1; start < end; start++, end--) {
        if (*start != *end) {
            return 0;
        }
    }

    return 1;
}

static int so(const char *s, int len, int current_index) {
    /* assert(len >= 1); */
    if (len < 1) {
        return 0;
    }

    while (1) {
        if (len == 1 || len == 2) {
            return current_index;
        }

        char start = s[0];
        char end   = s[len - 1];
        if (start != end) {
            /* we have to remove either one */
            /* test [start + 1, end] */
            if (is_palindrome(s + 1, len - 1)) {
                return current_index;
            } else {
                return current_index + len - 1;
            }
        } else {
            /* return so(s + 1, len - 2, current_index + 1); */
            s ++;
            len -= 2;
            current_index ++;
        }
    }
}

static int solve(const char *s) {
    return so(s, strlen(s), 0);
}

int main(int argc, char *argv[]) {
    int t = read_int();
    /* assert(is_palindrome("aba", 3) == 1); */
    /* assert(is_palindrome("abc", 3) == 0); */
    /* assert(is_palindrome("a", 1) == 1); */
    /* assert(is_palindrome("ab", 2) == 0); */
    /* assert(is_palindrome("aa", 2) == 1); */
    /* assert(is_palindrome("abba", 4) == 1); */

    for (int i = 0; i < t; ++i) {
        char buf[100010];
        scanf(" %s", buf);
        printf("%d\n", solve(buf));
    }
    return 0;
}
