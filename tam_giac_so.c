#include <stdio.h>
#include <malloc.h>

void ReadData(int *a[],int *n){
	FILE *f;
	f=fopen("tam_giac_so.txt","r");
	if(f==NULL){
		printf("Error");
	}
	a = (int*)malloc(sizeof(int));
	
	int i=0,j;
	while(!feof(f)){
		for(j=0;j<=i;j++)
			fscanf(f,"%d",&a[i][j]);
		i++;
		a=realloc(a,(i+1)*(i+1)*sizeof(int));
		
	}
	*n=i;
	fclose(f);
}

void PrintData(int *a[], int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<=i;j++)
			printf("%5d",a[i][j]);
		printf("\n");
	}
}
int max(int a[], int j){
	if(j==0)
	return (a[0]>a[1])?0:1;
	if(a[j-1]>a[j]&&a[j-1]>a[j+1])
		return j-1;
	if(a[j]>a[j-1]&&a[j]>a[j+1])
		return j;
	if(a[j+1]>a[j]&&a[j+1]>a[j-1])
		return j+1;
}
void GreedyTopDown(int *a[], int n, int PA[]){
	int i,j;
	PA[0]=a[0][0];
	j=0;
	for(i=1;i<n;i++){
		j=max(a[i],j);
		PA[i]=a[i][j];
	}
}

int GiaPA(int PA[], int n){
	int i;
	int sum = 0;
	for(i=0;i<n;i++) sum +=PA[i];
	return sum;
}

void PrintPA(int PA[], int n){
	int i;
	printf("Phuong phap tham an tren xuong:\n");
	printf("Phuong an la duong di qua cac so:\n \n");
	printf("%d", PA[0]);
	for(i=1;i<n;i++) printf("=> %d", PA[i]);
	printf("\n\nTong cac so tren duong di la: %d\n",GiaPA(PA,n));
}

int main(){
	int **a;
	int n;
	ReadData(a,&n);
	int PA[n];
	PrintData(PA,n);
	
	GreedyTopDown(a,n,PA);
	PrintPA(PA,n);
	
	return 0;
	
}