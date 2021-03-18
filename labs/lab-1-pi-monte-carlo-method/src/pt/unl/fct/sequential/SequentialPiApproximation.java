package pt.unl.fct.sequential;

public class SequentialPiApproximation {

    private final int numPoints;

    private int insideHitsCount;

    private boolean finished;


    public SequentialPiApproximation(int numPoints) {

        this.numPoints = numPoints;

        this.insideHitsCount = 0;

        this.finished = false;

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

        this.finished = true;

    }

    public int getNumPoints() {

        return this.numPoints;

    }

    public int getHitsCount() {

        return (this.finished)? this.insideHitsCount : -1;

    }

    public boolean isFinished() {

        return this.finished;

    }

}
