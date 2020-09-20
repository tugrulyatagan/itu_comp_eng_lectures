#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <math.h>  
#include <stdlib.h> 
#define PI 3.14159265 // pi number
#define RoE 6373 // radius of Earth
#define OUTPUT "output.txt" // output file name

using namespace std;

float ar_lat; // latitude taken from command line argument
float ar_lon; // longtitude taken from command line argument

class City{
public:
	string name;
	float latitude;
	float longitude;
	float distance;
	City(string name, float latitude, float longitude);
	float CalculateDistance(float lat1, float lon1, float lat2, float lon2);
};

void print(City **, int); // funciton prototypes
void writeFile(City **, int );
void InsertionSort(City **, int );
void Merge(City **, int , int, int); // merge function for merge sort algorithm
void MergeSort(City **, int, int);
void LinearSearch(City **, int ,int);

City::City(string n, float la, float lo){ // constructer
	name = n;
	latitude = la;
	longitude = lo;
	distance = CalculateDistance(latitude, longitude, ar_lat, ar_lon); // distance from the desired point
}

float City::CalculateDistance(float lat1, float lon1, float lat2, float lon2){
	float dlon = lon2 - lon1;
	float dlat = lat2 - lat1;
	float a = pow((sin((dlat/2)*PI/180)), 2) + cos((lat1)*PI/180) * cos((lat2)*PI/180) * pow(((sin(dlon/2))*PI/180), 2);
	float c = 2 * atan2((sqrt(a))*PI/180, (sqrt(1-a))*PI/180);
	float d = RoE * c; // RoE: radius of Earth
	return d;
}

void print(City **A, int K){ // print list to screen
	for(int i =0;i<K;i++)
		cout << A[i]->name << "\t" << A[i]->latitude << "\t" << A[i]->longitude << endl;
	cout << endl;
}

void writeFile(City **A, int K){ // write output to file
	ofstream file;
	file.open(OUTPUT, ios::out);
	for(int i =0;i<K;i++)
		file << A[i]->name << "\t" << A[i]->latitude << "\t" << A[i]->longitude << endl;
}

void InsertionSort(City **A, int N) {
	for (int j = 1; j < N; j++ ) {
		City *key = A[j];
		int i = j - 1;
		while ((i >= 0) && (A[i]->distance > key->distance))
			A[i+1] = A[i--];
		A[i+1] = key;
	} 
}

void Merge(City **A, int p, int q, int r)
{
	int n1 = q - p;
	int n2 = r - q;
	City **L = new City*[n1];
	City **R = new City*[n2];
	for (int i = 0; i < n1; i++) 
		L[i] = A[p + i];
	for (int j = 0; j < n2; j++)
		R[j] = A[q + j]; 
	int i = 0, j = 0, k = 0;
	for ( k = p; i < n1 && j < n2; k++){
		if ( L[i]->distance < R[j]->distance )
			A[k] = L[i++];
		else 
			A[k] = R[j++];
	}
	for ( ; i < n1; k++, i++) 
		A[k] = L[i];
	for ( ; j < n2; k++, j++) 
		A[k] = R[j];
	delete[] L; 
	delete[] R;
}

void MergeSort(City **A, int p, int r){
	if (r > p + 1){
		int q = (p + r) / 2;
		MergeSort(A, p, q);
		MergeSort(A, q, r);
		Merge(A, p, q, r);
	}
}

void LinearSearch(City **A, int N, int K){
	City **Result = new City*[K];
	for (int i = 0; i < K;i++){ // for all elemnts in the result list
		int m = -1;
		for (int j = 0; j < N;j++) // scan all input elements
			if ((A[j] != NULL && m == -1) || (A[j] != NULL && A[j]->distance < A[m]->distance))
				m = j;
		Result[i] = A[m];
		A[m] = NULL;
	}
	for(int i = 0; i < K; i++) // assign result to A array
		A[i] = Result[i];
	delete[] Result;
}


int main(int argc, char* argv[]){
	if (argc != 6){
		cout << "Invalid arguments." << endl;
		return -1;
	}
	int N = atoi(argv[1]);
	int K = atoi(argv[2]);  
	string mode = argv[3];
	ar_lat = atof(argv[4]);
	ar_lon = atof(argv[5]);

	if (K > N){
		cout << "K can not be biger than N" << endl;
		return -1;
	}

	City **cities = new City*[N];
	
	string line;
	ifstream myfile("location.txt");
	if(myfile.is_open())
	{
		for (int i = 0; i < N; i++)
		{
			getline(myfile, line);
			unsigned pos = line.find("\t"); 
			string city_name = line.substr(0,pos);
			line = line.substr(pos+1);
			pos = line.find("\t");
			float latitude = atof(line.substr(0,pos).c_str());
			line = line.substr(pos+1);
			float longitude = atof(line.substr(0,pos).c_str());
			cities[i] = new City(city_name, latitude, longitude);
		} 
		myfile.close();
	}
	else{ 
		cout << "File could not be opened." << endl;
		return -1;
	}

	clock_t t = clock();


	if (mode == "insertion")
		InsertionSort(cities, N);
	else if (mode == "merge")
		MergeSort(cities, 0, N);
	else if (mode == "linear")
		LinearSearch(cities, N, K);
	else{
		cout << "Invalid algorithm type";
		return -1;
	}

	t = clock() - t;

	//print(cities, K); // for printing results to screen
	cout << "Clock: " << t << endl << endl;
	writeFile(cities, K);

	delete[] cities;
	return 0;
}
