// e84a.cpp
// http://www.buzluca.info/oop
// Abstract class and pure virtual functions 


#include<iostream>
using namespace std;

class GenericShape{          // Abstract base class
	protected:
		int x,y;
	public:
		GenericShape(int x_in,int y_in){x=x_in;y=y_in;}  // Constructor
		virtual void draw()const =0;      // pure virtual function
}; 

class Line:public GenericShape{       // Line class
 protected:
  int x2,y2;             // End coordinates of line
 public:
  Line(int x_in,int y_in,int x2_in,int y2_in):GenericShape(x_in,y_in),
	                                          x2(x2_in),y2(y2_in)
	{ }
	void draw()const;      // virtual draw function
};
void Line::draw()const
{ 
	cout << "Type: Line" << endl;
	cout << "Coordinates of end points: " << "X1=" << x <<  " ,Y1=" << y <<  " ,X2=" << x2 <<  " ,Y2=" << y2 << endl; 
} 

class Rectangle:public GenericShape{       // Rectangle class
 protected:
  int x2,y2;             // coordinates of 2nd corner point
 public:
  Rectangle(int x_in,int y_in,int x2_in,int y2_in):GenericShape(x_in,y_in),
	                                          x2(x2_in),y2(y2_in)
	{ }
	void draw()const;     // virtual draw
};
void Rectangle::draw()const
{ 
	cout << "Type: Rectangle" << endl;
	cout << "Coordinates of corner points: " << "X1=" << x <<  " ,Y1=" << y <<  " ,X2=" << x2 <<  " ,Y2=" << y2 << endl; 
} 
class Circle:public GenericShape{    // Circle class
 protected:
	int radius;
 public:
	Circle(int x_cen,int y_cen,int r):GenericShape(x_cen,y_cen),
										radius(r)
	{	}
	void draw() const;       // virtual draw
};

void Circle::draw()const
{ 
	cout << "Type: Circle" << endl;
	cout << "Coordinates of center point: " << "X=" << x <<  " ,Y=" << y << endl; 
	cout << "Radius: " << radius << endl; 
} 
 

/* A function to draw different shapes ***/
void show(const GenericShape &shape)
{              // Which draw function will be called?
 shape.draw(); // It is unknown at compile-time
}

int main()
{
	 Line line1(1,1,100,250);
	 Circle circle1(100,100,20);
	 Rectangle rectangle1(30,50,250,140);
	 Circle circle2(300,170,50);
	 show(circle1);
	 show(line1);
	 show(circle2);
	 show(rectangle1);
	return 0;
}
