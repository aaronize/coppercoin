#include <stdio.h>

/**
 * binary search
 */

int binarySearch(int arr[], int head, int tail, int target)
{
    if (tail >= 1)
    {
        int mid = head + (tail - head) / 2;

        if (arr[mid] == target) return mid;

        if (arr[mid] > target) return binarySearch(arr, head, mid, target);

        return binarySearch(arr, mid, tail, target);
    }

    return -1;
}

int main()
{
    int arr[] = {2, 10, 24, 56, 67, 71, 82, 97};
    int n = sizeof(arr) / sizeof(arr[0]);

    int target = 10;
    int result = binarySearch(arr, 0, n, target);

    (result == -1) ? printf("not found")
                    : printf("index is %d\n", result);

    return 0;
}
