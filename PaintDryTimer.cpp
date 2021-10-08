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
	
	int currTime = time(0) - dss.startTime;			// calculate elapsed time since the batch was created
	int duration = dss.timeToDry->GetTimeCodeAsSeconds() - currTime;	// duration from start to end
	return duration;
}


string drying_snap_shot_to_string(DryingSnapShot dss){
	TimeCode remainTime = TimeCode(0, 0, get_time_remaining(dss));
	string str = "Batch-" + dss.name + " (takes " + dss.timeToDry->ToString() 
				+ " to dry) time remaining: " + remainTime.ToString();
	return str;
}


//calculate the surface area of a sphere
double get_sphere_sa(double rad){
	return 4 * M_PI * pow(rad, 2);
}

// use surface area to calculate the time taken to dry
TimeCode *compute_time_code(double surfaceArea){
	int sa = int (surfaceArea);					// convert to int to prevent overflow
	TimeCode *totalDryTime = new TimeCode(0, 0, sa);		// place new data inside a heap
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
	
	TimeCode tc1 = TimeCode(1, 2, 5);
	dss.timeToDry = &tc1;
	ans = get_time_remaining(dss);
	assert(ans > 3724 && ans < 3726);
	
	TimeCode tc2 = TimeCode();
	dss.timeToDry = &tc2;
	ans = get_time_remaining(dss);
	assert(ans > -1 && ans < 1);


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	
	double sa1 = get_sphere_sa(0);
	assert (sa1 == 0);
	
	double sa2 = get_sphere_sa(90.78);
	assert(103559 < sa2 && sa2 < 103560);


	// compute_time_code
	TimeCode *tc3 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc3->GetTimeCodeAsSeconds() == 1);
	delete tc3;

	TimeCode *tc4 = compute_time_code(sa);
	assert(tc4->GetTimeCodeAsSeconds() == 50);
	delete tc4;
	
	TimeCode *tc5 = compute_time_code(sa1);
	assert(tc5->GetTimeCodeAsSeconds() == 0);
	delete tc5;


	cout << "ALL TESTS PASSED!" << endl;
}


int main(){
	char ans;
	double rad;
	DryingSnapShot dss;
	vector<DryingSnapShot> all_batch;
	unsigned int numItem = 0;
	
	cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
	cin >> ans;
	
	while (tolower(ans) != 'q'){
		
		if (tolower(ans) == 'a'){
			cout << "radius: ";
			cin >> rad;
			dss.startTime = time(0);
			dss.timeToDry = compute_time_code(get_sphere_sa(rad));
			dss.name = to_string(rand());
			
			cout << "Batch-" << dss.name << " will dry in " << dss.timeToDry->ToString() << endl;
			all_batch.push_back(dss);		// add each batch into a vector
			numItem++;
			
		} else if (tolower(ans) == 'v'){
			
			for (unsigned int i = 0; i < all_batch.size(); i++){
				
				/* If the time remaining reaches 0, delete the pointer from the heap 
				 * and erase the object from the vector to prevent memory leak */
				if (get_time_remaining(all_batch.at(i)) <= 0){		
					delete all_batch.at(i).timeToDry;
					all_batch.erase(all_batch.begin()+i);
					numItem--;
					i--;
					
				} else {
					cout << drying_snap_shot_to_string(all_batch.at(i)) << endl;
				}
			}
		
			cout <<  numItem << " items being tracked." << endl;
		}
		
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
		cin >> ans;
		
	}
				
	//tests();
	
	if (tolower(ans) == 'q' && all_batch.size() > 0){		// delete everything to make sure there's no memory leak
		for (unsigned int i = 0; i < all_batch.size(); i++){
			delete all_batch.at(i).timeToDry;
			all_batch.erase(all_batch.begin()+i);
			numItem--;
			i--;
		}
	}
	
	return 0;
}
