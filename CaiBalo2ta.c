#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char TenDV[25];
    float TL, GT, DG;
    int SL; // số lượng tối đa
    int So_dv_duocchon;
} DoVat;

// ================== ĐỌC FILE ==================
DoVat *ReadFromFile(float *W, int *n){
    FILE *f = fopen("CaiBalo2.txt","r");

    if (f == NULL) {
        printf("Khong mo duoc file!\n");
        return NULL;
    }

    fscanf(f,"%f",W);

    DoVat *dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i=0;

    while (fscanf(f, "%f %f %d %[^\n]",
        &dsdv[i].TL,
        &dsdv[i].GT,
        &dsdv[i].SL,
        dsdv[i].TenDV) == 4){

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

// ================== GREEDY (CÓ SỐ LƯỢNG) ==================
void greedy(DoVat *dsdv, int n, float W){
    for(int i=0;i<n;i++){
        int max_co_the_lay = W / dsdv[i].TL;

        if(max_co_the_lay > dsdv[i].SL)
            dsdv[i].So_dv_duocchon = dsdv[i].SL;
        else
            dsdv[i].So_dv_duocchon = max_co_the_lay;

        W -= dsdv[i].So_dv_duocchon * dsdv[i].TL;
    }
}

// ================== IN ==================
void printDSDV(DoVat *dsdv, int n, float W){
    float TongTL=0.0, TongGT=0.0;

    printf("\nPhuong an tham an (CO SO LUONG):\n");
    printf("|---|---------------------|-----------|-----------|-----------|------|\n");
    printf("|STT|Ten Do Vat           |T. Luong   |Gia Tri    |SL toi da  |Chon |\n");
    printf("|---|---------------------|-----------|-----------|-----------|------|\n");

    for(int i=0;i<n;i++){
        printf("|%-3d|%-21s|%9.2f|%11.2f|%11d|%5d |\n",
            i+1,
            dsdv[i].TenDV,
            dsdv[i].TL,
            dsdv[i].GT,
            dsdv[i].SL,
            dsdv[i].So_dv_duocchon);

        TongTL += dsdv[i].So_dv_duocchon * dsdv[i].TL;
        TongGT += dsdv[i].So_dv_duocchon * dsdv[i].GT;
    }

    printf("|---|---------------------|-----------|-----------|-----------|------|\n");

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