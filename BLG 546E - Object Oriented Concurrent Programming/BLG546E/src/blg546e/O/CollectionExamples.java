/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.O;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 *
 * @author ovatman
 */
public class CollectionExamples {

   

    public void lists() throws InterruptedException {
        //List seqList = new ArrayList<Integer>();
        //List seqList = new LinkedList<Integer>();
        //List parList = new CopyOnWriteArrayList<Integer>();
        Queue parList = new ConcurrentLinkedQueue<Integer>();
        /*
        Long start = System.currentTimeMillis();
        
        Thread[] t = new Thread[1000];
        for (int i = 0; i < t.length; i++) {
            t[i] = new Thread(new Producer(parList));
            t[i].start();
        }
        
        for (int i = 0; i < t.length; i++) {
            t[i].join();
        }

        Long end = System.currentTimeMillis();
        
        System.out.println(parList.size()+" elements added in "+ (end-start) +" msec.");
        
        start = System.currentTimeMillis();
        for (int i = 0; i < t.length; i++) {
            t[i] = new Thread(new Consumer(parList));
            t[i].start();
        }
        for (int i = 0; i < t.length; i++) {
            t[i].join();
        }
        end = System.currentTimeMillis();
        
        System.out.println(parList.size()+" elements remain in "+ (end-start) +" msec.");
          */      
    }
    
    public void queues() throws InterruptedException {
        
        //Queue parQueue = new ConcurrentLinkedQueue<Integer>();
        BlockingQueue parQueue = new ArrayBlockingQueue<Integer>(10000);
        
        
        Thread[] t = new Thread[100000];
        for (int i = 0; i < 50000; i++) {
            t[i] = new Thread(new Producer(parQueue));
            t[50000+i] = new Thread(new Consumer(parQueue));
            t[i].start();
            t[50000+i].start();
        }
        
        for (int i = 0; i < t.length; i++) {
            t[i].join();
        }

        
        System.out.println(parQueue.size()+" elements remain");
                
    }

    class Producer implements Runnable {

        private BlockingQueue bag;

        public Producer(BlockingQueue bag) {
            this.bag = bag;
        }

        @Override
        public void run() {
            try {
                for (int i = 0; i < 100; i++) {
                    int num = (int) (Math.random() * 1000000000);
                    bag.put(num);
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

    }

    class Consumer implements Runnable {

        private BlockingQueue bag;

        public Consumer(BlockingQueue bag) {
            this.bag = bag;
        }

        @Override
        public void run() {
            try {
                for (int i = 0; i < 100; i++) {
                    //if (!bag.isEmpty()) {
                        int num = (int) bag.take();
                        //System.out.println(num);
                    //}
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }

    }
}
