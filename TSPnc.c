#include <stdio.h>
#define size 30

typedef struct{
	float do_dai;
	int dau, cuoi;
	int da_dung;
	
}canh;

void read_file(char file_name[], canh a[][size], int *n){
	int i,j;
	FILE *f;
	f = fopen(file_name, "r");
	if(f==NULL){
		printf("Error..");
		return;
	}
	
	fscanf(f,"%d",n);
	
	for(i=0; i<*n;i++)
		for(j=0; j<*n;j++){
			fscanf(f,"%f",&a[i][j].do_dai);
			a[i][j].dau=i;
			a[i][j].cuoi=j;
			a[i][j].da_dung=0;
			
		}
	fclose(f);
}
void in_ma_tran(canh a[][size], int n){
	int i, j;
	printf("Ma tran trong so cua do thi\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
		printf("%c%c=%8.2f",a[i][j].dau+65,a[i][j].cuoi+65,a[i][j].do_dai);
		printf("\n");
	}
}

void in_PA(canh PA[], int n){
	int i;
	float sum = 0.0;
	printf("\nPhuong an tim duoc:\n");
	for(i=0;i<n;i++){
		sum += PA[i].do_dai;
		printf("Canh %c%c= %8.2f\n",PA[i].dau+65,PA[i].cuoi+65,PA[i].do_dai);
		
		
	}
	printf("Tong do dai cac canh cua chu trinh = %8.2f\n",sum);
}

float canh_NN(canh a[][size], int n){
	float Cmin = 3.4e+38;
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		if(i!=j&& !a[i][j].da_dung && a[i][j].do_dai<Cmin)
			Cmin = a[i][j].do_dai;
		return Cmin;
}
int co_chu_trinh(canh x[], int k,int ke_tiep){
	int i =0, co_CT =0;
	while (i<k&&!co_CT)
		if(ke_tiep==x[i].dau) co_CT=1;
		else i++;
		return co_CT;
}
void Cap_Nhat_PA_TNTT(canh a[][size],int n,float TGT,float *GiaNNTT, canh x[],canh PA[]){
	int i;
	x[n-1]=a[x[n-2].cuoi][x[0].dau];
	TGT = TGT + x[n-1].do_dai;
	if(*GiaNNTT>TGT){
		*GiaNNTT=TGT;
		for(i=0;i<n;i++)
		PA[i]=x[i];
	}
}

float can_duoi(canh a[][size], float TGT, int n, int i){
	return TGT + (n-1)*canh_NN(a,n);
}

void Nhanh_Can(canh a[][size], int n, int i, int dau, float *TGT,float *CD,float *GiaNNTT,canh x[],canh PA[]){
	int j;
	for(j=0;j<n;j++)
	
	if(dau!=j&& !a[dau][j].da_dung&& !co_chu_trinh(x,i,j)){
		*TGT = *TGT + a[dau][j].do_dai;
		*CD = can_duoi(a, *TGT,n,i+1);
		if(*CD <*GiaNNTT){
			x[i]=a[dau][j];
			a[dau][j].da_dung=1;
			a[j][dau].da_dung=1;
			
			if(i==n-2){
				Cap_Nhat_PA_TNTT(a,n,*TGT,GiaNNTT,x,PA);
				
			}
			else{
				Nhanh_Can(a,n,i+1,j,TGT,CD,GiaNNTT,x,PA);
			}
		*TGT =*TGT - a[dau][j].do_dai;
		a[dau][j].da_dung=0;
		a[j][dau].da_dung=0;
		}
	}
}

void reset(canh a[][size], int n){
	int i,j;
	for(i=0;i<n;i++)
	 for(j=0;j<n;j++)
	 	a[i][j].da_dung=0;
}

int main(){
	canh a[size][size];
	int n;
	read_file("TSP1.txt",a,&n);
	canh PA[n];
	canh x[n];
	char tpxp,yn;
	while(1){
		fflush(stdin);
		in_ma_tran(a,n);
		float TGT=0.0, CD = 0.0,GiaNNTT = 3.4e+38;
		printf("\n Xuat phat tu thanh pho nao?(Tu A den %c)",n-1+65);
		scanf("%c",&tpxp);
		if(tpxp>=97) tpxp-=32; 
		Nhanh_Can(a, n,0, tpxp-65,&TGT,&CD,&GiaNNTT,x,PA);
		in_PA(PA,n);
		fflush(stdin);
		printf("\nTiep tuc Y/N?");
		scanf("%c",&yn);
		if(yn == 'N'||yn=='n')
			break;
		reset(a,n);
	}
	return 0;
}