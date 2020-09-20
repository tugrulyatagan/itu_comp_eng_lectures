package blg546e_hw2;

public abstract class MergeSort {
    protected int array[];

    protected MergeSort(int[] input) {
        /* Make a copy of input array */
        array = new int[input.length];
        System.arraycopy(input, 0, array,0, input.length);
    }

    protected void merge(int arr[], int leftIndex, int middleIndex, int rightIndex) {
        /* Find sizes of two subarrays to be merged */
        int size1 = middleIndex - leftIndex + 1;
        int size2 = rightIndex - middleIndex;

        /* Creating temp arrays every time function call is not a good idea */
        int leftTemp[] = new int[size1];
        int rightTemp[] = new int[size2];

        /* Copy data to temp arrays*/
        for (int i = 0; i < size1; ++i)
            leftTemp[i] = arr[leftIndex + i];
        for (int j = 0; j < size2; ++j)
            rightTemp[j] = arr[middleIndex + 1 + j];

        /* Initial indexes of first and second subarrays */
        int i = 0, j = 0;

        /* Initial index of merged subarray */
        int k = leftIndex;
        while (i < size1 && j < size2) {
            if (leftTemp[i] <= rightTemp[j]) {
                arr[k] = leftTemp[i];
                i++;
            } else {
                arr[k] = rightTemp[j];
                j++;
            }
            k++;
        }

        /* Copy remaining elements of leftTemp[] if any */
        while (i < size1) {
            arr[k] = leftTemp[i];
            i++;
            k++;
        }

        /* Copy remaining elements of rightTemp[] if any */
        while (j < size2) {
            arr[k] = rightTemp[j];
            j++;
            k++;
        }
    }

    /* used for sub sorting sub arrays */
    protected  void qsort(int arr[], int low, int high) {
        int i = low, j = high;
        // Get the pivot element from the middle of the list
        int pivot = arr[low + (high-low)/2];

        // Divide into two lists
        while (i <= j) {
            while (arr[i] < pivot) {
                i++;
            }

            while (arr[j] > pivot) {
                j--;
            }

            if (i <= j) {
                // swap
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;

                i++;
                j--;
            }
        }

        // Recursion
        if (low < j)
            qsort(arr, low, j);
        if (i < high)
            qsort(arr, i, high);
    }

    public static void printArray(int arr[]) {
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    }

    public static boolean isSorted(int arr[]) {
        for (int i = 0; i < arr.length-1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
        return true;
    }
}
