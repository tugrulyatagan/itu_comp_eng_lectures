// using hex, oct, dec and setbase stream manipulator

#include <iostream>

#include <iomanip>

using namespace std;


int main()

{

int p; 

cout<<"Enter a decimal number:"<<endl;
cin>>p;

cout<<p<< " in hexadecimal is: "<<hex<<p<<'\n'<<dec<<p<<" in octal is: "<<oct<<p<<'\n'

<<setbase(10) <<p<<" in decimal is: "

<<p<<endl;

cout<<endl;

return 0;

}
