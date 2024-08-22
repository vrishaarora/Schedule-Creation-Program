#include "../header/Task.h"
#include "../header/Date.h"

#include <iostream>
#include <string>
#include <map>

using namespace std;

Task::Task() {
    this->title = "NEED_TITLE"; 
    this->category = "NEED_CATEGORY"; 
    this->desc = "NEED_DESC"; 
    this->complete = false; 
    this->priority = 0; 
    //dueDate should've already called Date default constr. 
}

Task::Task(Date dd, string t, string c, string d, unsigned p) {
    this->dueDate = dd; 
    this->title = t; 
    this->category = c; 
    this->desc = d; 
    this->complete = false; 
    this->priority = p; 
}

Task::Task(Date dd, string t, string c, string d, unsigned p, bool complete) { 
    this->dueDate = dd; 
    this->title = t; 
    this->category = c; 
    this->desc = d; 
    this->complete = complete; 
    this->priority = p; 
}

void Task::printAll(ostream& out) {
    out << "Title: " << this->title << "\n";
    out << "Category: " << this->category << "\n";
    out << "Description: " << this->desc << "\n";
    out << "Due Date: " << this->dueDate.dateString() << "\n";
    out << "Priority: " << this->priority << "\n";
}
