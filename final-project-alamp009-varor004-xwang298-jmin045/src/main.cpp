#include "../header/TaskManager.h"

#include <iostream> 
#include <string> 
#include <sstream>

using namespace std; 

int main() { 
    // Task t1(Date(4,2,2025), "T1", "C1", "D1", 1); 
    // Task t2(Date(2,8,2023), "T2", "C2", "D2", 1); 
    // Task t3(Date(11,14,2024), "T3", "C3", "D3", 1); 
    // Task t4(Date(2,29,2024), "T4", "C4", "D4", 1); 
    // vector<Task> input = {t1, t2, t3, t4}; 
    TaskManager TM; 
    while (TM.printMainMenu(cout)); 
}