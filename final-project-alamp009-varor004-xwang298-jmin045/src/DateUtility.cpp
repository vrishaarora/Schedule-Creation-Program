#include "../header/DateUtility.h"

// DateUtility::DateUtility() { 
//     monthMap[1] = "January";
//     monthMap[2] = "February";
//     monthMap[3] = "March";
//     monthMap[4] = "April";
//     monthMap[5] = "May";
//     monthMap[6] = "June";
//     monthMap[7] = "July";
//     monthMap[8] = "August";
//     monthMap[9] = "September";
//     monthMap[10] = "October";
//     monthMap[11] = "November";
//     monthMap[12] = "December";
// }

bool DateUtility::isLeap(unsigned y) {
    if ( y%4 != 0 ) return false; 
    if ( y%100 == 0 && y%400 != 0 ) return false; 
    return true; 
}

unsigned DateUtility::numDays(unsigned m, unsigned y) { 
    if (m == 1) return 31; 
    else if (m == 2 && isLeap(y)) return 29; 
    else if (m == 2) return 28; 
    else if (m == 3) return 31; 
    else if (m == 4) return 30; 
    else if (m == 5) return 31; 
    else if (m == 6) return 30; 
    else if (m == 7) return 31; 
    else if (m == 8) return 31; 
    else if (m == 9) return 30; 
    else if (m == 10) return 31; 
    else if (m == 11) return 30;
    else if (m == 12) return 31;
    return 1;
}

void DateUtility::correctDate(Date& date, unsigned m, unsigned d, unsigned y) {
    date.setYear(y);
    if ( m <= 12 ) 
    { 
        date.setMon(m); 
        if ( d <= numDays(m,y)) {
            date.setDay(d);  
        }
        else { 
            date.setDay(1);   
        }
    }
    else { 
        date.setMon(1); 
        date.setDay(1);   
    }
}

string DateUtility::monName(unsigned m) { 
    map<int, string> monthMap; 
    monthMap[1] = "January";
    monthMap[2] = "February";
    monthMap[3] = "March";
    monthMap[4] = "April";
    monthMap[5] = "May";
    monthMap[6] = "June";
    monthMap[7] = "July";
    monthMap[8] = "August";
    monthMap[9] = "September";
    monthMap[10] = "October";
    monthMap[11] = "November";
    monthMap[12] = "December";
    return monthMap[m]; 
}

