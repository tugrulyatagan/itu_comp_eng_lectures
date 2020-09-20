#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>

#define stopwords "stopwords.txt"
#define inputname "input.txt"
#define outputname "output.txt"

using namespace std;

bool search(string);
set <string> stopset;

int main(){
	cout << "Word frequency aplication" << endl;
	multimap<int,string> freq_rev;
	map<string,int> freq;

	fstream stopfile;
	stopfile.open(stopwords, fstream::in);
	string temp;
	while(!stopfile.eof()){
		stopfile >> temp;
		stopset.insert(temp);
	}
	stopfile.close();


	fstream infile;
	infile.open(inputname, fstream::in);
	int total = 0;
	while(!infile.eof()){
		total++;
		infile >> temp;   
		if(search(temp) == true)
			freq[temp]++;
	} 
	infile.close();


	map<string,int>::iterator it;
	for(it = freq.begin(); it != freq.end(); it++)
		freq_rev.insert(make_pair(it->second, it->first));
	
	multimap <int,string>::reverse_iterator myit;
	int count;
	float frq;
	cout << "Word\tCount\tFrequency" << endl;
	for (myit = freq_rev.rbegin(), count=0, frq = 0; count < 10; myit++, count++){
		frq = static_cast<float>((*myit).first) * 100 / total;
		cout << (*myit).second << "\t" << (*myit).first << "\t" << "%" << frq << endl;
	}
	cout << "Total word number: "<< total << endl << endl;

	fstream outfile;
	outfile.open(outputname, fstream::out);
	for (myit = freq_rev.rbegin(), count=0, frq = 0; count < 10; myit++, count++){
		frq = static_cast<float>((*myit).first) * 100 / total;
		outfile << (*myit).second << "\t" << (*myit).first << "\t" << "%" << frq << endl;
	}
	outfile.close();
	cout << "Output file succesfuly created." << endl << endl;

	return 0;
}

bool search(string x){
	set<string>::iterator it;
	for(it = stopset.begin(); it != stopset.end(); it++){
		if(*it == x)
			return true;
	}
	return false;
}