/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.C;

import java.util.Random;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ovatman
 */
public class ActiveObject implements Runnable{

    public void func1() throws InterruptedException{
        
        Runnable r = () -> {
  
            try {
                Thread.sleep(1500+((int)Math.random()*1000));
                System.out.println("This is func 1");
            } catch (InterruptedException ex) {
                Logger.getLogger(ActiveObject.class.getName()).log(Level.SEVERE, null, ex);
            }
        };
        
        Thread t = new Thread(r);
        t.start();
    }

    public void func2() throws InterruptedException{
        
        Runnable r = () -> {
            try {
                Thread.sleep(1500+((int)Math.random()*1000));
                System.out.println("This is func 2");
            } catch (InterruptedException ex) {
                Logger.getLogger(ActiveObject.class.getName()).log(Level.SEVERE, null, ex);
            }
        };
        
        Thread t = new Thread(r);
        t.start();
    }

    public void func3() throws InterruptedException{
        
        Runnable r = () -> {
        try {
                Thread.sleep(1500+((int)Math.random()*1000));
                System.out.println("This is func 3");
            } catch (InterruptedException ex) {
                Logger.getLogger(ActiveObject.class.getName()).log(Level.SEVERE, null, ex);
            }
        };
        
        Thread t = new Thread(r);
        t.start();
    }

    public void func4() throws InterruptedException{
        
        Runnable r = () -> {
            try {
                Thread.sleep(1500+((int)Math.random()*1000));
                System.out.println("This is func 4");
            } catch (InterruptedException ex) {
                Logger.getLogger(ActiveObject.class.getName()).log(Level.SEVERE, null, ex);
            }
        };
        
        Thread t = new Thread(r);
        t.start();
        
    }
    
    
    @Override
    public void run() {
        
        try {
            Thread.sleep(5000);
        } catch (InterruptedException ex) {
            Logger.getLogger(ActiveObject.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        System.out.println(Thread.currentThread().getName()+ "-" + Thread.currentThread().getId());
    
    }
    
}
