/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.D;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

/**
 *
 * @author ovatman
 */
public class Counter {
    private Integer count;
    
    public Counter(int count) {
        this.count = count;
    }
    
    public void increment(){
        for(int i=0;i<100;i++){
            count=count+1;
        } 
    }
    
    
    public void decrement(){
        count=count-1;
    }

    public int getCount() {
        return count;
    }
    
    
}
