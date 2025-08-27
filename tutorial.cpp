#include <iostream>//cout
#include <string>//string

#include "CTask.hpp"


int main()
{
    std::string description = "Task created with string.";
    CTask Task(description);
    Task.Display();

    const char* const c_description = "Task created with string char*.";
    CTask Task2(c_description);
    Task2.Display();

    return 0;
}