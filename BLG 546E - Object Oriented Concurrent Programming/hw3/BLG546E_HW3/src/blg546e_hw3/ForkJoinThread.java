package blg546e_hw3;

import java.util.ArrayList;
import java.util.Collection;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Callable;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.Future;
import java.util.concurrent.atomic.AtomicInteger;

public class ForkJoinThread {
    private int[] inputArray;
    private int inputParallelism;
    private AtomicInteger currentArrayIndex;

    ForkJoinThread(int[] orderedOddArray, int parallelism) {
        inputArray = orderedOddArray;
        inputParallelism = parallelism;

        currentArrayIndex = new AtomicInteger(0);
    }

    private Callable worker = () -> {
        int myIndex = currentArrayIndex.getAndIncrement();

        boolean result = BLG546E_HW3.testPrime(inputArray[myIndex]);

//        System.out.printf("myIndex=%d, myCell=%d, result=%b\n", myIndex, inputArray[myIndex], result);

        return result;
    };

    public long execute() {
        long startTime = System.nanoTime();
        /* START */

        /* Measure pool creation time too */
        ForkJoinPool pool = new ForkJoinPool(inputParallelism);
        Collection<Callable<Boolean>> tasks = new LinkedList<Callable<Boolean>>();

        /* Create task list */
        for (int i = 0; i < inputArray.length; i++) {
            tasks.add(worker);
        }

        /* Execute task */
        List<Future<Boolean>> futures = pool.invokeAll(tasks);
        Collection<Boolean> results = new ArrayList<>(futures.size());

        /* END */
        long endTime = System.nanoTime();
        return (endTime - startTime) / 1000000;
    }
}
