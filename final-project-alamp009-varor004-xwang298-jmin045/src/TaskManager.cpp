#include <iostream>
#include <vector>
#include <climits>
#include "../header/TaskManager.h"
#include "../header/Task.h"
#include "../header/Date.h"
#include "../header/EditUtility.h"
#include "../header/SortStrategy.h"
#include "../header/SortByDate.h"
#include "../header/SortByCategory.h"
#include "../header/SortByPriority.h"
#include "../header/Scheduler.h"

using namespace std;


bool TaskManager::printMainMenu(ostream& out) {
    int input; 
    if ( firsTimePrompt ) { 
        list = EditUtility::firstPrompts(out);  
        firsTimePrompt = false; //only does this once
    }
    out << "----------------------------------------" << endl;
    EditUtility::printCentered(out,"Main Menu");
    out << "----------------------------------------" << endl;
    out << "1. Add Task" << endl;
    out << "2. Edit Task" << endl;
    out << "3. Complete Task" << endl;
    out << "4. Delete Task" << endl;
    out << "5. View Tasks" << endl; 
    out << "6. Calculate Schedule" << endl; 
    out << "7. Exit Program" << endl;
    out << "----------------------------------------" << endl;
    out << "Enter your choice here (ex: 1): " << endl;
    out << "> "; 
    while( !(cin >> input) || input < 1 || input > 7 ) { 
        out << "Unexpected input, please enter an option 1-5: " << endl; 
        cin.clear(); // Clear input buffer to handle non-integer input
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        out << "> "; 
    }
    if ( input == 1 ) { 
        printAddMenu(out);
        return true; 
    }
    else if (input == 2) {
        printEditMenu(out);
        return true; 
    }
    else if (input == 3) {
        printCompleteMenu(out);
        return true; 
    }
    else if (input == 4) {
        printDeleteMenu(out);
        return true; 
    }
    else if (input == 5) {
        printViewMenu(out);
        return true; 
    }
    else if (input == 6) {
        printScheduleMenu(out);
        return true; 
    }
    else return false; 
}

void TaskManager::printEditMenu(ostream& out) {
    if ( list->size() == 0 ) { 
        out << "----------------------------------------" << endl;
        EditUtility::printCentered(out,"Task List is empty");
        EditUtility::printCentered(out,"Exiting Edit Menu...");
        return;
    }
    int taskNum;
    out << "----------------------------------------" << endl;
    EditUtility::printCentered(out,"Current Incomplete Tasks");
    list->printUnfinishedTitles(out); 
    out << "----------------------------------------" << endl;
    out << "Enter the # of the task to edit: " << endl;
    out << "> "; 
    while (!(cin >> taskNum) || taskNum < 1 || taskNum > list->size()) {
        out << "Unexpected input, please enter an option 1-" << list->size() << ": " << endl; 
        cin.clear(); // Clear input buffer to handle non-integer input
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        out << "> "; 
    }
    taskNum--; // makes it index now
    Task replacement = EditUtility::editPrompts(out, taskNum, *list); 
    if ( replacement.getTitle() == "DEBUG" ) return; 
    else list->editTask(taskNum, replacement); 
}

void TaskManager::printAddMenu(ostream& out) {
    Task newTask = EditUtility::addPrompts(out, *list);
    list->addTask(newTask); 
    out << newTask.getTitle() << " has been appended to current list." << endl;
}

void TaskManager::printCompleteMenu(ostream& out) {
    if ( list->size() == 0 ) { 
        out << "----------------------------------------" << endl;
        EditUtility::printCentered(out,"Task List is empty");
        EditUtility::printCentered(out,"Exiting Complete Menu...");
        return;
    }
    int taskNum;
    out << "----------------------------------------" << endl;
    EditUtility::printCentered(out,"Current Incomplete Tasks");
    list->printUnfinishedTitles(out); 
    out << "----------------------------------------" << endl;
    out << "Enter the # of the task to complete: " << endl;
    out << "> "; 
    while (!(cin >> taskNum) || taskNum < 1 || taskNum > list->size()) {
        out << "Unexpected input, please enter an option 1-" << list->size() << ": " << endl; 
        cin.clear(); // Clear input buffer to handle non-integer input
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        out << "> "; 
    }
    taskNum--; // makes it index now
    out << "Confirm that you want to mark " << list->getTask(taskNum).getTitle(); 
    out << " as complete (y): " << endl << "> "; 
    char confirmation;
    if (!(cin >> confirmation) || confirmation != 'y' ){
        out << "\nNo changes will be made, going back to main menu." << endl;
        return;
    }
    out << "----------------------------------------" << endl;
    list->completeTaskUsingIndex(taskNum);
    out << "Task #" << taskNum + 1 << " has been marked as complete.\nReturning to main menu." << endl;
    return;
}

