#ifndef CTask_HPP
#define CTask_HPP

#include <string>// string

class CTask
{
public:
    CTask(const std::string& description_, unsigned int priority_);
    ~CTask() = default;

    // Enable copy and move semantics for STL container compatibility
    // the default implementations are sufficient as all members support these operations
    
    void Display() const;
    unsigned int GetPriority() const;
    const std::string& GetDescription() const;
    void ChangeName(const std::string& new_name_);
private:
    std::string m_description;
    unsigned int m_priority;
};

#endif // CTask_HPP