#pragma once
#include <iostream>
#include <vector>
#include "../header/TaskList.h"

using namespace std;

class EditUtility{
    private: 
        static TaskList* firstPrompts(ostream& out); 
        static void printCentered(ostream&, string);
        static Task editPrompts(ostream&, unsigned, TaskList&);
        static Task addPrompts(ostream&, TaskList&); 
        friend class TaskManager; 
    public: 
        static Date convertToDate(string dateString);
}; 
