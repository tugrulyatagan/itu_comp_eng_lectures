package blg546e_hw2;

import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.atomic.AtomicInteger;

public class ParallelMergeSort  extends MergeSort {

    private int numOfCurrentThread;
    private int currentArray[];

    /* Shared atomic variables among threads */
    private AtomicInteger threadOrder;
    private CyclicBarrier barrier;

    public ParallelMergeSort(int[] input) {
        super(input);
        currentArray = new int[input.length];
        numOfCurrentThread = 0;
        threadOrder = new AtomicInteger();
    }

    public long[] execute(int[] threadNumbers) {
        long[] executionDurations = new long[threadNumbers.length];

        /* Run for different thread numbers */
        for (int i = 0; i < threadNumbers.length; i++) {

            /* Restore original array */
            System.arraycopy(array, 0, currentArray,0, array.length);

            threadOrder.set(0);
            numOfCurrentThread = threadNumbers[i];

            /* Do parallel merge sort and measure duration */
            long startTime = System.nanoTime();

            parallelSort();

            long endTime = System.nanoTime();
            executionDurations[i] = (endTime - startTime) / 1000000;

//            printArray(currentArray);

            if (isSorted(currentArray) == false) {
                System.out.println("Array is not sorted!!!");
                printArray(currentArray);
            }
        }
        return executionDurations;
    }

    private void parallelSort() {
        /* Create barrier */
        barrier = new CyclicBarrier(numOfCurrentThread);

        /* Create threads */
        Thread[] threads = new Thread[numOfCurrentThread];

        try {
            for (int i = 0; i < numOfCurrentThread; i++) {
                threads[i] = new Thread(worker);
                threads[i].start();
            }

            /* Wait for all threads to end */
            for (int i = 0; i < numOfCurrentThread; i++) {
                threads[i].join();
            }
        } catch (InterruptedException ex) {
            System.out.println("Error! " + ex.getMessage());
        }
    }

    Runnable worker = () -> {
        try {
            int myThreadOrder = threadOrder.getAndIncrement();
            int currentSectionSize = currentArray.length / numOfCurrentThread;

            int myLeftIndex = myThreadOrder * currentSectionSize;
            int myRightIndex = myLeftIndex + currentSectionSize;

//            System.out.println("My thread order: " + myThreadOrder + "/" + numOfCurrentThread);

            /* Each thread sort its sub array */
            qsort(currentArray, myLeftIndex, myRightIndex-1);

            /* Wait other threads */
            barrier.await();

            for(int t = numOfCurrentThread / 2; t > 0; t /= 2){
                if(myThreadOrder < t){
                    int subLeftIndex = 2 * myThreadOrder * currentSectionSize;
                    int subMiddleIndex = subLeftIndex + currentSectionSize;
                    int subRightIndex = subMiddleIndex + currentSectionSize;
                    merge(currentArray, subLeftIndex, subMiddleIndex-1, subRightIndex-1);
                }
                currentSectionSize *= 2;
                barrier.await();
            }

        } catch (InterruptedException | BrokenBarrierException ex) {
            /* What happens if one thread throws exception before barrier await */
            System.out.println("Error! " + ex.getMessage());
        }
    };
}