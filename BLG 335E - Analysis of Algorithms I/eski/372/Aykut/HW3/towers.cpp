/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 09.05.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#include "towers.h"

Towers::Towers(string fileName){
	readData(fileName);
	
	// build array of blocks in all 3 orientations
	for(int i=0; i<towerList.size(); i++){
		int n = towerList[i]->numofblocks; // number of blocks for each tower
		for(int j=0; j<towerList[i]->numofblocks; j++){
			towerList[i]->blockList[j+n].x = towerList[i]->blockList[j].y;
			towerList[i]->blockList[j+n].y = towerList[i]->blockList[j].h; 
			towerList[i]->blockList[j+n].h = towerList[i]->blockList[j].x;
			towerList[i]->blockList[j+2*n].x = towerList[i]->blockList[j].h;
			towerList[i]->blockList[j+2*n].y = towerList[i]->blockList[j].x; 
			towerList[i]->blockList[j+2*n].h = towerList[i]->blockList[j].y;
		}
	}
}

void Towers::setGraphWithTopOrder(){

	for(int i=0; i<towerList.size(); i++){
		Graph* graph0 = new Graph;// Create graph
		graph0->numofnodes = towerList[i]->numofblocks*3; 

		for(int j=0; j<graph0->numofnodes; j++) 
			graph0->nodeList[j].adj.clear();// Graph has no member

		for(int j=0; j<graph0->numofnodes; j++){ 
			for(int k=0; k<graph0->numofnodes; k++){
				if (towerList[i]->blockList[j].x < towerList[i]->blockList[k].x && 
					towerList[i]->blockList[j].y < towerList[i]->blockList[k].y || 
					towerList[i]->blockList[j].x < towerList[i]->blockList[k].y && 
					towerList[i]->blockList[j].y < towerList[i]->blockList[k].x){
						graph0->nodeList[j].adj.push_back(k); // If block is strictly larger add as an adjacent
				}
			}
		}

		graphList.push_back(graph0);
		TopOrderedList.push_back(toporder(i));
		assert(static_cast<int>(TopOrderedList[i].size()) == graph0->numofnodes);
	}
}

vector<int> Towers::toporder(int num){// Order the graph according to their counts
	int n = graphList[num]->numofnodes;// count is a frequency of nodes
    vector<int> result;				// If a node1 is adjacent of other node2, its(node1) count=count+1
    vector<int> free;
    result.reserve(n);
    free.reserve(n);

    for(int i=0; i<n; i++)
		graphList[num]->nodeList[i].count = 0;

    for(int i=0; i<n; i++){
		for(int j=0; j<graphList[num]->nodeList[i].adj.size(); j++)
			graphList[num]->nodeList[graphList[num]->nodeList[i].adj[j]].count++;
	}

    for(int i=0; i<n; i++) {
		if (graphList[num]->nodeList[i].count == 0) 
			free.push_back(i);
	}

    for(int ii=0; ii<free.size(); ii++){
        int i = free[ii];
        result.push_back(i);
        for(int jj=0; jj<graphList[num]->nodeList[i].adj.size(); jj++){
            int j = graphList[num]->nodeList[i].adj[jj];
            graphList[num]->nodeList[j].count--;
            assert(graphList[num]->nodeList[j].count >= 0);
            if (graphList[num]->nodeList[j].count == 0) 
				free.push_back(j);
        }
    }

    for(int i=0; i<n; i++){  
		if (graphList[num]->nodeList[i].count > 0) 
			return vector<int>(); // graph cyclic
	}

    return result;
}

bool sortFunc (Block b1, Block b2){ return b1.y < b2.y;}

void Towers::getAnswers(){
	for(int k=0; k<TopOrderedList.size(); k++){
			
		int* m = new int[graphList[k]->numofnodes]; // includes maximum heights for each block
		int** n; // includes which block is added to other block 
		n = new int*[graphList[k]->numofnodes];
		for(int i=0; i<graphList[k]->numofnodes; i++)
			n[i] = new int[graphList[k]->numofnodes];

		for(int i=0; i<graphList[k]->numofnodes; i++){
			m[i] = 0;
			for(int j=0; j<graphList[k]->numofnodes; j++)
				n[i][j] = 0;
		}

		int ans = 0; int num=0;

        for(int x=graphList[k]->numofnodes-1; x>=0; x--){
			int i = TopOrderedList[k][x];//take a block
			m[i] = towerList[k]->blockList[i].h;//add its own h to itself
			n[i][i] = 1;//block[i] is added
            int add = 0;
			for(int y=0; y<graphList[k]->nodeList[i].adj.size(); y++){// look for adjacent of block[i]				
                int j = graphList[k]->nodeList[i].adj[y];
				if(m[j] > add){// if we can can grow the wall with adding adjacent j, add adjacent to height
					add = m[j];//----------------------memoization is done with using array m----------------------
					for(int z=0; z<graphList[k]->numofnodes; z++){
						if(n[j][z]==1)//if we add an adjacent then we add its adjacents too
							n[i][z]=1;
					}			
				}
            }
            m[i] += add;
			if(m[i] > ans){
				ans = m[i];
				num = i;//maximum answer's slot
			}
        }
        cout<<"Max height = "<<ans<<endl;
		vector<Block> answer;
		for(int i=0; i<graphList[k]->numofnodes; i++){
			if(n[num][i]==1)//add blocks which are used in maximum solution
				answer.push_back(towerList[k]->blockList[i]);
		}
		sort(answer.begin(),answer.end(),sortFunc);
		for(int i=0; i<answer.size(); i++)
			cout<< answer[i].x <<" " << answer[i].y << " " << answer[i].h << endl;
		cout << "////////////////////////////"<<endl;
	}
}

void Towers::readData(string fileName){
	ifstream infile (fileName.c_str());//open file
	int num;

	if(!infile.is_open())
		cout << "Unable to open file"<<endl; 

	else{
		while(infile >> num){

			if(num==0)
				break;

			else{
				Blocks* blocks0 = new Blocks;
				blocks0->numofblocks = num;
				for(int i=0; i<num; i++){					
					infile >> blocks0->blockList[i].x;
					infile >> blocks0->blockList[i].y;
					infile >> blocks0->blockList[i].h;
				}
				towerList.push_back(blocks0);
			}		
		}
		infile.close();
	}
}