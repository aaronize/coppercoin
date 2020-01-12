#include <stdio.h>
#include <stdlib.h>

int* fn1()
{
    int i = 0;

    // warning: function returns address of local variable
    return &i;
}

int main()
{
    int *i = fn1();
    printf("return value: %d\n", *i);

    *i = 6;
    printf("value: %d\n", *i);
    return 0;
}
