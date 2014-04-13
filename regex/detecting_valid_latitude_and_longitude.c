#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>

/* EREGEXP */
#define _X "[+-]?(([1-8]?[0-9](\\.[0-9]+)?)|90(\\.0+)?)"
#define _Y "[+-]?(((([1-9]?[0-9])|(1[0-7][0-9]))(\\.[0-9]+)?)|180(\\.0+)?)"
/* static const char *REGEX_STRING = "\\([+-]?(((([1-9]?[0-9])|(1[0-7][0-9]))(\\.[0-9]+)?)|180(\\.0+)?), [+-]?(((([1-9]?[0-9])|(1[0-7][0-9]))(\\.[0-9]+)?)|180(\\.0+)?)\\)"; */
static const char *REGEX_STRING = "\\(" _X ", " _Y "\\)";
static regex_t regex;

static void init() {
    regcomp(&regex, REGEX_STRING, REG_EXTENDED | REG_NOSUB);
}

static int verify(char *buffer) {
    if (regexec(&regex, buffer, 0, NULL, 0) == 0) {
        return 1;
    } else {
        return 0;
    }
}

static void finish() {
    regfree(&regex);
}

int main(int argc, char *argv[])
{
    init();
    int n;
    scanf(" %d", &n);
    for (int i = 0; i < n; ++i) {
        char buffer[2048];
        fscanf(stdin, " %[^\n]", buffer);
        /* printf("buffer: %s\n", buffer); */
        printf("%s\n", verify(buffer) ? "Valid" : "Invalid");
    }

    finish();
    return 0;
}
