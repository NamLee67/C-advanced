#include <stdio.h>
#include <stdint.h>
#include <time.h>

clock_t start, end;


int main(int argc, char const *argv[])
{
    register uint32_t i;
    // uint32_t i;
    double time;
    start = clock();
    for (i=0; i<1000000000; i++){

    }
    end = clock();
    time = (double)(end - start)/CLOCKS_PER_SEC;
    printf("Time : %f\n", time);

    return 0;
}
