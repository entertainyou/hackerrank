#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

int main(int argc, char *argv[])
{
    regex_t regex;
    const char *REGEX_STRING = "hackerrank";
    regcomp(&regex, REGEX_STRING, REG_EXTENDED | REG_ICASE | REG_NOSUB);

    int n, count = 0;
    fscanf(stdin, " %d", &n);
    for (int i = 0; i < n; ++i) {
        char buffer[2048];
        fscanf(stdin, " %[^\n]", buffer);
        /* fprintf(stdout, "buffer: %s|\n", buffer); */
        if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
            count ++;
        }
    }

    printf("%d\n", count);
    return 0;
}
