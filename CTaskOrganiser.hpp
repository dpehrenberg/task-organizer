#ifndef CTask_HPP
#define CTask_HPP

#include <string>// string
#include "CTask.hpp"// CTask

class CTaskOrganiser
{
public:
    CTaskOrganiser() = default;
    ~CTaskOrganiser() = default;

    // Disable copy and move semantics for CTaskOrganiser to prevent accidental copies or moves
    CTaskOrganiser(const CTaskOrganiser&) = delete;
    CTaskOrganiser& operator=(const CTaskOrganiser&) = delete;
    CTaskOrganiser(CTaskOrganiser&&) = delete;
    CTaskOrganiser& operator=(CTaskOrganiser&&) = delete;

    void AddTask(std::string description);
    void CompleteFirstTask();
    void DisplayFirstTask() const;
private:
    // Using a simple vector to store tasks; can be replaced with more complex structures if needed
    //what data structure to use here? vector, list, deque?
};



#endif // CTask_HPP