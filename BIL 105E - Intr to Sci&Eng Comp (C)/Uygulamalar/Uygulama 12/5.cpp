// printing the address stored in a char * variable

#include <iostream>

using namespace std;

 

int main()

{

       const char * string = "pointer testing";

       cout<<"\nThe string is: "<<string

              <<"\nValue of (void *) string, the address is: "

              <<&string <<endl;

       return 0;

}

 
