/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e;

import blg546e.C.ActiveObject;
import blg546e.D.Counter;
import blg546e.D.Incrementer;
import blg546e.A.C;
import blg546e.A.D;
import blg546e.A.B;
import blg546e.A.A;
import blg546e.E.AtomicCounter;
import blg546e.E.AtomicIncrementer;
import blg546e.F.ReadWriteClass;
import blg546e.F.Reader;
import blg546e.F.Writer;
import blg546e.G.SharedObject;
import blg546e.G.SynchIncrementer;
import blg546e.H.Changer;
import blg546e.H.Listener;
import blg546e.N.Monitor;
import blg546e.O.CollectionExamples;
import blg546e.P.Student;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.concurrent.BrokenBarrierException;
import java.util.concurrent.Callable;
import java.util.concurrent.CompletionService;
import java.util.concurrent.CountDownLatch;
import java.util.concurrent.CyclicBarrier;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorCompletionService;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.ForkJoinTask;
import java.util.concurrent.Future;
import java.util.concurrent.RecursiveAction;
import java.util.concurrent.RecursiveTask;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ovatman
 */
public class  Ornekler {

    public static volatile int VALUE = 0;

    public void A_Polymorphism() {
        A[] dizi = new A[2];

        dizi[0] = new B();
        dizi[1] = new C();

        for (A a : dizi) {
            a.method();
        }

        B nesne = new D();

        nesne.method();
    }

    public void B_Thread_creation() throws InterruptedException {
        System.out.println(Thread.currentThread().getName() + "-" + Thread.currentThread().getId());

        ActiveObject o = new ActiveObject();

        Thread t1 = new Thread(new ActiveObject());

        t1.start();

        t1.join();

        System.out.println(Thread.currentThread().getName() + "-" + Thread.currentThread().getId());

    }

    public void C_Active_object() throws InterruptedException {
        ActiveObject o = new ActiveObject();

        o.func1();
        o.func2();
        o.func3();
        o.func4();
    }

    public void D_Race_condition() throws InterruptedException {
        int numofthreads = 10000;

        Counter sharedCounter = new Counter(0);

        Thread[] threads = new Thread[numofthreads];

        long start = System.currentTimeMillis();
        for (int i = 0; i < numofthreads; i++) {
            threads[i] = new Thread(new Incrementer(sharedCounter));
            threads[i].start();
        }

        for (int i = 0; i < numofthreads; i++) {
            threads[i].join();
        }

        long end = System.currentTimeMillis();

        System.out.println(sharedCounter.getCount());
        System.out.println("Duration:" + (end - start));
    }

    public void E_AtomicCounter() throws InterruptedException {
        int numofthreads = 10000;

        AtomicCounter sharedCounter = new AtomicCounter(0);

        Thread[] threads = new Thread[numofthreads];

        long start = System.currentTimeMillis();
        for (int i = 0; i < numofthreads; i++) {
            threads[i] = new Thread(new AtomicIncrementer(sharedCounter));
            threads[i].start();
        }

        for (int i = 0; i < numofthreads; i++) {
            threads[i].join();
        }

        long end = System.currentTimeMillis();

        System.out.println(sharedCounter.getCount());
        System.out.println("Duration:" + (end - start));
    }

    public void F_Locks() throws InterruptedException {
        ReadWriteClass rwo = new ReadWriteClass();

        Reader[] readers = new Reader[10];
        Writer[] writers = new Writer[10];
        Thread[] threads = new Thread[readers.length + writers.length];

        int i = 0;

        for (Reader r : readers) {
            r = new Reader(rwo);
            threads[i++] = new Thread(r);
        }

        for (Writer w : writers) {
            w = new Writer(rwo);
            threads[i++] = new Thread(w);
        }

        for (Thread t : threads) {
            t.start();
        }

        for (Thread t : threads) {
            t.join();
        }

    }

