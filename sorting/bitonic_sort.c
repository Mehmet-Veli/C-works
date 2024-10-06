#include <stdio.h>

// Function to compare and swap elements
void compareAndSwap(int *x, int *y, int order) {
    if ((order == 1 && *x > *y) || (order == 0 && *x < *y)) {
        int temp = *x;
        *x = *y;
        *y = temp;
    }
}

// Function to perform bitonic merge
void bitonicMerge(int arr[], int low, int cnt, int order) {
    if (cnt > 1) {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++) {
            compareAndSwap(&arr[i], &arr[i + k], order);
        }
        bitonicMerge(arr, low, k, order);      // First half
        bitonicMerge(arr, low + k, k, order);  // Second half
    }
}

// Function to sort a bitonic sequence
void bitonicSort(int arr[], int low, int cnt, int order) {
    if (cnt > 1) {
        int k = cnt / 2;
        // Sort first half in ascending order
        bitonicSort(arr, low, k, 1);
        // Sort second half in descending order
        bitonicSort(arr, low + k, k, 0);
        // Merge the whole sequence in order
        bitonicMerge(arr, low, cnt, order);
    }
}

// Helper function to start the sorting process
void sort(int arr[], int n, int order) {
    bitonicSort(arr, 0, n, order);
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function to test Bitonic Sort
int main() {
    int arr[] = {12, 4, 7, 9, 6, 3, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    // Sort the array in ascending order
    sort(arr, n, 1);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
