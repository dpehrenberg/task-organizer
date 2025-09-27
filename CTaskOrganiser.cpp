#include <iostream>
#include <algorithm>// std::sort
#include <limits> // std::numeric_limits

#include "CTaskOrganiser.hpp"

CTaskOrganiser::CTaskOrganiser()
{
    m_tasks.emplace_back("START", 0);
    m_tasks.emplace_back("END", std::numeric_limits<unsigned int>::max());
}

void CTaskOrganiser::AddTask(const std::string& description)
{
    int left = 0;
    int right = m_tasks.size() - 1;
    int insertPos = 1; // Default to after START

    while (left < right - 1)
    {
        int mid = left + (right - left) / 2;
        std::cout << "Should the new task come before: ";
        m_tasks[mid].Display();
        std::cout << "(y/n): ";
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
                   CTask(description, newPriority));
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
    if (2 >= m_tasks.size())
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
    std::system("clear");
    if (2 >= m_tasks.size())
    {
        std::cout << "No tasks" << std::endl;
        return;
    }

    std::cout << "\nAll tasks (highest priority first):\n";
    // Skip dummy tasks: first (START) and last (END)
    for (size_t i = 1; i < m_tasks.size() - 1; ++i)
    {
        m_tasks[i].Display();
    }
}