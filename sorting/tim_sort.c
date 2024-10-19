#include <stdio.h>   
#include <stdlib.h> 
#include <string.h>  

#define RUN 32  // Size of the subarrays that will be sorted using insertion sort

// Function to perform insertion sort on a subarray
void insertionSort(int arr[], int l, int r) {
    // Loop through each element from the second element in the subarray
    for (int i = l + 1; i <= r; i++) {
        int temp = arr[i];  // Store the current element to be positioned
        int j = i - 1;
        
        // Shift elements that are greater than temp to one position ahead
        while (j >= l && arr[j] > temp) {
            arr[j + 1] = arr[j];  // Shift the larger element rightwards
            j--;
        }
        arr[j + 1] = temp;  // Place the stored element at its correct position
    }
}

// Function to merge two sorted subarrays into a single sorted array
void merge(int arr[], int l1, int m, int r1) {
    int len1 = m - l1 + 1;  // Length of the left subarray
    int len2 = r1 - m;     // Length of the right subarray
    
    // Dynamically allocate memory for the temporary left and right subarrays
    int *leftArr = (int *)malloc(len1 * sizeof(int));
    int *rightArr = (int *)malloc(len2 * sizeof(int));

    // Copy the values of the left and right subarrays from the main array
    for (int i = 0; i < len1; i++)
        leftArr[i] = arr[l1 + i];
    for (int i = 0; i < len2; i++)
        rightArr[i] = arr[m + 1 + i];

    // Initialize pointers for traversing leftArr, rightArr, and the main array
    int i = 0, j = 0, k = l1;
    
    // Merge the two subarrays back into the main array in sorted order
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];  // Copy the smaller element from leftArr
            i++;
        } else {
            arr[k] = rightArr[j];  // Copy the smaller element from rightArr
            j++;
        }
        k++;  // Move to the next position in the main array
    }

    // Copy any remaining elements from leftArr (if any)
    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    // Copy any remaining elements from rightArr (if any)
    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

    // Free the dynamically allocated memory for leftArr and rightArr
    free(leftArr);
    free(rightArr);
}

// Tim Sort implementation
void timSort(int arr[], int n) {
    // Sort individual subarrays of size RUN using insertion sort
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, (i + RUN - 1 < n - 1) ? i + RUN - 1 : n - 1);  
        // Sort subarrays starting at i, and ending at either i + RUN - 1 or n - 1, whichever is smaller

    // Merge sorted subarrays iteratively using merge sort technique
    for (int size = RUN; size < n; size = 2 * size) {
        // Merge arrays in pairs of size 'size'
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;  // Define the midpoint for the merge
            int right = (left + 2 * size - 1 < n - 1) ? left + 2 * size - 1 : n - 1;  // Define the right boundary

            if (mid < right)  // If there are at least two subarrays to merge
                merge(arr, left, mid, right);  // Merge them
        }
    }
}

// Utility function to print the elements of the array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)  // Iterate through the array
        printf("%d ", arr[i]);  // Print each element followed by a space
    printf("\n");  // Print a new line after the array
}

int main() {
    // Initialize the array to be sorted
    int arr[] = {20, 21, 7, 23, 19, 15, 12, 7, 22, 9, 4};  // Unsorted array
    int n = sizeof(arr) / sizeof(arr[0]);  // Calculate the number of elements in the array

    printf("Original array:\n");
    printArray(arr, n);  // Print the original (unsorted) array

    timSort(arr, n);  // Sort the array using Tim Sort

    printf("Sorted array:\n");
    printArray(arr, n);  // Print the sorted array

    return 0;  // End the program
}
