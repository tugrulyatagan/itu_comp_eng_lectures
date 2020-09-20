#include <cstdio>
#include <iostream>

using namespace std;

int main()
{
	int choice;

	cout << "1-Turkce" << endl;
	cout << "2-Ingilizce" << endl;
	cout << "3-Fransizca" << endl;

	cin >> choice;
	switch (choice)
	{
		case 1: {cout << "Merhaba" << endl; break;}
		case 2: {cout << "Hello" << endl; break;}
		case 3: {cout << "Salut" << endl; break;}
	}

	return 0;
}

