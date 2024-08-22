#include "gtest/gtest.h"
#include <sstream>
#include "../header/TaskList.h"
#include "../header/SortByDate.h"
#include "../header/SortByCategory.h"
#include "../header/SortByPriority.h"
#include "../header/Scheduler.h"

class TaskListTest : public ::testing::Test {
protected:
    TaskList* taskList{};

    Task task1{Date{10, 1, 2023}, "Task 1", "Work", "Description 1",0};
    Task task2{Date{12, 2, 2023}, "Task 2", "Personal", "Description 2",1};

    Task categoryTask1{Date{10, 1, 2023}, "Task 1", "A", "Description 1",0};
    Task categoryTask2{Date{12, 2, 2023}, "Task 2", "B", "Description 2",1};

    Task schedulerTask1{Date{1, 1, 2023}, "Task 1", "Work", "Description 1", 1};
    Task schedulerTask2{Date{1, 2, 2023}, "Task 2", "Personal", "Description 2", 2};
    Task schedulerTask3{Date{1, 3, 2023}, "Task 3", "Work", "Description 3", 0}; // This task should be excluded by the date limit

    SortStrategy* sortByDate{};
    SortStrategy* sortByCategory{};
    SortStrategy* sortByPriority{};
    void SetUp() override {
        taskList = new TaskList();
        sortByDate = new SortByDate();
        sortByCategory = new SortByCategory();
        sortByPriority = new SortByPriority();
    }

    void TearDown() override {
        taskList = {};
        sortByDate = {};
        sortByCategory = {};
        sortByPriority = {};
    }

    // after merge with others code, printTitles is now return:
    // out.str()
    //    Which is: "1) Task 1\n2) Task 2\n3) Task 3\n"
};

TEST_F(TaskListTest, AddTask) {
    taskList->addTask(task1);
    std::ostringstream out;
    taskList->printTitles(out);
    std::string expected = "1) Task 1\n";
    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, DeleteTask) {
    taskList->addTask(task1);
    taskList->addTask(task2);
    taskList->delTask(0);
    std::ostringstream out;
    taskList->printTitles(out);
    std::string expected = "1) Task 2\n";
    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, EditTask_AttributesIndividually) {
    // Add the original task to the list
    taskList->addTask(task1);

    // Edit the task's title
    taskList->editTask(0, TaskList::EditType::TITLE, "Updated Title");
    // Edit the task's category
    taskList->editTask(0, TaskList::EditType::CATEGORY, "Updated Category");
    // Edit the task's description
    taskList->editTask(0, TaskList::EditType::DESCRIPTION, "Updated Description");
    // Edit the task's date
    taskList->editTask(0, TaskList::EditType::DATE, "12/31/2023");

    Task editedTask = taskList->getTask(0);

    // Verify that the task at index 0 has been updated correctly
    EXPECT_EQ(editedTask.getTitle(), "Updated Title");
    EXPECT_EQ(editedTask.getCategory(), "Updated Category");
    EXPECT_EQ(editedTask.getDesc(), "Updated Description");
    Date expectedDate2 = Date{12, 31, 2023};
    EXPECT_EQ(editedTask.getDate().dateString(), expectedDate2.dateString());
}

TEST_F(TaskListTest, CompleteTask) {
    taskList->addTask(task1);
    taskList->completeTaskUsingIndex(0);
    std::ostringstream out;
    taskList->printCompletedTasks(out);
    EXPECT_TRUE(taskList->getTask(0).isComplete());
}

TEST_F(TaskListTest, SortByDateAsc) {
    taskList->addTask(task1);
    taskList->addTask(task2);
    taskList->setSortStrategy(sortByDate);
    TaskList result = taskList->applySort(SortStrategy::SortOrder::ASCENDING);
    std::ostringstream out;
    result.printTitles(out);
    std::string expected = "1) Task 1\n2) Task 2\n";
    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, SortByDateDesc) {
    taskList->addTask(task1);
    taskList->addTask(task2);
    taskList->setSortStrategy(sortByDate);
    TaskList result = taskList->applySort(SortStrategy::SortOrder::DESCENDING);
    std::ostringstream out;
    result.printTitles(out);
    std::string expected = "1) Task 2\n2) Task 1\n";
    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, SortByCategoryAsc) {
    taskList->addTask(categoryTask1);
    taskList->addTask(categoryTask2);
    taskList->setSortStrategy(sortByCategory);
    TaskList result = taskList->applySort(SortStrategy::SortOrder::ASCENDING);
    EXPECT_EQ(result.getTask(0).getCategory(), "A");
    EXPECT_EQ(result.getTask(1).getCategory(), "B");
}

