#include <stdio.h>
#include <stdlib.h>

// Function to sort individual buckets using insertion sort
void insertionSort(float bucket[], int n) {
    for (int i = 1; i < n; i++) {
        float key = bucket[i];
        int j = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

// Function to perform bucket sort on array arr[] of size n
void bucketSort(float arr[], int n) {
    // 1) Create n empty buckets
    float **buckets = (float **)malloc(n * sizeof(float *));
    int *bucketSizes = (int *)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        buckets[i] = (float *)malloc(n * sizeof(float));
        bucketSizes[i] = 0;
    }

    // 2) Put array elements in different buckets
    for (int i = 0; i < n; i++) {
        int bucketIndex = n * arr[i];  // Index in bucket
        buckets[bucketIndex][bucketSizes[bucketIndex]++] = arr[i];
    }

    // 3) Sort individual buckets using insertion sort
    for (int i = 0; i < n; i++) {
        if (bucketSizes[i] > 0) {
            insertionSort(buckets[i], bucketSizes[i]);
        }
    }

    // 4) Concatenate all buckets back into arr[]
    int index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < bucketSizes[i]; j++) {
            arr[index++] = buckets[i][j];
        }
    }

    // Free memory for buckets
    for (int i = 0; i < n; i++) {
        free(buckets[i]);
    }
    free(buckets);
    free(bucketSizes);
}

int main() {
    int n;

    // Input number of elements
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    float arr[n];

    // Input array elements
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i + 1);
        scanf("%f", &arr[i]);
    }

    // Perform bucket sort
    bucketSort(arr, n);

    // Output the sorted array
    printf("Sorted array is: \n");
    for (int i = 0; i < n; i++) {
        printf("%f ", arr[i]);
    }

    return 0;
}
