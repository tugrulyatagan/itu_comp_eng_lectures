#include <iostream>
#include <fstream>

using namespace std;

int main()
 {
    ofstream file;

    file.open("file.txt",ios::out);  //open a file for writing
    if(file.good()) cout<<"Dosya basariyla olusturuldu."<<endl;
     else cout<<"Hata!"<<endl;
    
    file<<"Hello file\n"; //write to it
    
    file.close(); //close it
    
return 0;
    
 }
