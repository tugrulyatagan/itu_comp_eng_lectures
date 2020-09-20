/****************************************
* ornek   : 8-4							*
* aciklama: pointerlarla atama ornegi	*
* derleme : g++ -o program_ismi 4.cpp   *
****************************************/

#include <iostream>
using namespace std;

int main()
{
	int count = 0, *temp, sum = 0;
	
	temp  = &count;
	*temp = 20;
	temp  = &sum;
	*temp = count;
	
	cout<<"count: "<<count<<", temp: "<<temp<<", sum: "<<sum<<endl;
	//printf("count: %d, temp: %d, sum: %d\n", count, *temp, sum);
	
	return 0;
}
