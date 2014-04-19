#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    static int count[10001];
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i)
    {
        int M, N;
        scanf("%d%d", &M, &N);
        memset(count, 0, 10000 * sizeof(int));

        for (int j = 0; j < N; ++j)
        {
            int val;
            scanf("%d", &val);
            if (val < M && count[M - val] != 0) {
                printf("%d %d\n", count[M - val], j + 1);
            } else if (val < M) {
                count[val] = j + 1;
            }
        }
    }
    return 0;
}
