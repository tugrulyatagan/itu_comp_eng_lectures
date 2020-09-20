/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.D;

/**
 *
 * @author ovatman
 */
public class Incrementer implements Runnable{

    private Counter cntr;

    public Incrementer(Counter cntr) {
        this.cntr = cntr;
    }
    
    @Override
    public void run() {
        cntr.increment();
    }
    
}
