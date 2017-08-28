#include <stdio.h>

struct ST{
    int a;
    int b;
    static cons int c = 3;
};

int main(int argc, char *argv[])
{
    ST st;
    st.a = 1, st.b=2;
    printf("ST.a = %d, ST.b = %d\n", st.a, st.b);

    /*st ={1,2};*/
    /*printf("ST.a = %d, ST.b = %d\n", st.a, st.b);*/
    printf("ST.c  = %d\n", st.c);
    return 0;
}
