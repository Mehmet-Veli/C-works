#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#define N 32  // Defining the array size
#define RUN 32  // Minimum run size for Tim Sort

// Function to print the array
void display(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function to perform insertion sort on an array
void insertionSort(int arr[], int left, int right) {
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

// Function to merge the sorted runs
void merge(int arr[], int l, int m, int r) {
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];

    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;

    // Merge the two halves
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of left[], if any
    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    // Copy remaining elements of right[], if any
    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
}

// Iterative Timsort function
void timSort(int arr[], int n) {
    for (int i = 0; i < n; i += RUN) {
        insertionSort(arr, i, (i + RUN - 1) < (n - 1) ? (i + RUN - 1) : (n - 1));
    }

    for (int size = RUN; size < n; size = 2 * size) {
        for (int left = 0; left < n; left += 2 * size) {
            int mid = left + size - 1;
            int right = ((left + 2 * size - 1) < (n - 1)) ? (left + 2 * size - 1) : (n - 1);

            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
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

// Self-test function for TimSort
void test_timSort() {
    int test1[] = {10, 11, 9, 8, 4, 7, 3, 8};
    int expected1[] = {3, 4, 7, 8, 8, 9, 10, 11};
    timSort(test1, 8);
    for (int i = 0; i < 8; i++) {
        assert(test1[i] == expected1[i]);
    }

    int test2[] = {50, 40, 30, 20, 10, 0};
    int expected2[] = {0, 10, 20, 30, 40, 50};
    timSort(test2, 6);
    for (int i = 0; i < 6; i++) {
        assert(test2[i] == expected2[i]);
    }

    int test3[] = {3, 3, 3, 3, 3, 3};
    int expected3[] = {3, 3, 3, 3, 3, 3};
    timSort(test3, 6);
    for (int i = 0; i < 6; i++) {
        assert(test3[i] == expected3[i]);
    }

    // Check random array generation and sorting
    int random_test[N];
    srand(time(0));
    for (int i = 0; i < N; i++) {
        random_test[i] = rand() % (N << 1);
    }
    timSort(random_test, N);
    assert(is_sorted(random_test, N));

    printf("All test cases passed successfully!\n");
}

// Main function to initialize array and call timSort
int main() {
    // Self-test the implementation
    test_timSort();

    // Manual testing with randomly generated array
    int arr[N];

    // Generate random numbers for the array
    srand(time(0)); // Seed for random number generation
    for (int i = 0; i < N; i++)
        arr[i] = rand() % (N << 1); /* Random numbers from 0 to 2N */

    printf("Original array: ");
    display(arr, N);

    // Call the Tim Sort function
    timSort(arr, N);

    printf("Sorted array: ");
    display(arr, N);

    return 0;
}