    public void G_Synchronized() throws InterruptedException {

        SharedObject s1 = new SharedObject();
        SharedObject s2 = new SharedObject();

        Thread[] t = new Thread[100];

        for (int i = 0; i < t.length; i++) {
            if (i % 2 == 0) {
                t[i] = new Thread(new SynchIncrementer(s1));
            } else {
                t[i] = new Thread(new SynchIncrementer(s2));
            }
            t[i].start();
        }

        for (int i = 0; i < t.length; i++) {
            t[i].join();
        }

        System.out.println(SharedObject.value);
    }

    public void H_Volatility() throws InterruptedException {
        Listener l = new Listener();
        Changer c = new Changer();

        Thread t1 = new Thread(l);
        Thread t2 = new Thread(c);

        t1.start();
        t2.start();

        t2.join();
        t1.join();
    }

    public void I_Semaphores() throws InterruptedException {
        Semaphore s = new Semaphore(1);
        Lock l = new ReentrantLock();

        class Runner implements Runnable {

            Semaphore s;
            Lock l;

            public Runner(Semaphore s) {
                this.s = s;
            }

            public Runner(Lock l) {
                this.l = l;
            }

            @Override
            public void run() {
                try {
                    s.acquire();
                    //l.lockInterruptibly();
                    //l.lock();
                    /*int i=1;
                     while(i>=0){
                     i=(i+1)%1000000000;
                     if(i==999999999)
                     Thread.sleep(1);
                     }*/

                } catch (InterruptedException ex) {
                    System.out.println("Thread " + Thread.currentThread().getName() + " has been interrupted");
                } finally {
                    s.release();
                    //l.unlock();
                }
            }

        };

        Thread t1 = new Thread(new Runner(s));
        t1.start();

        Thread.sleep(100);

        Thread t2 = new Thread(new Runner(s));
        t2.start();

        Thread.sleep(1000);

        System.out.println(t1.getState());
        System.out.println(t2.getState());
        Thread.sleep(2000);
        t1.interrupt();

        while (t1.getState() != Thread.State.TERMINATED);

        System.out.println(t1.getState());
        System.out.println(t2.getState());
        Thread.sleep(2000);
        t2.interrupt();

    }

    static int[][] dizi = {{1, 2, 3, 4, 5}, {4, 5, 6, 7, 8, 9, 10}, {7, 8}};
    static int[] toplam = {0, 0, 0};
    static int sonToplam = 0;

    public void J_CountDownLatch() throws InterruptedException {

        CountDownLatch latch = new CountDownLatch(3);

        class RowSummer implements Runnable {

            CountDownLatch myLatch;
            int myRow;

            public RowSummer(CountDownLatch latch, int rowNo) {
                myLatch = latch;
                myRow = rowNo;
            }

            @Override
            public void run() {
                int sum = 0;
                for (int i = 0; i < dizi[myRow].length; i++) {
                    sum += dizi[myRow][i];
                }

                toplam[myRow] = sum;

                latch.countDown();
                try {
                    latch.await();
                } catch (InterruptedException ex) {
                    Logger.getLogger(Ornekler.class.getName()).log(Level.SEVERE, null, ex);
                }
            }

        };

        class Summer implements Runnable {

            CountDownLatch myLatch;

            public Summer(CountDownLatch latch) {
                myLatch = latch;
            }

            @Override
            public void run() {
                int sum = 0;
                System.out.println("Total Summer");

                try {

                    latch.await();
                } catch (InterruptedException ex) {
                    Logger.getLogger(Ornekler.class.getName()).log(Level.SEVERE, null, ex);
                }

                for (int i = 0; i < toplam.length; i++) {
                    sum += toplam[i];
                }

                sonToplam = sum;
            }
        };

        Thread tSum = new Thread(new Summer(latch));
        tSum.start();

        Thread[] rowSummers = new Thread[dizi.length];

        for (int i = 0; i < rowSummers.length; i++) {
            rowSummers[i] = new Thread(new RowSummer(latch, i));
            rowSummers[i].start();
        }

        tSum.join();
        for (int i = 0; i < rowSummers.length; i++) {
            rowSummers[i].join();
        }

        System.out.println(sonToplam);
    }

