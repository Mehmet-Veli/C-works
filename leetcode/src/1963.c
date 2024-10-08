// Time complexity: O(n)
// Space complexity: O(1)

int minSwaps(char* s)
{
    int n = strlen(s);
    int sum = 0;
    int minmSum = INT_MAX;

    for (int i = 0; i < n; i++)
    {
        if (s[i] == '[')
        {
            // if opening bracket comes increase the sum
            sum = sum + 1;
        }
        else
        {
            sum = sum - 1;
            // in case of closing bracket decrease the sum
        }

        // find the minimum sum
        if (sum < minmSum)
        {
            minmSum = sum;
        }
    }
    // if minimum sum is greater than 0 then no need of swap
    // in one swap we can increase the minimum swap by 2
    if (minmSum > 0)
    {
        return 0;
    }
    else
    {
        return (abs(minmSum) + 1) / 2;
    }
}
