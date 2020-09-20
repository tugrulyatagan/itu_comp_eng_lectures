/**
 * @author Tugrul Yatagan 504161551
 */

package blg546e_hw1;

import java.util.Random;


public class BLG546E_HW1 {

    public static void main(String[] args) throws Exception {
        /* Generate random input and kernel matrices */
        int[][] input = generate_random_matrix(10000, 10000);
        int[][] kernel = generate_random_matrix(7, 7);
//        int[][] input = new int[][] {
//                { 1, 2, 3 },
//                { 4, 5, 6 },
//                { 7, 8, 9 }
//        };
//        int[][] kernel = new int[][] {
//                {  1,  2,  1 },
//                {  0,  0,  0 },
//                { -1, -2, -1 }
//        };
        int[] thread_numbers = new int[]{2, 4, 8, 16, 32, 64, 128};

        SequentialConv sequentialConv = new SequentialConv(input, kernel);
        SynchronizedConv synchronizedConv = new SynchronizedConv(input, kernel);
        LockedConv lockedConv = new LockedConv(input, kernel);
        AtomicConv atomicConv = new AtomicConv(input, kernel);

        long sequentialDuration = sequentialConv.Execute();
        long[] synchronizedDurations = synchronizedConv.Execute(thread_numbers);
        long[] lockedDurations = lockedConv.Execute(thread_numbers);
        long[] atomicDurations = atomicConv.Execute(thread_numbers);

        System.out.printf("Input matrix size is %dx%d, kernel matrix size is %dx%d\n\n", input.length, input[0].length, kernel.length, kernel[0].length);
        System.out.printf("Sequential execution duration is %d ms\n\n", sequentialDuration);
        System.out.println("Synchronized section method execution:\n#Threads   Duration   Speedup");
        for (int i = 0; i < thread_numbers.length; i++) {
            double speedup = (double)sequentialDuration / synchronizedDurations[i];
            System.out.printf("%4d      %5d ms    %.2f\n", thread_numbers[i], synchronizedDurations[i], speedup);
        }
        System.out.println("\nReentrantLock method execution:\n#Threads   Duration   Speedup");
        for (int i = 0; i < thread_numbers.length; i++) {
            double speedup = (double)sequentialDuration / lockedDurations[i];
            System.out.printf("%4d      %5d ms    %.2f\n", thread_numbers[i], lockedDurations[i], speedup);
        }
        System.out.println("\nAtomicInteger method execution:\n#Threads   Duration   Speedup");
        for (int i = 0; i < thread_numbers.length; i++) {
            double speedup = (double)sequentialDuration / atomicDurations[i];
            System.out.printf("%4d      %5d ms    %.2f\n", thread_numbers[i], atomicDurations[i], speedup);
        }
    }

    public static int[][] generate_random_matrix(int row, int col) {
        int[][] matrix = new int[row][col];
        Random rand = new Random();

        for (int i = 0; i < row; i++)
            for (int j = 0; j < col; j++)
                matrix[i][j] = rand.nextInt(1000);

        return matrix;
    }
}
