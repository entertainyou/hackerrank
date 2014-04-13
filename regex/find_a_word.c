#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

int get_match_count(const char *regexp, const char *string) {
    regex_t regex;
    int error;

    if ((error = regcomp(&regex, regexp, REG_EXTENDED))) {
        printf("error: %d\n", error);
        return -1;
    }

    regmatch_t regmatch[1];
    int index = 0, count = 0;

    while (regexec(&regex, string + index, 1, regmatch, 0) == 0) {
        index += regmatch[0].rm_so + 1;
        count ++;
    }
    regfree(&regex);
    return count;
}

int main(int argc, char *argv[]) {
    int n;
    scanf("%d\n", &n);
    char **buffers;

    buffers = malloc(sizeof(char *) * n);
    for (int i = 0; i < n; ++i) {
        buffers[i] = malloc(sizeof(char) * 1024);
        /* scanf("%s", buffers[i]); */
        fgets(buffers[i], 1024, stdin);
    }

    int t;
    scanf("%d\n", &t);
    char **needles;
    needles = malloc(sizeof(char *) * t);
    for (int i = 0; i < t; ++i) {
        char buf[1024];
        needles[i] = malloc(sizeof(char) * 1024);
        fgets(buf, 1024, stdin);

        for (char *iter = buf; *iter; iter++) {
            if (*iter == '\n') {
                *iter = '\0';
                break;
            }
        }
        snprintf(needles[i], 1024, "(\\<%s\\>)", buf);
    }

    /* printf("n = %d, t = %d BUFFER: %s NEEDLES: %s\n", n, t, buffers[0], needles[0]); */
    for (int i = 0; i < t; ++i) {
        int count = 0;
        for (int j = 0; j < n; ++j) {
            /* printf("%s %s\n", needles[i], buffers[j]); */
            count += get_match_count(needles[i], buffers[j]);
        }
        printf("%d\n", count);
    }
    return 0;
}
