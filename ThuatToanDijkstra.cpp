#include <stdio.h>
#include <string.h>
#define MAX 100
#define VOCUC 1000

typedef struct {
    int n;
    float a[MAX][MAX];
} DOTHI;

int LuuVet[MAX];
int ChuaXet[MAX];
float DoDaiDuongDiToi[MAX];

int TimDuongDiNhoNhat(DOTHI g) {
    int li = -1;
    float p = VOCUC;
    for (int i = 0; i < g.n; i++) {
        if (ChuaXet[i] == 0 && DoDaiDuongDiToi[i] < p) {
            p = DoDaiDuongDiToi[i];
            li = i;
        }
    }
    return li;
}

void CapNhatDuongDi(int u, DOTHI g) {
    ChuaXet[u] = 1;
    for (int v = 0; v < g.n; v++) {
        if (ChuaXet[v] == 0 && g.a[u][v] > 0 && g.a[u][v] < VOCUC) {
            if (DoDaiDuongDiToi[v] > DoDaiDuongDiToi[u] + g.a[u][v]) {
                DoDaiDuongDiToi[v] = DoDaiDuongDiToi[u] + g.a[u][v];
                LuuVet[v] = u;
            }
        }
    }
}

void Dijkstra(int S, int F, DOTHI g) {
    for (int i = 0; i < g.n; i++) {
        ChuaXet[i] = 0;
        DoDaiDuongDiToi[i] = VOCUC;
        LuuVet[i] = -1;
    }
    DoDaiDuongDiToi[S] = 0;

    while (ChuaXet[F] == 0) {
        int u = TimDuongDiNhoNhat(g);
        if (u == -1) break;
        CapNhatDuongDi(u, g);
    }

    if (ChuaXet[F] == 1) {
        printf("Duong di ngan nhat tu [%d] den [%d] la:\n\t", S, F);
        printf("%d ", F);
        int i = LuuVet[F];
        while (i != -1) {
            printf("<- %d ", i);
            i = LuuVet[i];
        }
        printf("\n\tVoi do dai la %d\n", (int)DoDaiDuongDiToi[F]);
    } else {
        printf("Khong co duong di tu dinh %d den dinh %d\n", S, F);
    }
}

int DocMaTranKe(char *tenfile, DOTHI *g, int *S, int *F) {
    FILE *f = fopen(tenfile, "r");
    if (f == NULL) {
        printf("Khong mo duoc file.\n");
        return 0;
    }

    fscanf(f, "%d", &g->n);
    for (int i = 0; i < g->n; i++) {
        for (int j = 0; j < g->n; j++) {
            fscanf(f, "%f", &g->a[i][j]);
        }
    }

    fscanf(f, "%d %d", S, F);
    fclose(f);
    return 1;
}

int main() {
    char filename[100];
    DOTHI g;
    int S, F;

    printf("Nhap ten file du lieu: ");
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = '\0'; 

    if (DocMaTranKe(filename, &g, &S, &F)) {
        Dijkstra(S, F, g);
    }
    return 0;
}

