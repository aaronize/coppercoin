/**
 * 可变参函数 variadic function
 * 
 */
#include <stdio.h>
#include <stdarg.h>

double average(int num, ...);

int main()
{
    double sum = average(5, 1.0, 2.0, 3.0, 4.0, 5.0);
    printf("The average is: %f\n", sum);
    return 0;
}

double average(int num, ...)
{
    int i;
    double sum = 0.0;
    va_list argptr;
    va_start(argptr, num);

    for (i = 0; i < num; i++)
    {
        printf("parameter: %f\n", va_arg(argptr, double));
        // sum += va_arg(argptr, int);
    }

    va_end(argptr);

    return sum/num;
}
