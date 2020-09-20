/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.G;

/**
 *
 * @author ovatman
 */
public class SynchIncrementer implements Runnable{

    private SharedObject s;

    public SynchIncrementer(SharedObject s) {
        this.s = s;
    }
    
    
    
    @Override
    public void run() {
        for(int i = 0 ; i<1000 ;i++)
            s.increment();
    }
    
    
}
