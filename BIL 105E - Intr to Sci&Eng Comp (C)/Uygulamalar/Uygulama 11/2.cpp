#include <iostream>
#include <fstream>

using namespace std;

int main()
 {
    ifstream file;

    file.open("file.txt",ios::in);  //open a file for reading
    if(file.good()) cout<<"Dosya basariyla olusturuldu."<<endl;
     else cout<<"Hata!"<<endl;
    char ch;
 
	while (true) {      	
      file>>ch;
	  if( file.eof() ) break;
      cout<<ch;
      }
	  
	   
    
    file.close(); //close it
    
return 0;
    
 }
