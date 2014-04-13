#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

/* 4M */
#define BUFFER_SIZE 4 *1024 * 1024

/* WHY SO UGLY.... */
static const char *REGEX_STRING = "<div class=\"summary\">\\s*<h3>\\s*<a href=\"/questions/([0-9]+)/[^\"]+\" class=\"question-hyperlink\">\\s*([^<]+)\\s*</a>\\s*</h3>\\s*<div class=\"excerpt\">[^<]*(<span[^>]*>[^<]*</span>)?[^<]*</div>\\s*<div[^>]*>\\s*(<a[^>]*>[^<]*</a>\\s*)*\\s*</div>\\s*<div[^>]*>\\s*<div[^>]*>\\s*<div[^>]*>\\s*asked\\s*<span[^>]*>\\s*([^<]+)\\s*</span>";
static regex_t regex;
#define MATCH_NUM 6
static regmatch_t matches[MATCH_NUM];
static int start_index = 0;
static const int IDENTIFIER_INDEX = 1;
static const int QUESTION_TEXT_INDEX = 2;
static const int TIME_INDEX = 5;


static void init() {
    regcomp(&regex, REGEX_STRING, REG_EXTENDED);
}

/* caller should free the resource */
static char *generate_string_from_regmatch(const regmatch_t *match, const char *buffer) {
    int length = (match->rm_eo - match->rm_so) + 1;
    char *result = malloc(length * sizeof(int));
    strncpy(result, buffer + match->rm_so, length - 1);
    result[length - 1] = '\0';

    return result;
}

static void loop(const char *buffer) {
    int index = 0;
    while (regexec(&regex, buffer + index, MATCH_NUM, matches, 0) == 0) {
        /* for (int i = 0; i < MATCH_NUM; ++i) { */
        /*     printf("%d [%d, %d]\n", i, matches[i].rm_so, matches[i].rm_eo); */
        /* } */

        int next_start_index = matches[start_index].rm_eo;
        assert(next_start_index != -1);
        /* printf("index = %d\n", index); */
        char *id = generate_string_from_regmatch(matches + IDENTIFIER_INDEX, buffer + index);
        char *question = generate_string_from_regmatch(matches + QUESTION_TEXT_INDEX, buffer + index);
        char *time = generate_string_from_regmatch(matches + TIME_INDEX, buffer + index);
        printf("%s;%s;%s\n", id, question, time);
        index += next_start_index;
    }
}

static void finish() {
    regfree(&regex);
}

int main(int argc, char *argv[])
{
    init();
    /* 4M buffer */
    char buffer[BUFFER_SIZE];

    size_t read = fread(buffer, sizeof(char), BUFFER_SIZE, stdin);
    assert(read < BUFFER_SIZE && feof(stdin));

    /* printf("%s\n", buffer); */
    loop(buffer);
    finish();
    return 0;
}
