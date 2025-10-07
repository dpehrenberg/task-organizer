#ifndef CAvlTree_HPP
#define CAvlTree_HPP

#include <memory>      // For std::unique_ptr (smart pointers for tree nodes)
#include <functional>  // For std::function (if needed for callbacks/comparisons)

#include "CTask.hpp"  // For the CTask class used as the value in the AVL tree

class CAvlTree
{
public:
    struct SNode
    {
        SNode(const CTask& t, SNode* p = nullptr)
            : task(t), left(nullptr), right(nullptr), parent(p), height(1), size(1) {}

        CTask                  task;
        std::unique_ptr<SNode> left;
        std::unique_ptr<SNode> right;
        SNode*                 parent;
        int                    height; // height of the node
        int                    size;   // subtree size for rank-based access
    };

    class CIterator
    {
    public:
        CIterator(SNode* SNode = nullptr) : m_SNode(SNode) {}
        CTask& operator*() const { return m_SNode->task; }
        CTask* operator->() const { return &m_SNode->task; }
        bool operator==(const CIterator& other) const { return m_SNode == other.m_SNode; }
        bool operator!=(const CIterator& other) const { return m_SNode != other.m_SNode; }
        // Increment/decrement for in-order traversal can be added here
    private:
        SNode* m_SNode;
        friend class CAvlTree;
    };

    CAvlTree();
    ~CAvlTree();

    CIterator insert(const CTask& task);
    void erase(CIterator it);
    CIterator find_by_index(int idx) const;
    CIterator begin() const;
    CIterator end() const;
    int size() const;
    bool empty() const;
    void clear();

    // Additional methods as needed

private:
    std::unique_ptr<SNode> m_root;
    int m_size;
    // Helper functions for rotations, balancing, updating sizes/heights, etc.
};

#endif // CAvlTree_HPP