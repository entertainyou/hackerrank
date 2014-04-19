#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;

        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        int x3 = x2 + (x2 - x1);
        int y3 = y2 + (y2 - y1);
        printf("%d %d\n", x3, y3);
    }

    return 0;
}
