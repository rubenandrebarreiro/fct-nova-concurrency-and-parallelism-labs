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


// Package pt.unl.fct.parallel.executorservice
package pt.unl.fct.parallel.executorservice;


// Import the InsideHitsCounterThread from the pt.unl.fct.parallel.threads Package
import pt.unl.fct.parallel.threads.InsideHitsCounterThread;

// Import the ExecutorService, Executors and TimeUnit, from the Java.Util Package
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;

// Class of Parallel Executor Service, for Pi Approximation/Estimation
public class ParallelExecutorServicePiApproximation {

    // Global Variables:

    /**
     * The Total Number of Points of the Simulation.
     */
    private final int numTotalPoints;

    /**
     * The size of the Threads' Pool.
     */
    private final int threadPoolSize;

    /**
     * The Number of Points, specified for each Thread.
     */
    private final int numPointsPerThread;

    /**
     * The number of Inside Hits Count, from the Random Points generated, in the Simulation,
     * verified to be within the Circle of radius 1.
     */
    private int insideHitsCount;

    /**
     * The Boolean Flag for the Logging of the Performance of the Simulation.
     */
    private final boolean loggingPerformanceBooleanFlag;


    // Constructors:

    /**
     * Constructor #1:
     * - Constructs the Object for the Parallel Pi Approximation/Estimation, with an Executor Service,
     *   given the total number of points and the number of threads, for the Simulation;
     *
     * @param numTotalPoints the Total Number of Points of the Simulation
     *
     * @param numThreads the Number of Threads, specified for the Simulation
     *
     * @param loggingPerformanceBooleanFlag the Boolean Flag for the Logging of the Performance of the Simulation
     */
    public ParallelExecutorServicePiApproximation(int numTotalPoints, int numThreads,
                                                  boolean loggingPerformanceBooleanFlag) {

        this.numTotalPoints = numTotalPoints;

        this.threadPoolSize = numThreads;

        this.numPointsPerThread = ( this.numTotalPoints / this.threadPoolSize );

        this.loggingPerformanceBooleanFlag = loggingPerformanceBooleanFlag;

        this.insideHitsCount = 0;

    }


    // Methods:

    /**
     * Execution of the Simulation, in Parallel, with an Executor Service and a fixed Threads' Pool.
     *
     * @throws InterruptedException the Interrupted Exception, for the Execution of the Simulation, in Parallel
     */
    public void executeSimulationInParallel() throws InterruptedException {

        // Create an Executor Service, with an Executor Service and a fixed Thread Pool's size
        ExecutorService executorService = Executors.newFixedThreadPool(this.threadPoolSize);

        // Create a Pool of Threads for the Inside Hits Counter
        InsideHitsCounterThread[] insideHitsCounterThreadPool = new InsideHitsCounterThread[this.threadPoolSize];

        // For each Thread in the Threads' Pool
        for(int currentThreadID = 0; currentThreadID < this.threadPoolSize; currentThreadID++) {

            // All the Threads (with the exception of the last one),
            // will always perform an integer and divisible number of tasks
            // (i.e., this Threads will generate always a fixed number of random points)
            if(currentThreadID < (this.threadPoolSize - 1)) {

                insideHitsCounterThreadPool[currentThreadID] =
                        new InsideHitsCounterThread(currentThreadID, this.numPointsPerThread,
                                                    this.loggingPerformanceBooleanFlag);

            }
            // The last Thread will perform the same number of tasks than the others and the remaining ones,
            // due to a possible non-integer division of the tasks
            // (i.e., this Thread will generate the predefined number of
            //  random points and eventually, some remaining ones)
            else {

                insideHitsCounterThreadPool[currentThreadID] =
                        new InsideHitsCounterThread(currentThreadID,
                                (this.numPointsPerThread + (this.numTotalPoints % this.threadPoolSize)),
                                this.loggingPerformanceBooleanFlag);

            }

            executorService.execute(insideHitsCounterThreadPool[currentThreadID]);

        }

        // Terminate/Shutdown the Executor Service
        executorService.shutdown();

        // Retrieve the termination result of the Executor Service
        boolean terminationResult = executorService.awaitTermination(1L, TimeUnit.MINUTES);


        // The Executor Service terminated
        if(terminationResult) {

            synchronized (this) {

                // For each Thread in the Threads' Pool
                for(int currentThreadID = 0; currentThreadID < this.threadPoolSize; currentThreadID++) {

                    // Update the final counting of Inside Hits, within the Circle of radius 1
                    this.insideHitsCount +=
                            insideHitsCounterThreadPool[currentThreadID].getInsideHitsCountForThisThread();

                }

                System.out.printf("%n%n");
            }

        }
        // The Executor Service does not terminated
        else {

            // The timeout elapsed
            System.err.println("ERROR: Timeout elapsed!!!");

            // An unexpected error happened
            System.exit(-1);

        }

    }

    /**
     * Return the Total Number of Points of the Simulation.
     *
     * @return the Total Number of Points of the Simulation
     */
    public int getNumTotalPoints() {

        return this.numTotalPoints;

    }

    /**
     * Return the number of Inside Hits Count, from the Random Points generated, in the Simulation,
     * verified to be within the Circle of radius 1.
     *
     * @return the number of Inside Hits Count, from the Random Points generated, in the Simulation,
     *         verified to be within the Circle of radius 1
     */
    public int getInsideHitsCount() {

        return this.insideHitsCount;

    }

}
