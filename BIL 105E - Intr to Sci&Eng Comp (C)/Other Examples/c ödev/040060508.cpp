// AMMAR YASÝR KORKUSUZ - 040060508 - CRN : 13780

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int fonk(int number1, int number2){
int k,i;
srand(time(NULL));

for(i=1;i<=100;i++)
{                
printf("%d \t",number1+1+(rand()%(number2-number1)));
//seçilen iki sayý da dahil olmayacak biçimde, aralarýndaki sayýlardan rasgele sayýlar seçiyor

if(i%10==0)          
printf("\n"); //10. terimden sonra alt satýra geçiyor
}
return k;
}

int main() // main fonksiyonuna giriyor
{
    int a, b; // iki integer tanýmlýyor
    
    while(1){
        printf("enter N1:");
        scanf("%d", &a);         //verilen ilk integerý N1 e eþitliyor
        printf("enter N2:");     
        scanf("%d", &b);         //verilen ikinci integerý N2 ye eþitliyor
        
        if (a == 0 || b == 0) // N1 veya N2 "0" a eþitse döngüden çýkýyor
        {
           printf("\nN1 and N2 can't be zero, loop terminated");    
           break;
        }  
        else if(a < 0 || a > b )  // N1 negatifse yada N2 den büyükse yeni deðerler istiyor
        {
           printf("\nN1 can't be negative or bigger than N2 enter new values \n"); 
           continue;
        }
            
        else  // bu koþullarda deðilse random fonksiyonuna giriyor
           fonk(a, b); 
    }
    
    scanf("%d", &a);
    return 0;    
}


