#include <stdio.h>
#include<stdlib.h>

#define MAX 10

typedef struct GRAPH {
    int n;
    int a[MAX][MAX];
} DOTHI;

int DocMaTranKe(DOTHI &g, const char *filename) {
    FILE *f = fopen(filename, "rt");
    if (f == NULL) return 0;
    fscanf(f, "%d", &g.n);
    for (int i = 0; i < g.n; i++)
        for (int j = 0; j < g.n; j++)
            fscanf(f, "%d", &g.a[i][j]);
    fclose(f);
    return 1;
}

void timDinhLienThong(DOTHI &g, int nhan[MAX], int i) {
    for (int j = 0; j < g.n; j++) {
        if (g.a[i][j] != 0 && nhan[i] != nhan[j]) {
            nhan[j] = nhan[i];
            timDinhLienThong(g, nhan, j);
        }
    }
}

int soTPLienThong(DOTHI &g) {
    int SoTPLT = 0, nhan[MAX];
    for (int i = 0; i < g.n; i++) nhan[i] = 0;
    for (int i = 0; i < g.n; i++) {
        if (nhan[i] == 0) {
            SoTPLT++;
            nhan[i] = SoTPLT;
            timDinhLienThong(g, nhan, i);
        }
    }
    return SoTPLT;
}

typedef struct EDGE {
    int u, v, value;
} CANH;

CANH T[MAX];

void Prim(DOTHI g) {
    if (soTPLienThong(g) != 1) {
        printf("Do thi khong lien thong, dung thuat toan Prim\n");
        return;
    }

    int nT = 0, ChuaXet[MAX];
    for (int i = 0; i < g.n; i++) ChuaXet[i] = 0;
    ChuaXet[0] = 1;

    while (nT < g.n - 1) {
        CANH CanhNhoNhat;
        int GiaTriNhoNhat = 1000;

        for (int i = 0; i < g.n; i++) {
            if (ChuaXet[i] == 1) {
                for (int j = 0; j < g.n; j++) {
                    if (ChuaXet[j] == 0 && g.a[i][j] != 0 && g.a[i][j] < GiaTriNhoNhat) {
                        CanhNhoNhat.u = i;
                        CanhNhoNhat.v = j;
                        CanhNhoNhat.value = g.a[i][j];
                        GiaTriNhoNhat = g.a[i][j];
                    }
                }
            }
        }

        T[nT++] = CanhNhoNhat;
        ChuaXet[CanhNhoNhat.v] = 1;
    }
}

int main() {
    DOTHI g;
    char filename[100];

    printf("Nhap ten tap tin du lieu do thi: ");
    scanf("%s", filename);

    if (DocMaTranKe(g, filename) == 1) {
        int soTP = soTPLienThong(g);
        if (soTP == 1) {
            printf("Do thi lien thong.\n");
        } else {
            printf("Do thi khong lien thong. Co %d thanh phan lien thong.\n", soTP);
        }

        Prim(g);
        printf("Cay khung nho nhat cua do thi la:\n");
        int trongSoCuaCayKhung = 0;
        for (int i = 0; i < g.n - 1; i++) {
            printf("(%d, %d) Trong so = %d\n", T[i].u, T[i].v, T[i].value);
            trongSoCuaCayKhung += T[i].value;
        }
        printf("Tong trong so cay khung la %d\n", trongSoCuaCayKhung);
    } else {
        printf("Khong mo duoc file.\n");
    }

    return 0;
}

