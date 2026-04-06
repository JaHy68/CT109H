#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char TenDV[25];
    float TL, GT, DG;
    int So_dv_duocchon;
} DoVat;

// ================== ĐỌC FILE ==================
DoVat *ReadFromFile(float *W, int *n){
    FILE *f = fopen("CaiBalo3.txt","r");

    if (f == NULL) {
        printf("Khong mo duoc file!\n");
        return NULL;
    }

    fscanf(f,"%f",W);

    DoVat *dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i=0;

    while (fscanf(f, "%f %f %[^\n]",
        &dsdv[i].TL,
        &dsdv[i].GT,
        dsdv[i].TenDV) == 3){

        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        dsdv[i].So_dv_duocchon = 0;

        i++;
        dsdv = realloc(dsdv,sizeof(DoVat)*(i+1));
    }

    *n = i;
    fclose(f);
    return dsdv;
}

// ================== SWAP ==================
void Swap(DoVat *x, DoVat *y){
    DoVat temp = *x;
    *x = *y;
    *y = temp;
}

// ================== SẮP XẾP ==================
void BubbleSort(DoVat *dsdv, int n){
    for(int i=0;i<n-1;i++)
        for(int j=n-1;j>i;j--)
            if(dsdv[j].DG > dsdv[j-1].DG)
                Swap(&dsdv[j], &dsdv[j-1]);
}

// ================== GREEDY (VÔ HẠN) ==================
void greedy(DoVat *dsdv, int n, float W){
    for(int i=0;i<n;i++){
        int so_luong = W / dsdv[i].TL;   // lấy tối đa có thể
        dsdv[i].So_dv_duocchon = so_luong;
        W -= so_luong * dsdv[i].TL;      // cập nhật lại balo
    }
}

// ================== IN ==================
void printDSDV(DoVat *dsdv, int n, float W){
    float TongTL=0.0, TongGT=0.0;

    printf("\nPhuong an tham an (VO HAN):\n");

    for(int i=0;i<n;i++){
        printf("%-20s | TL=%.2f | GT=%.2f | DG=%.2f | Chon=%d\n",
            dsdv[i].TenDV,
            dsdv[i].TL,
            dsdv[i].GT,
            dsdv[i].DG,
            dsdv[i].So_dv_duocchon);

        TongTL += dsdv[i].So_dv_duocchon * dsdv[i].TL;
        TongGT += dsdv[i].So_dv_duocchon * dsdv[i].GT;
    }

    printf("\nTrong luong balo: %.2f\n", W);
    printf("Tong TL: %.2f\n", TongTL);
    printf("Tong GT: %.2f\n", TongGT);
}

// ================== MAIN ==================
int main(){
    int n;
    float W;

    DoVat *dsdv = ReadFromFile(&W,&n);
    if(dsdv == NULL) return 0;

    BubbleSort(dsdv,n);
    greedy(dsdv,n,W);
    printDSDV(dsdv,n,W);

    free(dsdv);
    return 0;
}