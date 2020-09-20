#include <string.h>

using namespace std;

class Pair{

	private:

		int a;
		int b;
		pthread_mutex_t plock;

	public:
		bool operator<(Pair &);
		bool operator>(Pair &);
		bool operator==(Pair &);
		void setA(int);
		void setB(int);
		void setAB(int,int);
		Pair(int,int);
		Pair(void);
		~Pair();
		void print(string);
		void lock();
		void unlock();
};
