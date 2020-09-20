#include "Node.h"
#include "Graph.h"

//Construct an empty graph
Graph::Graph(){
     char num[3];                       //buffer to hold graph number
     sprintf(num,"%d",Graph::nOfGraphs);

     Graph::nOfGraphs++;
     name="graph";
     name=name+num;

     graphFile= new fstream((name+".dat").c_str(), ios::out);
     nofNodes=0;
     nodes=NULL;
}

//Construct a graph with <par> number of arbitrary nodes
Graph::Graph(int nofNodes){
     char nodeName[2]={'\0','\0'};          //buffer to hold each node's name
     char num[3];
     sprintf(num,"%d",Graph::nOfGraphs);

     Graph::nOfGraphs++;
     name="graph";
     name=name+num;

     graphFile= new fstream((name+".dat").c_str(), ios::out );
     this->nofNodes=0;

     for(int i=0;i<nofNodes;i++){
          nodeName[0]=65+i;         //Start giving ASCII names from 'A'(65)
          addNode(nodeName);
     }
}

//Construct a graph, reading its contents from a file
Graph::Graph(string fileName){
     char *p,*r;

     Graph::nOfGraphs++;

     nofNodes=0;
     string line;

    graphFile= new fstream(fileName.c_str(), ios::in | ios::out | ios::app);

     if (graphFile->is_open())
     {
         //Get graph name
          getline((*graphFile),line);
          this->name=line.substr(6,line.size()-6);

          //Get nodes
          getline((*graphFile),line);
          p = strtok(const_cast <char*> (line.c_str())," \r\n");
          while (p) {
               addNode(p);
               p = strtok(NULL, " \r\n");
          }

          //Get edges
          while (!graphFile->eof() )
          {
               getline((*graphFile),line);
               if(line.find("-")!=string::npos){
                    p = strtok(const_cast <char*> (line.c_str()), "-\r\n");
                    r = strtok(NULL, "-\r\n");
                    addEdge(p,r);
               }
          }

     }
     else
          cout << "Unable to open file";
}

//Copy constructor of a graph
Graph::Graph(const Graph& aGraph){
     char num[3];
     sprintf(num,"%d",Graph::nOfGraphs);

     Graph::nOfGraphs++;
     name="graph";
     name=name+num;

     graphFile= new fstream((name+".dat").c_str(), ios::out );

     this->nofNodes=0;

     //Reconstruct nodes and edges. Just copying references won't do.
     for(int i=0;i<aGraph.nofNodes;i++)
          this->addNode(aGraph.nodes[i].getNodeName());

     for(int i=0;i<aGraph.nofNodes;i++)
          for(int j=0;strcmp(aGraph.nodes[i].getAdjacent(j).c_str(),"")!=0;j++)
               this->addEdge(aGraph.nodes[i].getNodeName(),aGraph.nodes[i].getAdjacent(j));

}

//Destruct the graph writing the operations buffer to a file.
Graph::~Graph(){


     if(graphFile->is_open())
     {
         if(graphFile->eof())
             graphFile= new fstream((name+".dat").c_str(), ios::out );

          (*graphFile) << toString();
          (*graphFile) << "----------------------------"<<endl;
          (*graphFile) << opBuf<<endl;
          graphFile->close();
     }
     else
          cout << "Unable to open file";

}

//Get graph name
string Graph::getGraphName(){
     return name;
}

//look for a node named <par>. Return its indice if present. Return -1 if not.
int Graph::containsNode(string s){
     int i;

     for(i=0;i<nofNodes;i++)
          if(nodes[i].getNodeName().compare(s)==0)
               return i;
     return -1;

}

//delete a node from the graph
bool Graph::deleteNode(string nodeName){
     int index,i,j;

     index=containsNode(nodeName);

     //If the node doesn't exist, return doing nothing
     if(index<0)
          return false;

     opBuf=opBuf+"node "+nodeName+" has been deleted\n";

     //Create a backup for the original nodes
     Node* temp=new Node[nofNodes-1];

     //Copy nodes except the one to be deleted
     for(i=0,j=0;i<nofNodes;i++)
          if(i!=index){
               nodes[i].deleteAdjacent(nodes[index]);
               temp[j]=nodes[i];
               j++;
          }

     //Get a smaller space
     nodes= new Node[--nofNodes];

     //Restore the backup
     for(i=0;i<nofNodes;i++)
          nodes[i]=temp[i];

     return true;

}

