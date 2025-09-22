#ifndef CTask_HPP
#define CTask_HPP

#include <string>// string

class CTask
{
public:
    CTask(const std::string& description_);
    ~CTask() = default;

    // Enable copy and move semantics for STL container compatibility
    CTask(const CTask&) = default;
    CTask& operator=(const CTask&) = default;
    CTask(CTask&&) = default;
    CTask& operator=(CTask&&) = default;
    
    void Display() const;
    unsigned int GetPriority() const; // Add getter for priority
    const std::string& GetDescription() const; // Add getter for description
private:
    void SetPriority();
    const std::string m_description;
    unsigned int m_priority;
    //TODO: remember last removed task description and priority for undo functionality
};

#endif // CTask_HPP