    static int[][] binaryArray = {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}};

    void K_CyclicBarrier() throws InterruptedException {

        CyclicBarrier barrier = new CyclicBarrier(4);

        class Incrementer implements Runnable {

            CyclicBarrier myBarrier;
            int myRow;

            public Incrementer(CyclicBarrier barrier, int rowNo) {
                myBarrier = barrier;
                myRow = rowNo;
            }

            @Override
            public void run() {
                try {
                    for (int i = 0; i < binaryArray[myRow].length; i++) {
                        Thread.sleep((int) (Math.random() * 50));
                        binaryArray[myRow][i]++;
                    }
                    barrier.await();
                } catch (Exception ex) {
                    Logger.getLogger(Ornekler.class.getName()).log(Level.SEVERE, null, ex);
                }
            }
        };

        class Printer implements Runnable {

            CyclicBarrier myBarrier;

            public Printer(CyclicBarrier barrier) {
                myBarrier = barrier;
            }

            @Override
            public void run() {
                try {
                    barrier.await();

                    System.out.println("----------------------");
                    for (int i = 0; i < binaryArray.length; i++) {
                        Thread.sleep((int) (Math.random() * 50));
                        System.out.println(Arrays.toString(binaryArray[i]));
                    }
                } catch (Exception ex) {
                    Logger.getLogger(Ornekler.class.getName()).log(Level.SEVERE, null, ex);
                }

            }

        };

        Thread[] incerementers = new Thread[binaryArray.length];

        for (int cnt = 0; cnt < 5; cnt++) {
            for (int i = 0; i < incerementers.length; i++) {
                incerementers[i] = new Thread(new Incrementer(barrier, i));
                incerementers[i].start();
            }
            Thread printer = new Thread(new Printer(barrier));
            printer.start();

            for (int i = 0; i < incerementers.length; i++) {
                incerementers[i].join();
            }
            printer.join();

        }
    }

    static AtomicInteger cnt = new AtomicInteger(0);

    void L_ExecutorServices() throws InterruptedException, ExecutionException {

        Callable<Integer> r = () -> {
            Thread.sleep(1000);
            for (int i = 0; i < 10; i++) {
                cnt.getAndIncrement();
            }
            return cnt.get();
        };
        /*
         ExecutorService e = Executors.newCachedThreadPool();
             
         Future[] sonuclar = new Future[10];
        
         for(int i=0;i<10;i++){
         Future<Integer> f = e.submit(r);
         sonuclar[i] = f;
         }
         for(Future<Integer> f : sonuclar)
         System.out.println(f.get());
        
         e.shutdown();
         */

        ExecutorService e = Executors.newCachedThreadPool();
        CompletionService<Integer> cs = new ExecutorCompletionService<Integer>(e);

        for (int i = 0; i < 10; i++) {
            cs.submit(r);
        }

        while (true) {
            Future<Integer> f = cs.poll();
            if (f == null) {
                break;
            }
            System.out.println(f.get());
        }
        e.shutdown();

    }

    static int NUMBERS_LEN = 400000;
    static int[] numbers = new int[NUMBERS_LEN];

    void swap(int a, int b) {
        int temp = numbers[b];
        numbers[b] = numbers[a];
        numbers[a] = temp;
    }

    int pivotize(int start, int end) {
        int pivot = (start + end) / 2;
        boolean found = false;

        swap(pivot, end - 1);

        for (int i = start; i < end - 1; i++) {
            if (numbers[i] < numbers[end - 1]) {
                continue;
            } else {
                found = false;
                for (int j = i + 1; j < end - 1; j++) {
                    if (numbers[j] < numbers[end - 1]) {
                        swap(i, j);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    pivot = i;
                    break;
                }
            }
        }
        swap(pivot, end - 1);
        return pivot;
    }

    void quicksort(int start, int end) {
        if (start < end) {
            int pivot = pivotize(start, end);
            quicksort(start, pivot);
            quicksort(pivot + 1, end);
        }
    }

    void M_ForkJoinFramework() throws InterruptedException {

        for (int i = 0; i < NUMBERS_LEN; i++) {
            numbers[i] = NUMBERS_LEN - i;
        }

        ForkJoinPool pool = new ForkJoinPool(8);

        class SorterAction extends RecursiveAction {

            private int start, end;

            public SorterAction(int start, int end) {
                this.start = start;
                this.end = end;
            }

            void swap(int a, int b) {
                int temp = numbers[b];
                numbers[b] = numbers[a];
                numbers[a] = temp;
            }

            int pivotize(int start, int end) {
                int pivot = (start + end) / 2;
                boolean found = false;

                swap(pivot, end - 1);

                for (int i = start; i < end - 1; i++) {
                    if (numbers[i] < numbers[end - 1]) {
                        continue;
                    } else {
                        found = false;
                        for (int j = i + 1; j < end - 1; j++) {
                            if (numbers[j] < numbers[end - 1]) {
                                swap(i, j);
                                found = true;
                                break;
                            }
                        }
                        if (!found) {
                            pivot = i;
                            break;
                        }
                    }
                }
                swap(pivot, end - 1);
                return pivot;
            }

            @Override
            protected void compute() {
                if (start < end) {
                    int pivot = pivotize(start, end);
                    SorterAction left = new SorterAction(start, pivot);
                    SorterAction right = new SorterAction(pivot+1, end);
                    ForkJoinTask.invokeAll(left, right);
                }
            }

        };
        
         long start = System.currentTimeMillis();
         pool.invoke(new SorterAction(0,NUMBERS_LEN));
         long end = System.currentTimeMillis();
        
         System.out.println("Time spent=" + (end - start));
       
/*
        long start = System.currentTimeMillis();
        quicksort(0, NUMBERS_LEN);
        long end = System.currentTimeMillis();

        System.out.println("Time spent=" + (end - start));
*/
    }

    static Monitor m = new Monitor();
    
    void N_Monitors() throws InterruptedException {
        Runnable r = () -> {
            try{
                if(Math.random()>0.5)
                    m.setVal((int)(Math.random()*100));
                else
                    System.out.println(m.getVal()+"  ");
            }
            catch(Exception e){
                e.printStackTrace();
            }
        };    
        
        Thread[] t = new Thread[1000];
        for(int i=0;i<t.length;i++){
            t[i]=new Thread(r);
            t[i].start();
        }
        for(int i=0;i<t.length;i++){
            t[i].join();
        }

    }

    void O_Collections() throws InterruptedException {
        CollectionExamples ce = new CollectionExamples();
        
        //ce.lists();
        ce.queues();
    }

    void P_Hashing() {
        /*
        HashSet<Integer> aSet = new HashSet<Integer>();
        
        
        for(int i=0;i<100;i++)
            aSet.add(i%10);
        
        System.out.println(aSet);
                */
        
        /*
        HashSet<Student> aSet = new HashSet<Student>();
       
        aSet.add(new Student("EmreYılmaz",564562));
        aSet.add(new Student("Emre Yılmaz",564562));
        aSet.add(new Student("Duygu Ozkan",563323));
        aSet.add(new Student("Hulya Isler",324523));
        
        System.out.println(aSet);
                */
        
        HashMap<Student,String> aMap = new HashMap<Student,String>();
        
        aMap.put(new Student("Emre Yılmaz",564562),"Emre Yılmaz");
        aMap.put(new Student("Emre Yılmaz",564562),"Emre Yılmaz 2");
        aMap.put(new Student("Duygu Ozkan",563323),"Duygu Ozkan");
        aMap.put(new Student("Hulya Isler",324523),"Hulya Isler");
        
        System.out.println(aMap);
    }
    
    

    
    
}
