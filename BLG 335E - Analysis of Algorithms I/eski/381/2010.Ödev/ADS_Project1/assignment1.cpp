/*This program is an example of measuring time using clock() function.
  Implement heap sort.
  You have to implement an efficient main() function so users will be able to select
  data set and build or sort. 
*/

/* This program sorts an array's values into ascending order */

#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

#define SIZE 100000 // array size

using namespace std;

void heapsort(...); // your heap sort 

void readData(string fileName, int *a);
void writeData(string fileName, int *a);
/* function main begins program execution */
int main() 
{      
	int number;
  
   // Define an array and read data
	int a[SIZE];
	int choice;
	int i = 0;


   time_t  start, end; /* time_t  defined in <ctime> and <sys/ctype> as long */
   clock_t sort_start_clk, sort_end_clk, read_start_clk, read_end_clk, write_start_clk, write_end_clk; 
   /* clock_t defined in <ctime>, it is better to use clock.*/

	

	//READ AND PROCESS THE OPTIONS from the command line 
	
			read_start_clk = clock();
			readData("d9.txt", a);
			read_end_clk = clock();

			cout << "Sorting..";
			sort_start_clk = clock();
			insertionsort(a,SIZE);
			sort_end_clk = clock();
			cout << "...OK!" << endl;

			write_start_clk = clock();
			writeData("sorted_d9.txt",a);
			write_end_clk= clock();

   cout << "Using clock() function: " << ((sort_end_clk-sort_start_clk)*100/CLOCKS_PER_SEC) << endl;

   return 0; 
} 

void readData( string fileName, int *a)
{
//YOUR CODE HERE
}

void writeData(string fileName, int *a)
{
//YOUR CODE HERE
}


void heapsort(...)
{
..

//YOUR CODE HERE

..

..

} 

