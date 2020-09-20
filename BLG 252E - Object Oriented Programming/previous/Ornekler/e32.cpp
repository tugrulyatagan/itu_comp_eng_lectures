// e32.cpp
// this Pointer

#include <iostream>
using namespace std;

class Point{				// Delaration Point Class
	int x,y;					// Properties: x ve y coordinates
 public:
	void move(int, int);	// A function to move points
	void print();			// to prints cordinates on the screen
	bool is_zero();		// is point on the zero point(0,0)
	Point *far_away(Point &); // Finds the point that has the largest distance from (0,0)
};

// ***** Bodies of Member Functions *****

// A function to move the points 
void Point::move(int new_x, int new_y)
{
	x = new_x;				// assigns new value to x coordinat
	y = new_y;				// assigns new value to y coordinat 
}

// To print the coordinates on the screen 
void Point::print()
{
	cout << "X= " << x << ", Y= " << y << endl;
}
				
// is the point on the zero point(0,0)
bool Point::is_zero()
{
	return (x == 0) && (y == 0);	  
}


// Finds the point that has the largest distance from (0,0)
Point *Point::far_away(Point &p)
{
	unsigned long x1 = x*x;				
	unsigned long y1 = y*y;
	unsigned long x2 = p.x * p.x;
	unsigned long y2 = p.y * p.y;
	if ( (x1+y1) > (x2+y2) ) return this;
	else return &p;
}

int main()
{
	Point p1,p2;			 // 2 objects: p1 ve p2
	p1.move(100,50);		 // p1 to (100,50)
	p2.move(20,65);		 // p2 to (20,65)
	Point *pp;				 // pp is a pointer to points
	pp=p1.far_away(p2);
	pp->print();			// the poiont taht has dhe largest distanece on the screen
	return 0;
}
