#include<stdio.h>
main()
{
      int satir,i,j,l,k,t,p;
      printf("yazdirmak istediginiz papyonun satir sayisini tek sayi olarak giriniz\n\a\a\a\a");
      scanf("%d",&satir);
      for(i=1;i<=satir/2+1;i++){
                        for(t=1;t<=i ;t++){
                                     printf("*");
                                    
                                    }
                        for(l=1;l<=(satir-2*i+1);l++){  printf(" ");}
                        
                        for(t=1;t<=i ;t++){
                                     printf("*");
                                    }
                        printf("\n");
                        }
                        
                        
                        
                        for(i=1;i<=satir/2;i++){
                                          for(t=satir/2;t>=i ;t--){
                                                              printf("*");}
                                    
                                    
                                    
                                    for(l=(2*i);l>=1;l--){  printf(" ");}
                        
                        
                         for(t=satir-1;t>=i+satir/2 ;t--){
                                                              printf("*");
                                    
                                    }printf("\n");
                                    }
                                    
while(3);      
}
