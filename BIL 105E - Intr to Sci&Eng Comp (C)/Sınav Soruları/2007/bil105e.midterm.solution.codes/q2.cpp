#include <iostream>
using namespace std;

int getSumOfOddDigits(unsigned long int n){
    int sum=0,dig;
    for (;n>0;n/=10)
	if ((dig=(n%10))%2) sum+=dig;
    return sum;
}

int main(){
   unsigned long int n=123456789;
   cout << getSumOfOddDigits(n) ;
   return 0;
}
