#include <stdio.h>
#include <stdarg.h>     // Cần thiết để sử dụng va_list, va_start, va_arg, và va_end


#define SIZE 100        

#ifdef  SIZE        // Kiểm tra điều kiện nếu 'SIZE' đã được define hay chưa. Nếu rồi thì sẽ thực hiện dòng lệnh bên trong 
int arr[SIZE];     
#endif

#if SIZE > 100
int abb[200];
#elif SIZE == 100
int abb[100];
#else
int abb[50];
#endif


// Dấu ## dùng để nối chuỗi
#define DECLERE_VARIAVLE(type, name)    type normal_##name;\
type high_##name;\
type low_##name

// Hàm tính tổng khi chưa biết có bao nhiêu tham số đầu vào
int tong(int arr, ...){
    int sum = 0;
    va_list ap;             // Khai báo biến va_list để truy cập các đối số biến
    va_start(ap, arr);      // Khởi tạo ap để trỏ tới đối số đầu tiên sau 'arr'

    // chức năng chính của hàm
    for ( int i = 0; i < arr; i++){
        sum += va_arg(ap, int);     // Lấy đối số tiếp theo là kiểu int và cộng vào sum
    }
    va_end(ap);             // Kết thúc sử dụng va_list, giải phóng tài nguyên nếu cần

    return sum;
}


int main(int argc, char const *argv[])
{
    DECLERE_VARIAVLE(int, bien);
    printf("Tong : %d", tong(5, 1,2,3,4,5));
    return 0;
}
/*
Tiền xử lý (Preprocessing): gcc -E macro.c -o macro.i   GCC sẽ thực hiện việc mở rộng các macro, loại bỏ các chú thích
Biên dịch (Compilation):    gcc -S macro.i -o macro.s   chuyển đổi thành mã hợp ngữ (assembly)
Hợp dịch (Assembly):        gcc -c macro.s -o macro.o   mã hợp ngữ sẽ được chuyển đổi thành mã máy (machine code)
Liên kết (Linking):         gcc macro.o -o macro        tạo thành một tệp thực thi (executable file)  

Biên dịch nhanh :           gcc macro.c -o macro.exe
*/