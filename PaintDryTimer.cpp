#include <ctime> // for time(0)
#include <iostream> 
#include <cmath> // for M_PI and others
#include <vector> 
#include <string>
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's 

using namespace std;


struct DryingSnapShot {
	// A struct - an object that doesn't have any methods
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};


long long int get_time_remaining(DryingSnapShot dss){
	
	int currTime = time(0) - dss.startTime;			// elapsed time
	return dss.timeToDry->GetTimeCodeAsSeconds() - currTime;
}


string drying_snap_shot_to_string(DryingSnapShot dss){
	TimeCode remainTime = TimeCode(0, 0, get_time_remaining(dss));
	string str = "Batch-" + dss.name + " (takes " + dss.timeToDry->ToString() 
				+ " to dry) time remaining: " + remainTime.ToString();
	return str;
}


double get_sphere_sa(double rad){
	return 4 * M_PI * pow(rad, 2);
}


TimeCode *compute_time_code(double surfaceArea){
	int sa = int (surfaceArea);					// convert to int to prevent overflow
	TimeCode *totalDryTime = new TimeCode(0, 0, sa);
	return totalDryTime;
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;
}


int main(){
	string ans;
	double rad;
	DryingSnapShot dss;
	vector<DryingSnapShot> all_batch;
	int numItem = 0;
	
	cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
	cin >> ans;
	
	while (ans != "q"){
		
		if (ans == "a"){
			cout << "radius: ";
			cin >> rad;
			dss.startTime = time(0);
			dss.timeToDry = compute_time_code(get_sphere_sa(rad));
			dss.name = to_string(rand());
			
			cout << "Batch-" << dss.name << " will dry in " << dss.timeToDry->ToString() << endl;
			all_batch.push_back(dss);
			numItem++;
			
			cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
			cin >> ans;
			
		} else if (ans == "v"){
			for (unsigned int i = 0; i < numItem; i++){
				cout << drying_snap_shot_to_string(all_batch.at(i)) << endl;
			}
			
			cout <<  numItem << " items being tracked." << endl;
			cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
			cin >> ans;
		}
		
	}
				
	//tests());
	return 0;
}
