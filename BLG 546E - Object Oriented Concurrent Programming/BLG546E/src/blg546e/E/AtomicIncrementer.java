/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.E;

import blg546e.D.*;

/**
 *
 * @author ovatman
 */
public class AtomicIncrementer implements Runnable{

    private AtomicCounter cntr;

    public AtomicIncrementer(AtomicCounter cntr) {
        this.cntr = cntr;
    }
    
    @Override
    public void run() {
        cntr.increment();
    }
    
}