void TaskManager::printDeleteMenu(ostream& out) {
    if ( list->size() == 0 ) { 
        out << "----------------------------------------" << endl;
        EditUtility::printCentered(out,"Task List is empty");
        EditUtility::printCentered(out,"Exiting Delete Menu...");
        return;
    }
    int taskNum;
    out << "----------------------------------------" << endl;
    EditUtility::printCentered(out,"Current Tasks");
    list->printTitles(out); 
    out << "----------------------------------------" << endl;
    out << "Enter the # of the task to delete: " << endl;
    out << "> "; 
    while (!(cin >> taskNum) || taskNum < 1 || taskNum > list->size() + list->completesize()) {
        out << "Unexpected input, please enter an option 1-" << list->size() << ": " << endl; 
        cin.clear(); // Clear input buffer to handle non-integer input
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        out << "> "; 
    }
    taskNum--; // makes it index now
    out << "----------------------------------------" << endl;
    out << "Confirm that you want to delete " << list->getTask(taskNum).getTitle(); 
    out << " (y): "<< endl << "> "; 
    char confirmation;
    if (!(cin >> confirmation) || confirmation != 'y' ){
        out << "\nNo changes will be made, going back to main menu." << endl;
        return;
    }
    out << "----------------------------------------" << endl;
    list->delTask(taskNum);
    out << "Task #" << taskNum + 1 << " has been deleted.\nReturning to main menu." << endl;
    return;
}

void TaskManager::printViewMenu(ostream& out) {
    if ( list->size() == 0 && list->completesize() == 0 ) { 
        out << "----------------------------------------" << endl;
        EditUtility::printCentered(out,"Task List is empty");
        EditUtility::printCentered(out,"Exiting View Menu...");
        return;
    }
    out << "----------------------------------------" << endl;
    EditUtility::printCentered(out,"View Menu");
    out << "----------------------------------------" << endl;
    out << "1. View tasks by date" << endl;
    out << "2. View tasks by priority" << endl;
    out << "3. View tasks by category" << endl;
    out << "4. View Completed tasks" << endl;
    out << "5. Exit View Menu" << endl;
    out << "Enter your choice here (ex: 1): " << endl;
    out << "> "; 
    int input;
    while( !(cin >> input) || input < 1 || input > 5 ) { 
        out << "Unexpected input, please enter an option 1-5: " << endl; 
        cin.clear(); // Clear input buffer to handle non-integer input
        cin.ignore(INT_MAX, '\n'); // Discard invalid input
        out << "> "; 
    }
    out << "----------------------------------------" << endl;
    if ( input == 1 ) { 
        SortStrategy* temp = new SortByDate();
        TaskList sorted = temp->sortBy(*list, SortStrategy::SortOrder::ASCENDING); 
        sorted.printTasks(out);
        delete temp; 
    }
    else if (input == 2) {
        SortStrategy* temp = new SortByPriority();
        TaskList sorted = temp->sortBy(*list, SortStrategy::SortOrder::DESCENDING); 
        sorted.printTasks(out);
        delete temp; 
    }
    else if (input == 3) {
        SortStrategy* temp = new SortByCategory();
        TaskList sorted = temp->sortBy(*list, SortStrategy::SortOrder::ASCENDING); 
        sorted.printTasks(out);
        delete temp; 
    }
    else if (input == 4) {
        if ( list->completesize() == 0 ) { 
            EditUtility::printCentered(out,"Task List is empty");
            EditUtility::printCentered(out,"Exiting View Menu...");
            return;
        }
        EditUtility::printCentered(out,"Completed Tasks");
        out << "----------------------------------------" << endl;
        out << endl;
        list->printCompletedTasks(out); 
        return;
    }
    else if (input == 5) {
        return;
    }
}

void TaskManager::printScheduleMenu(ostream& out) {
    if ( list->size() == 0) { 
        out << "----------------------------------------" << endl;
        EditUtility::printCentered(out,"Task List is empty, nothing to schedule");
        EditUtility::printCentered(out,"Exiting Scheduler...");
        return;
    }
    int input;
    unsigned m,d,y; 
    out << "----------------------------------------" << endl;
    EditUtility::printCentered(out,"Schedule Menu");
    out << "----------------------------------------" << endl;
    EditUtility::printCentered(out,"End-Date for Scheduling");
    out << "Enter end date's MONTH (1-12):" << endl; 
    out << "> ";
    while (!(cin >> m)) { 
        out << "Unexpected input, please enter a valid month:" << endl; 
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        out << "> ";
    }

    out << "Enter end date's DAY (1-31):" << endl; 
    out << "> ";
    while (!(cin >> d)) { 
        out << "Unexpected input, please enter a valid day:" << endl; 
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        out << "> ";
    }

    out << "Enter end date's YEAR (>0):" << endl; 
    out << "> ";
    while (!(cin >> y)) { 
        out << "Unexpected input, please enter a valid year:" << endl; 
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        out << "> ";
    }
    Date newDueDate(m,d,y);
    out << "----------------------------------------" << endl;
    EditUtility::printCentered(out,"Optimal Schedule");
    TaskList scheduledTasks = Scheduler::ScheduleTasks(*list, newDueDate);
    scheduledTasks.printTasks(out);
}