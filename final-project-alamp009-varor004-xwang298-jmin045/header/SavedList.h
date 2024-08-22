#pragma once

#include "Task.h"
#include <iostream> 
#include <string> 
#include <fstream>
#include <stdexcept>
#include <vector> 
#include <sstream> 

#include "../header/TaskList.h"

using namespace std; 

class SavedList : public TaskList {
    private: 
        fstream saveFile; 
        std::string filename; 
        void saveHelper(unsigned i); 
        void saveHelperComplete(unsigned i);
    public: 
        SavedList(string fileName): filename(fileName) {
            this->saveFile.open(fileName);
            if (!saveFile.is_open()) { 
                throw std::runtime_error("Error opening file."); 
            }
            loadFromFile(this->saveFile); 
        }

        ~SavedList() {
            saveToFile(this->saveFile); 
            this->saveFile.close(); 
        }
        
        void saveToFile(fstream&);
        void loadFromFile(fstream&); 
};  