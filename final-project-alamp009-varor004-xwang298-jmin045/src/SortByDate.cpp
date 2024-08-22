#include "../header/SortByDate.h"
#include "../header/TaskList.h"
#include <algorithm>

TaskList SortByDate::sortBy(const TaskList &taskList, SortStrategy::SortOrder sortOrder) const {
    auto compare = [sortOrder](Task& a, Task& b) -> bool {
        if (a.getDate().getYear() != b.getDate().getYear())
            return sortOrder == SortOrder::ASCENDING ? a.getDate().getYear() < b.getDate().getYear() : a.getDate().getYear() > b.getDate().getYear();
        if (a.getDate().getMon() != b.getDate().getMon())
            return sortOrder == SortOrder::ASCENDING ? a.getDate().getMon() < b.getDate().getMon() : a.getDate().getMon() > b.getDate().getMon();
        return sortOrder == SortOrder::ASCENDING ? a.getDate().getDay() < b.getDate().getDay() : a.getDate().getDay() > b.getDate().getDay();
    };
    TaskList sortedTaskList = taskList;
    std::sort(sortedTaskList.tasks.begin(), sortedTaskList.tasks.end(), compare);
    return sortedTaskList;
}
