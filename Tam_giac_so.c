#include <stdio.h>
#define size 50

// ================== ĐỌC FILE ==================
void Read_Data(int a[][size], int *n){
    FILE *f = fopen("tam_giac_so.txt","r");
    if(f == NULL){
        printf("Error\n");
        return;
    }

    int i=0,j;
    while(1){
        for(j=0;j<=i;j++){
            if(fscanf(f,"%d",&a[i][j]) != 1){
                *n = i;
                fclose(f);
                return;
            }
        }
        i++;
    }
}

// ================== IN TAM GIÁC ==================
void Print_Data(int a[][size], int n){
    printf("\nTam giac so:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++)
            printf("%5d",a[i][j]);
        printf("\n");
    }
}

// ================== TẠO BẢNG F ==================
void Tao_Bang(int a[][size], int n, int F[][size]){
    int i,j;

    F[0][0] = a[0][0];

    for(i=1;i<n;i++){
        for(j=0;j<=i;j++){
            if(j==0)
                F[i][j] = a[i][j] + F[i-1][j];
            else if(j==i)
                F[i][j] = a[i][j] + F[i-1][j-1];
            else{
                if(F[i-1][j-1] > F[i-1][j])
                    F[i][j] = a[i][j] + F[i-1][j-1];
                else
                    F[i][j] = a[i][j] + F[i-1][j];
            }
        }
    }
}

// ================== IN BẢNG F ==================
void In_Bang(int F[][size], int n){
    printf("\nBang F:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++)
            printf("%5d",F[i][j]);
        printf("\n");
    }
}

// ================== TRUY VẾT ==================
void Tra_Bang(int a[][size], int F[][size], int n, int PA[]){
    int i,j;

    // tìm max ở dòng cuối
    int max = F[n-1][0];
    j = 0;
    for(int k=1;k<n;k++){
        if(F[n-1][k] > max){
            max = F[n-1][k];
            j = k;
        }
    }

    PA[n-1] = a[n-1][j];

    // truy ngược lên
    for(i=n-1;i>0;i--){
        if(j==0){
            j = j;
        }
        else if(j==i){
            j = j-1;
        }
        else{
            if(F[i-1][j-1] > F[i-1][j])
                j = j-1;
        }
        PA[i-1] = a[i-1][j];
    }
}

// ================== TÍNH GIÁ TRỊ ==================
int GiaPA(int PA[], int n){
    int sum=0;
    for(int i=0;i<n;i++)
        sum += PA[i];
    return sum;
}

// ================== IN KẾT QUẢ ==================
void Print_PA(int PA[], int n){
    printf("\nDuong di lon nhat:\n");
    printf("%d", PA[0]);
    for(int i=1;i<n;i++)
        printf(" -> %d", PA[i]);

    printf("\nTong = %d\n", GiaPA(PA,n));
}

// ================== MAIN ==================
int main(){
    int a[size][size];
    int n;

    Read_Data(a,&n);
    Print_Data(a,n);

    int F[size][size];
    int PA[size];

    Tao_Bang(a,n,F);
    In_Bang(F,n);

    Tra_Bang(a,F,n,PA);
    Print_PA(PA,n);

    return 0;
}