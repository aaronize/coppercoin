#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TE_SIZE 10

int* inputModule(int* ptrCount)
{
    int* arr, d, i = 0;
    int length = TE_SIZE;
    
    arr = (int*)malloc(TE_SIZE * sizeof(int));
    memset(arr, 0, length * sizeof(int));

    printf("Input numbers until you input zero:\n");
    while (1)
    {
        scanf("%d", &d);
        *ptrCount += 1;
        if (0 == d)
        {
            arr[i] = 0;
            break;
        } 
        else
        {
            arr[i++] = d;
        }
        if (i >= length)
        {
            realloc(arr, 2 * length * sizeof(int));
            memset(arr + length, 0, length * sizeof(int));
            length += 2;
        }
    }
    
    return arr;
}

// output module
void outputModule(int* arr, int* ptrCount)
{
    int i;

    printf("\nOutput all elements that have been input:\n");
    for (i = 0; i < *ptrCount; i++)
    {
        if (i && i%5 == 0)
            printf("\n");
        printf("\t%d", * (arr + i));
    }

    free(ptrCount);
    free(arr);
}

int main()
{
    int i = 0;
    int* ptrCount;
    int* arr;

    // Apply calloc()
    ptrCount = (int *)calloc(1, sizeof(int));
    // Input Module
    arr = inputModule(ptrCount);
    // Before free() function, output the count of input numbers
    printf("\n\nBefore using free() function, Count: %d", *ptrCount);
    // Output Module
    outputModule(arr, ptrCount);
    // After free() function, output the count of input numbers
    printf("\n\nAfter using free() function, Count: %d", *ptrCount);
    return 0;
}
