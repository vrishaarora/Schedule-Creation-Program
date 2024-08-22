#pragma once

#include "../header/Date.h"

#include <iostream>
#include <string>

using namespace std;

class Task{ 
    private: 
        Date dueDate; 
        string title; 
        string category; 
        string desc; 
        bool complete; 
        unsigned priority; 
    public: 
        Task(); 
        Task(Date,string,string,string,unsigned); 
        Task(Date,string,string,string,unsigned, bool); 
        
        void setDate(Date dd) { this->dueDate = dd; }
        void setTitle(string t) { this->title = t; }
        void setDesc(string d) { this->desc = d; }
        void setCategory(string c) { this->category = c; }
        void markAsComplete() { this->complete = true; }
        void setPriority(unsigned p) { this->priority = p; }

        Date getDate() { return this->dueDate; }
        string getTitle() { return this->title; }
        string getDesc() { return this->desc; }
        string getCategory() { return this->category; }
        bool isComplete() { return this->complete; }
        unsigned getPriority() { return this->priority; }

        void printAll(ostream&); 
}; 