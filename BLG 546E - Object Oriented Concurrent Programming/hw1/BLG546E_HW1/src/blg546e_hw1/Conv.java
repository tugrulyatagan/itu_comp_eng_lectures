package blg546e_hw1;

public abstract class Conv {

    protected int[][] input;
    protected int[][] kernel;
    protected int[][] output;
    protected int input_row, input_col, kernel_row, kernel_col;

    public Conv(int[][] input, int[][] kernel) {
        input_row = input.length;
        input_col = input[0].length;
        kernel_row = kernel.length;
        kernel_col = kernel[0].length;

        this.input = input;
        this.kernel = kernel;
        output = new int[input_row][input_col];
    }

    protected void pixel_convolution(int i, int j) {
        int sum = 0;
        int s_i = i - (kernel_row - 1) / 2;
        int s_j = j - (kernel_col - 1) / 2;

        for (int k_i = 0; k_i < kernel_row; k_i++) {
            if ((s_i + k_i >= 0) && (s_i + k_i < input_row)) {
                for (int k_j = 0; k_j < kernel_col; k_j++) {
                    if ((s_j + k_j >= 0) && (s_j + k_j < input_col)) {
                        sum += kernel[k_i][k_j] * input[s_i + k_i][s_j + k_j];
                    }
                }
            }
        }

        output[i][j] = sum;
    }

    public void print_matrix(int[][] matrix) {
        for (int row = 0; row < matrix.length; row++) {
            for (int col = 0; col < matrix[row].length; col++) {
                System.out.printf("%5d", matrix[row][col]);
            }
            System.out.println();
        }
    }
}
