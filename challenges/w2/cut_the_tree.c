#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int read_int() {
    int ret;
    scanf("%d", &ret);
    return ret;
}

/* caller should free the memory */
static int *read_int_array(int n) {
    int *ret = malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        scanf("%d", ret + i);
    }
    return ret;
}

static int intcomp(const void *v1, const void *v2) {
    return *(const int *)v1 - *(const int *)v2;
}

int main(int argc, char *argv[]) {
    int n = read_int();
    int total_weight = 0;
    int *weights = read_int_array(n);

    for (int i = 0; i < n; ++i) {
        total_weight += weights[i];
    }

    int **F = malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        F[i] = calloc(n, sizeof(int));
    }

    int **G = malloc(n * sizeof(int *));
    for (int i = 0; i < n; ++i) {
        G[i] = calloc(n, sizeof(int));
    }

    for (int i = 0; i < n - 1; ++i) {
        printf("PROCESS EDGE %d\n", i);
        int a = read_int() - 1, b = read_int() - 1;

        F[a][b] = weights[b];
        F[b][a] = weights[a];

        assert (G[b][a] == 0);
        assert (G[a][b] == 0);
        G[a][b] = F[a][b];
        G[b][a] = F[b][a];
        printf("--------------------\n");
        for (int k = 0; k < n; ++k) {
            for (int l = 0; l < n; ++l) {
                printf("%5d ", G[k][l]);
            }
            printf("\n");
        }
        printf("--------------------\n");

        for (int j = 0; j < n; ++j) {
            /* /\* update j, a *\/ */
            /* if (F[j][a] != 0 && j != b) { */
            /*     F[j][a] +=  */
            /* } */

            /* update G[a][b] */
            if (G[b][j] != 0 && j != a) {
                G[a][b] += G[b][j];
            }

            /* update G[b][a] */
            if (G[a][j] != 0 && j != b) {
                G[b][a] += G[a][j];
            }

            /* update j,a */
            if (G[j][a] != 0 && j != b) {
                G[j][a] += F[a][b];
            }

            /* update j,b */
            if (G[j][b] != 0 && j != a) {
                G[j][b] += F[b][a];
            }
        }

        printf("--------------------\n");
        for (int k = 0; k < n; ++k) {
            for (int l = 0; l < n; ++l) {
                printf("%5d ", G[k][l]);
            }
            printf("\n");
        }
        printf("--------------------\n");
    }


    int min_diff = total_weight;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (G[i][j] != 0) {
                if (abs(G[i][j] - G[j][i]) < min_diff) {
                    min_diff = abs(G[i][j] - G[j][i]);
                    printf("DIFF: %d %d %d\n", min_diff, i, j);
                }
            }
        }
    }
    printf("%d\n", min_diff);
    return 0;
}
