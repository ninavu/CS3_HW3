#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

#include "TimeCode.h"

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
	t = ComponentsToSeconds(hr, min, sec);
}

/* Copy constructor */
TimeCode::TimeCode(const TimeCode& tc){
	t = tc.t;
}		

/* Function allows user to set new hour */
void TimeCode::SetHours(unsigned int hours){
	t = t - (GetHours() * 3600) + hours * 3600;
}

/* Function allows user to set new minute */
void TimeCode::SetMinutes(unsigned int minutes){
	if (minutes > 59) {
		throw invalid_argument("Minutes cannot be larger than 60: " + to_string(minutes));
		
	} else {
		t = t - (GetMinutes() * 60) + minutes * 60;
	}	
}

/* Function allows user to set new second */
void TimeCode::SetSeconds(unsigned int seconds){
	if (seconds > 59) {
		throw invalid_argument("Seconds cannot be larger than 60: " + to_string(seconds));
		
	} else {
		t = t - GetSeconds() + seconds;
	}		
}

/* Function resets t to 0 */
void TimeCode::reset(){
	t = 0;
}

/* Function converts t seconds into hour */
unsigned int TimeCode::GetHours() const{
	return t / 3600;
}

/* Function converts t seconds into minute */
unsigned int TimeCode::GetMinutes() const{
	return (t % 3600) / 60; 
}

/* Function converts t seconds into second */
unsigned int TimeCode::GetSeconds() const{
	return t % 3600 % 60;
}

/* Function converts t seconds into hr, min, and sec by calling 3 getter functions above */
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int&sec) const{
	hr = GetHours();
	min = GetMinutes();
	sec = GetSeconds();
}

/* Function converts a given hr, min, and sec to the value stored in t */
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
	return (hr * 60 * 60) + (min * 60) + sec; 
}

/* Function returns TimeCode object as a string */
string TimeCode::ToString() const{
	return to_string(GetHours()) + ":" + to_string(GetMinutes()) + ":" + to_string(GetSeconds());	
}

/* Function returns the sum of 2 TimeCode objects */
TimeCode TimeCode::operator+(const TimeCode& other) const{
	TimeCode sum;
	sum.t = t + other.t;
	return sum;
}

/* Function returns the difference of 2 TimeCode objects */
TimeCode TimeCode::operator-(const TimeCode& other) const{
	TimeCode sub;
	
	if (t < other.t){
		throw invalid_argument("Negative output not allowed: " + sub.ToString());
		
	} else {	
		sub.t = t - other.t;
		return sub;
	}
}

/* Function returns the product of a TimeCode object and a double */
TimeCode TimeCode::operator*(double a) const{
	TimeCode product;
	
	if (a < 0){
		throw invalid_argument("Negative arguments not allowed: " + to_string(a));
		
	} else {
		product.t = t * a;
		return product;		
	}
}

/* Function returns the quotient of a TimeCode object and a double */
TimeCode TimeCode::operator/(double a) const{
	TimeCode div;
	
	if (a < 0){				// cannot divide by a negative input
		throw invalid_argument("Negative and zero arguments not allowed: " + to_string(a));
		
	} else if (a == 0){				// cannot divide by 0
		throw invalid_argument("Cannot divide by 0: " + to_string(a));	
		
	} else {
		div.t = t / a;
		return div;
	}
}

/* Function returns true if 2 TimeCode is equal to each other */
bool TimeCode::operator == (const TimeCode& other) const{
	return (t == other.t);
}

/* Function returns true if 2 TimeCode is not equal to each other */
bool TimeCode::operator != (const TimeCode& other) const{
	return !(t == other.t);
}

/* Function returns true if the first TimeCode is less than the second TimeCode */
bool TimeCode::operator < (const TimeCode& other) const{
	return (t < other.t);
}

/* Function returns true if the first TimeCode is less than or equal to the second TimeCode */
bool TimeCode::operator <= (const TimeCode& other) const{
	return !(t > other.t);
}

/* Function returns true if the first TimeCode is greater than the second TimeCode */
bool TimeCode::operator > (const TimeCode& other) const{
	return (other.t < t);
}

/* Function returns true if the first TimeCode is greater than or equal to the second TimeCode */
bool TimeCode::operator >= (const TimeCode& other) const{
	return !(t < other.t);	
}
