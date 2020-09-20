#include <iostream>
#include <vector>
using namespace std; 

template <typename T>
class MyQueue
{
     std::vector<T> data;
   public:
     void Add(T const &);
     void Remove();
     void Print();
};

template <typename T> void MyQueue<T> ::Add(T const &d)
{
     data.push_back(d);
}

template <typename T> void MyQueue<T>::Remove()
{
     data.erase(data.begin( ) + 0,data.begin( ) + 1);
}

template <typename T> void MyQueue<T>::Print()
{
     std::vector <int>::iterator It1;
     It1 = data.begin();
     for ( It1 = data.begin( ) ; It1 != data.end( ) ; It1++ )
        cout << " " << *It1<<endl;

}
//Usage for C++ class templates
void main()
{
     MyQueue<int> q;
     q.Add(1);
     q.Add(2);

     cout<<"Before removing data"<<endl;
     q.Print();

     q.Remove();
     cout<<"After removing data"<<endl;
     q.Print();
}
