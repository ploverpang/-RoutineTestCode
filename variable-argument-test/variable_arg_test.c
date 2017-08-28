#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

void va_test(int nStr, ...)
{
    va_list ap;
    va_start(ap, nStr);
    for(int va_cnt=0; va_cnt<nStr; ++va_cnt)
    {
        char *p = va_arg(ap, char*);
        printf("va_arg %d: %s\n", va_cnt, p);
    }
    va_end(ap);
}

int main(int argc, char *argv[])
{
    va_test(3, "a","b", "c");
    return 0;
}
