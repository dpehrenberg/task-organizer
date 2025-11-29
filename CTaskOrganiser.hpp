#ifndef CTaskOrganiser_HPP
#define CTaskOrganiser_HPP

#include <vector>
#include <string>
#include <iostream> // For std::cout
#include <optional>

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
    CTaskOrganiser(const CTaskOrganiser&)            = delete;
    CTaskOrganiser& operator=(const CTaskOrganiser&) = delete;
    CTaskOrganiser(CTaskOrganiser&&)                 = delete;
    CTaskOrganiser& operator=(CTaskOrganiser&&)      = delete;

    void AddTask(const std::string& description_);
    void AddMultipleTasks();
    void CompleteFirstTask();
    void CompleteNonFirstTask();
    void DisplayFirstTask() const;
    void DisplayAllTasks() const;
    void ChangeTaskPriority();
    void ChangeTaskName();
    void ChangeOrganiserName();
    void UndoLastComplete();
    void Save();
    void LoadFromFile(const std::string& filename);
    const std::string& GetName() const;
    
private:
    std::string          m_name = "default";
    std::vector<CTask>   m_tasks;
    std::optional<CTask> m_lastRemovedTask;//for undo functionality
    
    void SaveWithName(const std::string& filename) const;
    void PrintTasksWithIndices() const;
    bool HasRealTasks() const;
    bool IsValidTaskIndex(size_t idx) const;
};

#endif // CTaskOrganiser_HPP