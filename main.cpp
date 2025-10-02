#include <iostream> // std::cout, std::endl, std::cin
#include <string> // std::string, std::getline
#include <limits> // std::numeric_limits

#include "CTaskOrganiser.hpp"

int main()
{
    CTaskOrganiser organiser;
    std::string input;
    std::cout << "\033[2J\033[H"; // Clear for user to see clean welcome message

    std::cout << "\n\n\n\n"<< R"(
                                 _______   _      _____   _  __ _____
                                |__   __| / \    / ____) | |/ // ____) 
                                   | |   / _ \  ( (___   | ' /( (___  
                                   | |  / / \ \  \___  \ |  (  \___  \
                                   | | / /___\ \  ____) )| . \  ____) ) 
                                   |_|/_/     \_\(_____/ |_|\_\(_____/

)";
    std::cout << "\n\n\n\n\n\n\n\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Wait for user

    std::cout << "\033[2J\033[H"; // Clear after user sees welcome

    while (true)
    {
        std::cout << "\nOptions:\n";
        std::cout << "1. Add task\n";
        std::cout << "2. Complete next task\n";
        std::cout << "3. Complete any task\n";
        std::cout << "4. Add multiple tasks\n";
        std::cout << "5. Show all tasks\n";
        std::cout << "6. Exit\n";
        std::cout << "Choose an option: ";
        std::getline(std::cin, input);

        int option = 0;
        try 
        {
            option = std::stoi(input);
        }
        catch (...)
        {
            option = 0;
        }

        switch (option)
        {
            case 1:
            {
                std::cout << "Enter task description: ";
                std::string desc;
                std::getline(std::cin, desc);
                organiser.AddTask(desc);
                organiser.DisplayFirstTask();
                break;
            }
            case 2:
            {
                organiser.CompleteFirstTask();
                organiser.DisplayFirstTask();
                break;
            }
            case 3:
            {
                organiser.CompleteNonFirstTask();
                organiser.DisplayFirstTask();
                break;
            }
            case 4:
            {
                organiser.AddMultipleTasks();
                organiser.DisplayFirstTask();
                break;
            }
            case 5:
            {
                organiser.DisplayAllTasks();
                break;
            }
            case 6:
            {
                std::cout << "Exiting.\n";
                return 0;
            }
            default:
                std::cout << "Invalid option. Try again.\n";
                break;
        }
        std::cout << std::endl;
    }

    return 0;
}