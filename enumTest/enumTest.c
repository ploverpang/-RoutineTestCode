#include <stdio.h>

int main(int argc, char *argv[])
{
   /*! \enum name
    *
    *  Detailed description
    */
   enum name {RED=-10,
            BLUE,
            YELLOW};
   enum name color = RED;
   printf("color = %d\n", color);
   for (int i = 0; i < 3; ++i) {
       printf("enum = %d\n", color);
       color++;

   }
    return 0;
}
