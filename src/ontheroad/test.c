#include <stdio.h>
#include <string.h>

typedef struct TestSt
{
    unsigned short      sa_family;
    char                sa_data[14];
} TestSt;

int main(int argc, char **argv)
{
    // 
    int a[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {11, 12, 13, 14}, {15, 16, 17, 18}};
    int i = 0, j = 0, s = 0;

    while (i++ < 4)
    {
        if (i == 2 || i == 4) continue;
        j = 0;
        do {
            s += a[i][j];
            j++;
        } while (j < 4);
    }

    printf("%d\n", s);

    printf("char: %d\n", sizeof(char)); // 1
    printf("char *: %d\n", sizeof(char *)); // 8


    return 0;
}
