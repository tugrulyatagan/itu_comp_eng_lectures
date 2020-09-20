// e12_9.cpp
// http://www.buzluca.info/oop
// Using the find algorith with user defined-types (Complex Numbers)

#include <iostream>
#include <algorithm>
using namespace std;

class ComplexT{
	float re,im;
public:
	set(float r, float i){re=r;im=i;}
	bool operator==(const ComplexT &c) const{
		return re==c.re && im==c.im;
	}
};

int main()
{
	ComplexT z[3];
	z[0].set(1.1, 1.2);
	z[1].set(2.1, 2.2);
	z[2].set(3.1, 3.2);
	
	ComplexT zSearch;
	zSearch.set(2.1, 2.2);
	
	ComplexT *result;
	
	result=find(z, z+3, zSearch);
	if (result == z+3) cout << "Not found";
	    else		   cout << "Found";
   return 0;
}
