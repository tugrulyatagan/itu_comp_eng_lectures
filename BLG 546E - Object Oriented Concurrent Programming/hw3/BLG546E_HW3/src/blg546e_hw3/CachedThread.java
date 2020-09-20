package blg546e_hw3;

import java.util.concurrent.*;
import java.util.concurrent.atomic.AtomicInteger;

public class CachedThread {
    private int[] inputArray;
    private int inputParallelism;
    private AtomicInteger currentArrayIndex;
    private AtomicInteger currentThreadNum;

    CachedThread(int[] orderedOddArray, int parallelism) {
        inputArray = orderedOddArray;
        inputParallelism = parallelism;

        currentArrayIndex = new AtomicInteger(0);
        currentThreadNum = new AtomicInteger(0);
    }

    private Runnable worker = () -> {
        int myIndex = currentArrayIndex.getAndIncrement();

        boolean result = BLG546E_HW3.testPrime(inputArray[myIndex]);

//        System.out.printf("myIndex=%d, myCell=%d, result=%b\n", myIndex, inputArray[myIndex], result);

        currentThreadNum.decrementAndGet();
    };

    public long execute() {
        long startTime = System.nanoTime();
        /* START */

        int submittedCellTaskNum = 0;

        /* Measure pool creation time too */
        ExecutorService e = Executors.newCachedThreadPool();

        /* Loop until all array cell tasks are submitted */
        while (submittedCellTaskNum < inputArray.length) {

            /* Submit task if task number is below than allowed */
            if (currentThreadNum.get() < inputParallelism) {
                currentThreadNum.incrementAndGet(); /* Dont worry if currentThreadNum decremanted again after if check */
                submittedCellTaskNum++;
                e.submit(worker);
            }
        }

        /* Shutdown ExecutorService, terminate idle executors */
        e.shutdown();

        /* Wait for all tasks to terminate */
        while (!e.isTerminated()) {}

        /* END */
        long endTime = System.nanoTime();
        return (endTime - startTime) / 1000000;
    }
}
