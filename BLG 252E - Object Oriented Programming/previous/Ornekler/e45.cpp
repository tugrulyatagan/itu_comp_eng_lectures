// e45.cpp
// Constant objects and constant functions

#include <iostream>
using namespace std;

class Point{				// Declaration Point Class
   int x,y;					// Properties: x and y coordinates
 public:
   Point(int, int);		// Declaration of the constructor
   bool move(int, int);	// A function to move points
   void print() const;	// constant function: prints coordinates on the screen
};


// ***** Bodies of Member Functions *****

// A constructor with Parameters
// Cooridnates must be pozitive
Point::Point(int x_first, int y_first)
{
	cout << "Constructor is called..." << endl;
	if ( x_first < 0 )		// If the given value is negative
		x = 0;					// Assigns zero to x
	else
		x = x_first;
	if ( y_first < 0 )		// If the given value is negative
		y = 0;					// Assigns zero to x
	else
		y = y_first;
}

// A function to move the points 
bool Point::move(int new_x, int new_y)
{
	if (new_x >=0 && new_y>=0){
		x = new_x;				// assigns new value to x coordinate
	   y = new_y;				// assigns new value to y coordinate 
		return true;
	}
	return false;
}

// Constant function: It prints the coordinates on the screen 
void Point::print() const
{
	cout << "X= " << x << ", Y= " << y << endl;
}
				
// -------- Main Program -------------
int main()
{
	const Point cp(10,20);		// constant point
   Point ncp(0,50);        	// non-constant point
   cp.print();  					// OK. Const function operates on const object
   //cp.move(30,15); 			// ERROR! Non-const function on const object
   ncp.move(100,45);  			// OK. ncp is non-const
	return 0;
}
