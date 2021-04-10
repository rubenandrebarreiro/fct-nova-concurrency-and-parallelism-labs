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

// The Circle has Radius of 1
#define CIRCLE_RADIUS 1

// The Method for Parallel Multi-Threading, for Inside Hit Counts
void *parallel_multithreading_inside_hits_count(void *);

// The Method for the Pi Approximation, by the Parallel Version
void *parallel_pi_approximation(const long *arg_num_points, const int *arg_num_threads) {

    // The total number of Points, to be generated, during the Simulation
    long *total_num_points;
    total_num_points = (long *) malloc(sizeof(long));
    *total_num_points = *arg_num_points;

    // The number of Threads to be launched, in Parallel
    int *num_threads;
    num_threads = (int *) malloc(sizeof(int));
    *num_threads = *arg_num_threads;

    // The number of Points, to be generated, individually, by each Thread
    long *num_points_per_thread;
    num_points_per_thread = (long *) malloc(sizeof(long));
    *num_points_per_thread = (*total_num_points / *num_threads);

    // The number of remaining Points to be generated by the last Thread
    long *num_remaining_points_for_last_thread;
    num_remaining_points_for_last_thread = (long *) malloc(sizeof(long));
    *num_remaining_points_for_last_thread = (*total_num_points % *num_threads);

    // The total number of Hit Counts, within the Circle
    long *total_inside_hits_count;
    total_inside_hits_count = (long *) malloc(sizeof(long));
    *total_inside_hits_count = 0;

    // The number of Hit Counts, within the Circle,
    // processed individually by each Thread
    void *parallel_inside_hits_count;

    // The array of Threads, to be launched, in Parallel
    pthread_t threads[*num_threads];

    // The flag for the Status of
    // the process of creation of each Thread
    int pthread_creation_flag;

    // For each Thread
    for(int thread_id = 0; thread_id < *num_threads; thread_id++) {

        // If the current Thread is not the last one
        if( thread_id < ( *num_threads - 1 ) ) {

            // Creates the Thread, for its corresponding execution in Parallel,
            // retrieving the flag returned by it
            pthread_creation_flag = pthread_create(&(threads[thread_id]), NULL,
                                                   parallel_multithreading_inside_hits_count,
                                                   (void *) num_points_per_thread);

            // If the flag returned by the process of the creation and processing of
            // current Thread, corresponds to an error
            if(pthread_creation_flag != 0) {

                // Print the corresponding Message Error
                printf("ERROR: Return code from pthread_create(), from Thread no. %d is %d!!!\n",
                       thread_id, pthread_creation_flag);

                // Exit the program with the code, corresponding to an Error Code
                exit(1);

            }

        }
        else {

            // The number of Points, to be generated by the last Thread,
            // for the case of the total number of Points to be generated,
            // are not divisible for the number of Threads
            long *num_points_for_last_thread;
            num_points_for_last_thread = (long *) malloc(sizeof(long));
            *num_points_for_last_thread = ( *num_points_per_thread + *num_remaining_points_for_last_thread );

            // Creates the Thread, for its corresponding execution in Parallel,
            // retrieving the flag returned by it
            pthread_creation_flag = pthread_create(&(threads[thread_id]), NULL,
                                                   parallel_multithreading_inside_hits_count,
                                               (void *) num_points_for_last_thread );

            // If the flag returned by the process of the creation and processing of
            // current Thread, corresponds to an error
            if(pthread_creation_flag != 0) {

                // Print the corresponding Message Error
                printf("ERROR: Return code from pthread_create(), from Thread no. %d is %d!!!\n",
                       thread_id, pthread_creation_flag);

                // Exit the program with the code, corresponding to an Error Code
                exit(1);

            }

        }

    }

    // For each Thread
    for(int thread_id = 0; thread_id < *num_threads; thread_id++) {

        // Joins the computation made by the Thread,
        // for its corresponding execution in Parallel,
        // retrieving the flag returned by it
        pthread_creation_flag = pthread_join(threads[thread_id], &parallel_inside_hits_count);

        // If the flag returned by the process of the creation and processing of
        // current Thread, corresponds to an error
        if (pthread_creation_flag != 0) {

            // Print the corresponding Message Error
            printf("ERROR: Return code from pthread_create(), from Thread no. %d is %d!!!\n",
                   thread_id, pthread_creation_flag);

            // Exit the program with the code, corresponding to an Error Code
            exit(1);

        }

        // Join the individual Hit Counts, in Parallel, by each Thread
        *total_inside_hits_count += *(long *) parallel_inside_hits_count;

    }

    // Return the total number of Hit Counts, within the Circle
    return total_inside_hits_count;

}

// The Method for the Pi Approximation, by the Parallel Version
void *parallel_multithreading_inside_hits_count(void *num_points_to_be_generated_by_thread) {

    // The number of individual Hit Counts, in Parallel,
    // individual by each Thread
    long *parallel_inside_hits_count;
    parallel_inside_hits_count = (long *) malloc(sizeof(long));
    *parallel_inside_hits_count = 0;

    // The Random Seed, for the Pseudo-Random Generator
    unsigned int random_seed = time(NULL);

    // For each Point to be generated, during the Simulation
    for(int current_point = 0; current_point < *(long *)num_points_to_be_generated_by_thread; current_point++) {

        // Generate the random coordinates for the Point, using the Pseudo-Random Generator
        float point_x = ( ( (float) rand_r(&random_seed) ) / (float)(RAND_MAX) );
        float point_y = ( ( (float) rand_r(&random_seed) ) / (float)(RAND_MAX) );

        // Compute the Pythagoras formula
        double pythagoras_formula = ( (point_x * point_x) + (point_y * point_y) );

        // If the Point currently generated, is within the Circle
        if( pythagoras_formula <= CIRCLE_RADIUS ) {

            // Increment the number of Hit Counts, within the Circle,
            // by each Thread, individually
            *parallel_inside_hits_count += 1;

        }

    }

    // Call for the Thread exit the Multi-Threading computation in Parallel,
    // returning with its final result of individual Hit Counts
    pthread_exit((void *) parallel_inside_hits_count);

}

// The Method for printing the Results of the Pi Approximation, by the Parallel Version
int print_final_results_parallel_pi_approximation(const long *arg_num_points,
                                                  const int *arg_num_threads,
                                                  const long *arg_inside_hits_count) {

    // The total number of Points, for the Simulation
    long *total_num_points;
    total_num_points = (long *) malloc(sizeof(long));
    *total_num_points = *arg_num_points;

    // The number of Points, within the Circle
    int *num_threads;
    num_threads = (int *) malloc(sizeof(int));
    *num_threads = *arg_num_threads;

    // The Pi Estimation, by the computation of the Points within the Circle
    long *inside_hits_count;
    inside_hits_count = (long *) malloc(sizeof(long));
    *inside_hits_count = *arg_inside_hits_count;

    // The Pi Estimation, by the computation of the Points within the Circle
    double *pi_estimation;
    pi_estimation = (double *) malloc(sizeof(double));
    *pi_estimation = (double) ( 4 * ( (float) ( ( (double) *inside_hits_count ) / ( (double) *total_num_points ) ) ) );

    // Print the Final Results
    printf("--- Pi Approximation (Monte Carlo Method) [Parallel, with %d Thread(s)] ---\n", *num_threads);
    printf("Total Number of Points: %ld\n", *total_num_points);
    printf("Points within Circle: %ld\n", *inside_hits_count);
    printf("Pi Estimation: %1.5f\n", *pi_estimation);

    // Return from the function
    return 0;

}