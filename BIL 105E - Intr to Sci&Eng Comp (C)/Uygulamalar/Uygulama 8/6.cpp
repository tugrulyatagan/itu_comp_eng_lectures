/****************************************
* ornek   : 8-6							*
* aciklama: pointer / dizi iliskisi		*
* derleme : g++ -o program_ismi 6.cpp	*
****************************************/

#include <iostream>
using namespace std;

int main()
{
	int A[] = {1, 2, 3, 4, 5, 6, 7, 8, 9},
		*ptr, *ptr2, i;
		
	ptr  = A;
	ptr2 = &A[sizeof(A) / sizeof(int) - 1];
	
	cout<<"ptr ile dizinin son elemani:  "<<*(ptr + 8)<<endl;
	cout<<"ptr2 ile dizinin ilk elemani: "<<*(ptr2 - 8)<<endl;
	//printf("ptr ile dizinin son elemani:  %d\n", *(ptr + 8));
	//printf("ptr2 ile dizinin ilk elemani: %d\n", *(ptr2 - 8));
	
	for (i = 0; i < 9; i++, ptr++, ptr2--){
		if (ptr == ptr2) break;
		//printf("%d\t%d\n", *ptr, *ptr2);
		cout<<*ptr<<"\t"<< *ptr2<<endl;
	}
		
	return 0;
}
