/********************************************************************************
*	Name Surname: Aykut Akin													*
*	Number		: 040080177														*
*	Due Date	: 23.03.2011													*
*																				*
*	Every information about functions and classes can be found in report		*
*																				*
*********************************************************************************/

#include "Heap.h"

Heap::Heap(string optimal,string fileName, string wfileName, string wNum){
	
	if(fileName[4] == '5')
		heapSize = 5;
	if(fileName[6] == '.')
		heapSize = 10;
	if(fileName[4] == '2')
		heapSize = 20;
	if(fileName[7] == '.')
		heapSize = 100;

	for(int i=1; i<=heapSize; i++)
		engagements[i] = 0;

	roots = new int* [heapSize+1];
	readData(fileName);

	char o;
	if(optimal.compare("GSW")==0)
		o = 'w';
	else
		o = 'm';

	if(fileName[2] == o){
		count = new int[heapSize+1];

		for(int i=1; i<=heapSize; i++)
			count[i] = 0;
		inverse = NULL;
	}
	else{
		inverse = new int* [heapSize+1];
		for(int i=0; i<=heapSize; i++)
			inverse[i] = new int [heapSize+1];
		
		for(int i=1; i<=heapSize; i++)
			for(int j=1; j<=heapSize; j++)
				inverse[i][prefList[i][j]] = j;
		count = NULL;
	}

	if(wfileName.compare("")!=0 && wNum.compare("")!=0){
		wealth = new int[heapSize+1];
		readwData(wfileName,wNum);
	}
}

Heap::~Heap(){
	if(count)
		delete[] count;
	if(inverse){
		for (int i=0; i<=heapSize; ++i)
			delete [] inverse[i];
		 delete [] inverse;
	}
	delete [] roots;
}

void Heap::readData(string fileName){
	
	string filename = "data/"+fileName;
	ifstream infile (filename.c_str());//open file
	int person=1, num=1;

	if(!infile.is_open())
		cout << "Unable to open file"<<endl; 

	else{
		while(infile >> prefList[person][num]){
			
			if(num == 1)
				roots[person] = &prefList[person][num];

			if(num < heapSize)
				num++;
			else{
				person++;
				num=1;
			}
		}
		
		infile.close();
	}
}

void Heap::readwData(string wfileName,string num){

	string filename = "data/wealth"+num.substr(2,1)+"/"+wfileName;
	ifstream infile (filename.c_str());//open file
	int person=1;

	if(!infile.is_open())
		cout << "Unable to open file"<<endl; 

	else{
		while(infile >> wealth[person])
				person++;
		
		infile.close();
	}
}

void Heap::writeData(string fileName, int time)
{
	mkdir("./output", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	string filename = "output/"+fileName;
	ofstream outfile(filename.c_str());			
	int i=1;
	int countsum=0;

	if (!outfile.is_open())
		cout << "Unable to open file"<<endl;

	else{
		while(i <= heapSize){
			countsum += count[i];
			outfile << "	";
			outfile << i << "	";
			outfile << engagements[i++] << endl;		
		}
		outfile << endl << "time = "<< time << " ms"<<endl;
		outfile <<"count sum = "<< countsum;
		outfile.close();
	} 
}

int Heap::getHeapSize(){
	return heapSize;
}