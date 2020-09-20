// e11_2.cpp
// http://www.buzluca.info/oop
//    Objects as template arguments **/
#include <iostream>
using namespace std;

class ComplexT{								//A class to define complex numbers 
    float re,im;
  public:
	ComplexT(float r , float i):re(r),im(i){}  // Constructor
    bool operator>(const ComplexT&) const;     // header of operator> function
	 float get_re()const {return re;}
	 float get_im()const {return im;}
	 //friend ostream& operator <<(ostream&, const ComplexT&);
};

// The Body of the function for operator > 
bool ComplexT::operator>(const ComplexT& z) const
{
   float f1 = re * re + im * im;
   float f2 = z.re * z.re + z.im * z.im;
   return f1 > f2;
}

ostream& operator <<(ostream& out, const ComplexT& z)  // Overloading <<
{
	out << "( " << z.get_re() << " , " << z.get_im() << " )" << endl;
   return out;
};

// template function  
template <class type> 
const type & MAX(const type &v1, const type & v2) 
{ 
    if (v1 > v2) return v1;
       else      return v2;
} 

int main()
{
   int i1=5, i2= -3;
   char c1='D', c2='N';
   float f1=3.05, f2=12.47;
   ComplexT z1(1.4,0.6), z2(4.6,-3.8);
   cout << MAX(i1,i2) << endl;
   cout << MAX(c1,c2) << endl;
   cout << MAX(f1,f2) << endl;
   cout << MAX(z1,z2) << endl;
	return 0;
}
