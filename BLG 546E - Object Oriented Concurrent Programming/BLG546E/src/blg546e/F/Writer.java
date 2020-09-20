/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.F;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ovatman
 */
public class Writer implements Runnable{

    private ReadWriteClass rwo;

    public Writer(ReadWriteClass rwo) {
        this.rwo = rwo;
    }
    
    
    
    @Override
    public void run() {
        
        try {
            Thread.sleep(ReadWriteClass.rnd.nextInt(1000));
        } catch (InterruptedException ex) {
            Logger.getLogger(Writer.class.getName()).log(Level.SEVERE, null, ex);
        }
       
        rwo.setValue(ReadWriteClass.rnd.nextInt(100));
        
    }
    
}
