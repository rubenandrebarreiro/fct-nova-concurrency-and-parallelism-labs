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


// Package pt.unl.fct.utils
package pt.unl.fct.utils;


// Import the Local Package, from the Java.Util
import java.util.Locale;

// Class of Final Results
public class FinalResults {

    // Global Variables:

    /**
     * The Program's Version (i.e., SEQUENTIAL or PARALLEL).
     */
    private final String programVersion;

    /**
     * The number of Threads used, for the Parallel Versions.
     */
    private final int numThreads;

    /**
     * The total number of Random Points to be generated, in the Simulation.
     */
    private final int totalNumPoints;

    /**
     * The number of Inside Hits Count, from the Random Points generated, in the Simulation,
     * verified to be within the Circle of radius 1.
     */
    private final int insideHitsCount;

    /**
     * The Pi Approximation/Estimation value, from the number of Inside Hits Count.
     */
    private final double piEstimation;

    /**
     * The Real Time, in seconds, of the execution of the Simulation.
     */
    private final double executionRealTimeSecs;

    /**
     * The CPU Time, in seconds, of the execution of the Simulation.
     */
    private final double executionCPUTimeSecs;

    /**
     * The User Time, in seconds, of the execution of the Simulation.
     */
    private final double executionUserTimeSecs;

    /**
     * The System Time, in seconds, of the execution of the Simulation.
     */
    private final double executionSystemTimeSecs;


    // Constructors:

    /**
     * Constructor #1:
     * - Constructs the Object for the Final Results, for the Inside Hits Counter,
     *   given the ID and the number of Random Points, specified for the Thread;
     *
     * @param programVersion the Program's Version (i.e., SEQUENTIAL or PARALLEL)
     * @param numThreads the number of Threads used, for the Parallel Versions
     * @param totalNumPoints the total number of Random Points to be generated, in the Simulation
     * @param insideHitsCount the number of Inside Hits Count, from the Random Points generated, in the Simulation,
     *                        verified to be within the Circle of radius 1
     * @param startRealTimeNSecs the Real Time, in nanoseconds, at the Start of the Simulation
     * @param endRealTimeNSecs the Real Time, in nanoseconds, at the End of the Simulation
     * @param startCPUTimeNSecs the CPU Time, in nanoseconds, at the Start of the Simulation
     * @param endCPUTimeNSecs the CPU Time, in nanoseconds, at the End of the Simulation
     * @param startUserTimeNSecs the User Time, in nanoseconds, at the Start of the Simulation
     * @param endUserTimeNSecs the User Time, in nanoseconds, at the End of the Simulation
     */
    public FinalResults(String programVersion, int numThreads,
                        int totalNumPoints, int insideHitsCount,
                        long startRealTimeNSecs, long endRealTimeNSecs,
                        long startCPUTimeNSecs, long endCPUTimeNSecs,
                        long startUserTimeNSecs, long endUserTimeNSecs) {

        this.programVersion = programVersion.toUpperCase(Locale.ROOT);
        this.numThreads = (this.programVersion.equalsIgnoreCase("PARALLEL")) ? numThreads : 1;

        this.totalNumPoints = totalNumPoints;
        this.insideHitsCount = insideHitsCount;

        this.piEstimation = 4 * ( (float) ( ( (double) this.insideHitsCount ) / ( (double) this.totalNumPoints ) ) );

        this.executionRealTimeSecs = (endRealTimeNSecs - startRealTimeNSecs) / 1E9;
        this.executionCPUTimeSecs = (endCPUTimeNSecs - startCPUTimeNSecs) / 1E9;
        this.executionUserTimeSecs = (endUserTimeNSecs - startUserTimeNSecs) / 1E9;
        this.executionSystemTimeSecs = (this.executionCPUTimeSecs - this.executionUserTimeSecs) / 1E9;

    }


    // Methods:

    /**
     * Print the Final Results of the Simulation, by the Monte Carlo Method.
     */
    public void printFinalResults() {

        System.out.printf("[MONTE CARLO METHOD SIMULATION - PI ESTIMATION]%n%n");

        // If the Program's Version is set as Parallel
        if(this.programVersion.equalsIgnoreCase("PARALLEL")) {

            System.out.printf("---- RESULTS [%s, with %d Threads] ----%n", this.programVersion, this.numThreads);

        }
        // If the Program's Version is set as Sequential
        else {

            System.out.printf("---- RESULTS [%s] ----%n", this.programVersion);

        }

        // Prints the Information of the Final Results of the Simulation
        System.out.printf("Total Number of Points: %d%n", this.totalNumPoints);
        System.out.printf("Points within circle: %d%n", this.insideHitsCount);
        System.out.printf("Pi Estimation: %.6f%n", this.piEstimation);

        System.out.printf("%n");

        // If the Program's Version is set as Parallel
        if(this.programVersion.equalsIgnoreCase("PARALLEL")) {

            System.out.printf("---- PERFORMANCE [%s, with %d Threads] ----%n", this.programVersion, this.numThreads);

        }
        // If the Program's Version is set as Sequential
        else {

            System.out.printf("---- PERFORMANCE [%s] ----%n", this.programVersion);

        }

        // Prints the Information of the Global Performance of the Simulation
        System.out.printf("Real Time: %.3fs%n", this.executionRealTimeSecs);
        System.out.printf("CPU Time: %.3fs%n", this.executionCPUTimeSecs);
        System.out.printf("User Time: %.3fs%n", this.executionUserTimeSecs);
        System.out.printf("System Time: %.3fs%n", this.executionSystemTimeSecs);

    }

}
