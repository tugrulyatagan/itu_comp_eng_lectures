/***************************
Course         : Bil105e
Term           : 2010 Spring
Homework       : #4
Student Name   : Abdullah Aydeðer
Student Number : 040090533
***************************/
#include <stdio.h>
#include <stdlib.h>
#define boyut 1000           
        struct {
       int red,green,blue;  
}res[boyut][boyut];

int main()  {
                int i,j,column,row,maxcolor;        
                char format[3];                  char filename[20];
                FILE *ptr;
                FILE *rotateptr;
                FILE *mirrorptr;
                FILE *negativeptr;
                FILE *greyptr;
                FILE *smallptr;
                FILE *bigptr;
                
                printf("Enter name of input image file :");
                scanf("%s",filename);
                
                 if((ptr=fopen(filename,"r"))==NULL)
                              printf("File could not be opened\n");
                 else{
                                                      fscanf(ptr,"%s",format);
                                                      fscanf(ptr,"%d%d",&column,&row);
                                                      fscanf(ptr,"%d",&maxcolor);               
                                                              for(j=0;j<row;j++)  {
                                                                                   for(i=0;i<column;i++)
                                                                                        fscanf(ptr,"%d%d%d",&res[j][i].red,&res[j][i].green,&res[j][i].blue);
                                                                                  }                         
                     }                                                                                                                                                          
                 
                 /* Mirror.ppm*/
               if((mirrorptr=fopen("mirror.ppm","w"))==NULL)
                          printf("File could not be opened\n");
               else {
                    fprintf(mirrorptr,"%s\n",format);
                    fprintf(mirrorptr,"%d %d\n%d\n",column,row,maxcolor);
                    
                           for(j=0;j<row;j++) {
                                                for(i=column-1;i>=0;i--) 
                                                     fprintf(mirrorptr,"%d %d %d ",res[j][i].red,res[j][i].green,res[j][i].blue);  
                           fprintf(mirrorptr,"\n");              
                                               }
                  }
                                                                                                                                                                        
                  /*Rotate.ppm*/
               if((rotateptr=fopen("rotate.ppm","w"))==NULL)
                                 printf("File could not be opened\n");
               else {
                    fprintf(rotateptr,"%s\n",format);
                    fprintf(rotateptr,"%d %d\n%d\n",row,column,maxcolor);
                       
                           for(j=column-1;j>=0;j--) {
                                                     for(i=0;i<row;i++)
                                                        fprintf(rotateptr,"%d %d %d ",res[i][j].red,res[i][j].green,res[i][j].blue);                          
                            fprintf(rotateptr,"\n"); 
                                                     }
                    }
                       
                 /*Negative.ppm*/                                                     
               if((negativeptr=fopen("negative.ppm","w"))==NULL)
                                   printf("File could not be opened\n");
               else {
                    fprintf(negativeptr,"%s\n",format);
                    fprintf(negativeptr,"%d %d\n%d\n",column,row,maxcolor);
                    
                          for(j=0;j<row;j++){
                                             for(i=0;i<column;i++)
                                                 fprintf(negativeptr,"%d %d %d ",255-res[j][i].red,255-res[j][i].green,255-res[j][i].blue);    
                                       fprintf(negativeptr,"\n");
                                             }
                    }
                 
                 /*Grey.ppm*/
               if((greyptr=fopen("grey.ppm","w"))==NULL)                 
                                printf("File could not be opened\n");
               else {
                    fprintf(greyptr,"%s\n",format);
                    fprintf(greyptr,"%d %d\n%d\n",column,row,maxcolor);
                          for(j=0;j<row;j++){
                                            for(i=0;i<column;i++)
                                                 fprintf(greyptr,"%d %d %d ",
                                                        (res[j][i].red+res[j][i].green+res[j][i].blue)/3,(res[j][i].red+res[j][i].green+res[j][i].blue)/3,(res[j][i].red+res[j][i].green+res[j][i].blue)/3);    
                                       fprintf(greyptr,"\n");
                                            }
                    }       
                 
                 /*Small.ppm*/
               if((smallptr=fopen("small.ppm","w"))==NULL)
                                printf("File could not be opened\n");       
               else {
                    fprintf(smallptr,"%s\n",format);
                    fprintf(smallptr,"%d %d\n%d\n",column/2,row/2,maxcolor);
                          for(j=0;j<row;j=j+2){
                                               for(i=0;i<column;i=i+2)
                                                  fprintf(smallptr,"%d %d %d ",res[j][i].red,res[j][i].green,res[j][i].blue);    
                                       fprintf(smallptr,"\n");
                                              }
                    }              
                 
                 /*Big.ppm*/
               if((bigptr=fopen("big.ppm","w"))==NULL)
                                    printf("File could not be opened\n");
               else {
                    fprintf(bigptr,"%s\n",format);
                    fprintf(bigptr,"%d %d\n%d\n",column*2,row*2,maxcolor);
                          for(j=0;j<row;j++){
                                             for(i=0;i<column;i++){
                                                 fprintf(bigptr,"%d %d %d ",res[j][i].red,res[j][i].green,res[j][i].blue);
                                                 fprintf(bigptr,"%d %d %d ",res[j][i].red,res[j][i].green,res[j][i].blue); 
                                                                    }
                            fprintf(bigptr,"\n");
                                             for(i=0;i<column;i++){
                                                 fprintf(bigptr,"%d %d %d ",res[j][i].red,res[j][i].green,res[j][i].blue);
                                                 fprintf(bigptr,"%d %d %d ",res[j][i].red,res[j][i].green,res[j][i].blue); 
                                                                    }                                                                   
                          fprintf(bigptr,"\n");
                                            }
                    }
                            
                                                                                                                                                                                                                                                         
                                                                                                                                                                                                                                                                                                           
                                       
              printf("6 output image files have been generated.\n"
                        "PROGRAM ENDED.\n\n");                                                   
        system("pause");
        return 0;
}
