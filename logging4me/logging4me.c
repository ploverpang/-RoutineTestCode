#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("%s, %s, %d: I'm a message\n","abc", __FILE__, __LINE__);
    return 0;
}
