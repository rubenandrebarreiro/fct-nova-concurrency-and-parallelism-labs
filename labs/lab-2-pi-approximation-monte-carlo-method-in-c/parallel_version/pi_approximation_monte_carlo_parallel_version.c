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
#include <pthread.h>

#define CIRCLE_RADIUS 1

void *parallel_multithreading_inside_hits_count(void *);

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

    long *total_inside_hits_count;
    total_inside_hits_count = (long *) malloc(sizeof(long));
    *total_inside_hits_count = 0;

    void *parallel_inside_hits_count;

    pthread_t threads[*num_threads];
    int pthread_creation_flag;

    for(int thread_id = 0; thread_id < *num_threads; thread_id++) {

        if( thread_id < ( *num_threads - 1 ) ) {

            pthread_creation_flag = pthread_create(&(threads[thread_id]), NULL,
                                                   parallel_multithreading_inside_hits_count,
                                                   (void *) num_points_per_thread);

            if(pthread_creation_flag != 0) {

                printf("ERROR: Return code from pthread_create(), from Thread no. %d is %d!!!\n",
                       thread_id, pthread_creation_flag);

                exit(1);

            }

        }
        else {

            long *num_points_for_last_thread;
            num_points_for_last_thread = (long *) malloc(sizeof(long));
            *num_points_for_last_thread = ( *num_points_per_thread + *num_remaining_points_for_last_thread );

            pthread_creation_flag = pthread_create(&(threads[thread_id]), NULL,
                                                   parallel_multithreading_inside_hits_count,
                                               (void *) num_points_for_last_thread );

            if(pthread_creation_flag != 0) {

                printf("ERROR: Return code from pthread_create(), from Thread no. %d is %d!!!\n",
                       thread_id, pthread_creation_flag);

                exit(1);

            }

        }

    }


    for(int thread_id = 0; thread_id < *num_threads; thread_id++) {

        pthread_creation_flag = pthread_join(threads[thread_id], &parallel_inside_hits_count);

        if (pthread_creation_flag != 0) {

            printf("ERROR: Return code from pthread_create(), from Thread no. %d is %d!!!\n",
                   thread_id, pthread_creation_flag);

            exit(1);

        }

        parallel_inside_hits_count = (long *) parallel_inside_hits_count;

        *total_inside_hits_count += *(long *) parallel_inside_hits_count;

    }

    return total_inside_hits_count;

}

void *parallel_multithreading_inside_hits_count(void *num_points_to_be_generated_by_thread) {

    long *parallel_inside_hits_count;
    parallel_inside_hits_count = (long *) malloc(sizeof(long));
    *parallel_inside_hits_count = 0;

    unsigned int random_seed = time(NULL);

    for(int current_point = 0; current_point < *(long *)num_points_to_be_generated_by_thread; current_point++) {

        float point_x = ( ( (float) rand_r(&random_seed) ) / (float)(RAND_MAX) );
        float point_y = ( ( (float) rand_r(&random_seed) ) / (float)(RAND_MAX) );

        double pythagoras_formula = ( (point_x * point_x) + (point_y * point_y) );

        if( pythagoras_formula <= CIRCLE_RADIUS ) {

            *parallel_inside_hits_count += 1;

        }

    }

    pthread_exit((void *) parallel_inside_hits_count);

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