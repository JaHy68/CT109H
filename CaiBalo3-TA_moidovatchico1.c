//caibalo 1 greedy
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char TenDV[25];
	float TL,GT,DG;
	int SL;
	int So_dv_duocchon;
}DoVat;



DoVat * ReadFromFile(float *W, int *n){
	FILE *f =fopen("CaiBalo3.txt","r");
	fscanf(f,"%f",W);//trong luong balo
	DoVat *dsdv;
	dsdv=(DoVat*)malloc(sizeof(DoVat));
	int i=0;
	
	if (f == NULL) {
    printf("Khong mo duoc file!\n");
    return NULL;
}

while (fscanf(f, "%f %f %d %[^\n]", &dsdv[i].TL, &dsdv[i].GT,&dsdv[i].SL, dsdv[i].TenDV) == 4) {
	
		dsdv[i].DG= dsdv[i].GT/dsdv[i].TL;
		dsdv[i].So_dv_duocchon=0;
		i++;
		dsdv=realloc(dsdv,sizeof(DoVat)*(i+1));
	}
	*n=i;//so luong do vat
	fclose(f);
	return dsdv;
	
}
void Swap(DoVat *x,DoVat *y){
	DoVat Temp;
	Temp = *x;
	*x = *y;
	*y = Temp;
	
}




void printDSDV(DoVat *dsdv, int n, float W){
	int i;
	float TongTL=0.0; 
	float TongGT=0.0;
	printf("\nPhuong an thu tu ky thuat tham an:\n");
	printf("|---|---------------------|-----------|-------|-------|---------------|\n");
	printf("|STT|	Ten Do Vat	  |T. Luong   |Gia Tri|Don Gia|So DV duoc chon|\n");
	printf("|---|---------------------|-----------|-------|-------|---------------|\n");
	for(i=0;i<n;i++){
	printf("|%-3d|%-21s|%9.2f  |%9.2f|%9.2f|%8d   |\n", i+1, dsdv[i].TenDV, dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].So_dv_duocchon);
		TongTL = TongTL+dsdv[i].So_dv_duocchon*dsdv[i].TL;
		TongGT = TongGT + dsdv[i].So_dv_duocchon * dsdv[i].GT;
		
	}
	printf("|---|---------------------|-----------|-------|-------|---------------|\n");
	printf("\nTrong luong cua balo = %9.2f\n",W);
	printf("\nTong trong luong cac vat duoc chon = %9.2f\n\nTong gia tri = %-9.2f\n",TongTL,TongGT);
	
}

void BubbleSort(DoVat *dsdv, int n){
	int i,j;
	for(i=0;i<=n-2;i++)
		for(j=n-1;j>=i+1;j--){
			if(dsdv[j].DG>dsdv[j-1].DG)
				Swap(&dsdv[j],&dsdv[j-1]);
		}
}

int min(int a, int b){
	return a<b? a:b;
}
void greedy(DoVat *dsdv, int n, float W){
	int i;
	for(i=0;i<n;i++){
		   dsdv[i].So_dv_duocchon= min(1, W/dsdv[i].TL);
		W = W -dsdv[i].So_dv_duocchon*dsdv[i].TL;
	}
}

int main(){
	int n;
	float W;
	DoVat *dsdv;
	dsdv = ReadFromFile(&W,&n);
	BubbleSort(dsdv,n);
	greedy(dsdv,n,W);
	printDSDV(dsdv,n,W);
	free(dsdv);
	return 0;
}