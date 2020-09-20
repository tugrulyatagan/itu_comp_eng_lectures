//============================================================================
// Name			: 040100117.cpp
// Author		: Tugrul Yatagan
// Student Num	: 040100117
// Course		: BLG 372E Analysis of Algorithms
// CRN			: 22853
// Lecturer		: Zehra Cataltepe
// Date			: 18.03.2014
//============================================================================

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
using namespace std;

class Matching{ // base class for propose-reject algorithm
	int *proposable; // list of member who candiate for propose
	int *acceptable; // list of member who candiate for acceptance
	int currentPairNumber; // current number of pair
	int maxProposableNumber; // maximum number of propose list
	int maxPairNumber; // maximum number of pair list
protected:
	int maxAcceptanceNumber; // maximum number of acceptance list
public:
	int *pair; // pair list
	void setProposableList(int, int *); // initilazition for propoable list
	void setPairList(int); // initilazition for pair list
	void setAcceptableList(int, int *); // initilazition for accepatnce list
	int nextProposable(); // calculates next element suitable for propose
	void addToPair(int); // adds to pair list
	void removeFromPair(int); // removes pair list
	int getLastPair(); // returns pair
	int multiGetLastPair(); // return last piar for list
	bool accept(int); // checks if propse is acceptable
	bool multiAccept(int); // checks if propse is acceptable for list
	bool isFull(); // is pair list full
	bool isFree(); // is pair list emty
	Matching(); // constructor
};
Matching::Matching(){
	currentPairNumber = 0;
}
void Matching::setProposableList(int listCount, int *proList){
	proposable = new int[listCount];
	for (int i = 0; i < listCount; i++){
		proposable[i] = proList[i];
	}
	maxProposableNumber = listCount;
}
void Matching::setPairList(int pairNumber){
	pair = new int[pairNumber];
	for (int i = 0; i < pairNumber; i++){
		pair[i] = -1;
	}
	currentPairNumber = 0;
	maxPairNumber = pairNumber;
}
void Matching::setAcceptableList(int listCount, int *accList){
	acceptable = new int[listCount];
	for (int i = 0; i < listCount; i++){
		acceptable[i] = accList[i];
	}
	maxAcceptanceNumber = listCount;
}
int Matching::nextProposable(){
	for (int i = 0; i < maxProposableNumber; i++){
		if (proposable[i] != -1){
			int temp = proposable[i];
			proposable[i] = -1;
			return temp;
		}
	}
}
void Matching::addToPair(int newPair){
	for (int i = 0; i < maxPairNumber; i++){
		if (pair[i] == -1){
			currentPairNumber++;
			pair[i] = newPair;
			return;
		}
	}
}
void Matching::removeFromPair(int removed){
	for (int i = 0; i < maxPairNumber; i++){
		if (pair[i] == removed){
			currentPairNumber--;
			pair[i] =  -1;
		}
	}
}
int Matching::getLastPair(){
	return pair[0];
}

int Matching::multiGetLastPair() {
	int last = -1;
	for (int i = 0; i <= maxAcceptanceNumber; i++) {
		for (int j = 0; j < maxPairNumber; j++) {
			if ((acceptable[i] == pair[j]) && (last < i)) {
				last = i;
			}
		}
	}
	return acceptable[last];
}

bool Matching::accept(int newPair){
	for (int i = 0; i < maxAcceptanceNumber; i++) {
		if (acceptable[i] == newPair){
			maxAcceptanceNumber = i;
			return 1;
		}
	}
	return 0;
}
bool Matching::multiAccept(int newPair){
	if (currentPairNumber == maxPairNumber) {
		int last = -1;
		for (int i = 0; i <= maxAcceptanceNumber; i++) {
			for (int j = 0; j < maxPairNumber; j++) {
				if ((acceptable[i] == pair[j]) && (last < i)) {
					last = i;
				}
			}
		}
		maxAcceptanceNumber = last;
		for (int i = 0; i < maxAcceptanceNumber; i++) {
			if (acceptable[i] == newPair){
				return 1;
			}
		}
		return 0;
	}
	else {
		return 1;
	}
}
bool Matching::isFull(){
	return currentPairNumber == maxPairNumber;
}
bool Matching::isFree(){
	return currentPairNumber == 0;
}


