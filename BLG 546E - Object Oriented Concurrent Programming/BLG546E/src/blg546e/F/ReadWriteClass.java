/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.F;

import java.util.Random;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock.ReadLock;
import java.util.concurrent.locks.ReentrantReadWriteLock.WriteLock;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ovatman
 */
public class ReadWriteClass {
    
    private Integer value;
    public static Random rnd;
    public static ReentrantReadWriteLock lock;
    
    public ReadWriteClass() {
        rnd = new Random();
        lock = new ReentrantReadWriteLock();
        value=0;
    }
    
    public int getValue() {
        ReadLock rLock = lock.readLock();
        rLock.lock();
        
        System.out.println(Thread.currentThread().getId()+"-Started Reading");
        
        try {
            Thread.sleep(ReadWriteClass.rnd.nextInt(1000));
        } catch (InterruptedException ex) {
            Logger.getLogger(Writer.class.getName()).log(Level.SEVERE, null, ex);
        }
        
                
        int ret = value;
        
        System.out.println(Thread.currentThread().getId()+"-Finished Reading");
        
        rLock.unlock();
        
        return ret;
    }

    public void setValue(int value) {
        WriteLock wLock = lock.writeLock();
        wLock.lock();
        System.out.println(Thread.currentThread().getId()+"-Started Writing");
        
        this.value = value;
        
        System.out.println(Thread.currentThread().getId()+"-Finished Writing");
        
        wLock.unlock();
    }
    
    
}
