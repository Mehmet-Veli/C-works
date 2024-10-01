// Function to compare two integers for qsort
// This function is used to sort the array by comparing two integer values.
int compare(const void* a, const void* b) { return (*(int*)a - *(int*)b); }

// Function to find all unique triplets in the array that sum to zero
// This function uses sorting and a two-pointer approach to find triplets
// in a given array that add up to zero, ensuring no duplicate triplets are
// returned. The result is dynamically allocated and returned, along with column
// sizes and the total number of triplets found.
int** threeSum(int* nums, int numsSize, int* returnSize,
               int** returnColumnSizes)
{
    if (numsSize < 3)
    {
        *returnSize = 0;
        return NULL;
    }

    // Sort the array
    qsort(nums, numsSize, sizeof(int), compare);

    int** result = (int**)malloc(numsSize * numsSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(numsSize * sizeof(int));
    *returnSize = 0;

    // Iterate through each element as the first element of the triplet
    for (int i = 0; i < numsSize - 2; ++i)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;  // Skip duplicates for the first number
        }

        int left = i + 1;
        int right = numsSize - 1;

        // Two-pointer approach to find the second and third elements
        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0)
            {
                // Store the triplet
                result[*returnSize] = (int*)malloc(3 * sizeof(int));
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                // Skip duplicates for the second and third numbers
                while (left < right && nums[left] == nums[left + 1])
                {
                    left++;
                }
                while (left < right && nums[right] == nums[right - 1])
                {
                    right--;
                }

                left++;
                right--;
            }
            else if (sum < 0)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }

    return result;
}
