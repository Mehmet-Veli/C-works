/**
 * @file
 * @brief Program to perform a "quadratic search" of a target
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
int quadratic_search_recursive(const int *arr, int l, int r, int x)
{
    if (r >= l)
    {
        // Calculate "midpoint" using a quadratic function
        int mid = l + ((r - l) * (r - l)) / ((r - l + 1) * (r - l + 1));

        // Check if element is present at the midpoint
        if (arr[mid] == x)
            return mid;

        // If the element is smaller than arr[mid], search in the left subarray
        if (arr[mid] > x)
            return quadratic_search_recursive(arr, l, mid - 1, x);

        // Otherwise, search in the right subarray
        return quadratic_search_recursive(arr, mid + 1, r, x);
    }

    // Element is not present in the array
    return -1;
}

/** Iterative implementation
 * \param[in] arr array to search
 * \param[in] l left index of search range
 * \param[in] r right index of search range
 * \param[in] x target value to search for
 * \returns location of x assuming array arr[l..r] is present
 * \returns -1 otherwise
 */
int quadratic_search_iterative(const int *arr, int l, int r, int x)
{
    while (l <= r)
    {
        // Calculate "midpoint" using a quadratic function
        int mid = l + ((r - l) * (r - l)) / ((r - l + 1) * (r - l + 1));

        // Check if element is present at the midpoint
        if (arr[mid] == x)
            return mid;

        // If the element is smaller than arr[mid], search in the left subarray
        if (arr[mid] > x)
            r = mid - 1;
        else // Otherwise, search in the right subarray
            l = mid + 1;
    }

    // Element is not present in the array
    return -1;
}

/** Test implementations */
void test()
{
    int arr[] = {2, 3, 4, 10, 40};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Test 1.... ");
    int x = 10;
    int result = quadratic_search_recursive(arr, 0, n - 1, x);
    assert(result == 3);
    printf("passed recursive... ");
    result = quadratic_search_iterative(arr, 0, n - 1, x);
    assert(result == 3);
    printf("passed iterative...\n");

    printf("Test 2.... ");
    x = 5;
    result = quadratic_search_recursive(arr, 0, n - 1, x);
    assert(result == -1);
    printf("passed recursive... ");
    result = quadratic_search_iterative(arr, 0, n - 1, x);
    assert(result == -1);
    printf("passed iterative...\n");
}

/** Main function */
int main(void)
{
    test();
    return 0;
}
