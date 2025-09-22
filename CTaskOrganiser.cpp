#include <iostream>
#include <algorithm>

#include "CTaskOrganiser.hpp"

void CTaskOrganiser::AddTask(const std::string& description)
{
    m_tasks.emplace_back(description);
    std::sort(
        m_tasks.begin(), m_tasks.end(),
        [](const CTask& a, const CTask& b) {
            return a.GetPriority() < b.GetPriority();
        }
    );
}

void CTaskOrganiser::CompleteFirstTask()
{
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
    if (!m_tasks.empty())
    {
        std::cout << "Next task: ";
        m_tasks.front().Display();
    }
    else
    {
        std::cout << "No tasks available" << std::endl;
    }
}