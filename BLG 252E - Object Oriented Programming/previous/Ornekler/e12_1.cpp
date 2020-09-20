// e12_1.cpp
// http://www.buzluca.info/oop
// Simple vector example

#include <iostream>
#include <vector>
using namespace std;

int main() {
	vector<int> nums1;
	nums1.insert(nums1.begin(), -999);	// insert to the beginning -999
	nums1.insert(nums1.begin(), 14);		// 14, -999
	nums1.insert(nums1.end(), 25);		// insert to the end 14, -999, 25

	int i;
	for (i=0; i<nums1.size(); i++)		// prints elements of nums1
		cout << nums1[i] << " ";
	cout << endl;
	
	nums1.erase( nums1.begin() );		// -999, 25
	
	for (i=0; i<nums1.size(); i++)
		cout << nums1[i] << " ";		// prints elements of nums1
	cout << endl;
	
	vector<int> nums2 = nums1;
	nums2.insert(nums2.begin(), 32);	// 32, -999, 25
	
	vector<int> nums3;
	nums3 = nums2;
	
	for (i=0; i<nums3.size(); i++)
		cout << nums3[i] << " ";

	return 0;
}