#pragma once
#include <iostream> 
#include <string> 
#include <map> 
#include "../header/DateUtility.h"

using namespace std;

class DateUtility; 

class Date{ 

    private: 
        unsigned day; 
        unsigned mon; 
        unsigned year; 

    public: 
        Date();
        Date(unsigned, unsigned, unsigned);
        void setDate(unsigned, unsigned, unsigned); 
        void setMon(unsigned); 
        void setDay(unsigned);
        void setYear(unsigned); 
        unsigned getDay() const { return this->day; }
        unsigned getMon() const { return this->mon; } 
        unsigned getYear() const { return this->year; } 
        std::string dateString();
}; 