#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char TenDV[20];
    float GT;
    int TL, SL, So_DVduocchon;
} DoVat;

// ================== IN KẾT QUẢ ==================
void printDSDV(DoVat *dsdv, int n, int W){
    float TongTL=0, TongGT=0;

    printf("\nPhuong an (QHD - CO SL):\n");

    for(int i=0;i<n;i++){
        printf("%-20s | TL=%d | GT=%.2f | SL=%d | Chon=%d\n",
            dsdv[i].TenDV,
            dsdv[i].TL,
            dsdv[i].GT,
            dsdv[i].SL,
            dsdv[i].So_DVduocchon);

        TongTL += dsdv[i].So_DVduocchon * dsdv[i].TL;
        TongGT += dsdv[i].So_DVduocchon * dsdv[i].GT;
    }

    printf("\nTong TL: %.2f\n", TongTL);
    printf("Tong GT: %.2f\n", TongGT);
}

// ================== MIN ==================
int min(int a, int b){
    return a < b ? a : b;
}

// ================== QHD ==================
void TaoBang(DoVat *dsdv, int n,int W, float F[][W+1], int X[][W+1]){
    int k, V, xk;
    float FMax;
    int XMax;

    // dòng đầu
    for(V=0;V<=W;V++){
        int max0 = min(dsdv[0].SL, V/dsdv[0].TL);
        F[0][V] = max0 * dsdv[0].GT;
        X[0][V] = max0;
    }

    // các dòng sau
    for(k=1;k<n;k++){
        for(V=0;V<=W;V++){
            FMax = F[k-1][V];
            XMax = 0;

            int yk = min(dsdv[k].SL, V/dsdv[k].TL);

            for(xk=1; xk<=yk; xk++){
                if(F[k-1][V - xk*dsdv[k].TL] + xk*dsdv[k].GT > FMax){
                    FMax = F[k-1][V - xk*dsdv[k].TL] + xk*dsdv[k].GT;
                    XMax = xk;
                }
            }

            F[k][V] = FMax;
            X[k][V] = XMax;
        }
    }
}

// ================== TRUY VẾT ==================
void TraBang(DoVat *dsdv, int n, int W, int X[][W+1]){
    int V = W;

    for(int k=n-1;k>=0;k--){
        dsdv[k].So_DVduocchon = X[k][V];
        V -= X[k][V] * dsdv[k].TL;
    }
}

// ================== ĐỌC FILE ==================
DoVat* ReadFromFile(int *W, int *n){
    FILE *f = fopen("QHD_CaiBalo2.txt","r");
    if(f == NULL){
        printf("Khong mo duoc file!\n");
        return NULL;
    }

    fscanf(f,"%d",W);

    DoVat *dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i = 0;

    while (fscanf(f, "%d %f %d %[^\n]",
        &dsdv[i].TL,
        &dsdv[i].GT,
        &dsdv[i].SL,
        dsdv[i].TenDV) == 4){

        dsdv[i].So_DVduocchon = 0;
        i++;
        dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
    }

    *n = i;
    fclose(f);
    return dsdv;
}

// ================== MAIN ==================
int main(){
    int n, W;
    DoVat *dsdv = ReadFromFile(&W,&n);
    if(dsdv == NULL) return 0;

    float F[n][W+1];
    int X[n][W+1];

    TaoBang(dsdv,n,W,F,X);
    TraBang(dsdv,n,W,X);

    printDSDV(dsdv,n,W);

    free(dsdv);
    return 0;
}