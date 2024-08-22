#include "../header/Date.h"
#include "../header/DateUtility.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

Date::Date() { 
    this->day = 1; 
    this->mon = 1; 
    this->year = 2000;
}
Date::Date(unsigned m, unsigned d, unsigned y) {
    DateUtility::correctDate(*this, m, d, y); 
}

void Date::setDate(unsigned m, unsigned d, unsigned y) { 
    DateUtility::correctDate(*this, m,d,y); 
}
void Date::setMon(unsigned m) {
    if ( m > 12) DateUtility::correctDate(*this, m, this->day, this->year); 
    else this->mon = m; 
}
void Date::setDay(unsigned d) {
    if ( d > DateUtility::numDays(this->mon, this->year) ) DateUtility::correctDate(*this, this->mon, d, this->year); 
    else this->day = d; 
}
void Date::setYear(unsigned y) {
    this->year = y; 
}

string Date::dateString() { 
    return DateUtility::monName(this->mon) + " " + to_string(this->day) + ", " + to_string(this->year) ;
}
