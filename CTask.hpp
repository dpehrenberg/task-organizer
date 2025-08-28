#ifndef CTask_HPP
#define CTask_HPP

#include <string>// string

class CTask
{
public:
    CTask(const std::string& description_);
    ~CTask() = default;

    //copy and move constructors and assignment operators are enabled to allow storing CTask objects in STL containers
    // The compiler-generated versions are sufficient since all members support copying and moving.
    CTask(const CTask&) = default;
    CTask& operator=(const CTask&) = default;
    CTask(CTask&&) = default;
    CTask& operator=(CTask&&) = default;
    
    void Display() const;
private:
    int SetPriority() const;
    const std::string m_description;
    int m_priority;
    //TODO: remember last removed task description
};

#endif // CTask_HPP