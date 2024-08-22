#include "../header/SavedList.h"

#include <iostream> 
#include <string> 
#include <fstream>
#include <stdexcept>
#include <sstream>  

void SavedList::saveHelper(unsigned i) { 
    if (  tasks.at(i).getTitle() != "" ) saveFile << tasks.at(i).getTitle() << "~"; //printing empty strings destroys everything
    else saveFile << "NEED_TITLE" << "~"; 
    if (  tasks.at(i).getCategory() != "" ) saveFile << tasks.at(i).getCategory() << "~"; 
    else saveFile << "NEED_CATEGORY" << "~"; 
    if (  tasks.at(i).getDesc() != "" ) saveFile << tasks.at(i).getDesc() << "~"; 
    else saveFile << "NEED_DESC" << "~"; 
    saveFile << tasks.at(i).isComplete() << " "; //1 or 0 
    saveFile << tasks.at(i).getPriority() << " ";
    saveFile << tasks.at(i).getDate().getMon() << " "; //can't have an empty date so i'm just 
    saveFile << tasks.at(i).getDate().getDay() << " "; //gonna print it and hope it doesnt ruin my file
    saveFile << tasks.at(i).getDate().getYear() << "\n"; 
}
void SavedList::saveHelperComplete(unsigned i) { 
    if (  completedTasks.at(i).getTitle() != "" ) saveFile << completedTasks.at(i).getTitle() << "~"; //printing empty strings destroys everything
    else saveFile << "NEED_TITLE" << "~"; 
    if (  completedTasks.at(i).getCategory() != "" ) saveFile << completedTasks.at(i).getCategory() << "~"; 
    else saveFile << "NEED_CATEGORY" << "~"; 
    if (  completedTasks.at(i).getDesc() != "" ) saveFile << completedTasks.at(i).getDesc() << "~"; 
    else saveFile << "NEED_DESC" << "~"; 
    saveFile << completedTasks.at(i).isComplete() << " "; //1 or 0 
    saveFile << completedTasks.at(i).getPriority() << " ";
    saveFile << completedTasks.at(i).getDate().getMon() << " "; //can't have an empty date so i'm just 
    saveFile << completedTasks.at(i).getDate().getDay() << " "; //gonna print it and hope it doesnt ruin my file
    saveFile << completedTasks.at(i).getDate().getYear() << "\n"; 
}

void SavedList::saveToFile(fstream& saveFile){ 
    if (!saveFile.is_open()) {
        throw std::runtime_error("File is not open for saving.");
    }

    saveFile.close();
    saveFile.open(filename, std::ios::out | std::ios::trunc);

    int count = 0, badcount = 0; 
    for ( unsigned i = 0; i < tasks.size(); ++i ) { 
        if ( tasks.at(i).getTitle() != "NEED_TITLE" ) { //does NOT save any default-tasks 
            saveHelper(i);
            count++; 
        }
        else badcount++; 
    }
    for ( unsigned i = 0; i < completedTasks.size(); ++i ) { 
        if ( completedTasks.at(i).getTitle() != "NEED_TITLE" ) { //does NOT save any default-tasks 
            saveHelperComplete(i);
            count++; 
        }
        else badcount++; 
    }
    cout << "Successfully saved " << count << "/" << badcount+count << " tasks." << endl; 
}

void SavedList::loadFromFile(fstream& saveFile) { 
    if (!saveFile.is_open()) {
        throw std::runtime_error("File is not open for loading.");
    }
    string title, category, desc;
    unsigned prio, mon, day, year; 
    bool complete;  

    while ( std::getline(saveFile, title, '~') ){
        if ( title == "~") return; //just in case something goes wrong for now lol 
        
        std::getline(saveFile, category, '~');
        std::getline(saveFile, desc, '~');
        saveFile >> complete >> prio >> mon >> day >> year; 
        saveFile.ignore(); 
        
        if( title != "NEED_TITLE" ) {
            Task t(Date(mon,day,year), title, category, desc, prio, complete); 
            if (t.isComplete()) { 
                completedTasks.push_back(t); 
            }   
            else { 
                tasks.push_back(t); 
            }
        }
    }
    cout << "Loaded " << tasks.size() + completedTasks.size() << " tasks from your previous save." << endl; 
}