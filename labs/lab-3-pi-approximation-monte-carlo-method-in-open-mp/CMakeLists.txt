cmake_minimum_required(VERSION 3.19)
project(lab_3_pi_approximation_monte_carlo_method_in_open_mp C)

set(CMAKE_C_STANDARD 99)

add_executable(lab_3_pi_approximation_monte_carlo_method_in_open_mp main.c sequential_version/pi_approximation_monte_carlo_sequential_version.h sequential_version/pi_approximation_monte_carlo_sequential_version.c parallel_version/pi_approximation_monte_carlo_parallel_version.h parallel_version/pi_approximation_monte_carlo_parallel_version.c)