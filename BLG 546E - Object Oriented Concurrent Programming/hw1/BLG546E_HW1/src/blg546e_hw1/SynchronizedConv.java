/**
 * @author Tugrul Yatagan 504161551
 */

package blg546e_hw1;


public class SynchronizedConv extends Conv {
    private int filter_order_counter; /* shared variable among threads */

    private int num_of_current_filter;


    public SynchronizedConv(int[][] input_matrix, int[][] input_kernel) {
        super(input_matrix, input_kernel);
    }

    public synchronized int inc_and_get_filter_order() {
        filter_order_counter++;
        return filter_order_counter;
    }

    public long[] Execute(int[] thread_count) {
        long[] execution_durations = new long[thread_count.length];

        /* Run for different filter/thread numbers */
        for (int i = 0; i < thread_count.length; i++) {
            /* Clear output matrix */
            for (int z = 0; z < output.length; z++)
                for (int k = 0; k < output.length; k++)
                    output[z][k] = 0;

            filter_order_counter = 0;
            num_of_current_filter = thread_count[i];

            /* Do parallel convolution and measure duration */
            long startTime = System.nanoTime();

            convolution();

            long endTime = System.nanoTime();
            execution_durations[i] = (endTime - startTime) / 1000000;
            System.out.println();
        }
        return execution_durations;
    }

    Runnable worker = () -> {
        int my_filter_order = inc_and_get_filter_order();
        //System.out.println("Filter order: " + my_filter_order + "/" + num_of_current_filter);

        /*  Calculate which rows this thread will use to do convolution */
        int start_row = (int) (Math.floor((my_filter_order - 1) * ((double) input_row / num_of_current_filter)));
        int end_row = (int) (Math.ceil(my_filter_order * ((double) input_row / num_of_current_filter)));

        //System.out.printf("thread=%d/%d  start=%d  end=%d\n", my_filter_order, num_of_current_filter, start_row, end_row);

        for (int i = start_row; i < end_row; i++) {
            for (int j = 0; j < input_col; j++) {
                pixel_convolution(i, j);
            }
        }
    };


    private void convolution() {
        Thread[] threads = new Thread[num_of_current_filter];

        try {
            for (int i = 0; i < num_of_current_filter; i++) {
                threads[i] = new Thread(worker);
                threads[i].start();
            }

            /* Wait for all threads to end */
            for (int i = 0; i < num_of_current_filter; i++) {
                threads[i].join();
            }
        } catch (InterruptedException ex) {
            System.out.println("Error!");
        }
    }
}
