/*
 * <--Introduction-->
 * Refer to this exercise for full details:
 * https://exercism.org/tracks/c/exercises/darts
 *   
*/

#include "darts.h"

unsigned int score(coordinate_t landing_position){
    
    // We used the Pythagorean theorem to get the radius by using the two coordinates:
    // 1. landing_position.x
    // 2. landing_position.y
    float radius = sqrt(pow(landing_position.x, 2) + pow(landing_position.y, 2));

    /*
     * Note: Interval notation is used to show the range of the radius to
     * determine the score
     *
     * If radius is [0, 1]    , return a score of 10
     * If radius is (1, 5]    , return a score of 5
     * If radius is (5, 10]   , return a score of 1
     * If radius is (-inf, 0) or (10, +inf), return a score of 0
     * 
     */
    return radius >= 0 && radius <= 1 ? 10 : radius > 1 && radius <= 5 ? 5 : radius > 5 && radius <= 10 ? 1 : 0;
}
