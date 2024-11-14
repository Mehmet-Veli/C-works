/**
 * @file
 * @brief Program to perform "Meta Binary Search" of a target
 * value in a given *sorted* array.
 * @authors [Your Name] - recursive and iterative algorithms
 */

#include <assert.h>
#include <stdio.h>

/** Recursive implementation
 * \param[in] arr array to search
 * \param[in] l left index of search range
 * \param[in] r right index of search range
 * \param[in] x target value to search for
 * \returns location of x assuming array arr[l..r] is present
 * \returns -1 otherwise
 */
int meta_binary_search_recursive(const int *arr, int l, int r, int x)
{
    if (r >= l)
    {
        // Calculate the mid-point with a different approach
        int mid = l + (r - l) / 3;

        // Check if element is present at the calculated mid
        if (arr[mid] == x)
            return mid;

        // Calculate second mid-point
        int mid2 = r - (r - l) / 3;

        // Check if element is present at the second mid
        if (arr[mid2] == x)
            return mid2;

        // Recursive search based on value at mid points
        if (x < arr[mid])
            return meta_binary_search_recursive(arr, l, mid - 1, x);
        else if (x > arr[mid2])
            return meta_binary_search_recursive(arr, mid2 + 1, r, x);
        else
            return meta_binary_search_recursive(arr, mid + 1, mid2 - 1, x);
    }

    // Element is not present in the array
    return -1;
}

/** Iterative implementation
 * \param[in] arr array to search
 * \param[in] n length of the array
 * \param[in] x target value to search for
 * \returns location of x assuming array arr is present
 * \returns -1 otherwise
 */
int meta_binary_search_iterative(const int *arr, int n, int x)
{
    int l = 0, r = n - 1;

    while (l <= r)
    {
        // Calculate the first mid-point
        int mid = l + (r - l) / 3;

        // Check if element is present at the first mid
        if (arr[mid] == x)
            return mid;

        // Calculate the second mid-point
        int mid2 = r - (r - l) / 3;

        // Check if element is present at the second mid
        if (arr[mid2] == x)
            return mid2;

        // Narrow the search range based on the target value
        if (x < arr[mid])
            r = mid - 1;
        else if (x > arr[mid2])
            l = mid2 + 1;
        else
        {
            l = mid + 1;
            r = mid2 - 1;
        }
    }

    // Element is not present in the array
    return -1;
}

/** Test implementations */
void test()
{
    int arr[] = {2, 3, 4, 10, 40, 50, 60, 70, 80};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Test 1.... ");
    int x = 10;
    int result = meta_binary_search_recursive(arr, 0, n - 1, x);
    assert(result == 3);
    printf("passed recursive... ");
    result = meta_binary_search_iterative(arr, n, x);
    assert(result == 3);
    printf("passed iterative...\n");

    printf("Test 2.... ");
    x = 5; // Element not in array
    result = meta_binary_search_recursive(arr, 0, n - 1, x);
    assert(result == -1);
    printf("passed recursive... ");
    result = meta_binary_search_iterative(arr, n, x);
    assert(result == -1);
    printf("passed iterative...\n");
}

/** Main function */
int main(void)
{
    test();
    return 0;
}
