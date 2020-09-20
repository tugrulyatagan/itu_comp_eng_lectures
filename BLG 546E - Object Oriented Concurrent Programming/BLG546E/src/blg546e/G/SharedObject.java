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
public class SharedObject {
    
    public static int value;
    
    
    public synchronized void increment(){
            SharedObject.value++;
    }
}
