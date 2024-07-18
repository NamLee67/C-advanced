#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

void test (){
    printf("\ntest 1:");
}

int main(int argc, char const *argv[])
{
    atexit(test);   // hàm chạy sau toàn bộ chương trình, khi chương trình kết thúc thì sẽ chạy hàm được gọi đến.
                    // ví dụ : hàm được gọi đến lưu thông tin của game như điểm sổ, màn chơi, tên người chơi,...
                    // ứng dụng trong vi điều khiển : lưu các thông tin quan trọng khi có sự cố mất nguồn

    printf("\ntest 2:");
    printf("\ntest 3:");
    return 0;
}



