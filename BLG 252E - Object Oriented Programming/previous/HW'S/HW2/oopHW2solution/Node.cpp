#include "Node.h"

Node::Node(){
     this->name="";
     nofAdjacents=0;
     adjacents=NULL;
}

//Construct a Node with a the given name in <par>
Node::Node(string name){
     this->name=name;
     nofAdjacents=0;
     adjacents=NULL;
}

//Copy constructor of a node
Node::Node(const Node& aNode){
     this->name=aNode.name;
     this->nofAdjacents=aNode.nofAdjacents;
     this->adjacents=new Node*[this->nofAdjacents];

     for(int i=0;i<nofAdjacents;i++)
          this->adjacents[i]=aNode.adjacents[i];
}

//Node destructor, deletes adjacent array if any adjacents exists
Node::~Node(){
    if(adjacents)
        delete adjacents;
}

//get node name
string Node::getNodeName(){
     return name;
     }

//look for an adjacent named <par>. Return its indice if present. Return -1 if not.
int Node::containsAdjacent(string s){
     int i;

     for(i=0;i<nofAdjacents;i++)
          if(adjacents[i]->getNodeName().compare(s)==0)
               return i;

     return -1;

}

//get the name of the adjacent at i. Serves as an iterator for the node adjacents
string Node::getAdjacent(int i){
     if(i>=nofAdjacents)
          return "";
     else
          return adjacents[i]->getNodeName();
}

int Node::getNumOfAdjacents(){
    return nofAdjacents;
}
//delete and adjacent of a node
bool Node::deleteAdjacent(const Node& aNode){

     int index,i,j;

     index=containsAdjacent(aNode.name);

     //If the node doesn't exist, return doing nothing
     if(index<0)
          return false;

     //Create a backup for the original adjacents
     Node** temp=new Node*[nofAdjacents-1];

     //Copy adjacents except the one to be deleted
     for(i=0,j=0;i<nofAdjacents;i++)
          if(i!=index){
               temp[j]=adjacents[i];
               j++;
          }

     //Get a smaller space
     adjacents= new Node*[--nofAdjacents];

     //Restore the backup
     for(i=0;i<nofAdjacents;i++)
          adjacents[i]=temp[i];


     return true;
}

//add and adjacent to a node
bool Node::addAdjacent(const Node& aNode){

     int i;

     //If the node already exists, return doing nothing
     if(containsAdjacent(aNode.name)>=0)
          return false;

     //Create a backup for the original adjacents
     Node** temp=new Node*[++nofAdjacents];

     //Copy adjacents
     for(i=0;i<nofAdjacents-1;i++)
          temp[i]=adjacents[i];

     //add the new adjacent
     temp[i]=const_cast <Node*> (&aNode);

     //Get a larger space
     adjacents= new Node*[nofAdjacents];

     //Restore the backup
     for(i=0;i<nofAdjacents;i++)
          adjacents[i]=temp[i];

     return true;
}

//return a string representation of a node and its adjacents
string Node::toString(){
     string node="";

     //Concat all the adjacent names
     for(int i=0;i<nofAdjacents;i++)
          node=node+name+"-"+adjacents[i]->getNodeName()+"\n";

     return node;
}

//Intersect the adjacents of a node
void Node::intersect(const Node& aNode){
     int nofAdjacents=this->nofAdjacents<aNode.nofAdjacents?this->nofAdjacents:aNode.nofAdjacents;
     int i,j,k=0;

     Node** temp= new Node*[nofAdjacents];

     //Iterate through both nodes adjacents and save the intersecting ones
     for(i=0;i<this->nofAdjacents;i++)
          for(j=0;j<aNode.nofAdjacents;j++)
               if(this->adjacents[i]->getNodeName().compare(aNode.adjacents[j]->getNodeName())==0){
                    temp[k]=this->adjacents[i];
                    k++;
               }

     //Restore the saved adjacents to the calling objects array
     this->nofAdjacents=k;
     this->adjacents= new Node*[this->nofAdjacents];

     for(i=0;i<this->nofAdjacents;i++)
          this->adjacents[i]=temp[i];

}

//Unite the adjacents of a node
void Node::unite(const Node& aNode){
     int nofAdjacents=this->nofAdjacents+aNode.nofAdjacents;
     int i,k;

     Node** temp= new Node*[nofAdjacents];
     k=0;

     //Iterate through both nodes adjacents and save all the nodes

     for(i=0;i<this->nofAdjacents;i++){
          temp[k]=this->adjacents[i];
          k++;
     }

     for(i=0;i<aNode.nofAdjacents;i++)
         //Don't save if already saved
          if(this->containsAdjacent(aNode.adjacents[i]->getNodeName())<0){
               temp[k]=aNode.adjacents[i];
               k++;
          }

    //Restore the saved adjacents to the calling objects array
     this->nofAdjacents=k;
     this->adjacents= new Node*[this->nofAdjacents];

     for(i=0;i<this->nofAdjacents;i++)
          this->adjacents[i]=temp[i];

}
