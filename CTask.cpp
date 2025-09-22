#include <iostream>

#include "CTask.hpp"

CTask::CTask(const std::string& description_)
    : m_description(description_), m_priority(0)
{
    SetPriority();
}

void CTask::Display() const
{
    std::cout << "Task: " << m_description << " | Priority: " << m_priority << std::endl;
}

unsigned int CTask::GetPriority() const
{
    return m_priority;
}

const std::string& CTask::GetDescription() const
{
    return m_description;
}

// TODO: implement priority setting according to user prompts
void CTask::SetPriority()
{
    m_priority = m_description.length();
}