#include <stdio.h>  
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct SinhVien {    
    char maSV[100];
    char hoTen[50];
    float gpa;
};

typedef struct SinhVien SV;

void Nhapdata(SV *a) {  
    getchar();
    printf("Ma so sinh vien: "); 
    fgets(a->maSV, 100, stdin);
    a->maSV[strcspn(a->maSV, "\n")] = '\0';  // Remove newline character if present

    printf("Nhap ho ten: ");
    fgets(a->hoTen, 50, stdin);
    a->hoTen[strcspn(a->hoTen, "\n")] = '\0';  // Remove newline character if present

    printf("Nhap diem GPA: ");
    scanf("%f", &a->gpa);
}

void Indata(SV a, int n) {   
    printf("Thong tin cua sinh vien thu %d: %s - %s - %.2f\n", n + 1, a.maSV, a.hoTen, a.gpa);
}

void timkiem1(SV a[],int n, char m[100]){   
    for (int i; i < n; i++){
        if(strcmp(m,a[i].maSV)==0)  
        {
            Indata(a[i],i);
            return;
        }
    }
    printf("Khong tim thay thong tin!!!\n");
}

void timkiem2(SV a[],int n){    
    float res = 0; int pos;
    for (int i =0; i < n; i++){
        if(a[i].gpa > res){
            res = a[i].gpa;
            pos = i;
        }
    }
    Indata(a[pos],pos);
}

void sapxep(SV a[],int n){  
    for (int i = 0;i < n-1 ;i++){
        int max_idx = i;
        for (int j = i+1; j < n; j++){
            if(a[j].gpa > a[max_idx].gpa){
                max_idx = j;
            }
        }
        if (max_idx != i) {
            SV tmp = a[i];
            a[i] = a[max_idx];
            a[max_idx] = tmp;
        }
    }

}

void cmp(const void *a, const void *b){ 
    SV *x = (SV *) a;
    SV *y = (SV *) b;
    if (x->gpa > y->gpa)    return 1;
    else return -1;
}
int main() {  
    int n;  
    char m[100];
    printf("So luong sinh vien: ");
    scanf("%d", &n);
    SV a[n];
    for(int k = 0; k < n; k++) {
        Nhapdata(&a[k]);
    }

    for(int k = 0; k < n; k++) {
        Indata(a[k], k);
    }

    // printf("Ma sinh vien muon tim kiem :");
    // scanf("%s",&m);
    // timkiem1(a,n,m);
    // printf("Sinh vien co diem cao nhat :");
    // timkiem2(a,n);

    // sapxep(a, n);
    qsort(a,n,sizeof(SV),cmp);
    printf("\nDanh sach sinh vien sau khi sap xep giam dan theo GPA:\n");
    for (int i = 0; i < n; i++) {
        Indata(a[i], i);
    }

    return 0;
}
