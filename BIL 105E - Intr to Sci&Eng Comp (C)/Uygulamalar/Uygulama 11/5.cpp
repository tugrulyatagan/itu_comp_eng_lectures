#include <iostream>
#include <fstream>

using namespace std;
int main()
 {  
    ofstream file_w;      
	const char *isim = "Ahmet";
	int no = 123;
	cout<<isim<< "  "<<no<<endl;
	cout<<"Dosyaya yaziliyor...."<<endl;
	file_w.open("dosya5.txt",ios::out);  //open a file for writing
	  if(file_w.good()) cout<<"Dosya basariyla olusturuldu."<<endl;
         else cout<<"Hata!"<<endl; 
    file_w.write((char*) &isim, sizeof no);
    file_w.close();
    
    
    cout<<"Dosyadan okunuyor"<<endl;
    ifstream file_r;
    file_r.open("dosya5.txt",ios::in); 
     if(file_r.good()) cout<<"Dosya basariyla olusturuldu."<<endl;
         else cout<<"Hata!"<<endl; 
    while(!file_r.eof())
     {
     file_r.read((char*) &isim, sizeof no);
     cout<<isim<<" "<<no<<endl;   
               
     }
     
    cout<<endl;
    file_r.close(); 

	
	return 0;
}
