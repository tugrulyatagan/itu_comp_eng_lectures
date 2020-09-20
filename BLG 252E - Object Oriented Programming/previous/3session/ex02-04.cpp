#include <iostream>
using namespace std;

int main () {
  try
  {
    throw 20;
  }
  catch (int e)
  {
    cout << "An exception occurred. Exception Number: " << e << endl;
  }
  catch (char param) { cout << "char exception"; }
  catch (...) { cout << "default exception"; }
  return 0;
}
