#include <stdlib.h>
#include <stdint-gcc.h>
#include <stdio.h>
#include <string.h>

char mang1[]="Hello World";
char mang2[]="Hello World!!!";

uint8_t StringEqual(const char str1[], const char str2[]){
    while (*str1 && *str2)
    {
        str1++;
        str2++;
        if(str1 == str2){
            return 1;
        }else{
            return 0;
        }
    }
}

int my_atoi(const char *str){
    int result;
    int sign = 1;
    int i = 0;

    // xử lý khoảng trắng
    while(str[i] == ' '|| str[i] == '\t'|| str[i] == '\n')
    {
        i++;
    }
    // xử lý dấu
    if (str[i] == '-' || str[i] == '+' )
    {
        sign = (str[i] == '-') ? -1 : 1;    // điều_kiện ? giá_trị_nếu_đúng : giá_trị_nếu_sai
        i++;
    }
    // chuyển đổi ký tự số thành số nguyên
    while (str[i]>='0' && str[i]<='9')
    {
        result = result*10 + (str[i]-'0');
        i++;
    }
    return sign*result;   
}

int my_strtod(const char *str, char **ptr){
    for (int i = 0; i < strlen(str); i++)
    {
        /* code */
    }
    
}


int main(int argc, char const *argv[])
{
    #define mode 3
    #if mode == 0
    int val;
    char str[10];

    strcpy(str,"123.56 456.56 Hello World !\n");
    printf("Chuoi : %s\n",str);

    val = atoi(str);   // ascii to interger 
    printf("Val = %d",val);
    
    #elif mode == 1
    char str[30];
    char *ptr;
    char *arr;
    double ref1;
    double ref2;
    strcpy(str,"123.56 456.56 Hello World !\n");
    // Convert the string 'str' to a double value and store the result in 'ref'.
    // The function 'strtod' stops at the first character that is not a valid part of a double number.
    // The pointer 'ptr' is set to point to the first character after the last valid character of the number.
    ref1 = strtod(str, &ptr);
    printf("Gia tri cua ref1 : %f\n",ref1);
    ref2 = strtod(ptr, &arr);
    printf("Gia tri cua ref2 : %f\n",ref2);
    printf("Chuoi : %s\n",arr);

    #elif mode == 2
    char str[] = "Hello my nam is NamLee";
    char *token = strtok(str, " ");

    while (token!= NULL){
        printf("%s\n", token);
        token = strtok(NULL, " ");  
    }
    #elif mode == 3
    int i;
    char buffer[30];

    printf("Nhap vao mot so bat ky :");
    scanf("%d",&i);

    itoa(i, buffer,2);
    printf("Chuoi ky tu nhi phan : %s\n",buffer);

    itoa(i, buffer, 10);
    printf("Chuoi ky tu thap phan : %s\n",buffer);

    itoa(i, buffer, 16);
    printf("Chuoi ky tu thap luc phan : %s\n",buffer);
    #endif

    return 0;
}
