#include <iostream>//cout
#include <string>//string

#include "task.hpp"


int main()
{
    std::string description = "This is a task description.";
    Task task(description);
    task.Display();

    const char* c_description = "This is another task description.";
    Task task2(c_description);
    task2.Display();

    return 0;
}