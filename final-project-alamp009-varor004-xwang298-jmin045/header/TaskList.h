#pragma once
#include "Task.h"
#include "SortStrategy.h"
#include <vector>
#include <iostream>

class TaskList {

public:
    enum EditType { DATE, DESCRIPTION, CATEGORY, TITLE };

    std::vector<Task> tasks;
private:
    SortStrategy* sortStrategy{};
    friend class SortByCategory; 
    friend class SortByDate; 
    friend class SortByPriority; 
    friend class Scheduler;
    
protected:
    // still incomplete tasks
    std::vector<Task> completedTasks; // completed tasks

public:

    // constructor
    TaskList();

    virtual ~TaskList() = default;

    // Parameterized constructor that accepts an initial list of tasks
    explicit TaskList(const std::vector<Task>& initialTasks) : tasks(initialTasks) {}

    //---------------------------------------------Above are constructor-----------------------------------------------

    // Print all tasks in the list
    void printTasks(std::ostream& out);

    // Print all task titles in the list
    void printTitles(std::ostream& out);

    void printUnfinishedTitles(std::ostream& out);

    void printFinishedTitles(std::ostream& out);

    // Print all completed tasks
    void printCompletedTasks(std::ostream& out);

    // Print all completed task titles
    void printCompletedTitles(std::ostream& out);

    //---------------------------------------------Above are print methods---------------------------------------------

    // Get the number of tasks in the list by index
    Task getTask(unsigned i);

    unsigned size() { return tasks.size(); }
    unsigned completesize() { return completedTasks.size(); }

    //---------------------------------------------Above are tools---------------------------------------------

    // Add a new task to the list
    void addTask(Task&);

    // Delete a task from the list
    void delTask(unsigned);

    // Edit a task in the list
    void editTask(unsigned index, EditType editType, const std::string& newValue);

    void editTask(unsigned, Task&);

    // Mark a task as complete
    void completeTaskUsingIndex(unsigned);

    //---------------------------------------------Above are edit & completed------------------------------------

    // Set the sort strategy
    void setSortStrategy(SortStrategy* strategy);

    // Sort the tasks in the list
    TaskList applySort(SortStrategy::SortOrder sortOrder);

    //---------------------------------------------Above are sort related--------------------------------------

};