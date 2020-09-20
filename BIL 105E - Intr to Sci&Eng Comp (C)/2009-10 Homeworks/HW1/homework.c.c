//Purpose of this program to determine the arrangement status of two lines.

#include <stdio.h>
#include <math.h>
int main()
{
    float  A1,B1,C1,A2,B2,C2,d,f; // A1,B1,A2,B2 are the coefficient of x,y //C1,C2 are constants //d is shortened of distance  
	float angle,slope;
	float x0,y0; // These are intersection points
	
	printf("Please enter coefficients respectively A1,B1,C1:\n");
	scanf("%f%f%f",&A1,&B1,&C1);
        printf("Your first line is %.1fx+(%.1fy)+(%.1f)=0 \n",A1,B1,C1);    //This is first line

	printf("Please enter second line's coefficients A2,B2,C2:\n");
	scanf("%f%f%f",&A2,&B2,&C2);
        printf("Your second line is %.1fx+(%.1fy)+(%.1f)=0 \n",A2,B2,C2);     //This is second line
	
	if((A1/A2)==(B1/B2)&&(A1/A2)==(C1/C2))	 
	  printf("The two lines 'coincide'. (They lie on the same straight line)\n");
	
         else
          if((A1/A2)==(B1/B2)) { 
	   printf("The two lines are 'parallel'.\n");	
           f=sqrt(A1*A1+B1*B1);      //this formula is not always valid (if we use A2*A2+B2*B2 then we will get different result)
           d=(fabs(C1-C2))/f;  
 	   printf("Distance between two lines is %.2f \n",d);
	
 	}
	 
        
        else
          if((A1*A2+B1*B2)==0)   
{          printf("The two lines are 'perpendicular' with 90 degrees.\n");
           x0=(B1*C2-B2*C1)/(A1*B2-A2*B1);
           y0=(C1*A2-C2*A1)/(A1*B2-A2*B1);
           printf("Intersection point coordinates : (%.2f,%.2f)\n" ,x0,y0);   
}

        else   {
           printf("The two lines 'intersect' with an angle\n"); 
           slope=(A1*B2-A2*B1)/(A1*A2+B1*B2);   //With this slope we will determine angle
           angle=(atan(slope)*180)/3.1416;      //We use arctan function
           printf("Angle is %.2f\n",angle);  
           x0=(B1*C2-B2*C1)/(A1*B2-A2*B1);
           y0=(C1*A2-C2*A1)/(A1*B2-A2*B1);
           printf("Intersection point coordinates : (%.2f,%.2f)\n ",x0,y0);
  
	}
	         	
	return 0;
}
