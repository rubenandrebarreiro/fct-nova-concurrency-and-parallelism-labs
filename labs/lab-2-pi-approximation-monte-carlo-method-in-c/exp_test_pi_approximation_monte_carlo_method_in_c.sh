NUM_POINTS="1000 10000 100000 1000000 10000000 100000000 1000000000"
NUM_THREADS="1 2 4 8 12"
NUM_RUNS="5"

for NP in $NUM_POINTS; do
  for NR in $(seq 1 $NUM_RUNS); do
    # shellcheck disable=SC2028
    echo "Run/Execution no. $NR:"$'\n'
    time ./pi_approximation_monte_carlo_method_in_c sequential "$NP"
    echo $'\n\n'
  done
done | tee pi_approximation_monte_carlo_method_in_c_sequential_results.csv

for NP in $NUM_POINTS; do
  for NT in $NUM_THREADS; do
    # shellcheck disable=SC2034
    for NR in $(seq 1 $NUM_RUNS); do
      # shellcheck disable=SC2028
      echo "Run/Execution no. $NR:"$'\n'
      time ./pi_approximation_monte_carlo_method_in_c parallel "$NP" "$NT"
      echo $'\n\n'
    done
  done
done | tee pi_approximation_monte_carlo_method_in_c_parallel_results.csv