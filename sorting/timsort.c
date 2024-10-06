/**
 * @file
 * @author [LJFP](https://github.com/ljfp/)
 * @brief [Timsort](https://en.wikipedia.org/wiki/Timsort) implementation
 * @details
 * Timsort is a hybrid stable sorting algorithm, derived from merge sort and
 * insertion sort, designed to perform well on many kinds of real-world data.
 * Worst-case time complexity is O(n log n).
 * Worst-case space complexity is O(n).
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define min(a, b) \
    ((a) < (b) ? (a) : (b)) /* Macro to find the minimum of two numbers */

/**
 * @brief Performs insertion sort on a subarray
 * @param arr Array to be sorted
 * @param left Starting index of the subarray
 * @param right Ending index of the subarray
 */
void insertionSort(int arr[], int left, int right)
{
    for (int i = left + 1; i <= right; i++)
    {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

/**
 * @brief Merges two sorted subarrays of arr[]
 * @param arr The main array containing the subarrays to be merged
 * @param l Left index of the first subarray
 * @param m Ending index of the first subarray (midpoint)
 * @param r Right index of the second subarray
 */
void merge(int arr[], int l, int m, int r)
{
    int len1 = m - l + 1;
    int len2 = r - m;

    int *left = (int *)malloc(len1 * sizeof(int));
    int *right = (int *)malloc(len2 * sizeof(int));

    for (int i = 0; i < len1; i++) left[i] = arr[l + i];
    for (int i = 0; i < len2; i++) right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    /* Merging the two subarrays */
    while (i < len1 && j < len2)
    {
        if (left[i] <= right[j])
        {
            arr[k++] = left[i++];
        }
        else
        {
            arr[k++] = right[j++];
        }
    }

    /* Copying remaining elements of left[], if any */
    while (i < len1)
    {
        arr[k++] = left[i++];
    }

    /* Copying remaining elements of right[], if any */
    while (j < len2)
    {
        arr[k++] = right[j++];
    }

    free(left);
    free(right);
}

/**
 * @brief Implementation of Timsort with specified run size
 * @param arr Array to be sorted
 * @param n Size of the array
 * @param run_size Size of the runs. It should be a power of 2.
 */
void timsort(int arr[], int n, int run_size)
{
    /* Sort individual subarrays of size run_size */
    for (int i = 0; i < n; i += run_size)
    {
        insertionSort(arr, i, min((i + run_size - 1), (n - 1)));
    }

    /* Start merging from size run_size */
    for (int size = run_size; size < n; size *= 2)
    {
        /* Pick starting point of left subarray */
        for (int left = 0; left < n; left += 2 * size)
        {
            /* Find ending point of left subarray */
            int mid = min(left + size - 1, n - 1);
            int right = min(left + 2 * size - 1, n - 1);

            /* Merge subarrays arr[left...mid] & arr[mid+1...right] */
            if (mid < right)
            {
                merge(arr, left, mid, right);
            }
        }
    }
}

/**
 * @brief Test function to verify the Timsort implementation.
 */
void test()
{
    const int size = rand() % 500; /* Random array size between 0 and 499 */
    int *arr = (int *)malloc(size * sizeof(int));

    /* Generate 'size' random numbers from -500 to 499 */
    for (int i = 0; i < size; i++)
    {
        arr[i] = (rand() % 1000) - 500; /* Signed random numbers */
    }

    /* Test with different run sizes */
    for (int run_size = 16; run_size <= 64; run_size *= 2)
    {
        /* Copy the original array to preserve it for each run size */
        int *arr_copy = (int *)malloc(size * sizeof(int));
        for (int i = 0; i < size; i++)
        {
            arr_copy[i] = arr[i];
        }

        timsort(arr_copy, size, run_size);

        /* Verify that the array is sorted */
        for (int i = 0; i < size - 1; ++i)
        {
            assert(arr_copy[i] <= arr_copy[i + 1]);
        }

        free(arr_copy);
    }

    free(arr);
}

/**
 * @brief Main function to test Timsort implementation
 * @return 0 on success
 */
int main()
{
    /* Initialize random number generator */
    srand((unsigned int)time(NULL));

    /* Run the test multiple times */
    for (int i = 0; i < 1000; i++)
    {
        test();
    }

    printf("All tests passed successfully.\n");
    return 0;
}
