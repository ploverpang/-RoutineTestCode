#include <stdio.h>

typedef struct _st {
    int a;
    int b;
    /*! \enum
     *
     *  Detailed description
     */
    enum num {c=3,d=4  };
}ST;

int main(int argc, char *argv[])
{
    ST st ={.a=2, .b=1,};
    printf("ST.a = %d, ST.b = %d\n", st.a, st.b);

    /*st ={1,2};*/
    /*printf("ST.a = %d, ST.b = %d\n", st.a, st.b);*/
    printf("ST.num.c  = %d\n", c);
    return 0;
}
