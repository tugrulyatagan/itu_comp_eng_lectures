#include "Node.h"
#include "Tree.h"


//add an edge to the graph indicated by <par1> and <par2>
bool Tree::addChild(string aNode,string bNode){

     int aNodeInd,bNodeInd;

     //If both of the nodes exist in the graph
     aNodeInd=containsNode(aNode);
     bNodeInd=containsNode(bNode);
     if(aNodeInd<0 || bNodeInd<0)
          return false;

     //add both as adjacents to the other
     opBuf=opBuf+"edge "+aNode+"-"+bNode+" has been added\n";
     nodes[aNodeInd].addAdjacent(nodes[bNodeInd]);

     return true;
}

//delete an edge to the graph indicated by <par1> and <par2>
bool Tree::deleteChild(string aNode,string bNode){

     int aNodeInd,bNodeInd;

     //if both nodes exist
     aNodeInd=containsNode(aNode);
     bNodeInd=containsNode(bNode);

     if(aNodeInd<0 || bNodeInd<0)
          return false;

     //delete each node from the other's adjecent list
     if(!nodes[aNodeInd].deleteAdjacent(nodes[bNodeInd]))
          return false;

     opBuf=opBuf+"edge "+aNode+"-"+bNode+" has been deleted\n";

     return true;
     }

//Intersect the graph in the <par> with the caller
void Tree::intersect(const Tree& aGraph){

    //Number of nodes in the intersection cannot be larger than the number of nodes in the smaller graph
     int nofNodes=this->nofNodes<aGraph.nofNodes?this->nofNodes:aGraph.nofNodes;
     int i,j,k;
     Node* temp= new Node[nofNodes];

     k=0;

     //Iterate through both graph nodes and save the intersecting ones
     for(i=0;i<this->nofNodes;i++)
          for(j=0;j<aGraph.nofNodes;j++)
               if(this->nodes[i].getNodeName().compare(aGraph.nodes[j].getNodeName())==0){
                    this->nodes[i].intersect(aGraph.nodes[j]);
                    temp[k]=nodes[i];
                    k++;
               }


     //Restore the saved nodes to the calling objects array
     this->nofNodes=k;
     this->nodes= new Node[this->nofNodes];

     for(i=0;i<this->nofNodes;i++)
          this->nodes[i]=temp[i];

     opBuf=opBuf+"intersected with "+aGraph.name+"\n";
}

//Unite the graph in the <par> with the caller
void Tree::unite(const Tree& aGraph){

     int nofNodes=this->nofNodes+aGraph.nofNodes;
     int i,k,indice;

     Node* temp= new Node[nofNodes];

     k=0;

     //Iterate through both nodes adjacents and save all the nodes
     for(i=0;i<this->nofNodes;i++){
          indice=(const_cast <Tree*> (&aGraph))->containsNode(this->nodes[i].getNodeName());
          if(indice>=0)
               this->nodes[i].unite(aGraph.nodes[indice]);
          temp[k]=this->nodes[i];
          k++;
     }

     for(i=0;i<aGraph.nofNodes;i++)
         //Don't save if already saved
          if(this->containsNode(aGraph.nodes[i].getNodeName())<0){
               temp[k]=aGraph.nodes[i];
               k++;
          }

     //Restore the saved adjacents to the calling objects array
     this->nofNodes=k;
     this->nodes= new Node[this->nofNodes];

     for(i=0;i<this->nofNodes;i++)
          this->nodes[i]=temp[i];

     opBuf=opBuf+"united with "+aGraph.name+"\n";
}

//Accept the traversal in the <par> and send itself as a parameter
void Tree::acceptTraverse(Traversal* traverser){
    cout<<"Tree: "<<traverser->traverse(*this)<<endl;
}
