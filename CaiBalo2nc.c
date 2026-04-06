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
    if(f == NULL){
        printf("Khong mo duoc file!\n");
        return NULL;
    }

    fscanf(f,"%f",W);

    DoVat *dsdv = (DoVat*)malloc(sizeof(DoVat));
    int i = 0;

    while (fscanf(f, "%f %f %d %[^\n]",
        &dsdv[i].TL,
        &dsdv[i].GT,
        &dsdv[i].SL,
        dsdv[i].TenDV) == 4){

        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        dsdv[i].So_dv_duocchon = 0;

        i++;
        dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
    }

    *n = i;
    fclose(f);
    return dsdv;
}

// ================== ĐỔI CHỖ ==================
void Swap(DoVat *x, DoVat *y){
    DoVat t = *x;
    *x = *y;
    *y = t;
}

// ================== SẮP XẾP ==================
void BubbleSort(DoVat *dsdv, int n){
    for(int i=0;i<n-1;i++)
        for(int j=n-1;j>i;j--)
            if(dsdv[j].DG > dsdv[j-1].DG)
                Swap(&dsdv[j], &dsdv[j-1]);
}

// ================== KHỞI TẠO ==================
void Tao_Nut_Goc(float W, float *TLConLai, float *CT,
                 float *GiaLNTT, float *TGT, float maxDG){
    *TGT = 0;
    *TLConLai = W;
    *CT = W * maxDG;
    *GiaLNTT = 0;
}

// ================== CẬP NHẬT ==================
void Cap_Nhat_PA(float TGT, float *GiaLNTT,
                 int x[], DoVat *dsdv, int n){
    if(TGT > *GiaLNTT){
        *GiaLNTT = TGT;
        for(int i=0;i<n;i++)
            dsdv[i].So_dv_duocchon = x[i];
    }
}

// ================== NHÁNH CẬN ==================
int min(int a, int b){
    return a < b ? a : b;
}

void Nhanh_Can(int i, float *TGT, float *CT, float *TLConLai,
               float *GiaLNTT, int x[], DoVat *dsdv, int n){

    int j;

    // số lượng tối đa có thể chọn
    int max_chon = min(dsdv[i].SL, *TLConLai / dsdv[i].TL);

    for(j = max_chon; j >= 0; j--){

        *TGT += j * dsdv[i].GT;
        *TLConLai -= j * dsdv[i].TL;

        if(i == n-1)
            *CT = *TGT;
        else
            *CT = *TGT + (*TLConLai) * dsdv[i+1].DG;

        if(*CT > *GiaLNTT){
            x[i] = j;

            if(i == n-1 || *TLConLai == 0)
                Cap_Nhat_PA(*TGT, GiaLNTT, x, dsdv, n);
            else
                Nhanh_Can(i+1, TGT, CT, TLConLai, GiaLNTT, x, dsdv, n);
        }

        *TGT -= j * dsdv[i].GT;
        *TLConLai += j * dsdv[i].TL;
        x[i] = 0;
    }
}

// ================== IN KẾT QUẢ ==================
void printDSDV(DoVat *dsdv, int n, float W){
    float TongTL=0, TongGT=0;

    printf("\nKET QUA:\n");
    printf("|---|---------------------|-----------|-----------|-----------|-----|------|\n");
    printf("|STT|Ten Do Vat           |T. Luong   |Gia Tri    |Don Gia    | SL  |Chon |\n");
    printf("|---|---------------------|-----------|-----------|-----------|-----|------|\n");

    for(int i=0;i<n;i++){
        printf("|%-3d|%-21s|%9.2f|%11.2f|%11.2f|%5d|%5d |\n",
            i+1, dsdv[i].TenDV, dsdv[i].TL,
            dsdv[i].GT, dsdv[i].DG,
            dsdv[i].SL,
            dsdv[i].So_dv_duocchon);

        TongTL += dsdv[i].So_dv_duocchon * dsdv[i].TL;
        TongGT += dsdv[i].So_dv_duocchon * dsdv[i].GT;
    }

    printf("|---|---------------------|-----------|-----------|-----------|-----|------|\n");

    printf("\nTrong luong balo: %.2f\n", W);
    printf("Tong trong luong: %.2f\n", TongTL);
    printf("Tong gia tri: %.2f\n", TongGT);
}

// ================== MAIN ==================
int main(){
    DoVat *dsdv;
    int n;
    float W;

    float CT, TGT, TLConLai, GiaLNTT;

    dsdv = ReadFromFile(&W,&n);
    if(dsdv == NULL) return 0;

    int x[n];

    BubbleSort(dsdv,n);

    Tao_Nut_Goc(W, &TLConLai, &CT, &GiaLNTT, &TGT, dsdv[0].DG);

    Nhanh_Can(0, &TGT, &CT, &TLConLai, &GiaLNTT, x, dsdv, n);

    printDSDV(dsdv,n,W);

    free(dsdv);
    return 0;
}