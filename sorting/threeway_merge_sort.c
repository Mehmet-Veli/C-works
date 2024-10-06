#include <stdio.h>
#include <stdlib.h>

// Function to merge three sorted subarrays
void merge(int arr[], int left, int mid1, int mid2, int right) {
    int i, j, k;
    int n1 = mid1 - left + 1; // Size of the first subarray
    int n2 = mid2 - mid1;     // Size of the second subarray
    int n3 = right - mid2;    // Size of the third subarray

    // Temporary arrays
    int *L = (int*)malloc(n1 * sizeof(int));
    int *M = (int*)malloc(n2 * sizeof(int));
    int *R = (int*)malloc(n3 * sizeof(int));

    // Copy data to temporary arrays
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        M[j] = arr[mid1 + 1 + j];
    for (k = 0; k < n3; k++)
        R[k] = arr[mid2 + 1 + k];

    // Merge the temporary arrays back into arr[]
    i = 0; j = 0; k = 0;
    int idx = left;

    while (i < n1 && j < n2 && k < n3) {
        if (L[i] <= M[j] && L[i] <= R[k]) {
            arr[idx++] = L[i++];
        } else if (M[j] <= L[i] && M[j] <= R[k]) {
            arr[idx++] = M[j++];
        } else {
            arr[idx++] = R[k++];
        }
    }

    // Merge remaining elements of L[]
    while (i < n1 && j < n2) {
        if (L[i] <= M[j]) {
            arr[idx++] = L[i++];
        } else {
            arr[idx++] = M[j++];
        }
    }

    while (j < n2 && k < n3) {
        if (M[j] <= R[k]) {
            arr[idx++] = M[j++];
        } else {
            arr[idx++] = R[k++];
        }
    }

    while (i < n1 && k < n3) {
        if (L[i] <= R[k]) {
            arr[idx++] = L[i++];
        } else {
            arr[idx++] = R[k++];
        }
    }

    // Copy remaining elements of L[]
    while (i < n1) {
        arr[idx++] = L[i++];
    }

    // Copy remaining elements of M[]
    while (j < n2) {
        arr[idx++] = M[j++];
    }

    // Copy remaining elements of R[]
    while (k < n3) {
        arr[idx++] = R[k++];
    }

    // Free temporary arrays
    free(L);
    free(M);
    free(R);
}

// Recursive function to perform 3-way MergeSort
void mergeSort3Way(int arr[], int left, int right) {
    if (left < right) {
        int mid1 = left + (right - left) / 3;
        int mid2 = mid1 + (right - left) / 3 + 1;

        // Recursively sort three subarrays
        mergeSort3Way(arr, left, mid1);
        mergeSort3Way(arr, mid1 + 1, mid2);
        mergeSort3Way(arr, mid2 + 1, right);

        // Merge the sorted subarrays
        merge(arr, left, mid1, mid2, right);
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Main function to test 3-way MergeSort
int main() {
    int arr[] = {12, 4, 7, 9, 6, 3, 8, 10};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    mergeSort3Way(arr, 0, n - 1); // Sort the array

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
