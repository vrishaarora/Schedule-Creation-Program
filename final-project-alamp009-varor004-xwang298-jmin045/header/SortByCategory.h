#pragma once
#include "SortStrategy.h"

class TaskList;

class SortByCategory : public SortStrategy {
    public:
        [[nodiscard]] TaskList sortBy(const TaskList& taskList, SortStrategy::SortOrder sortOrder) const override;
};