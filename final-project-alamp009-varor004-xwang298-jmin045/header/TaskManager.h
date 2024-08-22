#pragma once
#include <iostream>
#include <vector>
#include "../header/Task.h"
#include "../header/Date.h"
#include "../header/EditUtility.h"
#include "../header/SortStrategy.h"
#include "../header/SortByDate.h"
#include "../header/SortByCategory.h"
#include "../header/SortByPriority.h"
#include "../header/Scheduler.h"

using namespace std;

class TaskManager {

private:
    TaskList* list = nullptr; 
    bool firsTimePrompt = true; 

public:
    ~TaskManager() { delete list; }
    bool printMainMenu(ostream&);
    void printEditMenu(ostream&);
    void printAddMenu(ostream&);
    void printCompleteMenu(ostream&);
    void printDeleteMenu(ostream&);
    void printViewMenu(ostream&);
    void printScheduleMenu(ostream&);
}; 