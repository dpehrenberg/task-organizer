#ifndef CTaskOrganiser_HPP
#define CTaskOrganiser_HPP

#include <vector>
#include <string>

#include "CTask.hpp"

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

    void AddTask(const std::string& description);
    void CompleteFirstTask();
    void DisplayFirstTask() const;

private:
    std::vector<CTask> m_tasks; // Store tasks in a vector
};

#endif // CTaskOrganiser_HPP