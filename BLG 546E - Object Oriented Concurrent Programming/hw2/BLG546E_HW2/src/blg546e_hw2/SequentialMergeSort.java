package blg546e_hw2;

public class SequentialMergeSort extends MergeSort {

    public SequentialMergeSort(int[] input) {
        super(input);
    }

    public long execute() {
        long startTime = System.nanoTime();

        sort(array, 0, array.length - 1);

        long endTime = System.nanoTime();

        if (isSorted(array) == false) {
            System.out.println("Array is not sorted!!!");
            printArray(array);
        }

        return (endTime - startTime) / 1000000;
    }

    /* Recursive merge sort call */
    protected void sort(int arr[], int leftIndex, int rightIndex) {
        if (leftIndex < rightIndex) {
            /* Find the middleIndex point */
            int middleIndex = (leftIndex + rightIndex) / 2;

            /* Sort first and second halves */
            sort(arr, leftIndex, middleIndex);
            sort(arr, middleIndex + 1, rightIndex);

            /* MergeSort the sorted halves */
            merge(arr, leftIndex, middleIndex, rightIndex);
        }
    }
}
