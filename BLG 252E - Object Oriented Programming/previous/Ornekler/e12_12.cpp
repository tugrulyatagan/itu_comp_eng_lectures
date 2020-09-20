// e12_12.cpp
// http://www.buzluca.info/oop
// uses for_each() to output inches array elements as centimeters **/
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

void in_to_cm(float in)         // convert and display as centimeters
{
   cout << (in * 2.54) << ' ';
}

int main()
{                                // array of inches values
   float array[] = { 3.5, 6.2, 1.0, 12.75, 4.33 };
   vector<float> inches (array, array+5);		// vector of inches values
                                // output as centimeters
   for_each(inches.begin(), inches.end(), in_to_cm);
   return 0;
}
