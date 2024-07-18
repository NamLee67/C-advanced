#include <stdio.h>
#include <string.h>

struct DuongBo{
    char xemay;
    char xedap;
    char oto;
};

struct DuongThuy{
    char tauthuy;
    char cano;
    char thuyen;
};

struct DuongHangKhong{
    char maybay;
    char tructhang;
};


// Chỉ lựa chọn một kiểu dữ liệu trong một lần sử dụng theo dạng datalist thì dùng union
union PhuongTien{
    struct DuongBo db;
    struct DuongThuy dt;
    struct DuongHangKhong dhk;
};

// Kĩ thuật struct lồng trong union
char value[]="013.2gioi";
union Data_Frame{
    struct Data{
        char id[3];
        char gpa[4];
        char result[5];
    }data;
    
    char data_storage[12];    
};

int main(int argc, char const *argv[])
{
    union Data_Frame frame;
    strcpy(frame.data_storage,value);
    printf("Value: %s\n",frame.data_storage);
    strncpy(frame.data.id, frame.data_storage, 2);  
    strncpy(frame.data.gpa, frame.data_storage + 3, 3); 
    strncpy(frame.data.result, frame.data_storage + 6, 4);
    // Đảm bảo mỗi chuỗi kết thúc đúng cách
    frame.data.id[3] = '\0';     // Thêm ký tự kết thúc cho id
    frame.data.gpa[4] = '\0';    // Thêm ký tự kết thúc cho gpa
    frame.data.result[5] = '\0'; // Thêm ký tự kết thúc cho result
    printf("ID: %s\n", frame.data.id);
    printf("GPA: %s\n", frame.data.gpa);
    printf("Result: %s\n", frame.data.result);

    return 0;
}




