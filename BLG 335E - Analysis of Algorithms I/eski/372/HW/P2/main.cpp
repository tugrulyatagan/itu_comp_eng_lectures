/************************************************************
*	Name Surname		: Abdullah AYDEÐER					*
*   Number				: 040090533							*
*	E-mail				: aydeger@itu.edu.tr				*
*	Lecture				: Analysis of Algorithms (BLG372E)	*
*	Lecturer			: Zehra ÇATALTEPE					*
*	Assistant			: A.Aycan ATAK						*
*	Project Number		: 2									*
*	Due Date			: 04.05.2012						*
*************************************************************/

#include <fstream>
#include <time.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <stdlib.h> 
#include <deque>
#include <vector>
#include <math.h>

#define MAXI 999999
#define MAXCHAR 50		//Maximum character of one line

using namespace std;

float greedyWordWrap(vector<string> &, int);

int dynamicWordWrap(vector<string> &, int, int, int *);

int fullDynamicWordWrap(vector<string> &, int, int, int *, int **);

int findMin(int, int);

double calculateCost(vector<string> &, int, int, int);

void calculateALL(vector<string> &words, int **, int);

double sendMyValue(int **, int, int, int);

int GetAvailableMemory(void){
	/************************************************************************************
	*	Function Name	  : GetAvailableMemory											*
	*	Aim to be written : Calculating the maximum amount of memory can be get 		*
	*	Parameters		  : --															*
	*	Return value      : integer that showing the amount								*
	*************************************************************************************/
	char *p,*q;
	int size = 1;
	q = p = (char *) calloc(1,size);
	while (q) {
		size = size*2; // Can be more to speed up things
		q = (char *)realloc(p,size);
		if (q)
		p = q;
	}
	free(p);
	return size;
}

int main(){
	ifstream read;
	string new_word;
	vector<string> words;	
	clock_t t1, t2, t3, t4;
	string inputName;
	cout << "Please enter the .txt file name\n";
	cin >> inputName;
	inputName += ".txt";
	int max_char_per_line = MAXCHAR;
	read.open(inputName,ios::in);
		if (read.fail()) {	
		  cerr << "Could not open file ";
		  cerr << inputName;
		  cerr << ".\n";
		  return 1;
		  }
		while(!read.eof()){
			read >> new_word;
			words.push_back(new_word);	//Adding all words from given text to the vector with name 'words'
		} 
	read.close();

	t1 = clock();
	float cost;
	//for(int i = 1; i <= 100; i++)
		 cost = greedyWordWrap(words, max_char_per_line);
	t2 = clock();
	cout << "COST WITH GREEDY: " << cost << endl;
	cout << "Time with GREEDY: " << t2-t1 << endl;
	cout << "Number of words: " << words.size() << endl;

	int *FN = new int[words.size()];
	for(int i=0; i<words.size(); i++)
		FN[i] = -2;
	
	int maxMemory = GetAvailableMemory();
	cout << "\n\nMax memory of system is nearly:" << maxMemory << " bytes " << endl;

		if( maxMemory*0.5 > words.size() * max_char_per_line ){		//If our memory can meet the demands(for guaranteeing 1/2 multiplying)
			cout << "\nMemory is enough for Fully Dynamic Programming \n";
			int **C;
			C = (int **) malloc(words.size() * sizeof(int *));
			if(C == NULL){
				fprintf(stderr, "out of memory\n");
				return 0;
			}

			for(int i=0; i< words.size(); i++){
				C[i] = (int *) malloc(max_char_per_line/3 *sizeof(int));
				if(C[i] == NULL){
					fprintf(stderr, "out of memory %d\n",i);
					return 0;
				}
			}

			calculateALL(words, C, max_char_per_line);	//Calculating all possible costs(if not exceed the MAXCHAR)
			t3 = clock();	
			fullDynamicWordWrap(words, max_char_per_line, words.size()-1, FN, C);
			t4 = clock();
			for(int i=0; i< words.size(); i++)	//After calculating necessary value
					delete C[i];	//Give taken memories back
			delete []C;
		}
		else{
			cout << "Memory is not enough. Therefore, running the code a little bit dynamic\n";
			t3 = clock();
			 dynamicWordWrap(words, max_char_per_line, words.size()-1, FN);
			t4 = clock();
		}
	
	int k, sums=0, t=0;
	for(k=words.size()-1; k>=0; k--){
		if(sums +words[k].length() < max_char_per_line){
			sums += words[k].length() +1;
			t++;
		}
		else
			break;
	}

	int min = FN[words.size() -2];
	for(int i=words.size()-3; i>=words.size()-t; i--){	//This loop calculates minumum possiblities of
															//if the last line do not want to be considered
		if(min > FN[i])											//(I think not not cleverly calculating)
			min = FN[i];
	}

	cout << "\nCost with dynamic " << min;
	
	cout << "\nTime with dynamic " << t4-t3;

	delete []FN;	//Give taken memory back
	getchar();
	getchar();
	return 0;
}

float greedyWordWrap(vector<string> &words, int mxpl ){
	int line_length = 0;
	float cost = 0;
	for(int iter = 0; iter< words.size(); iter++){	//For all words
		if((words[iter].length() + line_length) <= mxpl) {	//If does not exceeded current line's max length
			line_length = line_length + words[iter].length() + 1;	//add one more word
		}
		else{	//If new line needed
			cost += pow((mxpl - (line_length - 1.0)), 3);	//calculating cost
			line_length = words[iter].length() + 1;	//updating current line length
		}
	}
	return cost;
}

