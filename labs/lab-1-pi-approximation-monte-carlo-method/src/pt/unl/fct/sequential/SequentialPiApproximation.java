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


// Package sequential.fct.unl.pt
package pt.unl.fct.sequential;


// Class of Sequential Pi Approximation/Estimation
public class SequentialPiApproximation {

    // Global Variables:

    /**
     * The Total Number of Points of the Simulation.
     */
    private final int numTotalPoints;

    /**
     * The number of Inside Hits Count, from the Random Points generated, in the Simulation,
     * verified to be within the Circle of radius 1.
     */
    private int insideHitsCount;


    // Constructor:

    /**
     * Constructor #1:
     * - Constructs the Object for the Sequential Pi Approximation/Estimation,
     *   given the total number of points for the Simulation;
     *
     * @param numTotalPoints the Total Number of Points of the Simulation
     */
    public SequentialPiApproximation(int numTotalPoints) {

        this.numTotalPoints = numTotalPoints;

        this.insideHitsCount = 0;

    }


    // Methods:

    /**
     * Execute the Simulation/Estimation, for the Monte Carlo Method.
     */
    public void executeSimulation() {

        // For each current Point, of the Simulation
        for(int currentPoint = 0; currentPoint < this.numTotalPoints; currentPoint++) {

            // The Coordinates X and Y, for the Random Point generated
            float pointX = (float) Math.random();
            float pointY = (float) Math.random();

            // Computation of the Pythagoras Formula,
            // given the Coordinates X and Y, for the Random Point generated
            double pythagorasFormula = ( (pointX * pointX) + (pointY * pointY) );

            // The Random Point generated is inside the Circle of Radius 1
            if(pythagorasFormula <= 1) {

                this.insideHitsCount++;

            }

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
