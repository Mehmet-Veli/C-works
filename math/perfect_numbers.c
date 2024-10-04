#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>

/* This function returns true 
    if the submitted number is perfect,
    false if it is not.
    
    A perfect number is a positive integer that is
    equal to the sum of its positive proper
    divisors, excluding the number itself.

    About perfect numbers: https://en.wikipedia.org/wiki/Perfect_number

    @author Marco https://github.com/MaarcooC
    @param int $number
    @return bool */

bool isPerfect(int number) {
    // Handle edge cases: negative numbers and zero
    if (number <= 1) {
        return false; // 0 and negative numbers are not perfect
    }

    int sumOfDivisors = 1; // Initialize the sum of divisors with 1

    // Check for divisors from 2 to sqrt(number)
    for (int i = 2; i <= sqrt(number); i++) {
        if (number % i == 0) { // If it is divisible
            sumOfDivisors += i; // Add i to the sum of divisors
            if (i != number / i) {
                sumOfDivisors += number / i; // Add the corresponding divisor
            }
        }
    }

    return sumOfDivisors == number;
}

// tests
void tests() {
    assert(isPerfect(1) == false);
    assert(isPerfect(6) == true);
    assert(isPerfect(28) == true);
    assert(isPerfect(-1) == false);
    assert(isPerfect(0) == false);
    assert(isPerfect(496) == true);
}

int main() {
    tests();
    printf("All tests passed!");
    return 0;
}