TEST_F(TaskListTest, SortByCategoryDesc) {
    taskList->addTask(categoryTask1);
    taskList->addTask(categoryTask2);
    taskList->setSortStrategy(sortByCategory);
    TaskList result = taskList->applySort(SortStrategy::SortOrder::DESCENDING);
    EXPECT_EQ(result.getTask(0).getCategory(), "B");
    EXPECT_EQ(result.getTask(1).getCategory(), "A");
}

TEST_F(TaskListTest, SortByPriorityAsc) {
    taskList->addTask(task1);
    taskList->addTask(task2);
    taskList->setSortStrategy(sortByPriority);
    TaskList result = taskList->applySort(SortStrategy::SortOrder::ASCENDING);
    std::ostringstream out;
    result.printTitles(out);
    std::string expected = "1) Task 1\n2) Task 2\n";
    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, SortByPriorityDesc) {
    taskList->addTask(task1);
    taskList->addTask(task2);
    taskList->setSortStrategy(sortByPriority);
    TaskList result = taskList->applySort(SortStrategy::SortOrder::DESCENDING);
    std::ostringstream out;
    result.printTitles(out);
    std::string expected = "1) Task 2\n2) Task 1\n";
    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, ScheduleTasksBeforeDateLimit) {
    taskList->addTask(schedulerTask1);
    taskList->addTask(schedulerTask2);
    taskList->addTask(schedulerTask3);
    Date limit{1, 2, 2023}; // Set the limit to exclude schedulerTask3
    TaskList scheduledTasks = Scheduler::ScheduleTasks(*taskList, limit);

    std::ostringstream out;
    scheduledTasks.printTitles(out);
    std::string expected = "1) Task 1\n2) Task 2\n"; // Expect tasks to be sorted by date first, then by priority within the same date

    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, ScheduleTasksWithPrioritySorting) {
    taskList->addTask(schedulerTask1);
    taskList->addTask(schedulerTask2);
    taskList->addTask(schedulerTask3);
    Date limit{1, 3, 2023}; // Include all tasks
    TaskList scheduledTasks = Scheduler::ScheduleTasks(*taskList, limit);

    std::ostringstream out;
    scheduledTasks.printTitles(out);
    std::string expected = "1) Task 1\n2) Task 2\n3) Task 3\n"; // Expect tasks to be sorted by date first, then by priority within the same date

    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, ScheduleTest) {
    Task schedulerTask1{Date{1, 1, 1}, "test", "g", "g", 1};
    Task schedulerTask2{Date{2, 2, 2}, "two", "two", "two", 2};
    Task schedulerTask3{Date{2, 3, 2}, "two1", "two", "two", 0};
    taskList->addTask(schedulerTask1);
    taskList->addTask(schedulerTask2);
    taskList->addTask(schedulerTask3);
    Date limit{1, 3, 2023}; // Include all tasks
    TaskList scheduledTasks = Scheduler::ScheduleTasks(*taskList, limit);
    std::ostringstream out;
    scheduledTasks.printTitles(out);
    //out.str()
    //    Which is: "1) Task 3\n2) Task 1\n3) Task 2\n"
    std::string expected = "1) test\n2) two\n3) two1\n"; // Expect tasks to be sorted by date first, then by priority within the same date
    EXPECT_EQ(out.str(), expected);
}

TEST_F(TaskListTest, ScheduleTestFeb) {
    Task schedulerTask1{Date{2, 1, 1}, "1", "g", "g", 1};
    Task schedulerTask2{Date{2, 2, 1}, "2", "two", "two", 2};
    Task schedulerTask3{Date{2, 2, 1}, "3", "two", "two", 1};
    Task schedulerTask4{Date{2, 3, 1}, "4", "two", "two", 0};
    taskList->addTask(schedulerTask1);
    taskList->addTask(schedulerTask2);
    taskList->addTask(schedulerTask3);
    taskList->addTask(schedulerTask4);
    Date limit{1, 3, 2023}; // Include all tasks
    TaskList scheduledTasks = Scheduler::ScheduleTasks(*taskList, limit);
    std::ostringstream out;
    scheduledTasks.printTitles(out);
    // should output 1 3 2 4
    std::string expected = "1) 1\n2) 3\n3) 2\n4) 4\n"; // Expect tasks to be sorted by date first, then by priority within the same date
    EXPECT_EQ(out.str(), expected);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}