
/***************************
Course : Bil105e
Term : 2010 Spring
Homework : #2
Student Name :  
Student Number : 
***************************/

#include <stdio.h>
#include <math.h>

int main()  {
    
    float x[100];         //Center x coordinates of circles
    float y[100];        //Center y coordinates of circles
    float r[100];        //Radius of circles
    int countcon,countint,i,j,maxi=0,maxc=0,n;
    int intsect[100]={0};
    int c[100]={0};
    float k;
 
       printf("Please enter how many circles you want to compare? \n");     
       scanf("%d",&n);

          for(i=1;i<=n;i++){
                            printf("Please enter x,y,r values respectively: \n" );   
                            //User must enter the x and y coordinates of the center of the circle, followed by its radius r      
                            scanf("%f%f%f",&x[i],&y[i],&r[i]);                
                                                                }
  
          for(i=1;i<=n;i++){ 
                     for(j=1;j<=n;j++) {
                               if((x[i]!=x[j])||(y[i]!=y[j])||(r[i]!=r[j]))   {   // Same circles won't be compared                         
                                                                           k=sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
                                                                               if(k<=fabs(r[i]-r[j]))           
                                                                               //looking for containment
                                                                                   c[i]++;
                                                                               else if(k<=r[i]+r[j])            
                                                                               //looking for intersection 
                                                                                   intsect[i]++;                  }
                           
                                      }                           
                          }
                      
            for(i=1;i<=n;i++){
                          if(intsect[i]>maxi) {
                                        maxi=intsect[i];     
                                        //maxi is used for count of intersection
                                        countint=i;        
                                        //countint is my local variable for holding i value for which circle is the intersection is the biggest
                                                          }
                          if(c[i]>maxc){
                                       maxc=c[i];        
                                       //maxc is used for count of containment
                                       countcon=i;      
                                       //countcon is my local variable for holding i value for which circle is the containment is biggest
                                                    }
                             }

        printf("Circle with most intersections is (x y r):(%.2f %.2f %.2f) circle #%d\n ", x[countint],y[countint],r[countint],countint);
        printf(" Count of Intersections %d\n", maxi);    
        
        printf("Circle with most containments is (x y r):(%.2f %.2f %.2f) circle #%d \n", x[countcon],y[countcon],r[countcon],countcon);
        printf(" Count of Containments %d \n ",maxc);
        
       return 0;

}

