#include <iostream>
#include <algorithm>// std::sort
#include <limits> // std::numeric_limits

#include "CTaskOrganiser.hpp"

void CTaskOrganiser::AddTask(const std::string& description)
{
    std::cout << "Enter priority for this task (highest priority 0, lowest priority " << std::numeric_limits<unsigned int>::max() << "): ";
    unsigned int priority = 0;
    std::cin >> priority;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // clear input buffer

    m_tasks.emplace_back(description, priority);
    std::sort(
        m_tasks.begin(), m_tasks.end(),
        [](const CTask& a, const CTask& b) {
            return a.GetPriority() < b.GetPriority();
        }
    );
}

void CTaskOrganiser::CompleteFirstTask()
{
    std::system("clear");
    if (m_tasks.empty())
    {
        std::cout << "No tasks to complete" << std::endl;
    }
    else
    {
        std::cout << "Completing task: ";
        m_tasks.front().Display();
        m_tasks.erase(m_tasks.begin());
    }
}

void CTaskOrganiser::DisplayFirstTask() const
{
    std::system("clear");
    if (!m_tasks.empty())
    {
        std::cout << "Next task: ";
        m_tasks.front().Display();
    }
}

void CTaskOrganiser::DisplayAllTasks() const
{
    std::system("clear");
    if (m_tasks.empty())
    {
        std::cout << "No tasks available.\n";
        return;
    }

    std::cout << "\nAll tasks (highest priority first):\n";
    for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it)
    {
        it->Display();
    }
}