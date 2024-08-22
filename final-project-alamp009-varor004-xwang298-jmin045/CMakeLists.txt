CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

ADD_SUBDIRECTORY(googletest)

# Set the C++ standard to 11 or later
SET(CMAKE_CXX_STANDARD 11)

# Add all your source files to the variable SOURCES
SET(SOURCES
    src/DateUtility.cpp
    src/Date.cpp
    src/Task.cpp
    src/EditUtility.cpp
    src/TaskList.cpp
    src/SavedList.cpp
    src/SortByDate.cpp
    src/SortByCategory.cpp
    src/SortByPriority.cpp
    src/Scheduler.cpp
    src/TaskManager.cpp
    src/main.cpp
)

# Set the compiler flags for debugging information
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Create the executable for your main program
ADD_EXECUTABLE(all.out ${SOURCES})

# Add a target to run tests through Valgrind
FIND_PROGRAM(MEMORYCHECK_COMMAND valgrind)
SET(MEMORYCHECK_COMMAND_OPTIONS "--leak-check=full")

ADD_CUSTOM_TARGET(memcheck
    COMMAND ${MEMORYCHECK_COMMAND} ${MEMORYCHECK_COMMAND_OPTIONS} ./all.out
    DEPENDS all.out
    COMMENT "Running Valgrind for memory leak detection"
)

ADD_EXECUTABLE(allTests
    src/DateUtility.cpp
    src/Date.cpp
    src/Task.cpp
    src/EditUtility.cpp
    src/TaskList.cpp
    src/SavedList.cpp
    src/SortByDate.cpp
    src/SortByCategory.cpp
    src/SortByPriority.cpp
    src/Scheduler.cpp
    src/TaskManager.cpp
    
    src/test.cpp  
)

TARGET_LINK_LIBRARIES(allTests gtest)
TARGET_COMPILE_DEFINITIONS(allTests PRIVATE gtest_disable_pthreads=ON)