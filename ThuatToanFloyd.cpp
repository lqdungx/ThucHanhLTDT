#include <stdio.h>

#define MAX 100
#define VOCUC 1000

typedef struct {
    int n;
    int a[MAX][MAX];
} DOTHI;

int L[MAX][MAX];
int Sau_Nut[MAX][MAX];

void Floyd(DOTHI g) {
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            if (g.a[i][j] > 0 && i != j) {
                Sau_Nut[i][j] = j;
                L[i][j] = g.a[i][j];
            } else {
                Sau_Nut[i][j] = -1;
                if (i == j)
                    L[i][j] = 0;
                else
                    L[i][j] = VOCUC;
            }
        }
    }

    for (int k = 0; k < g.n; k++) {
        for (int i = 0; i < g.n; i++) {
            for (int j = 0; j < g.n; j++) {
                if (L[i][j] > L[i][k] + L[k][j]) {
                    L[i][j] = L[i][k] + L[k][j];
                    Sau_Nut[i][j] = Sau_Nut[i][k];
                }
            }
        }
    }

    int S, F;
    printf("Nhap dinh bat dau (S): ");
    scanf("%d", &S);
    printf("Nhap dinh ket thuc (F): ");
    scanf("%d", &F);

    if (Sau_Nut[S][F] == -1) {
        printf("Khong co duong di tu dinh %d den dinh %d.\n", S, F);
    } else {
        printf("Duong di ngan nhat tu dinh %d den dinh %d la:\n", S, F);
        printf("\t%d", S);
        int u = S;
        while (Sau_Nut[u][F] != F) {
            u = Sau_Nut[u][F];
            printf(" --> %d", u);
        }
        printf(" --> %d", F);
        printf("\nTong trong so: %d\n", L[S][F]);
    }
}

int main() {
    DOTHI g;
    printf("Nhap so dinh: ");
    scanf("%d", &g.n);

    printf("Nhap ma tran ke (%d x %d):\n", g.n, g.n);
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            scanf("%d", &g.a[i][j]);
        }
    }

    Floyd(g);
    return 0;
}