//add a node to the graph
bool Graph::addNode(string nodeName){

     int i;

      //If the node already exists, return doing nothing
     if(containsNode(nodeName)>=0)
          return false;

     opBuf=opBuf+"node "+nodeName+" has been added\n";

     //Create a backup for the original nodes
     Node* temp=new Node[++nofNodes];

     //Copy nodes
     for(i=0;i<nofNodes-1;i++)
          temp[i]=nodes[i];

      //add the new node
     temp[i]=Node(nodeName);

     //Get a larger space
     nodes= new Node[nofNodes];

     //Restore the backup
     for(i=0;i<nofNodes;i++)
          nodes[i]=temp[i];

     return true;
}

//add an edge to the graph indicated by <par1> and <par2>
bool Graph::addEdge(string aNode,string bNode){

     int aNodeInd,bNodeInd;

     //If both of the nodes exist in the graph
     aNodeInd=containsNode(aNode);
     bNodeInd=containsNode(bNode);
     if(aNodeInd<0 || bNodeInd<0)
          return false;

     //add both as adjacents to the other
     opBuf=opBuf+"edge "+aNode+"-"+bNode+" has been added\n";
     nodes[aNodeInd].addAdjacent(nodes[bNodeInd]);
     nodes[bNodeInd].addAdjacent(nodes[aNodeInd]);

     return true;
}

//delete an edge to the graph indicated by <par1> and <par2>
bool Graph::deleteEdge(string aNode,string bNode){

     int aNodeInd,bNodeInd;

     //if both nodes exist
     aNodeInd=containsNode(aNode);
     bNodeInd=containsNode(bNode);

     if(aNodeInd<0 || bNodeInd<0)
          return false;

     //delete each node from the other's adjecent list
     if(!nodes[aNodeInd].deleteAdjacent(nodes[bNodeInd]))
          return false;

     if(!nodes[bNodeInd].deleteAdjacent(nodes[aNodeInd]))
          return false;

     opBuf=opBuf+"edge "+aNode+"-"+bNode+" has been deleted\n";

     return true;
     }

//return a string representation of a graph
string Graph::toString(){
     string graph;

     //put allthe node names in
     graph="graph "+name+"\n";
     for(int i=0;i<nofNodes;i++){
          graph=graph+nodes[i].getNodeName();
          if(i!=nofNodes-1)
               graph=graph+" ";
     }
     graph=graph+"\n";

     //put all the edges in
     for(int i=0;i<nofNodes;i++)
          graph=graph+nodes[i].toString();

     return graph;
}

//Intersect the graph in the <par> with the caller
void Graph::intersect(const Graph& aGraph){

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
void Graph::unite(const Graph& aGraph){

     int nofNodes=this->nofNodes+aGraph.nofNodes;
     int i,k,indice;

     Node* temp= new Node[nofNodes];

     k=0;

     //Iterate through both nodes adjacents and save all the nodes
     for(i=0;i<this->nofNodes;i++){
          indice=(const_cast <Graph*> (&aGraph))->containsNode(this->nodes[i].getNodeName());
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

//Get number of Nodes in the graph
int Graph::getNumOfNodes(){
    return nofNodes;
}

//Get node numbered <par>
Node* Graph::getNode(int i){
    return &nodes[i];
}

//Get node named <par>
Node* Graph::getNode(string s){
    for(int i=0;i<nofNodes;i++)
        if(nodes[i].getNodeName()==s)
            return &nodes[i];
    return NULL;
}

//Accept the traversal in the <par> and send itself as a parameter
void Graph::acceptTraverse(Traversal* traverser){
    cout<<"Graph: "<<traverser->traverse(*this)<<endl;
}

//Query if the graph accepts DF traversal 
bool Graph::acceptsDF(){
    return true;
}
