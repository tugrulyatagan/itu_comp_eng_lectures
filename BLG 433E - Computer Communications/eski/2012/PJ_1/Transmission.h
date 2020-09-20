/*
* Istanbul Technical University
* BLG 433E - Computer Communications
* 2012 Autumn
* 1rd Project
*
*
* Student Name: ABDULLAH AYDEÐER
* Student ID : 040090533
*
*/
#ifndef TRANSMISSION_H
#define TRANSMISSION_H

#include <iostream>
#include <vector>

using namespace std;

class Transmission{
	private:
		
	public:
		const static int BANDWIDTH = 4096;	// 4096 kHz fq band
		vector<int> frequencyInterval;
		vector<char> c;
		int transmit[64];
};
#endif