#ifndef __NODE_H__
#define __NODE_H__

#include <iostream>
#include <string>
using namespace std;

class Node {
      private:
      string name;//dugumun adi
	  Node** adjacent;

      public:
      Node();//yeni dugum
      Node(string);//yeni dugum
      Node(const Node &);//dugum kopyala
      ~Node();//dugum sil
	  bool delAdjacent(string);
	  bool addAdjacent(const Node &);
      Node** getAdjacents();
      string getName();//dugumun adini dondurur
	  int numEdges;
};
#endif