class Lecturer: public Matching { // lecturer class inherited from matching
public:
	int courseNumber;
	int assistantPLNumber;
	int *courses; // course list
	int *assistantPL; // assistant preference list
	void addCourses(int, int *); // initilaziton for course list
	void addAssistantPL(int, int *); // initilaziton for assistant preference list
	bool searchCourse(int); // searchs course
	int calculateWeight(); // calculates weight for lecturer
};
void Lecturer::addCourses(int crsNumber, int *crs){
	courseNumber = crsNumber;
	courses = crs;
}
void Lecturer::addAssistantPL(int asstNum, int *asst){
	assistantPLNumber = asstNum;
	assistantPL = asst;
}
bool Lecturer::searchCourse(int searchCourse){
	for (int i = 0; i < courseNumber; i++){
		if (courses[i] == searchCourse){
			return 1;
		}
	}
	return 0;
}
int Lecturer::calculateWeight(){
	int sum = 0;
	for (int asst = 0; asst < assistantPLNumber; asst++){
		for (int crs = 0; crs < courseNumber; crs++ ){
			if (pair[crs] == assistantPL[asst]){
				sum += (assistantPLNumber - asst) * (assistantPLNumber - asst);
			}
		}
	}
	return sum;
}


class Assistant: public Matching {
public:
	int coursePLNumber; 
	int lecturerPLNumber;
	int *coursePL; // course preference list
	int *lecturerPL; // lecturer preference list
	void addCoursePL(int, int *); // initilaziton for course list
	void addLecturerPL(int, int *); // initilaziton for lecturer list
	int findInLecturerPL(int); // searches lecturere
	int calculateWeight(); // calculates weight for lecturer
};
void Assistant::addCoursePL(int crsNumber, int *newCoursePL){
	coursePLNumber = crsNumber;
	coursePL = newCoursePL;
}
void Assistant::addLecturerPL(int lctrNumber, int *newLecturerPL){
	lecturerPLNumber = lctrNumber;
	lecturerPL = newLecturerPL;
}
int Assistant::findInLecturerPL(int search){
	for (int i = 0 ; i < lecturerPLNumber; i++){
		if (lecturerPL[i] == search){
			return i;
		}
	}
	return -1;
}
int Assistant::calculateWeight(){
	for (int matchOrder = 0; matchOrder < lecturerPLNumber; matchOrder++ ){
		if(pair[0] == lecturerPL[matchOrder]){
			return (lecturerPLNumber - matchOrder) * (lecturerPLNumber - matchOrder);
		}
	}
}

int findFreeLecturer();
int findFreeAssistant();


Lecturer *lecturerList;
int lecturerNumber;
Assistant *assistantList;
int assistantNumber;

