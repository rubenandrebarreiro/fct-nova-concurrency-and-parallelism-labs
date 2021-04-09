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

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

#include "sequential_version/pi_approximation_monte_carlo_sequential_version.h"
#include "parallel_version/pi_approximation_monte_carlo_parallel_version.h"

#define SEQUENTIAL_VERSION_TAG "sequential"
#define PARALLEL_VERSION_TAG "parallel"

#define ERROR_WRONG_ARGS_MESSAGE "ERROR: Wrong Arguments!!!\n\n"
#define ERROR_USAGE_MESSAGE_1 "USAGE: ./pi-approximation-monte-carlo-method-in-c simulation-version num-points [num-threads]\n"
#define ERROR_USAGE_MESSAGE_2 "       simulation-version: The Version of the Simulation ({sequential , parallel})\n"
#define ERROR_USAGE_MESSAGE_3 "       num-points: The number of points to be generated on the simulation\n"
#define ERROR_USAGE_MESSAGE_4 "       [num_threads]: The number of Threads to be launched in Parallel Version (if none is specified, 1 Thread will be used, as default) [OPTIONAL - only specifiable for the Parallel Versions]\n"

int print_error_arguments_messages() {

    fprintf(stderr, "%s", ERROR_WRONG_ARGS_MESSAGE);
    fprintf(stderr, "%s", ERROR_USAGE_MESSAGE_1);
    fprintf(stderr, "%s", ERROR_USAGE_MESSAGE_2);
    fprintf(stderr, "%s", ERROR_USAGE_MESSAGE_3);
    fprintf(stderr, "%s", ERROR_USAGE_MESSAGE_4);

    return 1;

}

int main(const int argc, const char *argv[]) {

    if(argc <= 4) {

        char *simulation_version;

        simulation_version = (char *) malloc(strlen(argv[1]));

        strcpy(simulation_version, argv[1]);

        for(int char_index = 0; simulation_version[char_index]; char_index++) {

            simulation_version[char_index] = tolower(simulation_version[char_index]); // NOLINT(cppcoreguidelines-narrowing-conversions)

        }

        if(strcasecmp(simulation_version, SEQUENTIAL_VERSION_TAG) == 0) {

            if(argc == 3) {

                long *num_points;

                num_points = (long *) malloc(sizeof(long));

                *num_points = atol(argv[2]); // NOLINT(cert-err34-c)

                long *inside_hit_counts;

                inside_hit_counts = (long *) malloc(sizeof(long));

                *inside_hit_counts = *(long *) sequential_pi_approximation(num_points);

                print_final_results_sequential_pi_approximation(num_points, inside_hit_counts);

            }
            else{

                print_error_arguments_messages();
                exit(1);

            }

        }
        else if(strcasecmp(simulation_version, PARALLEL_VERSION_TAG) == 0)  {

            if( (argc == 3) || (argc == 4)) {

                long *num_points;

                num_points = (long *) malloc(sizeof(long));

                *num_points = atol(argv[2]); // NOLINT(cert-err34-c)

                int *num_threads;

                num_threads = (int *) malloc(sizeof(int));

                if(argc == 3) {

                    printf("WARNING: The number of Threads was not specified!!!\n");
                    printf("         It will be used the minimum number of Threads (i.e., %d Thread), as argument of the Simulation...\n\n", 1);

                    *num_threads = 1;

                }
                else {

                    *num_threads = atoi(argv[3]); // NOLINT(cert-err34-c)

                    if(*num_threads > get_nprocs()) {

                        printf("WARNING: The number of Threads specified is greater than the number of Threads available!!!\n");
                        printf("         It will be used the number of Threads available (i.e., %d Thread(s)), as argument of the Simulation...\n\n", get_nprocs());

                        *num_threads = get_nprocs();

                    }

                }

                long *inside_hit_counts;

                inside_hit_counts = (long *) malloc(sizeof(long));

                *inside_hit_counts = *(long *) parallel_pi_approximation(num_points, num_threads);

                print_final_results_parallel_pi_approximation(num_points, num_threads, inside_hit_counts);

            }
            else{

                print_error_arguments_messages();
                exit(1);

            }

        }
        else {

            print_error_arguments_messages();
            exit(1);

        }

        return 0;

    }
    else {

        print_error_arguments_messages();
        exit(1);

    }

}
