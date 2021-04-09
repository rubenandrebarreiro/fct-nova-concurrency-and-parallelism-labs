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


// Package pt.unl.fct.parallel.threads
package pt.unl.fct.parallel.threads;


// Import the Thread Local Random, from the Java.Util.Concurrent
import java.util.concurrent.ThreadLocalRandom;


// Class of Inside Hits Counter Thread, extending the Thread Class
public class InsideHitsCounterThread extends Thread {

    // Global Variables:

    /**
     * The ID of the Thread.
     */
    private final int threadID;

    /**
     *  The number of the number of Random Points, specified for the Thread.
     */
    private final int numPointsForThisThread;

    /**
     * The variable for the Coordinate X of the current generated Random Point,
     * specified for the Thread.
     */
    private float pointXForThisThread;

    /**
     * The variable for the Coordinate Y of the current generated Random Point,
     * specified for the Thread.
     */
    private float pointYForThisThread;

    /**
     * The Inside Hits Count, for the Thread.
     */
    private int insideHitsCountForThisThread;

    /**
     * The Boolean Flag for the Logging of the Performance of the Simulation.
     */
    private final boolean loggingPerformanceBooleanFlag;


    // Constructors:

    /**
     * Constructor #1:
     * - Constructs the Object for the Thread, for the Inside Hits Counter,
     *   given the ID and the number of Random Points, specified for the Thread;
     *
     * @param threadID the ID of the Thread
     *
     * @param numPointsForThisThread the number of Random Points, specified for the Thread
     *
     * @param loggingPerformanceBooleanFlag the Boolean Flag for the Logging of the Performance of the Simulation
     */
    public InsideHitsCounterThread(int threadID, int numPointsForThisThread,
                                   boolean loggingPerformanceBooleanFlag) {

        this.threadID = threadID;

        this.numPointsForThisThread = numPointsForThisThread;

        this.pointXForThisThread = this.pointYForThisThread = 0;

        this.loggingPerformanceBooleanFlag = loggingPerformanceBooleanFlag;

    }


    // Methods:

    /**
     * Runnable Override method, for this Thread.
     */
    @Override
    public void run() {

        this.countInsideHitsInParallel();

    }

    /**
     * Perform the Inside Hits Count, in Parallel.
     */
    private void countInsideHitsInParallel() {

        // Initialize the Inside Hits Count, for the Thread
        this.insideHitsCountForThisThread = 0;

        // For each Random Point to be generated, by the Thread
        for (int currentPointForThisThread = 0;
             currentPointForThisThread < this.numPointsForThisThread;
             currentPointForThisThread++) {

            // The Random Points generated
            this.pointXForThisThread = ThreadLocalRandom.current().nextFloat();
            this.pointYForThisThread = ThreadLocalRandom.current().nextFloat();

            double pythagorasFormula = ((this.pointXForThisThread * this.pointXForThisThread) +
                    (this.pointYForThisThread * this.pointYForThisThread));

            // If the Random Point generated, is inside the circle
            if (pythagorasFormula <= 1) {

                // Increase the Inside Hits Count, for the Thread
                this.insideHitsCountForThisThread++;

            }

        }

        // Synchronize the Print of the Information of the Inside Hits Count, for the Thread
        synchronized (this) {

            // If the Boolean Flag for the Logging of the Performance of the Simulation is set to True
            if (this.loggingPerformanceBooleanFlag) {

                this.printHitsCountInformationForThisThread();

            }

        }

    }

    /**
     * Return the Inside Hits Count, for the Thread.
     *
     * @return the Inside Hits Count, for the Thread
     */
    public int getInsideHitsCountForThisThread() {

        return this.insideHitsCountForThisThread;

    }

    /**
     * Prints the Hits Count Information, for this Thread.
     */
    public synchronized void printHitsCountInformationForThisThread() {

        double piEstimationForThisThread = 4 * ( (float) ( ( (double) this.insideHitsCountForThisThread ) /
                                                           ( (double) this.numPointsForThisThread ) ) );

        System.out.printf("-- INDIVIDUAL RESULTS [PARALLEL, Thread %d] -- %n", this.threadID);
        System.out.printf("Total Number of Points, for this Thread: %d%n", this.numPointsForThisThread);
        System.out.printf("Points within circle, for this Thread: %d%n", this.insideHitsCountForThisThread);
        System.out.printf("Pi Estimation, for this Thread: %.6f%n", piEstimationForThisThread);

        System.out.printf("%n");

    }

}
