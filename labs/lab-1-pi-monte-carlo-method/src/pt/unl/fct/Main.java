package pt.unl.fct;

public class Main {

    public static void main(String[] args) {

        if(args.length == 0 || args.length > 2) {

            // If the program does not receive the expected arguments,
            // it will print an error message, providing a suggestion of the
            // arguments needed
            System.err.println("Usage: pi-monte-carlo-method program_version num_points [num_threads]");

        }

    }

}
