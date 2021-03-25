/**
 *
 * Pi Approximation/Estimation, for the Monte Carlo Method,
 * using Sequential and Parallel Versions
 *
 * @author: Ruben Andre Barreiro
 * @email: r.barreiro@campus.fct.unl.pt
 * @number-student: 42648
 *
 * NOVA School of Science and Technology | NOVA University of Lisbon (FCT NOVA)
 *
 */


// Package fct.unl.pt
package pt.unl.fct;

// Import the Local Packages needed, for the Sequential and Parallel Versions,
// as also, the object for the Final Results
import pt.unl.fct.parallel.executorservice.ParallelExecutorServicePiApproximation;
import pt.unl.fct.sequential.SequentialPiApproximation;
import pt.unl.fct.utils.FinalResults;

// Import the Management Factory, for monitoring the Multi-Threading Factoring
import java.lang.management.ManagementFactory;

// Import the ThreadMXBean, for monitoring the Multi-Threading Factoring
import java.lang.management.ThreadMXBean;
import java.util.Locale;


// The Class of the Main Program
public class Main {

    // The Command-Line method, for the Main Program
    public static void main(String[] args) throws InterruptedException {

        // If it were provided a wrong number of arguments
        if(args.length == 0 || args.length > 4) {

            // If the program does not receive the expected arguments,
            // it will print an error message, providing a suggestion of the
            // arguments needed
            System.err.println("Error: Wrong arguments!!!");
            System.err.println("Usage: PiMonteCarloMethod.jar program_version num_points [logging] [num_threads]");
            System.err.println("Run: \"PiMonteCarloMethod help\" for help...");

            // Wrong Command-Line argument(s)
            System.exit(1);

        }
        // If it were provided a correct number of arguments
        else {

            // It were selected the Help command
            if( (args.length == 1) && (args[0].equalsIgnoreCase("HELP")) ) {

                // Print the suggestions of Usage of the Program
                System.err.println("Usage: PiMonteCarloMethod program_version num_points [num_threads]");
                System.err.println("program_version: [sequential,parallel]");
                System.err.println("num_points: the number of points to simulate in the Monte Carlo Simulation");
                System.err.println("[num_threads]: the number of threads to launch for the Monte Carlo Simulation" +
                                   "(only valid for the parallel version) [OPTIONAL]");

                // Everything went fine
                System.exit(0);

            }
            else {

                // The Program's Version (i.e., Sequential or Parallel Version)
                String programVersion = args[0].toUpperCase(Locale.ROOT);

                // The number of points for the Monte Carlo Simulation and Pi Approximation
                int numPoints = Integer.parseInt(args[1]);

                // Set the boolean flag for the Logging of the Performance
                boolean loggingPerformanceBooleanFlag = ( args.length >= 3 && Boolean.parseBoolean(args[2]) );

                // It was chosen the Parallel Version, for the Simulation, with a given number of Threads
                if(programVersion.equalsIgnoreCase("PARALLEL")) {

                    // Retrieve the number of Available Processors
                    int numAvailableProcessors = Runtime.getRuntime().availableProcessors();

                    // Try to use the specified number of Threads, otherwise,
                    // it will be used the number of Available Processors
                    int numThreads = (args.length == 4) ? Integer.parseInt(args[3]) : numAvailableProcessors;

                    // The specified number of Threads to use is bigger than the number of Available Processors
                    if(numThreads > numAvailableProcessors) {

                        // Warning for the specified number of Threads to use be bigger than
                        // the number of Available Processors
                        System.err.println("The number of Threads specified is bigger than" +
                                           "the number of available Processors...");

                        // Warning for the setup of the number of Threads to use as
                        // the number of Available Processors
                        System.err.println("It will be used the " + numAvailableProcessors +
                                           " available Processors, in the CPU.");

                        // Set the number of Threads to use as the number of Available Processors
                        numThreads = numAvailableProcessors;

                    }

                    // Get the ThreadMXBean, for monitoring the Multi-Threading Factoring
                    ThreadMXBean threadMXBean = ManagementFactory.getThreadMXBean();

                    // Create the object for the Simulation and Pi Approximation/Estimation,
                    // for the Monte Carlo Method, in Parallel Version, with an Executor Service
                    ParallelExecutorServicePiApproximation parallelExecutorServicePiApproximation =
                            new ParallelExecutorServicePiApproximation(numPoints, numThreads);

                    // Retrieve the current Real, CPU and User times, before the Simulation be performed
                    long startRealTimeNSecs = System.nanoTime();
                    long startCPUTimeNSecs = threadMXBean.getCurrentThreadCpuTime();
                    long startUserTimeNSecs = threadMXBean.getCurrentThreadUserTime();

                    // Execute the Simulation, in Parallel Version, with an Executor Service
                    parallelExecutorServicePiApproximation.executeSimulationInParallel();

                    // Retrieve the current Real, CPU and User times, after the Simulation be performed
                    long endCPUTimeNSecs = threadMXBean.getCurrentThreadCpuTime();
                    long endUserTimeNSecs = threadMXBean.getCurrentThreadUserTime();
                    long endRealTimeNSecs = System.nanoTime();

                    // Retrieve the Total Number of Points generated and the number of the Inside Hit Count
                    int numTotalPoints = parallelExecutorServicePiApproximation.getNumTotalPoints();
                    int insideHitsCount = parallelExecutorServicePiApproximation.getInsideHitsCount();

                    // Create the object for the Final Results, in Parallel Version, with an Executor Service
                    FinalResults finalResults = new FinalResults(programVersion, numThreads,
                                                                 numTotalPoints, insideHitsCount,
                                                                 startRealTimeNSecs, endRealTimeNSecs,
                                                                 startCPUTimeNSecs, endCPUTimeNSecs,
                                                                 startUserTimeNSecs, endUserTimeNSecs,
                                                                 loggingPerformanceBooleanFlag);

                    // Print the Final Results
                    finalResults.printFinalResults();

                }
                else {

                    // It was chosen the Sequential Version, for the Simulation
                    if(programVersion.equalsIgnoreCase("SEQUENTIAL") && args.length <= 3) {

                        // Get the ThreadMXBean, for monitoring the Multi-Threading Factoring
                        ThreadMXBean threadMXBean = ManagementFactory.getThreadMXBean();

                        // Create the object for the Simulation and Pi Approximation/Estimation,
                        // for the Monte Carlo Method, in Sequential Version
                        SequentialPiApproximation sequentialPiApproximation =
                                new SequentialPiApproximation(numPoints);

                        // Retrieve the current Real, CPU and User times, before the Simulation be performed
                        long startRealTimeNSecs = System.nanoTime();
                        long startCPUTimeNSecs = threadMXBean.getCurrentThreadCpuTime();
                        long startUserTimeNSecs = threadMXBean.getCurrentThreadUserTime();

                        // Execute the Simulation, in Sequential Version, with an Executor Service
                        sequentialPiApproximation.executeSimulation();

                        // Retrieve the current Real, CPU and User times, after the Simulation be performed
                        long endCPUTimeNSecs = threadMXBean.getCurrentThreadCpuTime();
                        long endUserTimeNSecs = threadMXBean.getCurrentThreadUserTime();
                        long endRealTimeNSecs = System.nanoTime();

                        // Retrieve the Total Number of Points generated and the number of the Inside Hit Count
                        int numTotalPoints = sequentialPiApproximation.getNumTotalPoints();
                        int insideHitsCount = sequentialPiApproximation.getInsideHitsCount();

                        // Create the object for the Final Results, in Sequential Version
                        FinalResults finalResults = new FinalResults(programVersion, 1,
                                                                     numTotalPoints, insideHitsCount,
                                                                     startRealTimeNSecs, endRealTimeNSecs,
                                                                     startCPUTimeNSecs, endCPUTimeNSecs,
                                                                     startUserTimeNSecs, endUserTimeNSecs,
                                                                     loggingPerformanceBooleanFlag);

                        // Print the Final Results
                        finalResults.printFinalResults();

                    }
                    else {

                        // Print Error's information, due to wrong arguments and
                        // the suggestions of Usage of the Program
                        System.err.println("Error: Wrong arguments!!!");
                        System.err.println("Usage: PiMonteCarloMethod program_version num_points [num_threads]");
                        System.err.println("Run: \"PiMonteCarloMethod help\" for help...");

                        // Wrong Command-Line argument(s)
                        System.exit(1);

                    }

                }

            }

        }

    }

}
