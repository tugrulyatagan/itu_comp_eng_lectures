/**
 * @author Tugrul Yatagan 504161551
 */

package blg546e_hw3;

public class BLG546E_HW3 {

    public static void main(String[] args) throws Exception {
        int parallelism = 32; /* Number of allowed thread or task pool size */
        int orderedOddArraySize = 1000000;

        int[] orderedOddArray = generateOrderedOddArray(orderedOddArraySize);

        System.out.printf("orderedOddArraySize=%d, parallelism=%d\n", orderedOddArraySize, parallelism);

        SeparateThread separateThread = new SeparateThread(orderedOddArray, parallelism);
        CachedThread cachedThread = new CachedThread(orderedOddArray, parallelism);
        ForkJoinThread forkJoinThread = new ForkJoinThread(orderedOddArray, parallelism);
        RecursiveForkJoinThread recursiveForkJoinThread = new RecursiveForkJoinThread(orderedOddArray, parallelism);

        /* Execute and measure all methods */
        long separateThreadDuration = separateThread.execute();
        System.out.printf("SeparateThread execution time is %d ms\n", separateThreadDuration);

        long cachedThreadDuration = cachedThread.execute();
        System.out.printf("CachedThread execution time is %d ms\n", cachedThreadDuration);

        long forkJoinThreadDuration = forkJoinThread.execute();
        System.out.printf("ForkJoinThread execution time is %d ms\n", forkJoinThreadDuration);

//        long recursiveForkJoinThreadDuration = recursiveForkJoinThread.execute();
//        System.out.printf("RecursiveForkJoinThread execution time is %d ms\n", recursiveForkJoinThreadDuration);
    }

    public static int[] generateOrderedOddArray(int n) {
        int[] array = new int[n];

        for (int i = 0; i < n; i++) {
            array[i] = (i * 2) + 1;
        }
        return array;
    }

    public static boolean testPrime(int num) {

        for(int i = 3; i < Math.sqrt(num); i += 2){
            if(num % i == 0)
                return true;
        }

        return false;
    }
}
