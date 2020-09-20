#include <iostream>

using namespace std;

int main()
{
  char character = 'A';
  char string[] = "This is a string";
  const  char *stringPtr = "This is also a string";

  cout<<character<<endl; /* c --> char */
  cout<<"this is a string"<<endl; /* s --> string */
  cout<<string<<endl;
  cout<<stringPtr;
 return 0;
}
