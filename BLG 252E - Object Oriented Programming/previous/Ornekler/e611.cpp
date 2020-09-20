// e611.cpp
//	Example for virtual classes 

class Gparent
{
	 protected:
		int Gi;
};

class Mother : virtual public Gparent
{
	protected:
		int Mi;
};

class Father : virtual public Gparent
{
	protected:
		int Fi;
};

class Child : public Mother, public Father
{
 public:
	 int Ci;
	 void set(){Gi=5;}
};

int main()
{
	Child c;
	c.Ci=6;
	c.set();
	return 0;
}
