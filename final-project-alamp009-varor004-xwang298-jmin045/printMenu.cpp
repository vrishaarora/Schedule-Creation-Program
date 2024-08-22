#include <iostream>
#include <vector>
#include "Task.h" // not made yet

using namespace std;

class TaskManager {
private:
    TaskList list;

public:
    void printMenu(sostream& out) const {
        out << "Task Manager Menu" << endl;
        out << "1. Add Task" << endl;
        out << "2. Edit Task" << endl;
        out << "3. View Completed Tasks" << endl;
        out << "4. Delete Task" << endl;
        out << "5. Exit Task Maker" << endl;
        out << "Enter your choice here: ";
    }
};
