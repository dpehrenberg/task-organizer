#include <iostream> // std::cout, std::endl, std::cin
#include <string> // std::string, std::getline
#include <limits> // std::numeric_limits
#include <fstream> // std::ifstream
#include <vector> // std::vector
#include <filesystem> // std::filesystem::directory_iterator

#include "CTaskOrganiser.hpp"

std::vector<std::string> ListOrganisers()
{
    std::vector<std::string> organisers;

    for (const auto& entry : std::filesystem::directory_iterator("organisers"))
    {
        if ((entry.path().extension() == ".txt") && (entry.path().filename() != "last_organiser.txt"))
        {
            organisers.push_back(entry.path().stem());
        }
    }
    return organisers;
}

void LoadOrganiser(CTaskOrganiser &organiser)
{
    std::vector<std::string> organisers = ListOrganisers();
    if (organisers.empty())
    {
        std::cout << "No organisers found.\n";
        
        return;
    }

    std::cout << "\nAvailable organisers:\n";

    size_t orgCount = organisers.size();
    for (size_t i = 0; i < orgCount; ++i)
    {
        std::cout << (i + 1) << ". " << organisers[i] << "\n";
    }

    std::cout << "Enter organiser number to load: ";
    std::string idxInput;
    std::getline(std::cin, idxInput);
    size_t idx = 0;

    try
    {
        idx = std::stoul(idxInput);
    }
    catch (...)
    {
        std::cout << "Invalid input.\n";

        return;
    }

    if (idx < 1 || idx > orgCount)
    {
        std::cout << "Invalid organiser number.\n";

        return;
    }
    
    organiser.LoadFromFile("organisers/" + organisers[idx - 1] + ".txt");
    std::cout << "Organiser '" << organisers[idx - 1] << "' loaded.\n";
}

int main()
{
    ClearScreen();
    std::cout << "\n\n\n\n"<< R"( 
                                 _______   _      _____   _  __ _____
                                |__   __| / \    / ____) | |/ // ____) 
                                   | |   / _ \  ( (___   | ' /( (___  
                                   | |  / / \ \  \___  \ |  (  \___  \
                                   | | / /___\ \  ____) )| . \  ____) ) 
                                   |_|/_/     \_\(_____/ |_|\_\(_____/

)";
    std::cout << "\n\n\n\n\n\n\n\n";
    std::cout << "1. Continue previous organiser\n";
    std::cout << "2. Load organiser\n";

    std::cout << "3. New organiser\n";
    std::cout << "Choose: ";
    std::string startChoice;
    std::getline(std::cin, startChoice);

    CTaskOrganiser organiser;
    if (startChoice == "1")
    {
        std::ifstream last("organisers/last_organiser.txt");
    
        std::string last_name;
        if (last && std::getline(last, last_name) && !last_name.empty())
        {
            organiser.LoadFromFile("organisers/" + last_name + ".txt");
            std::cout << "Loaded last organiser: " << last_name << std::endl;
        }
        else
        {
            std::cout << "No previous organiser found.\n";
        }
    }
    else if (startChoice == "2")
    {
        LoadOrganiser(organiser);
    }   
    // else: new organiser (default)

    std::string input;

    while (true)
    {
        organiser.DisplayAllTasks();
        std::cout << "\nOptions:\n";
        std::cout << "1. Add task\n";
        std::cout << "2. Complete next task\n";
        std::cout << "3. Complete any task\n";
        std::cout << "4. Add multiple tasks\n";
        std::cout << "5. Change task priority\n";
        std::cout << "6. Undo last complete\n";
        std::cout << "7. Change task name\n";
        std::cout << "8. Save tasks\n";
        std::cout << "9. Exit\n";
        std::cout << "10. Load previous organiser\n";
        std::cout << "11. Change organiser name\n";
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
                std::cout << "Enter task description: ";
                {
                    std::string desc;
                    std::getline(std::cin, desc);
                    organiser.AddTask(desc);
                }
                
                break;
            case 2:
                organiser.CompleteFirstTask();
                
                break;
            case 3:
                organiser.CompleteNonFirstTask();
                
                break;
            case 4:
                organiser.AddMultipleTasks();
                
                break;
            case 5:
                organiser.ChangeTaskPriority();
                
                break;
            case 6:
                organiser.UndoLastComplete();
                
                break;
            case 7:
                organiser.ChangeTaskName();
                
                break;
            case 8: // Save tasks
            {
                organiser.Save();
                
                break;
            }
            case 9: // Exit and save
            {
                std::cout << "Saving and exiting.\n";
                organiser.Save();
                
                return 0;
            }
            case 10: // Load previous organiser
            {
                LoadOrganiser(organiser);
                
                break;
            }
            case 11: // Change organiser name
            {
                std::string oldName = organiser.GetName(); // Add a GetName() method if needed
                organiser.ChangeOrganiserName();
                std::string newName = organiser.GetName();
                
                if ((oldName != newName) && (oldName != "default"))
                {
                    std::string oldPath = "organisers/" + oldName + ".txt";
                    std::string newPath = "organisers/" + newName + ".txt";

                    if (std::filesystem::exists(oldPath))
                    {
                        std::filesystem::rename(oldPath, newPath);
                        std::cout << "Organiser file renamed to '" << newPath << "'.\n";
                    }
                }

                break;
            }
            default:
                std::cout << "Invalid option. Try again.\n";
                
                break;
        }
    
        std::cout << std::endl;
    }

    return 0;
}