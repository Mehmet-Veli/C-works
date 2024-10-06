#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RUN 32 // Size of the run

// Function to perform insertion sort on a subarray
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int key = arr[i]; // Element to be inserted
        int j = i - 1;
        
        // Move elements of arr[left..i-1] that are greater than key
        // to one position ahead of their current position
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Place the key in its correct position
    }
}

// Function to merge two sorted subarrays
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray

    // Create temporary arrays for left and right subarrays
    int *L = (int*)malloc(n1 * sizeof(int));
    int *R = (int*)malloc(n2 * sizeof(int));

    // Copy data to temporary arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    i = 0; 
    j = 0; 
    k = left;

    // Merge while both subarrays have elements
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i]; // If the current element of L[] is smaller
            i++;
        } else {
            arr[k] = R[j]; // If the current element of R[] is smaller
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    free(L);
    free(R);
}

// Main TimSort function
void timSort(int arr[], int n) {
    // Step 1: Sort individual subarrays of size RUN
    for (int start = 0; start < n; start += RUN) {
        int end = (start + RUN - 1 < n - 1) ? (start + RUN - 1) : (n - 1);
        insertionSort(arr, start, end); // Sort the run using insertion sort
    }

    // Step 2: Merge the sorted runs
    for (int size = RUN; size < n; size *= 2) { // Double the size of the run
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1; // Ending index of the left subarray
            int right = ((left + 2 * size - 1) < (n - 1)) ? (left + 2 * size - 1) : (n - 1); // Ending index of the right subarray

            // Merge the two subarrays if valid
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }
}

// Function to print the array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]); // Print each element
    printf("\n"); // New line after printing the array
}

// Main function to test the TimSort implementation
int main() {
    int arr[] = {5, 21, 7, 23, 19, 10, 1, 34, 0}; // Example array
    int n = sizeof(arr) / sizeof(arr[0]); // Calculate number of elements in the array

    printf("Original array: ");
    printArray(arr, n); // Print the original array

    timSort(arr, n); // Call TimSort on the array

    printf("Sorted array: ");
    printArray(arr, n); // Print the sorted array

    return 0; // End of program
}
