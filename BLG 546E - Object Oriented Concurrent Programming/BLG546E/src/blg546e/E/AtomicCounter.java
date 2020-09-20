/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.E;

import blg546e.D.*;
import java.util.concurrent.atomic.AtomicInteger;

/**
 *
 * @author ovatman
 */
public class AtomicCounter {
    private AtomicInteger count;

    public AtomicCounter(int count) {
        this.count = new AtomicInteger();
        this.count.set(count);
    }
    
    public void increment(){
        for(int i=0;i<100;i++)
            count.incrementAndGet();
    }
    
    
    public void decrement(){
        count.decrementAndGet();
    }

    public int getCount() {
        return count.get();
    }
    
    
}
