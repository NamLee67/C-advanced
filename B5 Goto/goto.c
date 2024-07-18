#include <stdio.h>

void checkEventOrNot(int num){
    if (num % 2 == 0){
        goto event;
    }else {
        goto odd; 
    }   
event:
    printf("So chan");
    return;

odd:
    printf("So le");
    return;
}
int main(int argc, char const *argv[])
{
    int n = 2;
    checkEventOrNot(n);
    return 0;
}
