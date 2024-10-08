#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#define N 32  // Defining the array size for testing

// Function to print the array
void display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform a bitonic merge
void bitonicMerge(int arr[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++) {
            if (dir == (arr[i] > arr[i + k])) {
                swap(&arr[i], &arr[i + k]);
            }
        }
        bitonicMerge(arr, low, k, dir);
        bitonicMerge(arr, low + k, k, dir);
    }
}

// Function to recursively sort a bitonic sequence
void bitonicSort(int arr[], int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        bitonicSort(arr, low, k, 1);      // Sort in ascending order
        bitonicSort(arr, low + k, k, 0);  // Sort in descending order
        bitonicMerge(arr, low, cnt, dir); // Merge the entire sequence
    }
}

// Main function to sort the array using Bitonic Sort
void bitonicSortArray(int arr[], int n, int ascending) {
    bitonicSort(arr, 0, n, ascending);
}

// Function to check if an array is sorted
bool is_sorted(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

// Self-test function for Bitonic Sort
void test_bitonicSort() {
    int test1[] = {10, 11, 9, 8, 4, 7, 3, 8};
    int expected1[] = {3, 4, 7, 8, 8, 9, 10, 11};
    bitonicSortArray(test1, 8, 1);
    for (int i = 0; i < 8; i++) {
        assert(test1[i] == expected1[i]);
    }

    int test2[] = {50, 40, 30, 20, 10, 0};
    int expected2[] = {0, 10, 20, 30, 40, 50};
    bitonicSortArray(test2, 6, 1);
    for (int i = 0; i < 6; i++) {
        assert(test2[i] == expected2[i]);
    }

    int test3[] = {3, 3, 3, 3, 3, 3};
    int expected3[] = {3, 3, 3, 3, 3, 3};
    bitonicSortArray(test3, 6, 1);
    for (int i = 0; i < 6; i++) {
        assert(test3[i] == expected3[i]);
    }

    // Check random array generation and sorting
    int random_test[N];
    srand(time(0));
    for (int i = 0; i < N; i++) {
        random_test[i] = rand() % (N << 1);
    }
    bitonicSortArray(random_test, N, 1);
    assert(is_sorted(random_test, N));

    printf("All test cases passed successfully!\n");
}

// Main function to initialize array and call Bitonic Sort
int main() {
    // Self-test the implementation
    test_bitonicSort();

    // Manual testing with randomly generated array
    int arr[N];

    // Generate random numbers for the array
    srand(time(0)); // Seed for random number generation
    for (int i = 0; i < N; i++)
        arr[i] = rand() % (N << 1); /* Random numbers from 0 to 2N */

    printf("Original array: ");
    display(arr, N);

    // Call the Bitonic Sort function
    bitonicSortArray(arr, N, 1);

    printf("Sorted array: ");
    display(arr, N);

    return 0;
}

