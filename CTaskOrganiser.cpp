#include <iostream>
#include <algorithm>// std::sort
#include <limits> // std::numeric_limits
#include <fstream> // std::ifstream, std::ofstream
#include <filesystem> //create_directory

#include "CTaskOrganiser.hpp"

void EnsureOrganisersDir()
{
    std::filesystem::create_directory("organisers");
}

CTaskOrganiser::CTaskOrganiser()
{
    m_tasks.emplace_back("START", 0);
    m_tasks.emplace_back("END", std::numeric_limits<unsigned int>::max());
}

void CTaskOrganiser::AddMultipleTasks()
{
    std::vector<std::string> descriptions;
    std::cout << "Enter task descriptions (empty line to finish):\n";
    while (true)
    {
        std::string desc;
        std::getline(std::cin, desc);
        if (desc.empty())
        {
            break;
        }

        descriptions.push_back(desc);
    }

    for (const auto &desc : descriptions)
    {
        AddTask(desc);
    }
}

void CTaskOrganiser::AddTask(const std::string& description_)
{
    int left = 0;
    int right = m_tasks.size() - 1;
    int insertPos = 1; // Default to after START

    while (left < right - 1)
    {
        int mid = left + (right - left) / 2;
        std::cout << "Should the new task: \"" << description_ << "\" ";
        std::cout << "come before \"" << m_tasks[mid].GetDescription() << "\" (y/n): ";
        std::string answer;
        std::getline(std::cin, answer);

        if (answer == "y" || answer == "Y")
        {
            right = mid;
        }
        else
        {
            left = mid;
        }
    }
    insertPos = right;

    // Calculate new priority as average of adjacent tasks
    unsigned int prevPriority = m_tasks[left].GetPriority();
    unsigned int nextPriority = m_tasks[right].GetPriority();
    unsigned int newPriority = prevPriority / 2 + nextPriority / 2;

    m_tasks.insert(m_tasks.begin() + insertPos,
                   CTask(description_, newPriority));
}

void CTaskOrganiser::CompleteFirstTask()
{
    ClearScreen();
    if (!HasRealTasks())
    {
        std::cout << "No tasks to complete" << std::endl;
        return;
    }
    m_lastRemovedTask = m_tasks[1];
    std::cout << "Completing task: ";
    m_tasks[1].Display();
    m_tasks.erase(m_tasks.begin() + 1);
}

void CTaskOrganiser::DisplayFirstTask() const
{
    ClearScreen();
    if (!HasRealTasks())
    {
        std::cout << "No tasks" << std::endl;
        return;
    }
        
    std::cout << "Next task: ";
    m_tasks[1].Display();// Always the second task (first is START)
    std::cout << std::endl;
}

void CTaskOrganiser::DisplayAllTasks() const
{
    ClearScreen();
    if (!HasRealTasks())
    {
        return;
    }

    std::cout << "\nAll tasks (highest priority first):\n" << std::endl;
    // Skip dummy tasks: first (START) and last (END)
    for (size_t i = 1; i < m_tasks.size() - 1; ++i)
    {
        m_tasks[i].Display();
    }
}

void CTaskOrganiser::CompleteNonFirstTask()
{
    ClearScreen();

    if (!HasRealTasks())
    {
        std::cout << "No tasks to complete.\n";
        return;
    }

    PrintTasksWithIndices();

    std::cout << "Enter the number of the task to complete: ";
    std::string idx_input;
    std::getline(std::cin, idx_input);
    size_t idx;
    try {
        idx = std::stoul(idx_input);
    } catch (...) {
        std::cout << "Invalid task number.\n";
        return;
    }
    if (!IsValidTaskIndex(idx))
    {
        std::cout << "Invalid task number.\n";
        return;
    }
    
    m_lastRemovedTask = m_tasks[idx];
    std::cout << "Completing task: ";
    m_tasks[idx].Display();
    m_tasks.erase(m_tasks.begin() + idx);
}

void CTaskOrganiser::ChangeTaskPriority()
{
    ClearScreen();

    if (!HasRealTasks())
    {
        std::cout << "No tasks to change.\n";
        return;
    }

    PrintTasksWithIndices();

    std::cout << "Enter the number of the task to change priority: ";
    size_t idx;
    std::cin >> idx;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (!IsValidTaskIndex(idx))
    {
        std::cout << "Invalid task number.\n";
        return;
    }

    // Save the description and remove the task
    std::string desc = m_tasks[idx].GetDescription();
    m_tasks.erase(m_tasks.begin() + idx);

    // Insert the task again using the AddTask logic (binary search with user prompts)
    std::cout << "Re-inserting task: " << desc << std::endl;
    AddTask(desc);

    std::cout << "Priority updated.\n";
}

