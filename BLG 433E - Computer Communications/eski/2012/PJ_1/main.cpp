#include "Station.h"
#include "Transmission.h"
#include <fstream>
#include <string>

#define INPUTFILE1	"data1.txt"		//Anyone can change the input files and their names
#define INPUTFILE2	"data2.txt"			//with changing these lines
#define INPUTFILE3	"data3.txt"

#define NUMBEROFDATA1 22
#define NUMBEROFDATA2 21
#define NUMBEROFDATA3 21
#define NUMBEROFSTATIONS 64		//As given in the HW description

#define TIMEINTERVAL 0.015625	// 1/64sn = 0.015625sn
#define BANDWIDTH 4096		// 4MHz = 4096 kHz
#define KILOBYTE 1024		

void read_from_file(Station *, string, int, int);	//Reading given files to Station class

void FDM(Station *, Transmission *);
bool FDMDemultiplex(Transmission *, Station *);

void TDM(Station *, Transmission *);
void TDMDemultiplex(Transmission *, Station *, int, int);

void createHadamard(int [][NUMBEROFSTATIONS]);

void CDM(Station *, Transmission *, int);

int main(){
	Transmission *tr = new Transmission();
	Station *st = new Station[NUMBEROFSTATIONS];

	int hadamardMatrix[NUMBEROFSTATIONS][NUMBEROFSTATIONS];
	createHadamard(hadamardMatrix);

	for(int hMCount=0; hMCount<NUMBEROFSTATIONS; hMCount++)
		for(int arrayCount=0; arrayCount<NUMBEROFSTATIONS; arrayCount++){
			if( hadamardMatrix[hMCount][arrayCount] == 1)
				st[hMCount].CDMChip[arrayCount] = -1;
			else
				st[hMCount].CDMChip[arrayCount] = 1;
		}

	read_from_file(st, INPUTFILE1, 0, NUMBEROFDATA1);
	read_from_file(st, INPUTFILE2, NUMBEROFDATA1, NUMBEROFDATA2);
	read_from_file(st, INPUTFILE3, NUMBEROFDATA1+NUMBEROFDATA2, NUMBEROFDATA3);

	cout << "\n Size of data1.txt : " << st[0].transmitDatas.size();
	cout << "\n Size of data2.txt : " << st[25].transmitDatas.size();
	cout << "\n Size of data3.txt : " << st[50].transmitDatas.size();

	FDM(st, tr);
	tr->c.clear();

	TDM(st, tr);
	tr->c.clear();
		
	int numOfBit;
    cout << "Please enter the number for number of bit to send with CDM \n";
	cin >> numOfBit;
	CDM(st, tr, numOfBit);
	tr->c.clear();

	getchar();
	getchar();
	return 0;
}

void CDMDemultiplex(Transmission *t, Station *s){
	int multiple[64];
	for(int i=0; i<NUMBEROFSTATIONS; i++){
		multiple[i] = 0;
		for(int j=0; j<NUMBEROFSTATIONS; j++){
			multiple[i] += (t->transmit[j] * s[i].CDMChip[j]);
		}
		if(multiple[i]/NUMBEROFSTATIONS > 0){		// It sent 1
			t->c.push_back('1'); 
		}
		else if(multiple[i]/NUMBEROFSTATIONS < 0){	// It sent 0
			t->c.push_back('-1'); 
		}
		//else it does not send anything (sent #)		
	}
}

void CDM(Station *s, Transmission *t, int maxIndex){
	int sum;
	for(int count=0; count<maxIndex; count++){
		for(int i=0; i<NUMBEROFSTATIONS; i++){
			sum = 0;
			for(int j=0; j<NUMBEROFSTATIONS; j++){
				if(s[j].transmitDatas[count] == '1')	//if controls for adding itself or reverse 
					sum += s[j].CDMChip[i];
				else if(s[j].transmitDatas[count] == '0')
					sum += (-1) * s[j].CDMChip[i];
			}
			t->transmit[i] = sum;
		}
		CDMDemultiplex(t, s);
	}
}

void createHadamard(int hM[][64]){
	/*
	This function is creating HadamardMatrix and saving it into given 2 dimensional array parameter
	*/
	hM[0][0] = 0;
	int say = 2;
	int H7[NUMBEROFSTATIONS][NUMBEROFSTATIONS];
	while(say <= NUMBEROFSTATIONS){	//till getting 64*64 hardamard matrix
		for(int i=0; i<say; i++){		
			for(int j=0; j<say; j++){
				if(i<say/2 && j<say/2)	//for first rows&columns of matrices
					H7[i][j] = hM[i][j];
				else{
					if(i>=say/2 && j>=say/2){	//for last rows&columns of matrices
						if(hM[i-say/2][j-say/2] == 1)	//take reverse of Hn
							H7[i][j] = 0;	
						else
							H7[i][j] = 1;
					}
					else if(i>=say/2){		//just change the index of hM
						H7[i][j] = hM[i-say/2][j];
					}
					else
						H7[i][j] = hM[i][j-say/2];
				}
			}
		}
		for(int say1=0; say1<say; say1++){
			for(int say2=0; say2<say; say2++){				
				hM[say1][say2] = H7[say1][say2];
			//	cout << hM[say1][say2] << " ";	//For controlling the matrices
			}
		}	
		say = say*2;
	}
}

