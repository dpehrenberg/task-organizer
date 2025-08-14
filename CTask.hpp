#ifndef CTask_HPP
#define CTask_HPP

#include <string>// string
#include <iostream>// cout

class CTask
{
public:
    CTask(const std::string& description_): m_description(description_) {};
    CTask(const char* const description_): m_description(description_) {};
    ~CTask() = default;

    
    // Disable copy and move semantics
    CTask(const CTask&) = delete;
    CTask& operator=(const CTask&) = delete;
    CTask(CTask&&) = delete;
    CTask& operator=(CTask&&) = delete;
    
    void Display() const
    {
        std::cout << "CTask description: " << m_description << std::endl;
    }
private:
    const std::string m_description;
};

#endif // CTask_HPP