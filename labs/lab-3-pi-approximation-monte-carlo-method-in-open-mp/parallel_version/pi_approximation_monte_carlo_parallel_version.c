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
#include <omp.h>

#define CIRCLE_RADIUS 1

void *parallel_pi_approximation(const long *arg_num_points, const int *arg_num_threads) {

    long *total_num_points;
    total_num_points = (long *) malloc(sizeof(long));
    *total_num_points = *arg_num_points;

    int *num_threads;
    num_threads = (int *) malloc(sizeof(int));
    *num_threads = *arg_num_threads;

    long *num_points_per_thread;
    num_points_per_thread = (long *) malloc(sizeof(long));
    *num_points_per_thread = (*total_num_points / *num_threads);

    long *num_remaining_points_for_last_thread;
    num_remaining_points_for_last_thread = (long *) malloc(sizeof(long));
    *num_remaining_points_for_last_thread = (*total_num_points % *num_threads);

    long *num_points_for_last_thread;
    num_points_for_last_thread = (long *) malloc(sizeof(long));
    *num_points_for_last_thread = (*num_points_per_thread + *num_remaining_points_for_last_thread);

    long *total_inside_hits_count;
    total_inside_hits_count = (long *) malloc(sizeof(long));
    *total_inside_hits_count = 0;

    int thread_id;
    int current_thread;

    long parallel_inside_hits_count[*num_threads];
    long thread_inside_hits_count;
    unsigned int random_seed;

    omp_set_num_threads(*num_threads);

    for(current_thread = 0; current_thread < *num_threads; current_thread++) {

        parallel_inside_hits_count[current_thread] = 0;

    }

    #pragma omp parallel for private(thread_id, current_thread, thread_inside_hits_count, random_seed) num_threads(*num_threads) shared(num_threads, num_points_per_thread, parallel_inside_hits_count)
    for(current_thread = 0; current_thread < *num_threads; current_thread++) {

        thread_id = omp_get_thread_num();
        thread_inside_hits_count = 0L;
        random_seed = time(NULL);

        if (thread_id < (*num_threads - 1)) {

            for (int current_point = 0; current_point < *num_points_per_thread; current_point++) {

                float point_x = (((float) rand_r(&random_seed)) / ((float) (RAND_MAX)));
                float point_y = (((float) rand_r(&random_seed)) / ((float) (RAND_MAX)));

                double pythagoras_formula = ((point_x * point_x) + (point_y * point_y));

                if (pythagoras_formula <= CIRCLE_RADIUS) {

                    thread_inside_hits_count += 1;

                }

            }

        }
        else {

            for (int current_point = 0; current_point < *num_points_for_last_thread; current_point++) {

                float point_x = (((float) rand_r(&random_seed)) / ((float) (RAND_MAX)));
                float point_y = (((float) rand_r(&random_seed)) / ((float) (RAND_MAX)));

                double pythagoras_formula = ((point_x * point_x) + (point_y * point_y));

                if (pythagoras_formula <= CIRCLE_RADIUS) {

                    thread_inside_hits_count += 1;

                }

            }

        }

        parallel_inside_hits_count[current_thread] = thread_inside_hits_count;

    }

    for(current_thread = 0; current_thread < *num_threads; current_thread++) {

        *total_inside_hits_count += parallel_inside_hits_count[current_thread];

    }

    return total_inside_hits_count;

}

int print_final_results_parallel_pi_approximation(const long *arg_num_points,
                                                  const int *arg_num_threads,
                                                  const long *arg_inside_hits_count) {

    long *total_num_points;
    total_num_points = (long *) malloc(sizeof(long));
    *total_num_points = *arg_num_points;

    int *num_threads;
    num_threads = (int *) malloc(sizeof(int));
    *num_threads = *arg_num_threads;

    long *inside_hits_count;
    inside_hits_count = (long *) malloc(sizeof(long));
    *inside_hits_count = *arg_inside_hits_count;

    double *pi_estimation;
    pi_estimation = (double *) malloc(sizeof(double));
    *pi_estimation = (double) ( 4 * ( (float) ( ( (double) *inside_hits_count ) / ( (double) *total_num_points ) ) ) );

    printf("--- Pi Approximation (Monte Carlo Method) [Parallel, with %d Thread(s)] ---\n", *num_threads);
    printf("Total Number of Points: %ld\n", *total_num_points);
    printf("Points within Circle: %ld\n", *inside_hits_count);
    printf("Pi Estimation: %1.5f\n", *pi_estimation);

    return 0;

}