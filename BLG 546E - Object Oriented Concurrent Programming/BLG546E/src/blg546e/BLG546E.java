/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package blg546e;

import blg546e.C.ActiveObject;
import blg546e.H.Changer;
import blg546e.H.Listener;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author ovatman
 */
public class BLG546E {

    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws InterruptedException, ExecutionException {
        Ornekler o = new Ornekler();
        
        //o.A_Polymorphism();
        
        //o.B_Thread_creation();
        
        //o.C_Active_object();
        
        //o.D_Race_condition();
        
        //o.E_AtomicCounter();

        //o.F_Locks();
        
        //o.G_Synchronized();
        
        //o.H_Volatility();
        
        //o.I_Semaphores();
 
        //o.J_CountDownLatch();
        
//        o.K_CyclicBarrier();
        
//        o.L_ExecutorServices();
        
        o.M_ForkJoinFramework();

        //o.N_Monitors();

        //o.O_Collections();
        
        //o.P_Hashing();
    }
    
}
