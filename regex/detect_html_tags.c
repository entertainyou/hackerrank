#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <sys/types.h>

#define TAG_SIZE 1024
#define TAG_MAX_LENGTH 1024
#define REGMATCH_MAX_LENGTH 6

struct info {
    /* TODO: make a struct for regex_t and it's meta info */
    regex_t regex;
    regex_t regex2;
    /* shared between regex and regex2 */
    regmatch_t regmatches[REGMATCH_MAX_LENGTH];
    char *tags[TAG_SIZE];
    int tag_number;
};

static void init(struct info *infop) {
    infop->tag_number = 0;
    /* regcomp(&infop->regex, "< *([^ ]*) *>.*</\1>", REG_EXTENDED); */
    regcomp(&infop->regex, "< *([^ />]+) *( [^>]*=[^>]*)? *(>).*< */\\1 *>", REG_EXTENDED);
    regcomp(&infop->regex2, "< *([^ >/]+) *( [^>]*=[^>]*)? */(>)", REG_EXTENDED);
}

static int tag_exist(struct info*infop, const char *tag) {
    for (int i = 0; i < infop->tag_number; ++i) {
        if (strcmp(tag, infop->tags[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static void got_tag(struct info *infop, const char *tag) {
    if (tag_exist(infop, tag)) {
        return;
    } else {
        infop->tags[infop->tag_number ++] = strdup(tag);
    }
}

static void get_tag_v1(struct info *infop, const char *buffer, regex_t *regex, int nmatch, int start_index) {
    int index = 0;
    regmatch_t *matches = infop->regmatches;
    while (regexec(regex, buffer + index, nmatch, matches, 0) == 0) {
        char tag[TAG_MAX_LENGTH];
        int length = matches[1].rm_eo - matches[1].rm_so;
        memcpy(tag, buffer + index + matches[1].rm_so, length * sizeof(char));
        tag[length] = '\0';
        got_tag(infop, tag);
        index += matches[start_index].rm_eo - 1;
    }

}

static void feed(struct info *infop, const char *buffer) {
    get_tag_v1(infop, buffer, &infop->regex, 4, 3);
    get_tag_v1(infop, buffer, &infop->regex2, 4, 3);
}

static int cmpstringp(const void *p1, const void *p2)
{
    /* The actual arguments to this function are "pointers to
       pointers to char", but strcmp(3) arguments are "pointers
       to char", hence the following cast plus dereference */

    return strcmp(* (char * const *) p1, * (char * const *) p2);
}

static void print_result(struct info *infop) {
    qsort(infop->tags, infop->tag_number, sizeof(char *), cmpstringp);
    const char * delimiter = "";
    for (int i = 0; i < infop->tag_number; ++i) {
        printf("%s%s", delimiter, infop->tags[i]);
        delimiter=";";
    }
    printf("\n");
}

static void finish(struct info *infop) {
    for (int i = 0; i < infop->tag_number; ++i) {
        free(infop->tags[i]);
    }
}

int main(int argc, char *argv[])
{
    struct info info;
    init(&info);
    int n;
    fscanf(stdin, " %d", &n);
    char fragment[10001 * 100];
    fragment[0] = '\0';
    for (int i = 0; i < n; ++i) {
        char buffer[10001];
        fscanf(stdin, " %[^\n]", buffer);
        /* feed(&info, buffer); */
        strcat(fragment, buffer);
    }
    feed(&info, fragment);
    print_result(&info);
    finish(&info);
    return 0;
}