void CTaskOrganiser::ChangeTaskName()
{
    ClearScreen();

    if (!HasRealTasks())
    {
        std::cout << "No tasks to rename.\n";
        return;
    }

    PrintTasksWithIndices();

    std::cout << "Enter the number of the task to rename: ";
    std::string idx_input;
    std::getline(std::cin, idx_input);
    size_t idx;
    try {
        idx = std::stoul(idx_input);
    } catch (...) {
        std::cout << "Invalid task number.\n";
        return;
    }
    if (!IsValidTaskIndex(idx))
    {
        std::cout << "Invalid task number.\n";
        return;
    }

    std::cout << "Current name: ";
    m_tasks[idx].Display();
    std::cout << "Enter new name: ";
    std::string new_name;
    std::getline(std::cin, new_name);

    m_tasks[idx].ChangeName(new_name);

    std::cout << "Task name updated.\n";
}

bool CTaskOrganiser::HasRealTasks() const
{
    return 2 < m_tasks.size();
}

void CTaskOrganiser::PrintTasksWithIndices() const
{
    std::cout << "Tasks:\n";
    for (size_t i = 1; i < m_tasks.size() - 1; ++i)
    {
        std::cout << i << ". ";
        m_tasks[i].Display();
    }
}

bool CTaskOrganiser::IsValidTaskIndex(size_t idx_) const
{
    return (1 <= idx_) && (idx_ < m_tasks.size() - 1);
}

void CTaskOrganiser::UndoLastComplete()
{
    if (!m_lastRemovedTask)
    {
        std::cout << "No task to undo.\n";
        return;
    }

    // Restore the task at its original priority, without user prompts
    const std::string& desc = m_lastRemovedTask->GetDescription();
    unsigned int priority = m_lastRemovedTask->GetPriority();

    // Find the correct position to insert based on priority
    auto it = m_tasks.begin() + 1; // skip START dummy
    while (it != m_tasks.end() - 1 && it->GetPriority() < priority)
    {
        ++it;
    }

    m_tasks.insert(it, CTask(desc, priority));
    m_lastRemovedTask.reset();
    std::cout << "Last completed task restored.\n";
}

// Save all real tasks (skip dummies)
void CTaskOrganiser::SaveWithName(const std::string& filename) const
{
    std::ofstream ofs(filename);
    // Use iterator to skip START and END dummies
    auto end = m_tasks.end() - 1;
    for (auto it = m_tasks.begin() + 1; it != end; ++it)
    {
        ofs << it->GetPriority() << '\t' << it->GetDescription() << '\n';
    }
}

// Load tasks from file (clears current tasks)
void CTaskOrganiser::LoadFromFile(const std::string& filename)
{
    m_tasks.clear();
    m_tasks.emplace_back("START", 0);
    m_tasks.emplace_back("END", std::numeric_limits<unsigned int>::max());

    std::ifstream ifs(filename);
    unsigned int priority;
    std::string description;
    while (ifs >> priority)
    {
        ifs.get(); // skip tab
        std::getline(ifs, description);
        m_tasks.insert(m_tasks.end() - 1, CTask(description, priority));
    }
    // Set organiser name from filename (strip .txt and path)
    auto slash = filename.find_last_of("/\\");
    auto start = (slash == std::string::npos) ? 0 : slash + 1;
    auto pos = filename.rfind(".txt");
    if (pos != std::string::npos)
        m_name = filename.substr(start, pos - start);
    else
        m_name = filename.substr(start);
}

void CTaskOrganiser::Save()
{
    EnsureOrganisersDir();

    // If organiser is empty (no real tasks)
    if (!HasRealTasks())
    {
        std::cout << "Organiser is empty. Nothing to save.\n";
        return;
    }

    // If no name yet, ask for one
    if ("default" == m_name)
    {
        std::cout << "Enter organiser name to save: ";
        std::getline(std::cin, m_name);
    }
    std::string path = "organisers/" + m_name + ".txt";
    SaveWithName(path);

    // Update last_organiser.txt
    std::ofstream last("organisers/last_organiser.txt");
    last << m_name << std::endl;

    std::cout << "Organiser saved as \"" << m_name << "\".\n";
}

void CTaskOrganiser::ChangeOrganiserName()
{
    std::cout << "Current organiser name: " << GetName() << "\n";
    std::cout << "Enter new organiser name: ";
    std::string new_name;
    std::getline(std::cin, new_name);
    if (!new_name.empty())
    {
        m_name = new_name;
        std::cout << "Organiser name changed to \"" << m_name << "\".\n";
    }
    else
    {
        std::cout << "Organiser name not changed.\n";
    }
}

const std::string& CTaskOrganiser::GetName() const
{
    return m_name;
}