#ifndef TASK_HPP
#define TASK_HPP

#include <string>// string
#include <iostream>// cout

class Task
{
public:
    Task(const std::string& description_): m_description(description_) {};
    Task(const char* const description_): m_description(description_) {};
    ~Task() = default;

    
    // Disable copy and move semantics
    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;
    Task(Task&&) = delete;
    Task& operator=(Task&&) = delete;
    
    void Display() const
    {
        std::cout << "Task description: " << m_description << std::endl;
    }
private:
    const std::string m_description;
};

#endif // TASK_HPP