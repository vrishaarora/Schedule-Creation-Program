#pragma once
#include "SortStrategy.h"

class TaskList;

class SortByPriority : public SortStrategy {
    public:
        [[nodiscard]] TaskList sortBy(const TaskList& taskList, SortStrategy::SortOrder sortOrder) const override;
};