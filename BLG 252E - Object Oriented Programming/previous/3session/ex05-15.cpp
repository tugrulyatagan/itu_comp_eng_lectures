// Illustrating the generic remove algorithm
#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
  cout << "Illustrating the generic remove algorithm." << endl;
  const int  N = 11;
  int array1[N] = {1, 2, 0, 3, 4, 0, 5, 6, 7, 0, 8};
  vector<int> vector1;
  int i;
  for (i = 0; i < N; ++i)
    vector1.push_back(array1[i]);
   
   vector<int>::iterator where;
   where = vector1.begin();
   while (where != vector1.end())
	  cout <<*where++ << " ";
   cout <<endl;
  
   // Remove the zeros from vector1:
  vector<int>::iterator new_end;
  new_end = remove(vector1.begin(), vector1.end(), 0);

//ForwardIterator remove(ForwardIterator first, ForwardIterator last,const T& value);
//Remove removes from the range [first, last) all elements that are equal to value. 
//That is, remove returns an iterator new_last such that the range [first, new_last) contains no elements equal to value. 
//The relative order of elements that are not equal to value is unchanged. 
 
  // The size of vector1 remains the same:
  assert (vector1.size() == N);

  // The nonzero elements are left in 
  // [vector1.begin(), new_end).  Erase the rest:
  vector1.erase(new_end, vector1.end());
   cout << endl;
   where = vector1.begin();
   while (where != vector1.end())
	  cout <<*where++ << " ";
   cout <<endl;
  
  return 0;
}
