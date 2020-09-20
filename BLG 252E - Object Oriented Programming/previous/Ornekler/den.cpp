#include <iostream>
using namespace std;

enum basketSize{small, medium, large}; 

void func(basketSize bs){
	if (bs == small)
		cout << "anan" << bs;
	else
		cout << "baban";
}

int main(){
	int selected_size;
	cin >> selected_size;
	func(basketSize(selected_size));
	cout << "Program terminates" << endl;
	return 0;
}
