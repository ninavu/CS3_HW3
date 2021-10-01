#include <iostream>
#include <assert.h>
#include <string>

using namespace std;

#include "TimeCode.h"

TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
	t = ComponentsToSeconds(hr, min, sec);
}

TimeCode::TimeCode(const TimeCode& tc){
	t = tc.t;
}		

void TimeCode::SetHours(unsigned int hours){
	if (hours < 0){
		throw invalid_argument("Negative arguments not allowed: " + to_string(hours));
		
	} else {
		t = t - (GetHours() * 3600) + hours * 3600;
	}	
}

void TimeCode::SetMinutes(unsigned int minutes){
	if (minutes > 60) {
		throw invalid_argument("Minutes cannot be larger than 60: " + to_string(minutes));
		
	} else {
		t = t - (GetMinutes() * 60) + minutes * 60;
	}	
}

void TimeCode::SetSeconds(unsigned int seconds){
	if (seconds > 60) {
		throw invalid_argument("Seconds cannot be larger than 60: " + to_string(seconds));
		
	} else {
		t = t - GetSeconds() + seconds;
	}		
}

void TimeCode::reset(){
	t = 0;
}

/* Convert t seconds into hour */
unsigned int TimeCode::GetHours() const{
	return t / 3600;
}

/* Convert t seconds into minute */
unsigned int TimeCode::GetMinutes() const{
	return (t % 3600) / 60; 
}

/* Convert t seconds into second */
unsigned int TimeCode::GetSeconds() const{
	return t % 3600 % 60;
}

/* Convert t seconds into hr, min, and sec by calling 3 getter functions above */
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int&sec) const{
	hr = GetHours();
	min = GetMinutes();
	sec = GetSeconds();
}

long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
	return (hr * 60 * 60) + (min * 60) + sec; 
}

string TimeCode::ToString() const{
	return to_string(GetHours()) + ":" + to_string(GetMinutes()) + ":" + to_string(GetSeconds());	
}


TimeCode TimeCode::operator+(const TimeCode& other) const{
	TimeCode sum;
	sum.t = t + other.t;
	return sum;
}


TimeCode TimeCode::operator-(const TimeCode& other) const{
	TimeCode sub;
	
	if (t < other.t){
		throw invalid_argument("Negative arguments not allowed: " + sub.ToString());
		
	} else {	
		sub.t = t - other.t;
		return sub;
	}
}

TimeCode TimeCode::operator*(double a) const{
	TimeCode product;
	
	if (a < 0){
		throw invalid_argument("Negative arguments not allowed: " + to_string(a));
		
	} else {
		product.t = t * a;
		return product;		
	}
}

TimeCode TimeCode::operator/(double a) const{
	TimeCode div;
	
	if (a < 0){
		throw invalid_argument("Negative arguments not allowed: " + to_string(a));
		
	} else {
		div.t = t / a;
		return div;
	}
}

bool TimeCode::operator == (const TimeCode& other) const{
	return (t == other.t);
	
}

bool TimeCode::operator != (const TimeCode& other) const{
	return !(t == other.t);
	
}

bool TimeCode::operator < (const TimeCode& other) const{
	return (t < other.t);
}

bool TimeCode::operator <= (const TimeCode& other) const{
	return !(t > other.t);
}

bool TimeCode::operator > (const TimeCode& other) const{
	return (other.t < t);
}

bool TimeCode::operator >= (const TimeCode& other) const{
	return !(t < other.t);	
}
