/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.H;

import blg546e.BLG546E;
import blg546e.Ornekler;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ovatman
 */
public class Changer implements Runnable{

    @Override
    public void run() {
        int localValue = Ornekler.VALUE;
        
        while(Ornekler.VALUE < 5){
            localValue = ++Ornekler.VALUE;
            System.out.println("Globali az önce artırdım");
            
            try {
                Thread.sleep(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(Changer.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
    }
    
}
