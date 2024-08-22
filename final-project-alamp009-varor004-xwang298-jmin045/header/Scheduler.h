#pragma once
#include "TaskList.h"
#include "Date.h"

class Scheduler {
public:
    // as in
    // ...sure if we should be changing the original list
    // TaskList Scheduler::ScheduleTasks(TaskList&, Date limit) {
    // should take in list, sort by date first, prio second, ...
    static TaskList ScheduleTasks(TaskList& taskList, const Date& limit);
};
