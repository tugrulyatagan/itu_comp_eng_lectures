#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct {

char number[10];
char firstname[15];
char lastname[15];
float midterm;
float final;
float hw1;
float hw2;
double x;
double grade;
}student[100];


int main() {
	int i=0,k=0,n=0,j,c;       double tut=0;     char tut2[10]={0};		char tut3[15]={0};    char tut4[15]={0};
        double a;                
        float total=0.0;       float tot=0.0;
        float deviation;       float m;              float midavg=0.0;
        float finalavg=0.0;    float hw1avg=0.0;     float hw2avg=0.0;
        float devia;
        int aacount=0,bacount=0,bbcount=0,cbcount=0,cccount=0,dccount=0,ddcount=0,ffcount=0,vfcount=0;      
              i=0;
        while(k!=-1)
        {
         scanf("%s",student[i].number); 
         scanf("%s",student[i].firstname);     
         scanf("%s",student[i].lastname);
         scanf("%f",&student[i].midterm);
         scanf("%f",&student[i].final);
         scanf("%f",&student[i].hw1);
         scanf("%f",&student[i].hw2);
         printf("ogrenci[%d] no : %s\n",i+1,student[i].number);
         printf("ogrenci name: %s \tlast name: %s\n",student[i].firstname,student[i].lastname); 
                                                                                          
         k=atoi(student[i].number);
         i++;         
       }
          n=i-1;
                    
          
            //  Part 2             
          printf("CLASS AVERAGES \nNumber of student records = %d\n",n);
         
             a=atof("student.x[i]");
             if(a==0)
             n=n-1;
             
            printf("N = %d\n",n);
            
            for(i=0;i<=n;i++){
            midavg+=student[i].midterm;
            finalavg+=student[i].final;
            hw1avg+=student[i].hw1;
            hw2avg+=student[i].hw2; 
              student[i].grade=floor(((student[i].midterm)*(0.25))+((student[i].final)*(0.40))+((student[i].hw1)*(0.15))+((student[i].hw2)*(0.20))); 
              tot+=student[i].grade;   
            }
            m=tot/n;
            printf("Midterm Average = %.2f\nFinal Average  = %.2f\nhw1  average = %.2f\nhw2 average = %.2f \n",midavg/n,finalavg/n,hw1avg/n,hw2avg/n);
            printf("mean grade = %.2f\n",m);
            
          for(i=0;i<=n;i++){
          student[i].grade=floor(((student[i].midterm)*(0.25))+((student[i].final)*(0.40))+((student[i].hw1)*(0.15))+((student[i].hw2)*(0.20))); 
          
           total+=(pow(student[i].grade-m,2));
           devia=floor(sqrt(total/n));
        }
           printf("standar devi : %.2f\n",devia);
                      
                                                                                                                                       
               
               /////PART 1 
                                   
           printf("PART 1:\nRESULTS SORTED BY GRADE IN DESCENDING ORDER\nStudent Number     Student Name     Grade     Letter  \n");
           printf("========      ========      ======      =====  \n");
           
           for(j=0;j<n+1;j++){
           for(i=0;i<n+1;i++){
           if(student[i].grade<student[i+1].grade){
                        tut=student[i].grade;    student[i].grade=student[i+1].grade;     student[i+1].grade=tut;
						strncpy(tut3,student[i].firstname,15);   strncpy(student[i].firstname,student[i+1].firstname,15);	strncpy(student[i+1].firstname,tut3,15);
						strncpy(tut2,student[i].number,10);	strncpy(student[i].number,student[i+1].number,10);		strncpy(student[i+1].number,tut2,10);
                        strncpy(tut4,student[i].lastname,15);  strncpy(student[i].lastname,student[i+1].lastname,15);         strncpy(student[i+1].lastname,tut4,15);
       }}}
       
		   for(i=0;i<=n;i++){                               c=student[i].grade;
       printf("%10s    %15s     %15s    %d  ",student[i].number,student[i].firstname,student[i].lastname,c);
					if(c==0)                {                     
                         printf("VF\n");
                         ++vfcount;                       }
                   else
                        if(c>=m+1.5*devia) {
                         printf("AA \n");
                         ++aacount;                       }
                   else 
                        if(c>=m+1.0*devia) {
                        printf("BA\n");
                        ++bacount;                        }
                   else
                        if(c>=m+0.5*devia) { 
                        printf("BB\n");
                        ++bbcount;                        }
                   else
                        if(c>=m)            {
                        printf("CB\n");
                        ++cbcount;                         }
                   else
                        if(c>=m-0.5*devia) {
                        printf("CC\n");   
                        ++cccount;                        }
                   else
                        if(c>=m-1.0*devia)  {
                        printf("DC\n");
                        ++dccount;                         }
                   else
                        if(c>=m-1.5*devia)  {
                        printf("DD\n");
                        ++ddcount;                         }
                   else                                    {
                       printf("FF\n");             
                       ++ffcount;                          }
               
            }          
              
			

			// PART  3
            
            printf("PART 3: \nLETTER COUNTS AND HISTOGRAM\n\n");
            printf("AA count = %d ",aacount);
            for(i=0;i<aacount;i++)
                                   printf("*");
            printf("\nBAcount = %d",bacount);
            for(i=0;i<bacount;i++)
                                   printf("*");
           printf("\nBBcount = %d",bbcount);                     
           for(i=0;i<bbcount;i++)
                                   printf("*");
           printf("\nCBcount = %d",cbcount);                     
           for(i=0;i<cbcount;i++)
                                   printf("*");
           printf("\nCCcount = %d",cccount);                     
           for(i=0;i<cccount;i++)
                                   printf("*");
           printf("\nDCcount = %d",dccount);                     
           for(i=0;i<dccount;i++)
                                   printf("*");
           printf("\nDDcount = %d",ddcount);                     
           for(i=0;i<ddcount;i++)
                                   printf("*");
           printf("\nFFcount = %d",ffcount);                     
           for(i=0;i<ffcount;i++)
                                   printf("*");
           printf("\nVFcount = %d",vfcount);                     
           for(i=0;i<vfcount;i++)
                                   printf("*");
        system("pause");
        return 0;
}
