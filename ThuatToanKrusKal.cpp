#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int n;
    int a[MAX][MAX];
} DOTHI;

typedef struct {
    int u, v, value;
} CANH;

int DocMaTranKe(DOTHI &g, char filename[]) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) {
        printf("Khong mo duoc file %s\n", filename);
        return 0;
    }

    fscanf(f, "%d", &g.n);
    for (int i = 0; i < g.n; i++) {
        for (int j = 0; j < g.n; j++) {
            fscanf(f, "%d", &g.a[i][j]);
        }
    }
    fclose(f);
    return 1;
}

void SapXepTang(CANH E[], int tongsocanh) {
    for (int i = 0; i < tongsocanh - 1; i++) {
        for (int j = i + 1; j < tongsocanh; j++) {
            if (E[i].value > E[j].value) {
                CANH tmp = E[i];
                E[i] = E[j];
                E[j] = tmp;
            }
        }
    }
}

void Kruskal(DOTHI g) {
    CANH listEdge[MAX];
    int tongsocanh = 0;

    for (int i = 0; i < g.n; i++) {
        for (int j = i + 1; j < g.n; j++) {
            if (g.a[i][j] > 0) {
                listEdge[tongsocanh].u = i;
                listEdge[tongsocanh].v = j;
                listEdge[tongsocanh].value = g.a[i][j];
                tongsocanh++;
            }
        }
    }

    SapXepTang(listEdge, tongsocanh);

    int nT = 0;
    CANH T[MAX];
    int nhan[MAX];
    for (int i = 0; i < g.n; i++) {
        nhan[i] = i;
    }

    int canhdangxet = 0;
    while (nT < g.n - 1 && canhdangxet < tongsocanh) {
        CANH edge = listEdge[canhdangxet];
        int u = nhan[edge.u], v = nhan[edge.v];

        if (u != v) {
            T[nT++] = edge;
            for (int j = 0; j < g.n; j++) {
                if (nhan[j] == v) nhan[j] = u;
            }
        }
        canhdangxet++;
    }

    if (nT < g.n - 1) {
        printf("\nDo thi khong lien thong\n");
    } else {
        int trongSoCayKhung = 0;
        printf("Cay khung nho nhat cua do thi la:\n");
        for (int i = 0; i < nT; i++) {
            printf("(%d, %d) Trong so = %d\n", T[i].u, T[i].v, T[i].value);
            trongSoCayKhung += T[i].value;
        }
        printf("Tong trong so cay khung la %d\n", trongSoCayKhung);
    }
}

int main() {
    DOTHI g;
    char filename[100];

    printf("Nhap ten file chua ma tran ke: ");
    scanf("%s", filename);

    if (DocMaTranKe(g, filename)) {
        Kruskal(g);
    }

    return 0;
}

