#include <stdio.h>
#include <malloc.h>

typedef int keytype;
typedef float othertype;

typedef struct{// dinh nghia cau truc
	keytype key;
	othertype otherfields;
}recordtype;

void Swap(recordtype *x, recordtype *y){//phai dung con tro
	recordtype temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
void BubbleSort(recordtype a[], int n){
	int i,j;
	for(i=0;i<=n-2;i++)
		for(j=n-1;j>=n+1;j--)
			if(a[j].key<a[j-1].key)
			Swap(&a[j],&a[j-1]);
}
void Read_Data(recordtype a[], int *n){//doc du lieu 
	FILE *f;
	f = fopen("data.txt","r");//mo tep tin data, "r"mo ra de doc thong tin
	int i = 0;//khoi dau a[0]
	if(f!=NULL)//neu doc file thanh cong
	while(!feof(f)){//doc tung dong cua tep tin
		fscanf(f,"%d%f",&a[i].key,&a[i].otherfields);//gia tri tu nhat luu vao key, other giu gia tri thu hai
		i++;//sau khi doc xong thi tang i cho den khi het
	}else printf("Error\n");
	fclose(f);//dong file
	*n = i;//so phan tu a[n]=i
}

void Print_Data(recordtype a[],int n){//nhan vao a la mang, n la so phan tu
	int i;
	for(i=0;i<n;i++)
		printf("%3d%5d%8.2f\n",i+1,a[i].key,a[i].otherfields);
}//i+1 la so thu tu
int main(){
	recordtype a[100];//khai bao mang
	int n;
	Read_Data(a,&n);//goi ham, truyen du lieu 
	printf("Du lieu la:\n");
	Print_Data(a,n);//in ra du lieu ban dau
	
	BubbleSort(a,n);//sap xep mang a
	printf("Ket qua sap xep la:\n");
	Print_Data(a,n);//in du lieu da sap xep
	return 0;
}