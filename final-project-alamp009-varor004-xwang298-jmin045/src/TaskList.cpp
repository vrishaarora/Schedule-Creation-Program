#include <algorithm>
#include <sstream>
#include <cassert>
#include "../header/TaskList.h"
#include "../header/EditUtility.h"

TaskList::TaskList() {
    tasks = {};
    completedTasks = {};
}

SortStrategy* sortStrategy = {};

//---------------------------------------------Above are init part-------------------------------------------------

void TaskList::printTasks(std::ostream& out) {
    if (tasks.empty()) {
        out << "Task list is empty." << std::endl;
        return;
    }

    for (Task task : tasks) {
        task.printAll(out);
        out << std::endl;
    }
}

void TaskList::printUnfinishedTitles(std::ostream& out) {
    if (tasks.empty()) {
        out << "Task list is empty." << std::endl;
        return;
    }
    for (unsigned i = 0; i < tasks.size(); ++i) { 
        out << i+1 <<") " << tasks.at(i).getTitle() << std::endl; 
    }
}

void TaskList::printTitles(std::ostream& out) {
    if (tasks.empty() && completedTasks.empty()) {
        out << "Task list is empty." << std::endl;
        return;
    }
    for (unsigned i = 0; i < tasks.size(); ++i) { 
        out << i+1 <<") " << tasks.at(i).getTitle() << std::endl; 
    }
    for (unsigned i = 0; i < completedTasks.size(); ++i) { 
        out << tasks.size() + i + 1<<") " << completedTasks.at(i).getTitle() << std::endl; 
    }
}

void TaskList::printCompletedTasks(std::ostream& out) {
    if (completedTasks.empty()) {
        out << "No completed tasks." << std::endl;
        return;
    }

    for (Task task : completedTasks) {
        task.printAll(out);
        out << std::endl;
    }
}

void TaskList::printCompletedTitles(std::ostream& out) {
    if (completedTasks.empty()) {
        out << "No completed tasks." << std::endl;
        return;
    }

    for (unsigned i = 0; i < completedTasks.size(); ++i) { 
        out << i+1 <<") " << completedTasks.at(i).getTitle() << std::endl; 
    }
}

//---------------------------------------------Above are print methods---------------------------------------------

Task TaskList::getTask(unsigned index) {
    if (index >= tasks.size() && index < tasks.size() + completedTasks.size()) { 
        return completedTasks.at(index - tasks.size());
    }
    assert(index >= 0 && "Out of range - passed validation x2"); 
    return tasks.at(index); 
}

//---------------------------------------------Above are tools-----------------------------------------------------

void TaskList::addTask(Task &newTask) {
    tasks.push_back(newTask);
}

void TaskList::delTask(unsigned index) {
    if (index >= tasks.size() && index < tasks.size() + completedTasks.size()) { 
        completedTasks.erase(completedTasks.begin() + index - tasks.size());
        return;
    }
    assert(index >= 0 && "Out of range - passed validation x2"); 
    tasks.erase(tasks.begin()+index); 
}

void TaskList::editTask(unsigned index, EditType editType, const std::string& newValue) {
    if (index >= tasks.size()) {
        std::cout << "Task at index " << index << " not found in the list." << std::endl;
        return;
    }

    Task& task = tasks[index];
    switch (editType) {
        case DATE:
            task.setDate(EditUtility::convertToDate(newValue));
            break;
        case DESCRIPTION:
            task.setDesc(newValue);
            break;
        case CATEGORY:
            task.setCategory(newValue);
            break;
        case TITLE:
            task.setTitle(newValue);
            break;
    }
}

//---------------------------------------------Above are edit & completed-----------------------------------------------------


void TaskList::setSortStrategy(SortStrategy* strategy) {
    sortStrategy = strategy;
}

// apply the sort strategy
TaskList TaskList::applySort(SortStrategy::SortOrder sortOrder) {
    if (sortStrategy != nullptr) {
        return sortStrategy->sortBy(*this, sortOrder);
    } else {
        std::cout << "Sort strategy not set." << std::endl;
    }
    return *this;
}

void TaskList::editTask(unsigned index, Task& newTask) {
    assert(index >= 0 && index < tasks.size() && "Out of range - passed validation"); 
    // Directly update the task at the specified index with newTask
    tasks.at(index) = newTask;
}

void TaskList::completeTaskUsingIndex(unsigned index) {
    assert(index >= 0 && index < tasks.size() && !tasks.at(index).isComplete() && "Out of range - passed validation");
    tasks.at(index).markAsComplete(); 
    completedTasks.push_back(tasks.at(index));
    tasks.erase(tasks.begin() + index); 
}

//---------------------------------------------Above are edit & completed-----------------------------------------------------