int dynamicWordWrap(vector<string> &words, int max_char_per_line, int j, int *FN){
	/****************************************************************************************
	*	Function Name	  : dynamicWordWrap													*
	*	Aim to be written : Calculating the optimal solution					 			*
	*	Parameters		  : All words, maximum character of one line, from beginning to		*
	*							where that will be calculated, array for dynamic calculates	*
	*	Return value      : integer that showing the amount									*
	****************************************************************************************/
	double minum;
	double cs = calculateCost(words, max_char_per_line, 0,j);
	if( FN[j] != -2)
		return FN[j];
	else{
		if( cs < MAXI){
			FN[j] = cs;	//memoization
			return FN[j];
		}
		else{
			minum = dynamicWordWrap(words, max_char_per_line, 0, FN) + calculateCost(words, max_char_per_line, 1, j);
			for(int i=1; i<j; i++){
				minum = findMin(minum, 
					dynamicWordWrap(words, max_char_per_line, i, FN) + calculateCost(words, max_char_per_line, i+1, j) );
			}
			FN[j] = minum;	//memoization
		}
	}
	return FN[j];
}

double calculateCost(vector<string> &words, int mxpl, int a, int b){
	/****************************************************************************************
	*	Function Name	  : calculateCost													*
	*	Aim to be written : Calculating the cost for words between a to b indexes 			*
	*	Parameters		  : All words, maximum character of one line, from beginning to		*
	*							calculation and end of the calculation						*
	*	Return value      : double that showing the calculation, if calculation exceeds		*
	*							maximum character amount of one line, then return MAXI		*
	****************************************************************************************/
	if( b-a > mxpl/3)	//Assuming any sentences can not be consisted of only '2' length words
		return MAXI;	//If given range is very high, then return MAXI quick

	int sumOfPart = 0;	//holding sum of part of range
	for(int i=a; i<=b; i++){
		sumOfPart += words[i].length();
		if(sumOfPart > mxpl)	//if exceed now, do not continue for loop more
			return MAXI;
	}
	if(sumOfPart + b-a > mxpl)	//After an addition the blank spaces, does it exceed max char?
		return MAXI;				//if yes, return MAXI

	return pow((mxpl-(b-a)-sumOfPart)*1.0, 3);	//if still no return from function, then return cube of ...
}

int findMin(int a, int b){
	/****************************************************************************************
	*	Function Name	  : findMin															*
	*	Aim to be written : Calculating the minumum between given 2 parameters 				*
	*	Parameters		  : 2 integer value													*
	*	Return value      : Return which integer is smaller									*
	****************************************************************************************/
	if(a<b)
		return a;
	else
		return b;
}

int fullDynamicWordWrap(vector<string> &words, int max_char_per_line, int j, int *FN, int **C){
	/************************************************************************************************
	*	Function Name	  : fullDynamicWordWrap														*
	*	Aim to be written : Calculating optimal cost with fully dynamic programming					*
	*	Parameters		  : All words, maximum char per line, number of last word,					*
	*							array and matrix for memoization									*
	*	Return value      : Return optimal cost														*
	*************************************************************************************************/
	double minum;
	double cs = calculateCost(words, max_char_per_line, 0,j);
	if( FN[j] != -2)	//If calculated before
		return FN[j];		//Return this value back
	else{
		if( cs < MAXI){
			FN[j] = cs;	//By writing this line, we can supply memoization
			return FN[j];
		}
		else{
			minum = dynamicWordWrap(words, max_char_per_line, 0, FN) + calculateCost(words, max_char_per_line, 1, j);	//Let's consider first possible is minumum
			for(int i=1; i<j; i++){
				minum = findMin(minum, 
					dynamicWordWrap(words, max_char_per_line, i, FN) + sendMyValue(C, i+1, j, max_char_per_line));
						//If next calculation is smaller than last minumum, then update minumum('minum')
			}
			FN[j] = minum;	//write minumum('minum' variable) to the array (memoization)
		}
	}
	return FN[j];
}

void calculateALL(vector<string> &words, int **C, int mxpl){
	/************************************************************************************************
	*	Function Name	  : calculateALL															*
	*	Aim to be written : Calculating the all possible C(i,j)'s	 								*
	*	Parameters		  : All words, pointer array(pointer to pointers), maximum char per line	*
	*	Return value      : Return which integer is smaller											*
	*************************************************************************************************/
	int a = 0;	//this is clever counter
	for(int i =0; i< words.size(); i++){	//From all elements of words
		for(int j=0; j< mxpl/3; j++){			//To 'mxpl/3' next to the actual 'i' value
			C[i][j] = calculateCost(words, mxpl, i, a);	//calculate and write to C matrix
			if( ++a == words.size() )	
				break;		//For last words, this is necessary
		}
		a = a - mxpl/3 + 1;
	}
}

double sendMyValue(int **C, int a, int b, int mxpl){
	/************************************************************************************************
	*	Function Name	  : sendMyValue																*
	*	Aim to be written : Determining the necessary calculation by using given parameters			*
	*	Parameters		  : All words, two integer for beginning and end of calculation,			*
	*									maximum char per line, 										*
	*	Return value      : Return optimal cost														*
	*************************************************************************************************/
	if(b-a >= mxpl/3)	//If exceed the limit of array
		return MAXI;		//return MAXI

	return C[a][b-a];	//Else, return necessary plot of matrix
}
	