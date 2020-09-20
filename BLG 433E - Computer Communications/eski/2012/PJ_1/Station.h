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
#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <vector>

using namespace std;

class Station{
	private:
	public:
		const static int fqBand = 64;	// 64 kHz fq band
		vector<char> transmitDatas;
		int CDMChip[64];
};
#endif