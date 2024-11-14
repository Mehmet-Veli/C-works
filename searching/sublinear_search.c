/**
 * @file
 * @brief Program to perform a "sublinear search" of a target
 * value in a given *sorted* array by skipping elements.
 * @authors [Your Name] - iterative and recursive algorithms
 */

#include <assert.h>
#include <stdio.h>
#include <math.h>

/** Recursive implementation
 * \param[in] arr array to search
 * \param[in] l left index of search range
 * \param[in] r right index of search range
 * \param[in] x target value to search for
 * \param[in] step_size the size of steps to skip in each search iteration
 * \returns location of x assuming array arr[l..r] is present
 * \returns -1 otherwise
 */
int sublinear_search_recursive(const int *arr, int l, int r, int x, int step_size)
{
    if (l > r) {
        return -1; // Element is not present in array
    }

    int mid = l + step_size;

    // Check if we've found the element
    if (mid > r) {
        return -1; // Exceeded range without finding the element
    } else if (arr[mid] == x) {
        return mid; // Element found
    } else if (arr[mid] > x) {
        // If element at mid is greater than x, search the remaining part from l to mid - 1
        return sublinear_search_recursive(arr, l, mid - 1, x, 1);
    } else {
        // Else continue with a larger step from mid + step_size to r
        return sublinear_search_recursive(arr, mid + 1, r, x, step_size);
    }
}

/** Iterative implementation
 * \param[in] arr array to search
 * \param[in] n length of the array
 * \param[in] x target value to search for
 * \param[in] step_size the size of steps to skip in each search iteration
 * \returns location of x assuming array arr is present
 * \returns -1 otherwise
 */
int sublinear_search_iterative(const int *arr, int n, int x, int step_size)
{
    int i = 0;

    // Traverse the array in steps of step_size
    while (i < n) {
        // Check if element is found at current position
        if (arr[i] == x) {
            return i;
        }
        // If the current element is greater than x, do a linear search backwards
        if (arr[i] > x) {
            for (int j = i - step_size + 1; j < i; j++) {
                if (j >= 0 && arr[j] == x) {
                    return j;
                }
            }
            return -1; // Element not found
        }
        // Move to the next step
        i += step_size;
    }

    // Check the last block linearly
    for (int j = i - step_size + 1; j < n; j++) {
        if (arr[j] == x) {
            return j;
        }
    }

    return -1; // Element is not present in array
}

/** Test implementations */
void test()
{
    int arr[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int n = sizeof(arr) / sizeof(arr[0]);
    int step_size = sqrt(n); // Choosing a step size based on array size

    printf("Test 1.... ");
    int x = 7;
    int result = sublinear_search_recursive(arr, 0, n - 1, x, step_size);
    assert(result == 3);
    printf("passed recursive... ");
    result = sublinear_search_iterative(arr, n, x, step_size);
    assert(result == 3);
    printf("passed iterative...\n");

    printf("Test 2.... ");
    x = 8; // Element not in array
    result = sublinear_search_recursive(arr, 0, n - 1, x, step_size);
    assert(result == -1);
    printf("passed recursive... ");
    result = sublinear_search_iterative(arr, n, x, step_size);
    assert(result == -1);
    printf("passed iterative...\n");
}

/** Main function */
int main(void)
{
    test();
    return 0;
}
