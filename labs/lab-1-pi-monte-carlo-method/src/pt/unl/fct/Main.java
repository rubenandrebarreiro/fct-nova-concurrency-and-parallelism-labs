package pt.unl.fct;

import pt.unl.fct.sequential.SequentialPiApproximation;
import pt.unl.fct.utils.FinalResults;

import java.lang.management.ManagementFactory;
import java.lang.management.ThreadMXBean;

public class Main {

    public static void main(String[] args) {

        if(args.length == 0 || args.length > 3) {

            // If the program does not receive the expected arguments,
            // it will print an error message, providing a suggestion of the
            // arguments needed
            System.err.println("Error: Wrong arguments!!!");
            System.err.println("Usage: PiMonteCarloMethod program_version num_points [num_threads]");
            System.err.println("Run: \"PiMonteCarloMethod help\" for help...");

            // Wrong Command-Line argument(s)
            System.exit(1);

        }
        else {

            if( (args.length == 1) && (args[0].equalsIgnoreCase("HELP")) ) {

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
                String programVersion = args[0];

                // The number of points for the Monte Carlo Simulation and Pi Approximation
                int numPoints = Integer.parseInt(args[1]);

                // Parallel Version for a given number of Threads
                if(programVersion.equalsIgnoreCase("parallel") && args.length == 3) {

                    int numThreads = Integer.parseInt(args[2]);

                    // TODO: Parallel version go there

                }
                else {

                    if(programVersion.equalsIgnoreCase("sequential") && args.length == 2) {

                        ThreadMXBean threadMXBean = ManagementFactory.getThreadMXBean();

                        SequentialPiApproximation sequentialPiApproximation =
                                new SequentialPiApproximation(numPoints);

                        long startRealTimeNSecs = System.nanoTime();
                        long startCPUTimeNSecs = threadMXBean.getCurrentThreadCpuTime();
                        long startUserTimeNSecs = threadMXBean.getCurrentThreadUserTime();

                        sequentialPiApproximation.executeSimulation();

                        long endCPUTimeNSecs = threadMXBean.getCurrentThreadCpuTime();
                        long endUserTimeNSecs = threadMXBean.getCurrentThreadUserTime();
                        long endRealTimeNSecs = System.nanoTime();


                        int totalNumPoints = sequentialPiApproximation.getTotalNumPoints();
                        int insideHitsCount = sequentialPiApproximation.getInsideHitsCount();

                        FinalResults finalResults = new FinalResults(programVersion, totalNumPoints, insideHitsCount,
                                                                     startRealTimeNSecs, endRealTimeNSecs,
                                                                     startCPUTimeNSecs, endCPUTimeNSecs,
                                                                     startUserTimeNSecs, endUserTimeNSecs);

                        finalResults.printFinalResults();

                    }
                    else {

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
