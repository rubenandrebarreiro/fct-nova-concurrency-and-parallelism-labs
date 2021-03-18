package pt.unl.fct.sequential;

public class SequentialPiApproximation {

    private final int numPoints;

    private int insideHitsCount;


    public SequentialPiApproximation(int numPoints) {

        this.numPoints = numPoints;

        this.insideHitsCount = 0;

    }

    public void executeSimulation() {

        for(int currentRound = 0; currentRound < this.numPoints; currentRound++) {

            double pointX = Math.random();
            double pointY = Math.random();

            double pythagorasFormula = ( (pointX * pointX) + (pointY * pointY) );

            if(pythagorasFormula <= 1) {

                this.insideHitsCount++;

            }

        }

    }

    public int getTotalNumPoints() {

        return this.numPoints;

    }

    public int getInsideHitsCount() {

        return this.insideHitsCount;

    }

}
