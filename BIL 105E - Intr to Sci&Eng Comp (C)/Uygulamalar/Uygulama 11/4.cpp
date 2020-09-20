#include <iostream>
#include <fstream>

using namespace std;


int main()
 {
    ofstream file_w;
    file_w.open("file.txt",ios::out);  //open a file for writing
    char c[] = {'d', 'e', 'n', 'e', 'm', 'e','\0'};
	int i, uzunluk = sizeof(c) / sizeof(char);
	cout<<"Dosyaya yazilacak kelime: "<<c<< " ve uzunlugu: "<<uzunluk<<endl;
	for (i = 0; i < uzunluk; i++) 
	  file_w.put(c[i]);
    file_w.close(); //close it
    
    ifstream file_r;
    char oku;
    file_r.open("file.txt",ios::in); 
    while(true)
     {
      file_r>>oku;
	  if(file_r.eof()) break;
      cout<<oku;
     }
     
    cout<<endl;
    file_r.close();
    
 return 0;   
 }
