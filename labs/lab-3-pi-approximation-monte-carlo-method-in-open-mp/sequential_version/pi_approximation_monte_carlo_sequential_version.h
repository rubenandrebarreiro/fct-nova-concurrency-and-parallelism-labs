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

#ifndef LAB_3_PI_APPROXIMATION_MONTE_CARLO_METHOD_IN_OPEN_MP_PI_APPROXIMATION_MONTE_CARLO_SEQUENTIAL_VERSION_H
#define LAB_3_PI_APPROXIMATION_MONTE_CARLO_METHOD_IN_OPEN_MP_PI_APPROXIMATION_MONTE_CARLO_SEQUENTIAL_VERSION_H

// The Method for the Pi Approximation, by the Sequential Version
void *sequential_pi_approximation(const long *arg_num_points);

// The Method for printing the Results of the Pi Approximation, by the Sequential Version
int print_final_results_sequential_pi_approximation(const long *arg_num_points,
                                                    const long *arg_inside_hits_count);

#endif //LAB_3_PI_APPROXIMATION_MONTE_CARLO_METHOD_IN_OPEN_MP_PI_APPROXIMATION_MONTE_CARLO_SEQUENTIAL_VERSION_H
