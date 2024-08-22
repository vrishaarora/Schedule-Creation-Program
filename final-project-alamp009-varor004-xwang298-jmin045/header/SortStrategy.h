#pragma once

class TaskList;

class SortStrategy {
    public:
        enum class SortOrder {
            ASCENDING,
            DESCENDING
        };
        [[nodiscard]] virtual TaskList sortBy(const TaskList& taskList, SortStrategy::SortOrder sortOrder) const = 0;
        virtual ~SortStrategy() = default;
};
