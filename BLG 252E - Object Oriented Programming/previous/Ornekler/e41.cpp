// e41.cpp
// http://www.buzluca.info/oop/
// Default Constructor

#include <iostream>
using namespace std;

class Point{				// Declaration Point Class
	int x,y;					// Properties: x and y coordinates
 public:
	Point();					// Declaration of the default constructor	
	bool move(int, int);	// A function to move points
	void print();			// to print coordinates on the screen
};

// ***** Bodies of Member Functions *****

// Default Constructor
Point::Point()
{
	cout << "Constructor is called..." << endl;
	x = 0;					// Assigns zero to coordinates
	y = 0;
}

// A function to move the points 
bool Point::move(int new_x, int new_y)
{
	if (new_x >=0 && new_y>=0){
		x = new_x;				// assigns new value to x coordinat
	   y = new_y;				// assigns new value to y coordinat 
		return true;
	}
	return false;
}

// To print the coordinates on the screen 
void Point::print()
{
	cout << "X= " << x << ", Y= " << y << endl;
}
				
// -------- Main Program -------------
int main()
{
	Point p1,p2;				// Default construct is called 2 times
	Point *ptr;				    // ptr in not an object, construct is NOT called 
	ptr = new Point;	        // Default construct is called once 
	p1.print();					// p1's coordinates to the screen
	p2.print();					// p2's coordinates to the screen
	ptr->print();				// Coordinates of the object pointed by pp to the screen
	delete ptr;
	return 0;
}
