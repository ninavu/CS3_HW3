#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

#include "TimeCode.h"

//test with 0, 1, -1, big numbers (long long int) - 1000000

void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	long long unsigned int t1 = TimeCode::ComponentsToSeconds(4, 15, 32);
	assert(t1 == 15332);
	
	long long unsigned int t2 = TimeCode::ComponentsToSeconds(0, 0, 0);
	assert(t2 == 0);
	
	// t3 is bigger than a 32 bit signed int
	long long unsigned int t3 = TimeCode::ComponentsToSeconds(900000, 0, 0);
	assert(t3 == 3240000000);
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc1 = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc1.ToString() == "0:0:0");
	
	TimeCode tc2 = TimeCode(7, 59, 59);
	assert(tc2.ToString() == "7:59:59");
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	TimeCode tc4 = TimeCode(2, 60, 34719572143);
	assert(tc4.ToString() == "9644328:35:43");
	
	TimeCode tc5 = TimeCode(2, 60, 35);
	assert(tc5.ToString() == "3:0:35");
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc1 = TimeCode(5, 2, 18);
	tc1.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	TimeCode tc2 = TimeCode(0, 0, 0);
	tc2.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);

	//Roll-over inputs
	TimeCode tc3 = TimeCode(1, 60, 60);
	tc3.GetComponents(h, m, s);
	assert(h == 2 && m == 1 && s == 0);
	
	TimeCode tc4 = TimeCode(3, 71, 3801);
	tc4.GetComponents(h, m, s);
	assert(h == 5 && m == 14 && s == 21);
	
	cout << "PASSED!" << endl << endl;
}

void TestGetTimeCodeAsSeconds(){
	cout << "Testing GetTimeCodeAsSeconds" << endl;
	
	// Random but "safe" inputs
	TimeCode tc1 = TimeCode(8, 5, 9);
	assert(tc1.GetTimeCodeAsSeconds() == 29109);
	
	TimeCode tc2 = TimeCode(0, 0, 0);
	assert(tc2.GetTimeCodeAsSeconds() == 0);
	
	TimeCode tc3 = TimeCode(4, 15, 32);
	assert(tc3.GetTimeCodeAsSeconds() == 15332);
	
	TimeCode tc4 = TimeCode(4, 82, 47);
	assert(tc4.GetTimeCodeAsSeconds() == 19367);
	
	TimeCode tc5 = TimeCode(900000, 20, 60);
	assert(tc5.GetTimeCodeAsSeconds() == 3240001260);
	
	cout << "PASSED!" << endl << endl;
}


void TestCopyConstructor(){
	cout << "Testing Copy Constructor" << endl;
	
	TimeCode tc1 = TimeCode();
	TimeCode tc2 = TimeCode(tc1);
	assert(tc2.GetTimeCodeAsSeconds() == 0);
	
	TimeCode tc3 = TimeCode(4, 15, 32);
	TimeCode tc4 = TimeCode(tc3);
	assert(tc4.GetTimeCodeAsSeconds() == 15332);
	
	TimeCode tc5 = TimeCode(900000, 20, 60);
	TimeCode tc6 = TimeCode(tc5);
	assert(tc5.GetTimeCodeAsSeconds() == 3240001260);
	
	cout << "PASSED!" << endl << endl;
}

void TestGetHours(){
	cout << "Testing GetHours" << endl;
	
	TimeCode tc1 = TimeCode(8, 5, 9);
	assert(tc1.GetHours() == 8);
	
	TimeCode tc2 = TimeCode(0, 5, 9);
	assert(tc2.GetHours() == 0);
	
	// testing a very big number
	TimeCode tc3 = TimeCode(1000000, 5, 9);
	assert(tc3.GetHours() == 1000000);
	
	TimeCode tc4 = TimeCode(32, 65, 9);
	assert(tc4.GetHours() == 33);
	
	cout << "PASSED!" << endl << endl;
}

void TestGetMinutes(){
	cout << "Testing GetMinutes" << endl;
	
	TimeCode tc1 = TimeCode(8, 5, 9);
	assert(tc1.GetMinutes() == 5);
	
	TimeCode tc2 = TimeCode(8, 0, 9);
	assert(tc2.GetMinutes() == 0);
	
	TimeCode tc3 = TimeCode(8, 60, 9);
	assert(tc3.GetMinutes() == 0);
	
	TimeCode tc4 = TimeCode(8, 60, 60);
	assert(tc4.GetMinutes() == 1);
	
	cout << "PASSED!" << endl << endl;
}

void TestGetSeconds(){
	cout << "Testing GetSeconds" << endl;
	
	TimeCode tc1 = TimeCode(8, 5, 9);
	assert(tc1.GetSeconds() == 9);
	
	TimeCode tc2 = TimeCode(8, 5, 0);
	assert(tc2.GetSeconds() == 0);
	
	TimeCode tc3 = TimeCode(8, 5, 60);
	assert(tc3.GetSeconds() == 0);
	
	TimeCode tc4 = TimeCode(8, 5, 87947);
	assert(tc4.GetSeconds() == 47);
	
	
	cout << "PASSED!" << endl << endl;
	
}

void TestSetHours(){
	
	
}

void TestSetMinutes(){
	
	
	
}

void TestSetSeconds(){
	
	
}

void TestReset(){
	
	
	
}


void TestAdd(){
	
	
}

void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	// more tests
	
	cout << "PASSED!" << endl << endl;
}

void TestMutiply(){
	cout << "Testing Multiply" << endl;
	TimeCode tc1 = TimeCode(0, 1, 0);
	TimeCode tc2 = tc1 * 2;
	assert(tc2.ToString() == "0:2:0");
	
	TimeCode tc3 = TimeCode(3, 5, 17);
	TimeCode tc4 = tc3 * 5.5;
	assert(tc4.ToString() == "16:59:3");
	
	TimeCode tc5 = TimeCode(0, 5, 0);
	TimeCode tc6 = tc5 * 2.5;
	assert(tc6.ToString() == "0:12:30");
	
	TimeCode tc7 = TimeCode(1, 0, 0);
	TimeCode tc8 = tc7 * 0.5;
	assert(tc8.ToString() == "0:30:0");
	
	TimeCode tc9 = tc7 * 0;
	assert(tc9.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestDivide(){
	
	
	
}



void TestEquals(){
	
	
	
}

void TestNotEquals(){
	
	
	
}

void TestLessThan(){
	
	
	
}

void TestLessThanEquals(){
	
	
	
}


void TestGreaterThan(){
	
	
	
}

void TestGreaterThanEquals(){
	
	
	
}

	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestGetTimeCodeAsSeconds();
	TestCopyConstructor();
	
	TestGetHours();
	TestGetMinutes();
	TestGetSeconds();
	
	TestSetHours();
	TestSetMinutes();
	TestSetSeconds();
	
	TestAdd();
	TestSubtract();
	TestMutiply();
	TestDivide();
	
	TestEquals();
	TestNotEquals();
	TestLessThan();
	TestLessThanEquals();
	TestGreaterThan();
	TestGreaterThanEquals();
	
	cout << "PASSED ALL TESTS!!! CONGRATULATIONS!!!" << endl;
	return 0;
}
