#include <iostream>
#include <algorithm>// std::sort
#include <limits> // std::numeric_limits

#include "CTaskOrganiser.hpp"

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
        std::cout << "No tasks" << std::endl;
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
    size_t idx;
    std::cin >> idx;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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