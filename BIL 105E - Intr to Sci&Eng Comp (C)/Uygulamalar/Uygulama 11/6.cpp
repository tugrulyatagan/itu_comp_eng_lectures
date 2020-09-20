#include <iostream>
#include <fstream>
#define MAX_ISIM 40
using namespace std;
int main()
 {  
	string isim = "Ahmet Mehmet Turannn";
	ofstream file_w;      

	cout<<isim<<endl;
	cout<<"Dosyaya yaziliyor...."<<endl;
	file_w.open("dosya6.txt",ios::out);  //open a file for writing
	  if(file_w.good()) cout<<"Dosya basariyla olusturuldu."<<endl;
         else cout<<"Hata!"<<endl; 
    file_w<<isim;
    file_w.close();
    
    
    cout<<"Dosyadan okunuyor"<<endl;
    ifstream file_r;
    string line;
    file_r.open("dosya6.txt",ios::in); 
     if(file_r.good()) cout<<"Dosya basariyla olusturuldu."<<endl;
         else cout<<"Hata!"<<endl; 
    while(!file_r.eof())
     {
     file_r>>line;
     cout<<line;   
     }
     
     
    cout<<endl;
    file_r.close(); 

	
	return 0;
}
