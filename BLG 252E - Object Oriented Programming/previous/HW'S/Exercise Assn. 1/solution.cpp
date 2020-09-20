#include <iostream>
using namespace std;

class Parabola{
	int A,B,C;
public:
	Parabola(int, int, int);
	double get_y(double);
	void get_roots();
	void get_extremum(); 
};
Parabola::Parabola(int desired_A, int desired_B, int desired_C){
	A=desired_A;
	B=desired_B;
	C=desired_C;
}
double Parabola::get_y(double x){
	return A*x*x+B*x+C;
}
void Parabola::get_roots(){
	double D=B*B-4*A*C;
	if(D>0){
		double x1,x2;
		x1=(-1*B+sqrt(D))/(2*A);
		x2=(-1*B-sqrt(D))/(2*A);
		cout<<"There are 2 roots"<<endl;
		cout<<"Root1-> x="<<x1<<endl;
		cout<<"Root2-> x="<<x2<<endl;
	}
	else if(D==0){
		double x=(-1*B+sqrt(D))/(2*A);
		cout<<"There is one root at x= "<<x<<endl;
	}
	else{
		cout<<"No roots"<<endl;
	}
}
void Parabola::get_extremum(){
	double x;
	if(A<0){
		x=(-1*B)/(2*A);
		cout<<"There is a local maximum at x="<<x<<", y="<<this->get_y(x)<<endl;
	}
	else if(A>0){
		x=(-1*B)/(2*A);
		cout<<"There is a local minimum at x="<<x<<", y="<<this->get_y(x)<<endl;
	}
	else{
		cout<<"No local extremum"<<endl;
	}
}

int main(){
	Parabola p1(-1,2,1);	
	cout<<"y for x=5 is "<<p1.get_y(5)<<endl;
	p1.get_roots();
	p1.get_extremum();

	return 0;
}

