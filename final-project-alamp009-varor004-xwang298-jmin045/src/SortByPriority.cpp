#include "../header/SortByPriority.h"
#include "../header/TaskList.h"
#include <algorithm>

TaskList SortByPriority::sortBy(const TaskList &taskList, SortStrategy::SortOrder sortOrder) const {
    TaskList sortedTaskList = taskList;
    std::sort(sortedTaskList.tasks.begin(), sortedTaskList.tasks.end(),
              [sortOrder](Task &a, Task &b) {
                  return sortOrder == SortOrder::ASCENDING ? a.getPriority() < b.getPriority() : a.getPriority() > b.getPriority();
              });
    return sortedTaskList;
}