int main(int argc, char* argv[]) {
	if (argc != 7) { // there must be 7 arguments
		cerr << "Invalid arguments." << endl;
		return -1;
	}
	if (!strcmp(argv[1],"-i")){
		cerr << "Invalid input parameter." << endl;
		return -1;
	}
	if (!strcmp(argv[5],"-o")){
		cerr << "Invalid output parameter." << endl;
		return -1;
	}

	const char *CourseOfLecturersInputFileName = argv[2];
	const char *LecturersPLInputFileName = argv[3];
	const char *AssistantsPLInputFileName = argv[4];
	const char *GS_outOutputFileName = argv[6];

	ifstream CourseOfLecturersFile(CourseOfLecturersInputFileName);
	ifstream LecturersPLInputFile(LecturersPLInputFileName);
	ifstream AssistantsPLInputFile(AssistantsPLInputFileName);
	ofstream GS_outOutputFile(GS_outOutputFileName);

	if(CourseOfLecturersFile.is_open()){
		string stringLine;

		for (lecturerNumber = 0; getline(CourseOfLecturersFile, stringLine); lecturerNumber++ );
		CourseOfLecturersFile.clear();
		CourseOfLecturersFile.seekg(0, CourseOfLecturersFile.beg);

		lecturerList = new Lecturer[lecturerNumber];

		for(int rowNumber = 0; getline(CourseOfLecturersFile,stringLine); rowNumber++){
			Lecturer *lecturer = new Lecturer;
			int numberCountInRow;
			int intLine[10];
			istringstream is(stringLine);
		    for( numberCountInRow = 0; is >> intLine[numberCountInRow]; numberCountInRow++ );
		    int *dynamicIntLine = new int[numberCountInRow];
		    for (int i = 0; i < numberCountInRow; i++ ){
		    	dynamicIntLine[i] = intLine[i];
		    }
		    lecturer->addCourses(numberCountInRow,dynamicIntLine);
		    lecturerList[rowNumber] = *lecturer;
		}
		CourseOfLecturersFile.close();
	}
	else{
		cerr << "Input file " << CourseOfLecturersInputFileName << " could not be opened." << endl;
		return -1;
	}

	if(LecturersPLInputFile.is_open()){
		string stringLine;

		for(int rowNumber = 0; getline(LecturersPLInputFile,stringLine); rowNumber++){
			int numberCountInRow;
			int intLine[10];
			istringstream is(stringLine);
		    for( numberCountInRow = 0; is >> intLine[numberCountInRow]; numberCountInRow++ );
		    int *dynamicIntLine = new int[numberCountInRow];
		    for (int i = 0; i < numberCountInRow; i++ ){
		    	dynamicIntLine[i] = intLine[i] - 1; // for starting index from 0
		    }
		    lecturerList[rowNumber].addAssistantPL(numberCountInRow,dynamicIntLine);
		}
		LecturersPLInputFile.close();
	}
	else{
		cerr << "Input file " << LecturersPLInputFileName << " could not be opened." << endl;
		return -1;
	}


	if(AssistantsPLInputFile.is_open()){
		string stringLine;

		for (assistantNumber = 0; getline(AssistantsPLInputFile, stringLine); assistantNumber++ );
		AssistantsPLInputFile.clear();
		AssistantsPLInputFile.seekg(0, AssistantsPLInputFile.beg);

		assistantList = new Assistant[assistantNumber];

		for(int rowNumber = 0; getline(AssistantsPLInputFile,stringLine); rowNumber++){
			Assistant *assistant = new Assistant;
			int numberCountInRow;
			int intLine[10];
			istringstream is(stringLine);
		    for( numberCountInRow = 0; is >> intLine[numberCountInRow]; numberCountInRow++ );
		    int *dynamicIntLineCourse = new int[numberCountInRow];
		    int *dynamicIntLineLecturer = new int[numberCountInRow];
		    for (int i = 0; i < numberCountInRow; i++ ){
		    	dynamicIntLineCourse[i] = intLine[i];
		    	for (int lect = 0; lect < lecturerNumber; lect++){
		    		if(lecturerList[lect].searchCourse(intLine[i])){
		    			dynamicIntLineLecturer[i] = lect;
		    		}
		    	}
		    }
		    assistant->addCoursePL(numberCountInRow,dynamicIntLineCourse);
		    assistant->addLecturerPL(numberCountInRow,dynamicIntLineLecturer);
		    assistantList[rowNumber] = *assistant;
		}
		AssistantsPLInputFile.close();
	}
	else{
		cerr << "Input file " << AssistantsPLInputFileName << " could not be opened." << endl;
		return -1;
	}


	for (int i = 0; i < lecturerNumber; i++){
		lecturerList[i].setProposableList(lecturerList[i].assistantPLNumber, lecturerList[i].assistantPL);
		lecturerList[i].setPairList(lecturerList[i].courseNumber);

	}
	for (int i = 0; i < assistantNumber; i++){
		assistantList[i].setAcceptableList(assistantList[i].lecturerPLNumber, assistantList[i].lecturerPL);
		assistantList[i].setPairList(1);
	}

	while (findFreeLecturer() != -1){ // bosta hoca var mı
		int currentLec = findFreeLecturer(); // bos hoca ata
		int propose = lecturerList[currentLec].nextProposable(); // teklif edilebilcek kisi bul
		if(assistantList[propose].isFree()){ // teklif ettigim bos mu
			lecturerList[currentLec].addToPair(propose); // esi ekle
			assistantList[propose].addToPair(currentLec); // esimi bana ekle
			assistantList[propose].accept(currentLec); // esim beni kabul etsin
		}
		else if (assistantList[propose].accept(currentLec)){ // teklif ettigim beni tercih ediyor mu
			int exLecturer = assistantList[propose].getLastPair(); // teklif ettigim kisinin eski esini bul
			lecturerList[exLecturer].removeFromPair(propose); // eski esi teklif ettigim kisiden ayir
			assistantList[propose].removeFromPair(exLecturer); // teklif ettigimi eski sevgiliden ayir
			assistantList[propose].addToPair(currentLec); // teklif ettigim kisinin esini ben yap
			lecturerList[currentLec].addToPair(propose); // teklif ettigim kisiyi benim esim yap
		}
	}

	int lecturerWeightSum = 0;
	for (int lect = 0; lect < lecturerNumber; lect++){
		lecturerWeightSum += lecturerList[lect].calculateWeight();
	}

	int assistantWeightSum = 0;
	for (int asst = 0; asst < assistantNumber; asst++){
		assistantWeightSum += assistantList[asst].calculateWeight();
	}

	if (GS_outOutputFile.is_open()){
		GS_outOutputFile << "LECTURERS PROPOSE TO ASSISTANTS (LECTURER OPTIMAL)" << endl;
		GS_outOutputFile << "RESULTS (LECTURER-COURSE-ASSISTANT)" << endl;

		for (int lec = 0; lec < lecturerNumber ; lec++){
			for (int course = 0; course < lecturerList[lec].courseNumber; course++){
				GS_outOutputFile << lec + 1 << "-" << lecturerList[lec].courses[course] << "-" << lecturerList[lec].pair[course] + 1 << endl;
			}
		}
		GS_outOutputFile << "TOTAL WEIGHT OF LECTURERS= " << lecturerWeightSum << endl;
		GS_outOutputFile << "TOTAL WEIGHT OF ASSISTANTS= " << assistantWeightSum << endl << endl;
	}
	else{
		cerr << "Output file " << GS_outOutputFileName << " could not be opened." << endl;
		return -1;
	}



	for (int i = 0; i < assistantNumber; i++){
		assistantList[i].setProposableList(assistantList[i].lecturerPLNumber, assistantList[i].lecturerPL);
		assistantList[i].setPairList(1);
	}
	for (int i = 0; i < lecturerNumber; i++){
		lecturerList[i].setAcceptableList(lecturerList[i].assistantPLNumber, lecturerList[i].assistantPL);
		lecturerList[i].setPairList(lecturerList[i].courseNumber);

	}


	while (findFreeAssistant() != -1){ // bosta asistan var mı
		int currentAsst = findFreeAssistant(); // bos asistan ata
		int propose = assistantList[currentAsst].nextProposable(); // teklif edilebilcek kisi bul
		if(!lecturerList[propose].isFull()){ // teklif ettigim bos mu
			assistantList[currentAsst].addToPair(propose); // esi ekle
			lecturerList[propose].addToPair(currentAsst); // esimi bana ekle
			lecturerList[propose].multiAccept(currentAsst); // esim beni kabul etsin
		}
		else if (lecturerList[propose].multiAccept(currentAsst)){ // teklif ettigim beni tercih ediyor mu
			int exAssistant = lecturerList[propose].multiGetLastPair(); // teklif ettigim kisinin eski esini bul
			assistantList[exAssistant].removeFromPair(propose); // eski esi teklif ettigim kisiden ayir
			lecturerList[propose].removeFromPair(exAssistant); // teklif ettigimi eski sevgiliden ayir
			lecturerList[propose].addToPair(currentAsst); // teklif ettigim kisinin esini ben yap
			assistantList[currentAsst].addToPair(propose); // teklif ettigim kisiyi benim esim yap
		}
	}

	lecturerWeightSum = 0;
	for (int lect = 0; lect < lecturerNumber; lect++){
		lecturerWeightSum += lecturerList[lect].calculateWeight();
	}

	assistantWeightSum = 0;
	for (int asst = 0; asst < assistantNumber; asst++){
		assistantWeightSum += assistantList[asst].calculateWeight();
	}

	if (GS_outOutputFile.is_open()){
		GS_outOutputFile << "ASSISTANTS PROPOSE TO LECTURERS (ASSISTANT OPTIMAL)" << endl;
		GS_outOutputFile << "RESULTS (ASSISTANT-COURSE-LECTURER)" << endl;

		for (int asst = 0; asst < assistantNumber ; asst++){
			int lecture = 0;;
			for (int i = 0; i < lecturerList[assistantList[asst].pair[0]].courseNumber; i++){
				if (lecturerList[assistantList[asst].pair[0]].courses[i] != -1){
					lecture = lecturerList[assistantList[asst].pair[0]].courses[i];
					lecturerList[assistantList[asst].pair[0]].courses[i] = -1;
					break;
				}
			}
			GS_outOutputFile << asst + 1 << "-" << lecture << "-" << assistantList[asst].pair[0] + 1 << endl;
		}
		GS_outOutputFile << "TOTAL WEIGHT OF LECTURERS= " << lecturerWeightSum << endl;
		GS_outOutputFile << "TOTAL WEIGHT OF ASSISTANTS= " << assistantWeightSum << endl << endl;
		GS_outOutputFile.close();
	}
	else{
		cerr << "Output file " << GS_outOutputFileName << " could not be opened." << endl;
		return -1;
	}

	return 0;
}


int findFreeLecturer(){
	for (int i = 0; i < lecturerNumber; i++){
		if(!lecturerList[i].isFull()){
			return i;
		}
	}
	return -1;
}

int findFreeAssistant(){
	for (int i = 0; i < assistantNumber; i++){
		if(!assistantList[i].isFull()){
			return i;
		}
	}
	return -1;
}
