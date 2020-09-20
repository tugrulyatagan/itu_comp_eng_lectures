#include <iostream>
#include <fstream>



using namespace std;
int main()
 {  
          
    ofstream file_w;      
	cout<<"Dosyaya yaziliyor...."<<endl;
	file_w.open("dosya7.dat",ios::out);  //open a file for writing
	  if(file_w.good()) cout<<"Dosya basariyla olusturuldu."<<endl;
         else cout<<"Hata!"<<endl; 
  	for (int i = 0; i < 10; i++)    
    file_w<<i<<" "<<i*i<<endl;
    file_w.close();      

  
    ofstream file_w1;
    ifstream file_r;  
    int sayi;
    int sayi1;
   	file_r.open("dosya7.dat",ios::in); 
    file_w1.open("yeni_dosya7.dat",ios::out);
    while(true)
    {
     file_r>>sayi;
     file_r>>sayi1;
	 if(file_r.eof()) break;
     cout<<sayi<<" "<<sayi1<<endl;  
     file_w1<<sayi<<" "<<sayi1<<" "<<sayi*sayi1<<endl;
    }
   file_r.close();
   file_w1.close(); 
      
   ifstream file_r1;  
   int sayi2;
   file_r1.open("yeni_dosya7.dat",ios::in);  
    while(true)
    {
     file_r1>>sayi;
     file_r1>>sayi1;
     file_r1>>sayi2;
	 if (file_r1.eof()) break;
     cout<<sayi<<" "<<sayi1<<" "<<sayi2<<endl;  
     
    }
   return 0;
}
