#include "../header/SortByCategory.h"
#include "../header/TaskList.h"
#include <algorithm>

TaskList SortByCategory::sortBy(const TaskList &taskList, SortStrategy::SortOrder sortOrder) const {
    TaskList sortedTaskList = taskList;
    std::sort(sortedTaskList.tasks.begin(), sortedTaskList.tasks.end(),
              [sortOrder](Task &a, Task &b) {
                  return sortOrder == SortOrder::ASCENDING ? a.getCategory() < b.getCategory() : a.getCategory() > b.getCategory();
              });
    return sortedTaskList;
}
