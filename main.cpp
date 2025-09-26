#include <iostream> // std::cout, std::endl, std::cin
#include <string> // std::string, std::getline

#include "CTaskOrganiser.hpp"

int main()
{
    CTaskOrganiser organiser;
    std::string input;
    std::cout << "\nWelcome to Tasks!:\n";

    while (true)
    {
        organiser.DisplayFirstTask();
        std::cout << "\nOptions:\n";
        std::cout << "1. Add task\n";
        std::cout << "2. Complete next task\n";
        std::cout << "3. Show all tasks\n";
        std::cout << "4. Exit\n";
        std::cout << "Choose an option: ";
        std::getline(std::cin, input);

        if (input == "1")
        {
            std::cout << "Enter task description: ";
            std::string desc;
            std::getline(std::cin, desc);
            organiser.AddTask(desc);
        }
        else if (input == "2")
        {
            organiser.CompleteFirstTask();
        }
        else if (input == "3")
        {
            organiser.DisplayAllTasks();
        }
        else if (input == "4")
        {
            std::cout << "Exiting.\n";
            break;
        }
        else
        {
            std::cout << "Invalid option. Try again.\n";
        }
        std::cout << std::endl;
    }

    return 0;
}