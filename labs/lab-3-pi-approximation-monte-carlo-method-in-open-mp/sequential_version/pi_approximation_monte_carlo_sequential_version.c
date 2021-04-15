/**
 *
 * Pi Approximation/Estimation, for the Monte Carlo Method,
 * using Sequential and Parallel Versions (Version in OpenMP)
 *
 * @author: Ruben Andre Barreiro
 * @email: r.barreiro@campus.fct.unl.pt
 * @number_student: 42648
 *
 * NOVA School of Science and Technology | NOVA University of Lisbon (FCT NOVA)
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// The Circle has Radius of 1
#define CIRCLE_RADIUS 1

// The Method for the Pi Approximation, by the Sequential Version
void *sequential_pi_approximation(const long *arg_num_points) {

    // The total number of Points, to be generated, during the Simulation
    long *total_num_points;
    total_num_points = (long *) malloc(sizeof(long));
    *total_num_points = *arg_num_points;

    // The number of Hit Counts, within the Circle
    long *inside_hits_count;
    inside_hits_count = (long *) malloc(sizeof(long));
    *inside_hits_count = 0;

    // Initialise the Seed for the Pseudo-Random Generator
    srandom(time(NULL));

    // For each Point to be generated, during the Simulation
    for(long current_point = 0; current_point < *total_num_points; current_point++) {

        // Generate the random coordinates for the Point, using the Pseudo-Random Generator
        float point_x = ( ( (float) random() ) / (float)(RAND_MAX) );
        float point_y = ( ( (float) random() ) / (float)(RAND_MAX) );

        // Compute the Pythagoras formula
        double pythagoras_formula = ( (point_x * point_x) + (point_y * point_y) );

        // If the Point currently generated, is within the Circle
        if( pythagoras_formula <= CIRCLE_RADIUS ) {

            // Increment the number of Hit Counts, within the Circle
            *inside_hits_count += 1;

        }

    }

    // Return the number of Hit Counts, within the Circle
    return (void *) inside_hits_count;

}

// The Method for printing the Results of the Pi Approximation, by the Sequential Version
int print_final_results_sequential_pi_approximation(const long *arg_num_points,
                                                    const long *arg_inside_hits_count) {

    // The total number of Points, for the Simulation
    long *total_num_points;
    total_num_points = (long *) malloc(sizeof(long));
    *total_num_points = *arg_num_points;

    // The number of Points, within the Circle
    long *inside_hits_count;
    inside_hits_count = (long *) malloc(sizeof(long));
    *inside_hits_count = *arg_inside_hits_count;

    // The Pi Estimation, by the computation of the Points within the Circle
    double *pi_estimation;
    pi_estimation = (double *) malloc(sizeof(double));
    *pi_estimation = (double) ( 4 * ( (float) ( ( (double) *inside_hits_count ) / ( (double) *total_num_points ) ) ) );

    // Print the Final Results
    printf("--- Pi Approximation (Monte Carlo Method) [Sequential] ---\n");
    printf("Total Number of Points: %ld\n", *total_num_points);
    printf("Points within Circle: %ld\n", *inside_hits_count);
    printf("Pi Estimation: %1.5f\n", *pi_estimation);

    // Return from the function
    return 0;

}

