#include "gtest/gtest.h"
#include "../header/Date.h"
#include "../header/Task.h"
#include "../header/SavedList.h"
#include "../header/TaskList.h"
#include "../header/EditUtility.h"
#include "../header/SortStrategy.h"
#include "../header/SortByDate.h"
#include "../header/SortByCategory.h"
#include "../header/SortByPriority.h"
#include "../header/Scheduler.h"

#include <string>
#include <sstream>
#include <map>

#define ASSERT_STRING_CONTAINS(container, contained) assertStringContains(container, contained, __FILE__, __LINE__)
#define ASSERT_STRING_DOES_NOT_CONTAIN(container, notContained) assertStringDoesNotContain(container, notContained, __FILE__, __LINE__)

void assertStringContains(const std::string& container, const std::string& contained, const char* file, int line) {
    if (container.find(contained) == std::string::npos) {
        FAIL() << "Expected: \"" << contained << "\" found in \"" << container << "\"\n"
               << "  Location: " << file << ":" << line;
    }
}

void assertStringDoesNotContain(const std::string& container, const std::string& notContained, const char* file, int line) {
    if (container.find(notContained) != std::string::npos) {
        FAIL() << "Not expected: \"" << notContained << "\" found in \"" << container << "\"\n"
               << "  Location: " << file << ":" << line;
    }
}

TEST(DateTest, defaultCorrect) {
    Date d; 
    EXPECT_EQ(d.getDay(), 1);
}

TEST(DateTest, paramCorrect) {
    Date d(5,1,2014); 
    EXPECT_EQ(d.getDay(), 1);
    EXPECT_EQ(d.getMon(), 5);
    EXPECT_EQ(d.getYear(), 2014);
}

TEST(DateTest, fixesDate) {
    Date d(40,40,2023); 
    EXPECT_EQ(d.getDay(), 1);
    EXPECT_EQ(d.getMon(), 1);
    EXPECT_EQ(d.getYear(), 2023);
}

TEST(DateTest, leapBy4) { //is a leap year
    Date d(2,29,2024); 
    EXPECT_EQ(d.getDay(), 29);
    EXPECT_EQ(d.getMon(), 2);
    EXPECT_EQ(d.getYear(), 2024);
}

TEST(DateTest, leapBy4x2) {
    Date d(2, 29, 2016);
    EXPECT_EQ(d.getDay(), 29);
    EXPECT_EQ(d.getMon(), 2);
    EXPECT_EQ(d.getYear(), 2016);
}

TEST(DateTest, leapBy100) { //is NOT a leap year
    Date d(2,29,1900);
    EXPECT_EQ(d.getDay(), 1);
    EXPECT_EQ(d.getMon(), 2);
    EXPECT_EQ(d.getYear(), 1900);
}

TEST(DateTest, leapBy100x2) {
    Date d(2, 29, 2100);
    EXPECT_EQ(d.getDay(), 1);
    EXPECT_EQ(d.getMon(), 2);
    EXPECT_EQ(d.getYear(), 2100);
}

TEST(DateTest, leapBy400) { //is a leap year
    Date d(2,29,2000); 
    EXPECT_EQ(d.getDay(), 29);
    EXPECT_EQ(d.getMon(), 2);
    EXPECT_EQ(d.getYear(), 2000);
}

TEST(DateTest, leapBy400x2) {
    Date d(2,29,2400); 
    EXPECT_EQ(d.getDay(), 29);
    EXPECT_EQ(d.getMon(), 2);
    EXPECT_EQ(d.getYear(), 2400);
}

TEST(DateTest, defaultString) { 
    Date d; 
    EXPECT_EQ(d.dateString(), "January 1, 2000"); 
}

TEST(DateTest, paramString) { 
    Date d(3,2,2005); 
    EXPECT_EQ(d.dateString(), "March 2, 2005"); 
}

TEST(DateTest, nonLeapYearDateString) {
    Date d(7, 15, 2023);
    EXPECT_EQ(d.dateString(), "July 15, 2023");
}

TEST(DateTest, leapYearDateString) {
    Date d(2, 29, 2024);
    EXPECT_EQ(d.dateString(), "February 29, 2024");
}

TEST(DateTest, minimumYearDateString) {
    Date d(12, 31, 1);
    EXPECT_EQ(d.dateString(), "December 31, 1");
}

TEST(TaskTest, defaultConstr) { 
    Task t; 
    EXPECT_EQ(t.getTitle(), "NEED_TITLE"); 
    EXPECT_EQ(t.getCategory(), "NEED_CATEGORY"); 
    EXPECT_EQ(t.getDesc(), "NEED_DESC"); 
    EXPECT_EQ(t.getDate().dateString(), "January 1, 2000"); 
    EXPECT_EQ(t.getPriority(), 0); 
    EXPECT_EQ(t.isComplete(), false); 
}

TEST(TaskTest, paramConstr) {
    Task t(Date(2,29,2024), "T", "C", "D", 3); 
    EXPECT_EQ(t.getTitle(), "T"); 
    EXPECT_EQ(t.getCategory(), "C"); 
    EXPECT_EQ(t.getDesc(), "D"); 
    EXPECT_EQ(t.getDate().dateString(), "February 29, 2024"); 
    EXPECT_EQ(t.isComplete(), false); 
    EXPECT_EQ(t.getPriority(), 3); 
}

TEST(SavedListTest, addingToFile) {

    std::ofstream reset("test.txt", std::ios::trunc);

    if (reset.is_open()) {
        reset.close();
    } else {
        throw std::runtime_error("Error opening file for truncation.");
    }
    Task t(Date(1,1,2000), "T", "C", "D", 3); 
    SavedList SL("test.txt");
    SL.addTask(t); 
    EXPECT_EQ(SL.size(), 1);
}
TEST(SavedListTest, loadingFromFile) { 
    Task t(Date(1,1,2000), "T", "C", "D", 3); 
    SavedList SL("test.txt");
    SL.addTask(t); 
    EXPECT_EQ(SL.size(), 2);
    ostringstream result; 
    SL.printTasks(result); 
    ASSERT_STRING_CONTAINS(result.str(), "Priority: 3");
}

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
    std::string expected = "1) Task 2\n";  // Assuming delTask works correctly
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
    Date expectedDate = EditUtility::convertToDate("12/31/2023");
    EXPECT_EQ(editedTask.getDate().dateString(), expectedDate.dateString());
}

TEST_F(TaskListTest, CompleteTask) {
    taskList->addTask(task1);
    taskList->completeTaskUsingIndex(0);
    std::ostringstream out;
    taskList->printCompletedTasks(out);
    EXPECT_TRUE(out.str().find("Task 1") != std::string::npos);  // Verify task is marked or moved as completed
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
    std::string expected = "1) Task 1\n2) Task 2\n"; // Expect only task1 and task2 to be included and sorted by date

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