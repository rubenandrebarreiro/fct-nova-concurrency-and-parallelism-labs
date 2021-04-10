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

// Print the Error Message for Wrong Arguments' Usage
int print_error_arguments_messages() {

    // Print the Error Messages
    fprintf(stderr, "%s", ERROR_WRONG_ARGS_MESSAGE);
    fprintf(stderr, "%s", ERROR_USAGE_MESSAGE_1);
    fprintf(stderr, "%s", ERROR_USAGE_MESSAGE_2);
    fprintf(stderr, "%s", ERROR_USAGE_MESSAGE_3);
    fprintf(stderr, "%s", ERROR_USAGE_MESSAGE_4);

    // Return from the function
    return 1;

}

// The Main Method, with the Command-Line Interface
int main(const int argc, const char *argv[]) {

    // If it were given 4 arguments, at most, in the prompt of the Command-Line Interface
    if(argc <= 4) {

        // If it were given 3 arguments, at least, in the prompt of the Command-Line Interface
        if (argc >= 3) {

            // The Simulation Version (i.e., Sequential or Parallel)
            char *simulation_version;
            simulation_version = (char *) malloc(strlen(argv[1]));
            strcpy(simulation_version, argv[1]);

            // Convert the Simulation Version, to Lower Case
            for(int char_index = 0; simulation_version[char_index]; char_index++) {

                simulation_version[char_index] = tolower(simulation_version[char_index]); // NOLINT(cppcoreguidelines-narrowing-conversions)

            }

            // If the Simulation Version chosen is the Sequential
            if(strcasecmp(simulation_version, SEQUENTIAL_VERSION_TAG) == 0) {

                // If it were given 3 arguments, in the prompt of the Command-Line Interface
                if(argc == 3) {

                    // The number of the Points to be generated for the Simulation
                    long *num_points;
                    num_points = (long *) malloc(sizeof(long));
                    *num_points = atol(argv[2]); // NOLINT(cert-err34-c)

                    // The number of Hit Counts, within the Circle
                    long *inside_hit_counts;
                    inside_hit_counts = (long *) malloc(sizeof(long));

                    // Execute the Simulation, in Sequential, and retrieve the number of Hit Counts, within the Circle
                    *inside_hit_counts = *(long *) sequential_pi_approximation(num_points);

                    // Print the Final Results, for the Simulation, in Sequential
                    print_final_results_sequential_pi_approximation(num_points, inside_hit_counts);

                }
                else{

                    // Print the Error Messages for the Wrong Arguments' usage
                    print_error_arguments_messages();

                    // Exit the Program, with the Error Code
                    exit(1);

                }

            }
                // If the Simulation Version chosen is the Parallel
            else if(strcasecmp(simulation_version, PARALLEL_VERSION_TAG) == 0)  {

                // If it were given 3 or 4 arguments, in the prompt of the Command-Line Interface
                if( (argc == 3) || (argc == 4)) {

                    // The number of the Points to be generated for the Simulation
                    long *num_points;
                    num_points = (long *) malloc(sizeof(long));
                    *num_points = atol(argv[2]); // NOLINT(cert-err34-c)

                    // The number of Threads for the Parallel Version of the Simulation
                    int *num_threads;
                    num_threads = (int *) malloc(sizeof(int));

                    // If it were given 3 arguments, in the prompt of the Command-Line Interface
                    if(argc == 3) {

                        // Print the Error Message, related with a bad usage of the arguments, for the number of Threads
                        printf("WARNING: The number of Threads was not specified!!!\n");
                        printf("         It will be used the minimum number of Threads (i.e., %d Thread), as argument of the Simulation...\n\n", 1);

                        // Set the number of Threads to be used, as 1
                        *num_threads = 1;

                    }
                    else {

                        // Retrieve the number of Threads to be used, from the prompt of the Command-Line
                        *num_threads = atoi(argv[3]); // NOLINT(cert-err34-c)

                        // If the number of Threads, chosen, via the prompt of the Command-Line,
                        // is greater than the number of Processors available
                        if(*num_threads > get_nprocs()) {

                            // Print the Error Message, related with a bad usage of the arguments, for the number of Threads
                            printf("WARNING: The number of Threads specified is greater than the number of Threads available!!!\n");
                            printf("         It will be used the number of Threads available (i.e., %d Thread(s)), as argument of the Simulation...\n\n", get_nprocs());

                            // Set the number of Threads to be used, as the maximum number of Processors available
                            *num_threads = get_nprocs();

                        }

                    }

                    // The number of Hit Counts, within the Circle
                    long *inside_hit_counts;
                    inside_hit_counts = (long *) malloc(sizeof(long));

                    // Execute the Simulation, in Parallel, and retrieve the number of Hit Counts, within the Circle
                    *inside_hit_counts = *(long *) parallel_pi_approximation(num_points, num_threads);

                    // Print the Final Results, for the Simulation, in Parallel
                    print_final_results_parallel_pi_approximation(num_points, num_threads, inside_hit_counts);

                }
                else{

                    // Print the Error Messages for the Wrong Arguments' usage
                    print_error_arguments_messages();

                    // Exit the Program, with the Error Code 1
                    exit(1);

                }

            }
            else {

                // Print the Error Messages for the Wrong Arguments' usage
                print_error_arguments_messages();

                // Exit the Program, with the Error Code 1
                exit(1);

            }

        }
        // If it were given less than 3 arguments, in the prompt of the Command-Line Interface
        else {

            // Print the Error Messages for the Wrong Arguments' usage
            print_error_arguments_messages();

            // Exit the Program, with the Error Code 1
            exit(1);

        }

        // Return from the Main Method
        return 0;

    }
    // If it were given more than 4 arguments, in the prompt of the Command-Line Interface
    else {

        // Print the Error Messages for the Wrong Arguments' usage
        print_error_arguments_messages();

        // Exit the Program, with the Error Code 1
        exit(1);

    }

}