void FDM(Station *s, Transmission *t){
	int i = 0, bitGetterCounter = 0;
	t->frequencyInterval.push_back(i);
	int frequencyInterval = BANDWIDTH / Station::fqBand;
	for(int i=0; i<NUMBEROFSTATIONS; i++){
		for(int bitCounter=0; bitCounter<Station::fqBand*KILOBYTE; bitCounter++){
			if(bitCounter == s[i].transmitDatas.size())
				bitGetterCounter = bitCounter;
			t->c.push_back(s[i].transmitDatas[bitCounter - bitGetterCounter]);
		}
		if( i != 0)		//just for keeping frequency interval for each transmission station
			t->frequencyInterval.push_back(t->frequencyInterval[i-1] + frequencyInterval);
	}
	//After filling all inputs to transmission 't'
	FDMDemultiplex(t, s);	//Then demult it
}

bool FDMDemultiplex(Transmission *t, Station *s){
	int i = 0, bitGetterCounter = 0, transmissionCounter = 0;
	bool isValid = true;
	Station *s1 = new Station();	Station *s2 = new Station();	Station *s3 = new Station();
	int frequencyInterval = BANDWIDTH / Station::fqBand;
	for(int i=0; i<NUMBEROFSTATIONS; i++){
		for(int bitCounter=0; bitCounter<Station::fqBand*KILOBYTE; bitCounter++){
			if(bitCounter == s[i].transmitDatas.size())	//if it exceeds our vector(which is created with data.txt files) size
				bitGetterCounter = bitCounter;
			if(t->c[transmissionCounter] != s[i].transmitDatas[bitCounter - bitGetterCounter])	//if there is any error
				isValid = false;

			if(t->c[transmissionCounter] != '#' && i<NUMBEROFDATA1)	//data1.txt 
				s1->transmitDatas.push_back(t->c[transmissionCounter]);
			if(t->c[transmissionCounter] != '#' && i<NUMBEROFDATA1+NUMBEROFDATA2)	//data2.txt
				s2->transmitDatas.push_back(t->c[transmissionCounter]);
			else if(t->c[transmissionCounter] != '#')	//data3.txt
				s3->transmitDatas.push_back(t->c[transmissionCounter]);

			transmissionCounter++;
		}
	}
	cout << "Efficiency of data1.txt source type with FDM is : " << 
		(s1->transmitDatas.size()/NUMBEROFDATA1)/s[0].transmitDatas.size() << endl;
	cout << "Efficiency of data2.txt source type with FDM is : " << 
		(s2->transmitDatas.size()/NUMBEROFDATA2)/s[NUMBEROFDATA1].transmitDatas.size() << endl;
	cout << "Efficiency of data3.txt source type with FDM is : " << 
		(s3->transmitDatas.size()/NUMBEROFDATA3)/s[NUMBEROFDATA1+NUMBEROFDATA2].transmitDatas.size() << endl;

	return isValid;		//return back to success(true) or failure(false)
}

void TDM(Station *s, Transmission *t){
	int i = 0, bitGetterCounter = 0;
	int transmissionCounter = 0;
	double maxData = TIMEINTERVAL * BANDWIDTH;	
	Station *newStations1 = new Station[NUMBEROFDATA1];
	Station *newStations2 = new Station[NUMBEROFDATA2];
	Station *newStations3 = new Station[NUMBEROFDATA3];
	for(int i=0; i<NUMBEROFSTATIONS; i++){	//64 stations will transmit data accordingly
		for(int bitCounter=0; bitCounter< maxData * KILOBYTE; bitCounter++){		//64K data for each time interval 
			if(bitCounter == s[0].transmitDatas.size())
				bitGetterCounter = bitCounter;
			t->c.push_back(s[i].transmitDatas[bitCounter - bitGetterCounter]);
		}
		if(i < NUMBEROFDATA1)
			TDMDemultiplex(t, newStations1, i, transmissionCounter++);
		else if(i < NUMBEROFDATA1 + NUMBEROFDATA2)
			TDMDemultiplex(t, newStations2, i, transmissionCounter++);
		else 
			TDMDemultiplex(t, newStations3, i, transmissionCounter++);

	}

	cout << "Efficiency of data1.txt source type with TDM is : " << 
		s[0].transmitDatas.size()/newStations1[0].transmitDatas.size() << endl;
	cout << "Efficiency of data2.txt source type with TDM is : " << 
		s[NUMBEROFDATA1].transmitDatas.size()/newStations2[0].transmitDatas.size() << endl;
	cout << "Efficiency of data3.txt source type with TDM is : " << 
		s[NUMBEROFDATA1+NUMBEROFDATA2].transmitDatas.size()/newStations3[0].transmitDatas.size() << endl;

}

void TDMDemultiplex(Transmission *t, Station *newSt, int order, int tCounter){
	if(t->c[tCounter] != '#')
		newSt[order].transmitDatas.push_back(t->c[tCounter]);
}

void read_from_file(Station *s, string inputFile, int startOfArray, int endOfArray){
	/* This function open input file with given inputName parameter,
	   and assign each item to structure array. */
	ifstream read;
	char f;
	read.open(inputFile, ios::in);
		if (read.fail()) {	
		  cerr << "Could not open file ";
		  cerr << inputFile;
		  cerr << ".\n";
		  return;
		  }
		while(!read.eof()){
			read >>  f;
			for(int i=startOfArray; i<endOfArray+startOfArray; i++){	//loop variables determines the position
				s[i].transmitDatas.push_back(f);						//of current char in the station array
			}
		} 
	read.close();
}