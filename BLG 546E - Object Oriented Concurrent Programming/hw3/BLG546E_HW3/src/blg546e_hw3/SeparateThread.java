package blg546e_hw3;

import java.util.concurrent.atomic.AtomicInteger;

public class SeparateThread {
    private int[] inputArray;
    private int inputParallelism;
    private AtomicInteger currentArrayIndex;
    private AtomicInteger currentThreadNum;

    SeparateThread(int[] orderedOddArray, int parallelism) {
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

        int createdCellThreadNum = 0;

        /* Loop until all array cell threads are created */
        while (createdCellThreadNum < inputArray.length) {

            /* Create new thread if thread number is below than allowed */
            if (currentThreadNum.get() < inputParallelism) {
                currentThreadNum.incrementAndGet(); /* Dont worry if currentThreadNum decremanted again after if check */
                createdCellThreadNum++;
                Thread thread = new Thread(worker);
                thread.start();
            }
        }

        /* END */
        long endTime = System.nanoTime();
        return (endTime - startTime) / 1000000;
    }
}
