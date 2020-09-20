#include <iostream>
using namespace std;

int main(){
   double A,B,C;
   double D,E,F;
   
   cin >> A >> B >> C ;
   cin >> D >> E >> F ;
   double slope1= -A/B;
   double slope2= -D/E;

   if (slope1==slope2)
      cout << "Two lines are parallel." << endl ;
   else
   if ((slope1*slope2)==-1.)
      cout << "Two lines are perpendicular." << endl ;
	  
   return 0;
}
