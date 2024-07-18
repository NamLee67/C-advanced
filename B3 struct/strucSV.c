#include <stdio.h>
#include <string.h>
#include <time.h>

struct Date{
    int day;
    int month;
    int year;  
};
typedef struct Date Date;
struct SinhVien{
    char mssv[50];
    char hoTen[100];
    char gioiTinh[10];
    Date ngaySinh;
    int tuoi;
    float gpa;
    char hocLuc[50];
    char maLop[10];
};

typedef struct SinhVien SV;
void NhapSinhVien(SV *sv);
void InSinhVien(SV *sv);

void readInput(char *buffer,int size) {
    fflush(stdin);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';  // Loại bỏ ký tự newline nếu có
}
void NhapSinhVien(SV *sv){
    printf("MSSV :");   readInput(sv->mssv, sizeof(sv->mssv)); 
    printf("\nHo va ten :"); readInput(sv->hoTen, sizeof(sv->hoTen));
    printf("\nGioi tinh :");  readInput(sv->gioiTinh, sizeof(sv->gioiTinh));
    printf("\nNgay sinh :");  scanf("%d %d %d", &sv->ngaySinh.day, &sv->ngaySinh.month, &sv->ngaySinh.year);
    getchar();
    printf("\nGPA :"); scanf("%f",&sv->gpa);
    while (getchar() != '\n'); 
    printf("\nMa lop :"); readInput(sv->maLop, sizeof(sv->maLop)); 

}

void InSinhVien(SV *sv) {
    sv->tuoi = 2024 - sv->ngaySinh.year;  // Tính tuổi từ năm sinh
    if(sv->gpa >=3.6 && sv->gpa <= 4.0){
        strcpy(sv->hocLuc,"Xuat sac");  //kiểu dữ liệu là chuối thì không gán được, dùng hàm copy
    }
    else if(sv->gpa >=3.2 && sv->gpa < 3.6){
        strcpy(sv->hocLuc,"Gioi");
    }   
    else if(sv->gpa >=2.5 && sv->gpa < 3.2){
        strcpy(sv->hocLuc,"Kha");
    }else{
        strcpy(sv->hocLuc,"Trung binh");
    } 
    printf("%5s\t %10s \t %10s \t %5s \t\t %02d/%02d/%04d \t %5d \t %5.2f \t %5s\n",
           sv->maLop, sv->mssv, sv->hoTen, sv->gioiTinh, sv->ngaySinh.day, sv->ngaySinh.month,
           sv->ngaySinh.year, sv->tuoi, &sv->gpa, sv->hocLuc);
}

void LuuSinhVienVaoFile(SV *sv, const char *fileName) {
    FILE *file = fopen(fileName, "a");  // Mở file ở chế độ "append"
    
    if (file == NULL) {
        printf("Không thể mở file!\n");
        return;
    }
    
    sv->tuoi = 2024 - sv->ngaySinh.year;  // Tính tuổi từ năm sinh
    
    if (sv->gpa >= 3.6 && sv->gpa <= 4.0) {
        strcpy(sv->hocLuc, "Xuat sac");
    } else if (sv->gpa >= 3.2 && sv->gpa < 3.6) {
        strcpy(sv->hocLuc, "Gioi");
    } else if (sv->gpa >= 2.5 && sv->gpa < 3.2) {
        strcpy(sv->hocLuc, "Kha");
    } else {
        strcpy(sv->hocLuc, "Trung binh");
    } 
    
    fprintf(file, "%5s\t %10s \t %10s \t %5s \t\t %02d/%02d/%04d \t %5d \t %5.2f \t %5s\n",
            sv->maLop, sv->mssv, sv->hoTen, sv->gioiTinh, sv->ngaySinh.day, sv->ngaySinh.month,
            sv->ngaySinh.year, sv->tuoi, sv->gpa, sv->hocLuc);
    
    fclose(file);
}

int main(){
    int n;
    printf("So luong sinh vien: ");
    scanf("%d", &n);
    while (getchar() != '\n'); 
    SV sv[n];
    
    for(int k = 0; k < n; k++) {
        NhapSinhVien(&sv[k]);
        LuuSinhVienVaoFile(&sv[k], "sinhvien.txt");
    }
    printf("\n");
    printf("%5s\t %10s \t %10s \t %5s \t %5s \t %5s \t %5s \t %5s","Ma lop","Mssv","Ho va Ten","Gioi tinh","Ngay sinh","Tuoi","GPA","Hoc luc");
    
    for(int k = 0; k < n; k++) {
        printf("\n");
        InSinhVien(&sv[k]);
    }

    return 0;
}
