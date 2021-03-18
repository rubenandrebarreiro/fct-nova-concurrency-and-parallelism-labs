package pt.unl.fct.utils;

import java.util.Locale;

public class FinalResults {

    private final String programVersion;

    private final int totalNumPoints;

    private final int insideHitsCount;

    private final double piEstimation;

    private final double executionRealTimeSecs;

    private final double executionCPUTimeSecs;

    private final double executionUserTimeSecs;

    private final double executionSystemTimeSecs;


    public FinalResults(String programVersion, int totalNumPoints, int insideHitsCount,
                        long startRealTimeNSecs, long endRealTimeNSecs,
                        long startCPUTimeNSecs, long endCPUTimeNSecs,
                        long startUserTimeNSecs, long endUserTimeNSecs) {

        this.programVersion = programVersion.toUpperCase(Locale.ROOT);
        this.totalNumPoints = totalNumPoints;
        this.insideHitsCount = insideHitsCount;

        this.piEstimation = 4 * ( (float) ( ( (double) this.insideHitsCount ) / ( (double) this.totalNumPoints ) ) );

        this.executionRealTimeSecs = (endRealTimeNSecs - startRealTimeNSecs) / 1E9;
        this.executionCPUTimeSecs = (endCPUTimeNSecs - startCPUTimeNSecs) / 1E9;
        this.executionUserTimeSecs = (endUserTimeNSecs - startUserTimeNSecs) / 1E9;
        this.executionSystemTimeSecs = (this.executionCPUTimeSecs - this.executionUserTimeSecs) / 1E9;

    }

    public void printFinalResults() {

        System.out.printf("[MONTE CARLO SIMULATION - PI ESTIMATION]%n%n");

        System.out.printf("---- Results of the Monte Carlo Simulation [%s] ----%n", this.programVersion);
        System.out.printf("Total Number of Points: %d%n", this.totalNumPoints);
        System.out.printf("Points within circle: %d%n", this.insideHitsCount);
        System.out.printf("Pi Estimation: %.6f%n", this.piEstimation);

        System.out.printf("%n");

        System.out.printf("---- Performance of the Monte Carlo Simulation [%s] ----%n", this.programVersion);
        System.out.printf("Real Time: %.3fs%n", this.executionRealTimeSecs);
        System.out.printf("CPU Time: %.3fs%n", this.executionCPUTimeSecs);
        System.out.printf("User Time: %.3fs%n", this.executionUserTimeSecs);
        System.out.printf("System Time: %.3fs%n", this.executionSystemTimeSecs);

    }

}
