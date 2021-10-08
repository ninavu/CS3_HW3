#include <iostream>
#include <fstream>
#include <assert.h>
#include <vector>
#include <string>
#include <cstdlib>
#include "TimeCode.h"

using namespace std;

string vec_to_string(vector<string> v){
	string str = "[";
	for (unsigned int i = 0; i < v.size()-1; i++){
		str.append(v.at(i));
		str.append(", ");
	}
	
	str.append(v.at(v.size()-1));
	str.append("]");
	return str;
}


/* This function takes a string and a single character (delimiter, then 
 * returns a vector containing the sub-strings between all occurrences of the delimiter */ 
vector<string> split(string str, char delim){
	vector<string> v;
	int idx;
	
	while (str.size() > 0) {
		idx = str.find(delim);
		
		if (idx >= 0){
			v.push_back(str.substr(0, idx));
			str = str.substr(idx+1, str.size()-idx);
			
		} else {
			v.push_back(str);
			str = "";	//delete string
		}
	}
	return v;
} 

/* This function takes a line from the file (a string) and 
 * returns the TimeCode object for the time embedded in that line */
TimeCode parse_line(string str){
	
	vector<string> v = split(str, ':');
	unsigned int hr = stoi(v.at(0));
	unsigned int min = stoi(v.at(1));
	
	TimeCode tc = TimeCode(hr, min);
	return tc;
}
	

int main(){
	
	ifstream inFS; 
	string line;
	string timeVal;
	TimeCode sum;
	int count = 0;
	
	inFS.open("Space_Corrected.csv");

	if (!inFS.is_open()) {
		cout << "Could not open file Space_Corrected.csv" << endl;
		return 1;
	}
	
	getline(inFS, line);			//skip the first line

	while (!inFS.fail()) {
		getline(inFS, line);
		int idx = line.find(":");
		if (idx >= 0){	
			timeVal = line.substr(idx - 2, 5);
			sum = sum + parse_line(timeVal);
			count++;
		}
	}
	
	TimeCode avg = sum / count;
	cout << count << " data points. " << endl;
	cout << "AVERAGE: " << avg.ToString() << endl;
	
	if (!inFS.eof()) {
		cout << "Input failure before reaching end of file." << endl;
	}

	inFS.close();
}
