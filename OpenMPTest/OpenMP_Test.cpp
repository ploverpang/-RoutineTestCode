#include <stdio.h>
#include <iostream>
#include <omp.h>

int main(int argc, char* argv[])
{
    long long b=0;
    const double start_time = omp_get_wtime();
#pragma omp parallel
{
#pragma omp for
    for(int i=0; i<1000000; i++)
    {
        if(i== 100)
            break;
        int b =0;
    }
}
double processing_time = omp_get_wtime()-start_time;
    std::cout << processing_time << std::endl;
    return 0;

}
