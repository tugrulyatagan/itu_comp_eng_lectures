#include<iostream>
#include<fstream>
	
using namespace std;



int main()
{
	char *isim;
	int no = 5;
	
	
	cout << "Dosyadan okunuyor..." << endl;
	
	ifstream file_r;
	file_r.open("deneme.txt", ios::in);

	if(file_r.good())
		cout << "Dosya basariyla okundu" << endl;
	else
		cout << "Hata!" << endl;

	while(!file_r.eof())
	{
		file_r.read((char*) &isim, sizeof no);
		cout << isim << " " << endl;
	}
	cout << endl;

	file_r.close();

	return 0;
}	
	
