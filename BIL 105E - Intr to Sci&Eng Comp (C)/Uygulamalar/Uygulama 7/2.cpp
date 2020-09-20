/************************************************************************
* ornek   : 7-2															*
* aciklama: matrix matrisinin her satirinin en buyuk elemanini bulur	*
* derleme : g++ -o program_ismi 2.cpp										*
************************************************************************/

#include <iostream>
using namespace std;

int main()
{
    int Matrix[4][5]={
	                 {2,6,9,7,9},
	                 {7,3,8,3,6},
	                 {5,1,4,2,3},
	                 {5,2,7,3,1}
                     };
    int Max[4], row, col;
    cout<< "Matrix:\n";
   
    
    //her satirin max elemanlari bulunuyor ve Max dizisinde tutuluyor
	for (row = 0; row < 4; row++){
		Max[row] = Matrix[row][0];
        for (col = 1; col < 5; col++)
        	if (Max[row] < Matrix[row][col]) 
	       		Max[row]= Matrix[row][col];
    }

	//Matrix matrisi ekrana yaziliyor
    for (row = 0; row < 4; row++){
    	for (col = 0; col < 5; col++){        	
			cout<< Matrix[row][col]<<" ";
			}      
	   cout<< "\n";
    }
    
	cout<<"\nMax:\n";
   
    //Max dizisi ekrana yaziliyor
    for (row = 0; row < 4; row++){
    		cout<<Max[row]<<" ";;
		}
  	cout<< "\n";

    return 0; 
}
