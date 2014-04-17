#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int solve(char *buffer) {
    int len = strlen(buffer);
    if (len % 2 != 0) {
        return -1;
    }

    int *count1, *count2, half;
    half = len / 2;
    count1 = calloc(26, sizeof(int));
    count2 = calloc(26, sizeof(int));

    for (int i = 0; i < half; ++i) {
        char c1 = buffer[i], c2 = buffer[i + half];
        assert(c1 >= 'a' && c1 <= 'z');
        assert(c2 >= 'a' && c2 <= 'z');

        count1[c1 - 'a'] ++;
        count2[c2 - 'a'] ++;
    }

    int missing = 0;
    for (int i = 0; i < 26; ++i) {
        if (count2[i] > count1[i]) {
            missing += count2[i] - count1[i];
        }
    }
    return missing;
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);
    char buffer[100001];
    for (int i = 0; i < n; ++i) {
        scanf(" %s", buffer);
        printf("%d\n", solve(buffer));
    }
    return 0;
}
