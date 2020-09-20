/**
 * @author Tugrul Yatagan 504161551
 */

package blg546e_hw1;


public class SequentialConv extends Conv {
    public SequentialConv(int[][] input, int[][] kernel) {
        super(input, kernel);
    }

    public long Execute() {
        long startTime = System.nanoTime();

        convolution();

        long endTime = System.nanoTime();
        return (endTime - startTime) / 1000000;
    }

    private void convolution() {
        for (int i = 0; i < input_row; i++) {
            for (int j = 0; j < input_col; j++) {
                pixel_convolution(i, j);
            }
        }
        //print_matrix(output);
    }
}
