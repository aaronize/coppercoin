/*
存储类demo
 */
#include <stdio.h>

void reportCount();
void accumulate(int k);

int count = 0;

int main(void)
{
    int value;
    register int i;

    printf("Enter a positive integer (0 to quit): ");
    while (scanf("%d", &value) == 1 && value > 0)
    {
        ++count;
        for (i = value; i >=0; i--)
            accumulate(i);

        printf("Enter a positive integer (0 to quit): ");
    }
    reportCount();

    return 0;
}

void reportCount()
{
    printf("Loop executed %d times\n", count);
}
