/**
 * @author Tugrul Yatagan 504161551
 */

package blg546e_hw2;

import java.util.Random;


public class BLG546E_HW2 {

    public static void main(String[] args) throws Exception {
        /* Generate random randomArray */
        int[] randomArray = generateRandomArray(10240000); /* should be multiple of 128 */
        int[] threadNumbers = new int[]{2, 4, 8, 16, 32, 64, 128};

//        MergeSort.printArray(randomArray);

        SequentialMergeSort sequentialMergeSort = new SequentialMergeSort(randomArray);
        ParallelMergeSort parallelMergeSort = new ParallelMergeSort(randomArray);

        /* Recursive sequential merge sort */
        long sequentialDuration = sequentialMergeSort.execute();

        /* Iterative parallel merge sort */
        long[] parallelDurations = parallelMergeSort.execute(threadNumbers);

        System.out.printf("Input randomArray size is %d\n", randomArray.length);
        System.out.printf("Sequential execution duration is %d ms\n", sequentialDuration);
        System.out.println("Parallel execution:\n#Threads   Duration   Speedup");
        for (int i = 0; i < threadNumbers.length; i++) {
            double speedup = (double)sequentialDuration / parallelDurations[i];
            System.out.printf("%4d      %5d ms    %.2f\n", threadNumbers[i], parallelDurations[i], speedup);
        }
    }

    public static int[] generateRandomArray(int n) {
        int[] matrix = new int[n];
        Random rand = new Random();

        for (int i = 0; i < n; i++) {
            matrix[i] = rand.nextInt(10000);
        }
        return matrix;
    }
}
