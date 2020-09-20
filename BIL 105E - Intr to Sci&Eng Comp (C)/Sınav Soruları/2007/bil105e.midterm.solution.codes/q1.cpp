#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main(){
   int n,m=0;
   cin >> n;
   srand(time(NULL));
   for (int i=0;i<n;++i){
       double x,y;
       x = 2.0*((double)rand()/RAND_MAX)-1;
       y = 2.0*((double)rand()/RAND_MAX)-1;
       if ((x*x+y*y)<=1.0) ++m;
   }
   cout << "pi is " << ((4.0*m)/n) ;
   return 0;
}
