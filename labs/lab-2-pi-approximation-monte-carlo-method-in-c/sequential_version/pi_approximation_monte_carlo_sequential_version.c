/**
 *
 * Pi Approximation/Estimation, for the Monte Carlo Method,
 * using Sequential and Parallel Versions (Version in C)
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

#define CIRCLE_RADIUS 1

void *sequential_pi_approximation(const long *arg_num_points) {

    long *total_num_points;
    total_num_points = (long *) malloc(sizeof(long));
    *total_num_points = *arg_num_points;

    long *inside_hits_count;
    inside_hits_count = (long *) malloc(sizeof(long));
    *inside_hits_count = 0;

    srandom(time(NULL));

    for(int current_point = 0; current_point < *total_num_points; current_point++) {

        float point_x = ( ( (float) random() ) / (float)(RAND_MAX) );
        float point_y = ( ( (float) random() ) / (float)(RAND_MAX) );

        double pythagoras_formula = ( (point_x * point_x) + (point_y * point_y) );

        if( pythagoras_formula <= CIRCLE_RADIUS ) {

            *inside_hits_count += 1;

        }

    }

    return (void *) inside_hits_count;

}

int print_final_results_sequential_pi_approximation(const long *arg_num_points,
                                                    const long *arg_inside_hits_count) {

    long *total_num_points;
    total_num_points = (long *) malloc(sizeof(long));
    *total_num_points = *arg_num_points;

    long *inside_hits_count;
    inside_hits_count = (long *) malloc(sizeof(long));
    *inside_hits_count = *arg_inside_hits_count;

    double *pi_estimation;
    pi_estimation = (double *) malloc(sizeof(double));
    *pi_estimation = (double) ( 4 * ( (float) ( ( (double) *inside_hits_count ) / ( (double) *total_num_points ) ) ) );

    printf("--- Pi Approximation (Monte Carlo Method) [Sequential] ---\n");
    printf("Total Number of Points: %ld\n", *total_num_points);
    printf("Points within Circle: %ld\n", *inside_hits_count);
    printf("Pi Estimation: %1.5f\n", *pi_estimation);

    return 0;

}