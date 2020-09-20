#include <iostream>
using namespace std;
int main()
{
 char c;
 cout << "Bir harf giriniz : ";
 c = cin.get();
 cout << "Girilen harf '" << c << "', buyuk hali '" << static_cast <char>(c-32) << "'\n";
 return 0;
}
