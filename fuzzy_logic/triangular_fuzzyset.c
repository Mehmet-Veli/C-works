/**
 * @file
 * @brief Implementation of a triangular fuzzy set.
 * @details
 * This file provides functions to create and manipulate triangular fuzzy sets,
 * including methods to calculate membership values, union, intersection,
 * complement, and a basic plot representation.
 *
 * By @Shreya123714
 *
 * Based on: https://en.wikipedia.org/wiki/Fuzzy_set
 */

#include <assert.h>  // for assert
#include <math.h>    //for complex math operations
#include <stdio.h>   // for IO operations
#include <string.h>  // for string operations

/**
 * @brief Struct to represent a triangular fuzzy set.
 */
struct triangular_fuzzy_set
{
    char name[50];          ///< Name of the fuzzy set
    double left_boundary;   ///< Left boundary of the fuzzy set
    double peak;            ///< Peak (central) value of the fuzzy set
    double right_boundary;  ///< Right boundary of the fuzzy set
};

/**
 * @brief Creates a triangular fuzzy set.
 * @param name The name of the fuzzy set.
 * @param left_boundary The left boundary of the fuzzy set.
 * @param peak The peak of the fuzzy set.
 * @param right_boundary The right boundary of the fuzzy set.
 * @returns A triangular fuzzy set struct.
 */
struct triangular_fuzzy_set create_triangular_fuzzy_set(const char *name,
                                                        double left_boundary,
                                                        double peak,
                                                        double right_boundary)
{
    struct triangular_fuzzy_set set;
    strncpy(set.name, name, sizeof(set.name) - 1);
    set.name[sizeof(set.name) - 1] = '\0';  // Ensure null termination
    set.left_boundary = left_boundary;
    set.peak = peak;
    set.right_boundary = right_boundary;
    return set;
}

/**
 * @brief Calculates the membership value for a given input.
 * @param set The triangular fuzzy set.
 * @param x The value to evaluate the membership for.
 * @returns The membership value.
 */
double membership_value(struct triangular_fuzzy_set set, double x)
{
    if (x <= set.left_boundary || x >= set.right_boundary)
    {
        return 0.0;  // Out of range
    }
    else if (set.left_boundary < x && x <= set.peak)
    {
        return (x - set.left_boundary) /
               (set.peak - set.left_boundary);  // Increasing slope
    }
    else if (set.peak < x && x < set.right_boundary)
    {
        return (set.right_boundary - x) /
               (set.right_boundary - set.peak);  // Decreasing slope
    }
    return 0.0;  // Should not reach here
}

/**
 * @brief Calculates the complement (negation) of this fuzzy set.
 * @param set The triangular fuzzy set.
 * @returns A new triangular fuzzy set representing the complement.
 */
struct triangular_fuzzy_set complement(struct triangular_fuzzy_set set)
{
    return create_triangular_fuzzy_set(set.name, 1.0 - set.right_boundary,
                                       1.0 - set.left_boundary, 1.0 - set.peak);
}

/**
 * @brief Calculates the intersection of this fuzzy set with another fuzzy set.
 * @param set The triangular fuzzy set.
 * @param other The other triangular fuzzy set to intersect with.
 * @returns A new triangular fuzzy set representing the intersection.
 */
struct triangular_fuzzy_set intersection(struct triangular_fuzzy_set set,
                                         struct triangular_fuzzy_set other)
{
    return create_triangular_fuzzy_set(
        "Intersection", fmax(set.left_boundary, other.left_boundary),
        fmin(set.right_boundary, other.right_boundary),
        (set.peak + other.peak) / 2);
}

/**
 * @brief Calculates the union of this fuzzy set with another fuzzy set.
 * @param set The triangular fuzzy set.
 * @param other The other triangular fuzzy set to union with.
 * @returns A new triangular fuzzy set representing the union.
 */
struct triangular_fuzzy_set union_sets(struct triangular_fuzzy_set set,
                                       struct triangular_fuzzy_set other)
{
    return create_triangular_fuzzy_set(
        "Union", fmin(set.left_boundary, other.left_boundary),
        fmax(set.right_boundary, other.right_boundary),
        (set.peak + other.peak) / 2);
}

/**
 * @brief Prints the details of the triangular fuzzy set.
 * @param set The triangular fuzzy set.
 */
void print_triangular_fuzzy_set(struct triangular_fuzzy_set set)
{
    printf("Triangular Fuzzy Set '%s': [%f, %f, %f]\n", set.name,
           set.left_boundary, set.peak, set.right_boundary);
}

/**
 * @brief Basic plotting of the membership function of the fuzzy set.
 * This is a textual representation, as actual graphing is more complex in C.
 *
 * @param set The triangular fuzzy set to plot.
 */
void plot_triangular_fuzzy_set(struct triangular_fuzzy_set set)
{
    printf("Membership function of %s:\n", set.name);
    for (double x = 0; x <= 1.0; x += 0.1)
    {
        double membership = membership_value(set, x);
        printf("x: %0.1f | Membership: %0.2f | ", x, membership);
        for (int i = 0; i < (int)(membership * 50); i++)
        {  // Scale for better visibility
            printf("*");
        }
        printf("\n");
    }
}

/**
 * @brief Self-test implementations.
 * @returns void
 */
static void tests()
{
    struct triangular_fuzzy_set a =
        create_triangular_fuzzy_set("A", 0.0, 0.5, 1.0);
    struct triangular_fuzzy_set b =
        create_triangular_fuzzy_set("B", 0.2, 0.7, 1.0);

    // Test membership values
    assert(membership_value(a, 0.1) == 0.2);
    assert(membership_value(a, 0.5) == 1.0);
    assert(membership_value(a, 0.8) == 0.4);
    assert(membership_value(b, 0.6) == 0.8);

    // Test union
    struct triangular_fuzzy_set union_ab = union_sets(a, b);
    assert(union_ab.left_boundary == 0.0);
    assert(union_ab.right_boundary == 1.0);

    // Test intersection
    struct triangular_fuzzy_set intersection_ab = intersection(a, b);
    assert(intersection_ab.left_boundary == 0.2);

    // Test complement
    struct triangular_fuzzy_set complement_a = complement(a);
    assert(complement_a.left_boundary == 0.0);

    printf("All tests have successfully passed!\n");
}

/**
 * @brief Main function.
 * @returns 0 on exit.
 */
int main()
{
    tests();  // Run self-test implementations

    struct triangular_fuzzy_set a =
        create_triangular_fuzzy_set("A", 0.0, 0.5, 1.0);
    struct triangular_fuzzy_set b =
        create_triangular_fuzzy_set("B", 0.2, 0.7, 1.0);

    print_triangular_fuzzy_set(a);
    print_triangular_fuzzy_set(b);

    plot_triangular_fuzzy_set(a);
    plot_triangular_fuzzy_set(b);

    struct triangular_fuzzy_set union_ab = union_sets(a, b);
    struct triangular_fuzzy_set intersection_ab = intersection(a, b);
    struct triangular_fuzzy_set complement_a = complement(a);

    print_triangular_fuzzy_set(union_ab);
    print_triangular_fuzzy_set(intersection_ab);
    print_triangular_fuzzy_set(complement_a);

    plot_triangular_fuzzy_set(union_ab);
    plot_triangular_fuzzy_set(intersection_ab);
    plot_triangular_fuzzy_set(complement_a);

    return 0;
}
