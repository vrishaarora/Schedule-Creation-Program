#include "../header/Scheduler.h"
#include "../header/SortByDate.h"
#include "../header/SortByPriority.h"
#include <algorithm>

TaskList Scheduler::ScheduleTasks(TaskList &taskList, const Date &limit) {
    TaskList tasksWithinLimit;

    std::copy_if(taskList.tasks.begin(), taskList.tasks.end(), std::back_inserter(tasksWithinLimit.tasks),
                 [&limit](Task& task) {
                     const Date& d = task.getDate();
                     return d.getYear() < limit.getYear() ||
                            (d.getYear() == limit.getYear() && d.getMon() < limit.getMon()) ||
                            (d.getYear() == limit.getYear() && d.getMon() == limit.getMon() && d.getDay() <= limit.getDay());
                 });

    auto compareTasks = [](Task& a, Task& b) {
        const Date& dateA = a.getDate();
        const Date& dateB = b.getDate();
        if (dateA.getYear() != dateB.getYear()) return dateA.getYear() < dateB.getYear();
        if (dateA.getMon() != dateB.getMon()) return dateA.getMon() < dateB.getMon();
        if (dateA.getDay() != dateB.getDay()) return dateA.getDay() < dateB.getDay();
        return a.getPriority() < b.getPriority();
    };

    std::sort(tasksWithinLimit.tasks.begin(), tasksWithinLimit.tasks.end(), compareTasks);

    return tasksWithinLimit;
}

