#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* returnStr(char* str)
{
    sprintf(str, "%s,%s\n","hello", "world");
    return str;
       /*printf("%s", str);*/
}

int main(int argc, char *argv[])
{

    int a[10];
    for (int i = 0; i < 10; ++i) {
        a[i] = i;
    }

    int *pa = a;
    printf("pa=%d, *pa = %d\n",pa, *pa);
    *pa++ = *pa;
    printf("pa=%d, *pa = %d\n",pa, *pa);

    for (int i = 0; i < 10; ++i) {
        printf("a[%d] = %d\n",i, a[i]);
    }

    char *p = malloc(1280);
    sprintf(p, "%s1.0", p);
    sprintf(p, "%s\t2.0", p);
    sprintf(p, "%s\n", p);

    printf("p is:%s\n", p);

    int len = 2;
    int va_array[len];
    int i;

    for(i = 0; i < len; ++i) {
        va_array[i] = i;
    }

    for(i = 0; i < len; ++i) {
        printf("va_array[%d] = %d\n", i, va_array[i]);;
    }
    char* str2 = "Hello world!";
    printf("str2 len is %d\n", strlen(str2));
    char str[128];
    printf("%s", returnStr(str));
    return 0;
}
