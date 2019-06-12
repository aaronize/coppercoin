#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printArray(char **arr, int arrNum)
{
    for (int i = 0; i < arrNum; i++)
    {
        printf("方式1输出%s\n", arr[i]);
        printf("方式2输出%s\n", *(arr + i));
    }
}

void sortArray(char **arr, int arrNum)
{
    int i = 0, j = 0;
    char *tmp = NULL;

    printf("排序前输出：\n");
    for (i = 0; i < arrNum; i++)
    {
        printf("%s\n", *(arr + i));
    }

    for (i = 0; i < arrNum; i++)
    {
        for (j = i + 1; j < arrNum; j++)
        {
            if (strcmp(arr[i], arr[j]) > 0)
            {
                tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
    printf("排序后输出：\n");
    for (i = 0; i < arrNum; i++)
    {
        printf("%s\n", *(arr + i));
    }
}

int main()
{
    int arrNum = 0;
    char *arr[] = {"aasasa", "ababdd", "wdafwd", "ihiytnf", "wdafcr", "htotte"};
    arrNum = sizeof(arr) / sizeof(arr[0]);

    printf("sizeof(arr): %d\n", sizeof(arr));
    printf("sizeof(arr[0]): %d\n", sizeof(arr[3]));

    printArray(arr, arrNum);
    sortArray(arr, arrNum);

    return 0;
}
