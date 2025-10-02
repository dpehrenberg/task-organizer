#include <iostream>

#include "CTask.hpp"

CTask::CTask(const std::string& description_, unsigned int priority_)
    : m_description(description_), m_priority(priority_)
{}

void CTask::Display() const
{
    std::cout << m_description << std::endl;
}

unsigned int CTask::GetPriority() const
{
    return m_priority;
}

const std::string& CTask::GetDescription() const
{
    return m_description;
}

void CTask::ChangeName(const std::string& new_name_)
{
    m_description = new_name_;
}