#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

#include "TimeCode.h"

//test with 0, 1, -1, big numbers (long long int) - 1000000

void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t1 = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t1 == 11862);
	
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
	cout << "Testing SetHours" << endl;
	
	TimeCode tc = TimeCode(3, 5, 2);
	
	tc.SetHours(9);
	assert(tc.ToString() == "9:5:2");
	
	tc.SetHours(0);
	assert(tc.ToString() == "0:5:2");
	
	TimeCode tc1 = TimeCode(3, 60, 2);
	tc1.SetHours(3);
	assert(tc1.ToString() == "3:0:2");
	
	cout << "PASSED!" << endl << endl;
}

void TestSetMinutes(){
	cout << "Testing SetMinutes" << endl;
	
	TimeCode tc = TimeCode(3, 5, 2);
	
	tc.SetMinutes(9);
	assert(tc.ToString() == "3:9:2");
	
	tc.SetMinutes(0);
	assert(tc.ToString() == "3:0:2");
	
	try{
		tc.SetMinutes(60);
		assert(false);
		
	} catch(const invalid_argument& e){
		
	}
	
	TimeCode tc1 = TimeCode(3, 5, 60);
	tc1.SetMinutes(3);
	assert(tc1.ToString() == "3:3:0");
	
	cout << "PASSED!" << endl << endl;
}

void TestSetSeconds(){
	cout << "Testing SetSeconds" << endl;
	
	TimeCode tc = TimeCode(3, 5, 2);
	
	tc.SetSeconds(9);
	assert(tc.ToString() == "3:5:9");
	
	tc.SetSeconds(0);
	assert(tc.ToString() == "3:5:0");
	
	try{
		tc.SetSeconds(60);
		assert(false);
		
	} catch(const invalid_argument& e){
		
	}
	
	cout << "PASSED!" << endl << endl;
}

void TestReset(){
	cout << "Testing reset" << endl;
	TimeCode tc1 = TimeCode(0, 0 ,0);
	assert(tc1.GetTimeCodeAsSeconds() == 0);
	
	TimeCode tc2 = TimeCode(8, 5, 9);
	assert(tc2.GetTimeCodeAsSeconds() == 0);
	
	TimeCode tc3 = TimeCode(90000, 3, 60);
	assert(tc3.GetTimeCodeAsSeconds() == 0);
	
	cout << "PASSED!" << endl << endl;
}

void TestAdd(){
	cout << "Testing Add" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 + tc2;
	assert(tc3.ToString() == "1:50:0");
	
	// roll-over inputs
	TimeCode tc4 = TimeCode(1, 15, 55);
	TimeCode tc5 = TimeCode(0, 1, 25);
	TimeCode tc6 = tc4 + tc5;
	assert(tc6.ToString() == "1:17:20");

	TimeCode tc7 = TimeCode(3, 59, 55);
	TimeCode tc8 = TimeCode(0, 34, 15);
	TimeCode tc9 = tc7 + tc8;
	assert(tc9.ToString() == "4:34:10");
	
	cout << "PASSED!" << endl << endl;	
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
	}

	TimeCode tc5 = TimeCode(9, 23, 10);
	TimeCode tc6 = TimeCode(6, 50, 47);
	TimeCode tc7 = tc5 - tc6;
	assert(tc7.ToString() == "2:32:23");
	
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
	
	try{
		TimeCode tc10 = tc7 * (-1);
		cout << "tc7: " << tc7.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
	}
	
	cout << "PASSED!" << endl << endl;
}

void TestDivide(){
	cout << "Testing Divide" << endl;
	TimeCode tc1 = TimeCode(0, 1, 0);
	TimeCode tc2 = tc1 / 2;
	assert(tc2.ToString() == "0:0:30");
	
	TimeCode tc3 = TimeCode(3, 5, 17);
	TimeCode tc4 = tc3 / 3;
	assert(tc4.ToString() == "1:1:45");
	
	TimeCode tc5 = TimeCode(2, 10, 45);
	TimeCode tc6 = tc5 / 2.5;
	assert(tc6.ToString() == "0:52:18");
	
	try{
		TimeCode tc7 = tc5 / 0;			//can't divide by 0	
		cout << "tc7: " << tc7.ToString() << endl;
		assert(false);
		
		TimeCode tc8 = tc5 / (-1);		//don't take negative input
		cout << "tc8: " << tc8.ToString() << endl;
		assert(false);
		
	} catch(const invalid_argument& e){
		// just leave this empty
	}
	
	cout << "PASSED!" << endl << endl;
}


void TestEquals(){
	cout << "Testing Equals" << endl;
	TimeCode tc1 = TimeCode(1, 2, 3);
	TimeCode tc2 = TimeCode(1, 2, 3);
	assert(tc1 == tc2);
	
	TimeCode tc3 = TimeCode(0, 61, 63);
	assert(tc1 == tc3);
	assert(tc2 == tc3);
	
	TimeCode tc4 = TimeCode(5, 4, 3);
	assert(!(tc1 == tc4));
	
	cout << "PASSED!" << endl << endl;
}

void TestNotEquals(){
	cout << "Testing NotEquals" << endl;
	TimeCode tc1 = TimeCode(1, 2, 3);
	TimeCode tc2 = TimeCode(2, 2, 3);
	assert(tc1 != tc2);
	
	TimeCode tc3 = TimeCode(0, 61, 63);
	assert(!(tc1 != tc3));
	
	cout << "PASSED!" << endl << endl;
}

void TestLessThan(){
	cout << "Testing LessThan" << endl;
	TimeCode tc1 = TimeCode(1, 2, 3);
	TimeCode tc2 = TimeCode(2, 3, 4);
	assert(tc1 < tc2);
	
	TimeCode tc3 = TimeCode(0, 62, 63);
	assert(tc1 < tc3);
	
	cout << "PASSED!" << endl << endl;
}

void TestLessThanEquals(){
	cout << "Testing LessThanEquals" << endl;
	TimeCode tc1 = TimeCode(1, 2, 3);
	TimeCode tc2 = TimeCode(2, 3, 4);
	assert(tc1 <= tc2);
	
	TimeCode tc3 = TimeCode(1, 2, 3);
	assert(tc1 <= tc3);
	
	TimeCode tc4 = TimeCode(0, 61, 63);
	assert(tc1 <= tc4);
	
	cout << "PASSED!" << endl << endl;
}


void TestGreaterThan(){
	cout << "Testing GreaterThan" << endl;
	TimeCode tc1 = TimeCode(2, 2, 3);
	TimeCode tc2 = TimeCode(2, 1, 4);
	assert(tc1 > tc2);
	
	TimeCode tc3 = TimeCode(1, 62, 2);
	assert(tc1 > tc3);
	
	cout << "PASSED!" << endl << endl;
}

void TestGreaterThanEquals(){
	cout << "Testing GreaterThanEquals" << endl;
	TimeCode tc1 = TimeCode(2, 2, 3);
	TimeCode tc2 = TimeCode(2, 1, 4);
	assert(tc1 >= tc2);
	
	TimeCode tc3 = TimeCode(2, 2, 3);
	assert(tc1 >= tc3);
	
	TimeCode tc4 = TimeCode(1, 62, 3);
	assert(tc1 >= tc4);
	
	cout << "PASSED!" << endl << endl;
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
