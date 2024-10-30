/**
 * @file gaussian.c
 * @brief Implementation of the Gaussian function.
 * @details
 * This program calculates the value of the Gaussian function for a given
 * mean and standard deviation at a specific value.
 * The function follows the formula:
 * f(value) = (1 / (std_dev * sqrt(2 * pi))) * exp(-((value - mean)^2) / (2 *
 * std_dev^2))
 * @author Shreya123714 (https://github.com/Shreya123714)
 *
 * Based on: https://en.wikipedia.org/wiki/Fuzzy_set
 */

#include <assert.h>  // for assert
#include <math.h>    // for math functions like exp() and sqrt()
#include <stdio.h>   // for IO operations

/**
 * @brief Computes the Gaussian function value.
 * @param value The input value at which to evaluate the function.
 * @param mean The mean of the distribution.
 * @param std_dev The standard deviation of the distribution.
 * @returns The value of the Gaussian function at value.
 */
double gaussian(double value, double mean, double std_dev)
{
    // Check for valid std_dev
    assert(std_dev > 0);

    double exponent =
        exp(-((value - mean) * (value - mean)) / (2 * std_dev * std_dev));
    return (1 / (std_dev * sqrt(2 * M_PI))) * exponent;
}

/**
 * @brief Self-test implementations for the Gaussian function.
 * @returns void
 */
static void test_gaussian()
{
    // Test cases
    assert(fabs(gaussian(0, 0, 1) - 0.3989422804014337) <
           1e-9);  // Standard normal distribution
    assert(fabs(gaussian(1, 0, 1) - 0.24197072451914337) < 1e-9);
    assert(fabs(gaussian(0, 2, 1) - 0.24197072451914337) < 1e-9);
    assert(fabs(gaussian(2, 2, 1) - 0.3989422804014337) <
           1e-9);  // Should be 0.3989422804014337

    printf("All Gaussian tests have successfully passed!\n");
}

/**
 * @brief Main function
 * @returns 0 on exit
 */
int main()
{
    test_gaussian();  // Run self-test implementations
    return 0;
}
