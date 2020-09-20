#include<iostream>
#include<cmath>

using namespace std;

int main()
{
    float x,y,sonuc;
	
	cout << "x : "; cin >> x; cout << endl;
	cout << "y : "; cin >> y; cout << endl;
	
	sonuc = (pow(x,3)+sqrt(y))/exp(x+y);
    cout << "sonuc : " << sonuc << endl;
	
	return 0;
}
