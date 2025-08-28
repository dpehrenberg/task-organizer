#include <iostream>// cout

#include "CTask.hpp"

CTask::CTask(const std::string& description_): m_description(description_), m_priority(SetPriority())
{}

int CTask::SetPriority() const
{
    //phase 1: simple priority based on creation order
    static int ret = 0;
    ++ret;
    return ret;
}

void CTask::Display() const
{
    std::cout << m_description << std::endl;
}