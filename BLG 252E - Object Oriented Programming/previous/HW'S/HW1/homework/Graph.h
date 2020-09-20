#ifndef __GRAPH_H__
#define __GRAPH_H__
#include "Node.h"

#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

class Graph {
      private:
      int numNodes,numEdges; //dugumsayisi,ayritsayisi
      string name;//grafin adi
      Node* nodes;//grafin icerdigi dugumler
      //fstream* graphFile;//dosya-graf baglantisi
     
      public:
      static int graphCount;//graf sayisi
      Graph();//bos graf olustur
      //Graph(string filename);//dosyadan graf oku
      Graph(int);//dugum sayisi belli graf olustur
      Graph(const Graph &);//graf kopyala
      ~Graph();//grafi sil
      bool newNode(string); //returns true if the node is added
      bool newEdge(string,string); //returns true if the edge is added
      Node* deleteNode(string); //returns null if the node is absent
      bool deleteEdge(string,string); //returns false if the edge is absent
      string printGraph();//grafi yaz
      void intersect(const Graph &); //returns a new intersection graph.
      void unite(const Graph &); //returns a new union graph.
};
#endif