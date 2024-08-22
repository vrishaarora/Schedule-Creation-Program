#include <iostream>
#include <vector>
#include <climits>
#include <cassert>
#include <string>
#include <iomanip>
#include "../header/EditUtility.h"
#include "../header/SavedList.h"

using namespace std;

void EditUtility::printCentered(ostream& out, string text) {
    int spaces = (40 - text.length()) / 2;
    out << setw(spaces + text.length()) << text << endl;
}

Date EditUtility::convertToDate(string dateString) {
    unsigned year, month, day;
    char delimiter;

    std::istringstream dateStream(dateString);
    dateStream >> month >> delimiter >> day >> delimiter >> year;
    
    return Date(month, day, year);
}

TaskList* EditUtility::firstPrompts(ostream& out) { 
    out << "----------------------------------------" << endl;
    printCentered(out,"First Time Startup");
    out << "----------------------------------------" << endl;
    out << "Restore from a previous save? (y/n)" << endl << "> ";  
    char input;
    while (!(cin >> input) || (input != 'y' && input != 'n')) {
        out << "Unexpected input, enter \'y\' or \'n\': " << endl;
        cin.clear(); // Clear input buffer to handle non-integer input
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
    }
    cin.ignore();
    while (input == 'y') {
        out << "----------------------------------------" << endl;
        out << "Enter name of savefile: " << endl << "> "; 
        string filename; 
        getline(cin, filename); 
        try {
            TaskList* list = new SavedList(filename);
            return list;
        } catch (const std::runtime_error& e) {
            out << e.what() << endl;
            out << "----------------------------------------" << endl;
            out << "Attempt another filename? (y/n) " << endl; 
            while (!(cin >> input) || (input != 'y' && input != 'n')) {
                out << "Unexpected input, enter \'y\' or \'n\': " << endl;
                cin.clear(); // Clear input buffer to handle non-integer input
                cin.ignore(INT_MAX, '\n'); // Discard invalid input
            }
        }
    }
    TaskList* list = new TaskList(); //empty  
    return list; 
}

Task EditUtility::editPrompts(ostream& out, unsigned taskNum, TaskList& list) {
    out << "----------------------------------------" << endl;
    printCentered(out,"Edit Task Menu");
    out << "----------------------------------------" << endl;
    out << "1. Edit Task Title" << endl;
    out << "2. Edit Task Description" << endl;
    out << "3. Edit Task Due Date" << endl;
    out << "4. Edit Task Category" << endl;
    out << "5. Edit Task Priority" << endl;
    out << "6. Leave Edit Menu" << endl;
    out << "----------------------------------------" << endl;
    out << "Enter your choice here (ex: 1): ";
    int input;
    while (!(cin >> input) || input < 1 || input > 6) {
        out << "Unexpected input, please enter an option 1-6: " << endl;
        cin.clear(); // Clear input buffer to handle non-integer input
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
    }
    cin.ignore();
    out << "----------------------------------------" << endl;
    if (input == 1) { 
        string newTitle;  
        printCentered(out, "Edit new title:");  
        getline(cin, newTitle); 
        return Task(list.getTask(taskNum).getDate(), newTitle, list.getTask(taskNum).getCategory(), 
            list.getTask(taskNum).getDesc(), list.getTask(taskNum).getPriority()); 
    }
    else if (input == 2) {
        string newDescription;  
        printCentered(out, "Enter new description:"); 
        getline(cin, newDescription); 
        return Task(list.getTask(taskNum).getDate(), list.getTask(taskNum).getTitle(), 
            list.getTask(taskNum).getCategory(), newDescription, list.getTask(taskNum).getPriority()); 
    }
    else if (input == 3) {  
        unsigned m,d,y; 
        out << "Enter new due date's MONTH (1-12):" << endl; 
        out << "> ";
        while (!(cin >> m)) { 
            out << "Unexpected input, please enter a valid month:" << endl; 
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            out << "> ";
        }

        out << "Enter new due date's DAY (1-31):" << endl; 
        out << "> ";
        while (!(cin >> d)) { 
            out << "Unexpected input, please enter a valid day:" << endl; 
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            out << "> ";
        }

        out << "Enter new due date's YEAR (>0):" << endl; 
        out << "> ";
        while (!(cin >> y)) { 
            out << "Unexpected input, please enter a valid year:" << endl; 
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            out << "> ";
        }
        Date newDueDate(m,d,y);
        return Task(newDueDate, list.getTask(taskNum).getTitle(), list.getTask(taskNum).getCategory(),
            list.getTask(taskNum).getDesc(), list.getTask(taskNum).getPriority()); 
    }
    else if (input == 4) {
        string newCategory;
        printCentered(out,"Enter new description:"); 
        getline(cin, newCategory); 
        return Task(list.getTask(taskNum).getDate(), list.getTask(taskNum).getTitle(), 
            newCategory, list.getTask(taskNum).getDesc(), list.getTask(taskNum).getPriority());
    }
    else if (input == 5) {
        unsigned priority;  
        printCentered(out,"Enter new priority (1-5):");
        while( !(cin >> priority) && priority < 1 && priority > 5 ) { 
            out << "Unexpected input, please enter a valid priority:" << endl; 
            cin.clear(); // Clear input buffer to handle non-integer input
            cin.ignore(INT_MAX, '\n'); // Discard invalid input
        }
        return Task(list.getTask(taskNum).getDate(), list.getTask(taskNum).getTitle(), 
            list.getTask(taskNum).getCategory(), list.getTask(taskNum).getDesc(), priority);
    }
    else { 
        Task noChanges; 
        noChanges.setTitle("DEBUG");
        return noChanges; 
    }
}

Task EditUtility::addPrompts(ostream& out, TaskList& list) { 
    string newTitle, newDescription, newCategory;
    unsigned m, d, y, priority;

    out << "----------------------------------------" << endl;
    printCentered(out,"Add Task Menu");
    out << "----------------------------------------" << endl;
    
    printCentered(out,"Enter Task Title");
    cin.ignore(); 
    out << "> ";
    getline(cin, newTitle);
    out << "----------------------------------------" << endl;

    printCentered(out,"Enter Task Description");
    out << "> ";
    getline(cin, newDescription);
    out << "----------------------------------------" << endl;

    printCentered(out,"Enter Task Category");
    out << "> ";
    getline(cin, newCategory);
    out << "----------------------------------------" << endl;

    printCentered(out,"Task Due Date");
    out << "Enter due date's MONTH (1-12):" << endl; 
    out << "> ";
    while (!(cin >> m)) { 
        out << "Unexpected input, please enter a valid month:" << endl; 
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        out << "> ";
    }

    out << "Enter due date's DAY (1-31):" << endl; 
    out << "> ";
    while (!(cin >> d)) { 
        out << "Unexpected input, please enter a valid day:" << endl; 
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        out << "> ";
    }

    out << "Enter due date's YEAR (>0):" << endl; 
    out << "> ";
    while (!(cin >> y)) { 
        out << "Unexpected input, please enter a valid year:" << endl; 
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        out << "> ";
    }
    
    out << "----------------------------------------" << endl;

    printCentered(out,"Enter Task Priority (1-5):");
    out << "> "; 
    while (!(cin >> priority) || priority < 1 || priority > 5) { 
        out << "Unexpected input, please enter a valid priority:" << endl; 
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        out << "> "; 
    } 
    out << "----------------------------------------" << endl;

    Date dueDate(m,d,y);

    return Task(dueDate, newTitle, newDescription, newCategory, priority); 
}