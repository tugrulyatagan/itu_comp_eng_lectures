/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.N;

import java.lang.reflect.Method;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/**
 *
 * @author ovatman
 */
public class Monitor {
    Integer val;
    public ReentrantLock l;
    public ReentrantLock m;
    AtomicInteger count;
    public Condition setters,getters;
    
    public Monitor() {
        
        val=-1;
        l = new ReentrantLock();
        m = new ReentrantLock();
        setters = m.newCondition();
        getters = l.newCondition();
        count=new AtomicInteger(0);
    }

    public Integer getVal() throws InterruptedException {
        try{
            
            l.lock();
            getters.await();
            
            System.out.println("Getting value");
            Thread.sleep((int)(Math.random()*1000));

            return val;
        }
        finally{
            try{
                m.lock();
                setters.signal();
            }
            finally{
                m.unlock();            
                l.unlock();
            }
        }
    }

    public void setVal(Integer val) throws InterruptedException {
        try{
            m.lock();
            if(this.val>=0){
                setters.await();
            }
            System.out.println("Setting value to "+val);
            Thread.sleep((int)(Math.random()*3000));
            this.val = val;
            System.out.println("Value set to "+val);
        }
        finally{
            l.lock();
            getters.signal();
            l.unlock();
            m.unlock();
        }
    }
    
    
    
}
