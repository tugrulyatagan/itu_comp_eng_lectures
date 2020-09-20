#include <hidef.h>      /* common defines and macros */
#include <mc9s12c32.h>     /* derivative information */
#pragma LINK_INFO DERIVATIVE "mc9s12c32"

byte varX;

void delayS(){
 word i,j;
 for(i=0; i<0x0010; i++)
  for(j=0; j<0xFFFF; j++){}

}

void main(void) {
  DDRA=0x01;   //PORTA.0 connected to LED1 is output  
  DDRB=0x10;   //PORTB.4 connected to LED2 is output  
  
  PORTA=0x00;  //LED1 is on
  PORTB=0x00;  //LED2 is on
  
  varX=0x11;
  
  for(;;) {
  
    PORTA=varX;
    PORTB=varX;
    varX=~varX;
    delayS(); 
  } 
  
}
