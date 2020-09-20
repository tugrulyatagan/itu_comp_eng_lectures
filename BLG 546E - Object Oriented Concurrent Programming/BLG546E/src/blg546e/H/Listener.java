/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e.H;

import blg546e.BLG546E;
import blg546e.Ornekler;

/**
 *
 * @author ovatman
 */
public class Listener implements Runnable{

    @Override
    public void run() {
        
        int localValue = Ornekler.VALUE;
        
        while(localValue < 5){
            if(localValue != Ornekler.VALUE){
                localValue = Ornekler.VALUE;
                System.out.println("Global değişken değişti!!!");
            }
        }
    }
    
}
