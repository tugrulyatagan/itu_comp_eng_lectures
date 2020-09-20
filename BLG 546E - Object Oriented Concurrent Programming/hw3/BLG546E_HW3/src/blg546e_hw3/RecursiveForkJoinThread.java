package blg546e_hw3;

import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinTask;
import java.util.concurrent.RecursiveTask;

public class RecursiveForkJoinThread {
    private int[] inputArray;
    private int inputParallelism;

    RecursiveForkJoinThread(int[] orderedOddArray, int parallelism) {
        inputArray = orderedOddArray;
        inputParallelism = parallelism;
    }

    class FactorInRange extends RecursiveTask<Boolean> {
        int k, n;

        FactorInRange(int k, int n) {
            this.k = k;
            this.n = n;
        }

        @Override
        protected Boolean compute() {
            if (k >= n) {
                return false;
            } else if ((n % k) == 0) {
                return true;
            } else {
                FactorInRange right = new FactorInRange(k + 1, n);
//                return right.compute();
                invokeAll(right);
                return right.join();
            }
        }
    }

    public long execute() {
        long startTime = System.nanoTime();
        /* START */

        /* Measure pool creation time too */
        ForkJoinPool pool = new ForkJoinPool(inputParallelism);

        /* This sequentially runs recursive tasks for every array item so IsPrime calculation is done parallel but
        consecutive item calculations are not */
        for (int i = 0; i < inputArray.length; i++) {
            boolean result = ((i > 1) && !pool.invoke(new FactorInRange(2, i)));
//            System.out.printf("myIndex=%d, myCell=%d, result=%b\n", i, inputArray[i], result);
        }

        /* END */
        long endTime = System.nanoTime();
        return (endTime - startTime) / 1000000;
    }
}
