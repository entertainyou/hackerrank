#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int solve(int k, const char *string1, const char *string2) {
    int len = strlen(string1);
    assert(len == strlen(string2));

    int *M = calloc(len * len, sizeof(int));

    for (int i = len - 2; i >= 0; --i) {
        for (int j = len - 2; j >= 0; --j)
        {
            int equal = string1[i] == string2[j];
            int count = M[(i + 1) * len + j + 1] + (equal ? 0 : 1);
            M[i * len + j] = count;
        }
    }

    for (int i = 0; i < len; ++i)
    {
        for (int j = 0; j < len; ++j)
        {
            printf("%d ", M[i * len + j]);
        }
        printf("\n");
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        char string1[1501], string2[1501];
        int k;
        scanf("%d %s %s", &k, string1, string2);
        printf("%d\n", solve(k, string1, string2));
    }
    return 0;
}
