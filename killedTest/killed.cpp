#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define block (1024*1024*64L)
int main(int argc, char *argv[])
{
    unsigned long total = 0L;
    while(1)
    {

        char *mm = (char*)malloc(block);
        usleep(100000);
        if(NULL == mm)
        {
            continue;
        }
        bzero(mm, block);
    }
    return 0;
}
