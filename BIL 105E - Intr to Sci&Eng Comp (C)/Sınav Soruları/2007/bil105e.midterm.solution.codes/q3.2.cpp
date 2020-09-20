#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void printArray(int array[], int length){
   for (int i=0;i<length-1;++i)
	  cout << array[i] << "," ;
   cout << array[length-1] << endl ;
}
int main(){
   int array[16]={5};
   for (int i=1;i<sizeof(array)/sizeof(int);++i) 
       array[i]=array[i-1]+5;
   printArray(array,sizeof(array)/sizeof(int));
   srand(time(0L));
   int leftArray[8]={0},rightArray[8]={0};
   int left=0,right=0;
   for (int i=0;i<sizeof(array)/sizeof(int);++i){
        int k= (int)((double)rand()/RAND_MAX+0.5);
	if (left==sizeof(leftArray)/sizeof(int)) k=1;
	if (right==sizeof(rightArray)/sizeof(int)) k=0;
	switch(k){
	   case 0:
		   leftArray[left++]= array[i];
		   break;
	   case 1:
		   rightArray[right++]= array[i];
		   break;

	 }
       
   }
   printArray(leftArray,sizeof(leftArray)/sizeof(int));
   printArray(rightArray,sizeof(rightArray)/sizeof(int));

   return 0;
}
