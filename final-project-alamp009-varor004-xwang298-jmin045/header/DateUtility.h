#pragma once

#include <iostream> 
#include <string> 
#include <map> 
#include "../header/Date.h"

using namespace std; 

class Date;

class DateUtility{ 
    private:
        static bool isLeap(unsigned); 
        static unsigned numDays(unsigned, unsigned);
        static void correctDate(Date&, unsigned, unsigned, unsigned);
        static string monName(unsigned); 

        friend class Date;

    public: 
        //DateUtility(); 
}; 