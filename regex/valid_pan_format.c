#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <sys/types.h>


static int compile_regexp(regex_t *regex, const char *string) {
    return regcomp(regex, string, REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
}

int main(int argc, char *argv[]) {
    static const char *PAN_REGEX = "^[A-Z]{5}[0-9]{4}[A-Z]$";
    regex_t regex;
    compile_regexp(&regex, PAN_REGEX);
    int n;
    scanf("%d\n", &n);

    for (int i = 0; i < n; ++i) {
        char buf[1024];
        fgets(buf, 1024, stdin);
        if (regexec(&regex, buf, 0, NULL, 0) == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    regfree(&regex);
    return 0;
}
