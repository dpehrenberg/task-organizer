#ifndef CTaskOrganiser_HPP
#define CTaskOrganiser_HPP

#include <vector>
#include <string>
#include <iostream> // For std::cout

#include "CTask.hpp"

inline void ClearScreen()
{
    std::cout << "\033[2J\033[H";
}

class CTaskOrganiser
{
public:
    CTaskOrganiser();
    ~CTaskOrganiser() = default;

    // Disable copy and move semantics for CTaskOrganiser to prevent accidental copies or moves
    CTaskOrganiser(const CTaskOrganiser&) = delete;
    CTaskOrganiser& operator=(const CTaskOrganiser&) = delete;
    CTaskOrganiser(CTaskOrganiser&&) = delete;
    CTaskOrganiser& operator=(CTaskOrganiser&&) = delete;

    void AddTask(const std::string& description_);
    void AddMultipleTasks();
    void CompleteFirstTask();
    void CompleteNonFirstTask();
    void DisplayFirstTask() const;
    void DisplayAllTasks() const;
    void ChangeTaskPriority();

private:
    void PrintTasksWithIndices() const;
    bool HasRealTasks() const;
    bool IsValidTaskIndex(size_t idx) const;
    std::vector<CTask> m_tasks; // Store tasks in a vector
};

#endif // CTaskOrganiser_HPP