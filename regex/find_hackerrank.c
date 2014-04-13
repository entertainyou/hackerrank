#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

int main(int argc, char *argv[])
{
    regex_t start_regex, end_regex;
    const char *START_REGEX_STRING = "^hackerrank",
        *END_REGEX_STRING = "hackerrank$";
    regcomp(&start_regex, START_REGEX_STRING, REG_EXTENDED);
    regcomp(&end_regex, END_REGEX_STRING, REG_EXTENDED);
    int n;

    fscanf(stdin, " %d", &n);

    for (int i = 0; i < n; ++i) {
        char buffer[2048];

        fscanf(stdin, " %[^\n]", buffer);
        int start = regexec(&start_regex, buffer, 0, NULL, 0) == 0;
        int end = regexec(&end_regex, buffer, 0, NULL, 0) == 0;

        if (start && end) {
            printf("0\n");
        } else {
            if (start) {
                printf("1\n");
            } else if (end) {
                printf("2\n");
            } else {
                printf("-1\n");
            }
        }
    }
    return 0;
}
