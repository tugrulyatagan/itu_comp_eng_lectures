#ifndef TEKIL_H_
#define TEKIL_H_
#include <iostream>
using namespace std;

class Tekil
{
private:
  int veri;
  static Tekil* instance;
  Tekil();
public:
	static Tekil* getInstance()
        {
            if(instance==NULL)
              instance=new Tekil();
            
            return instance;
        };
	int getVeri();
	void setVeri(int);
	~Tekil();
};

#endif /*TEKIL_H_*/
