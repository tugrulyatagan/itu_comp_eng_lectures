#include <iostream>
#include <fstream>

using namespace std;

int main()
 {
    fstream file;

    file.open("file.txt",ios::out|ios::app);  //open a file for appending
      
    file<<"Hello file again\n"; //write to it
    
    file.close(); //close it
    
return 0;
    
 }
