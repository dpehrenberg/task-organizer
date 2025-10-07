/* this class implements an AVL tree. Basic understanding of AVL trees is required */

#ifndef CAvlTree_HPP
#define CAvlTree_HPP

#include <memory>      // For std::unique_ptr (smart pointers for tree nodes)
#include <functional>  // For std::function (if needed for callbacks/comparisons)
#include <limits>      // For std::numeric_limits (used for END dummy node priority)

#include "CTask.hpp"  // For the CTask class used as the value in the AVL tree

// The AVL tree always contains two dummy nodes:
//  - A START node (task name "START", priority 0) as the smallest element
//  - An END node (task name "END", priority UINT_MAX) as the largest element
// These nodes are present at all times and are not removed by normal operations.
// their purpose is to simplify the logic of determining the priority of a new tasks.

class CAvlTree
{
public:
    struct SNode
    {
        SNode(const CTask& t, SNode* p = nullptr, int h = 1, int s = 1)
            : task(t), left(nullptr), right(nullptr), parent(p), height(h), size(s) {}

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
    ~CAvlTree() = default;
    
    CIterator InsertBefore(const CTask& task, CIterator pos);
    void Erase(CIterator it);
    CIterator FindByIndex(int idx) const;
    CIterator Begin() const;
    CIterator End() const;
    size_t SizeWithDummies() const;
    size_t SizeWithoutDummies() const;
    void Clear();
    bool Empty() const;

    // Access the k-th element (0-based, in-order, excluding dummy nodes)
    CTask& operator[](int idx);
    const CTask& operator[](int idx) const;

    // Additional methods as needed

private:
    std::unique_ptr<SNode> m_root;
    int m_size;
    // Helper functions for rotations, balancing, updating sizes/heights, etc.

    // Helper to insert node before a given node
    SNode* insert_before(SNode* root, const CTask& task, SNode* before, SNode*& inserted, SNode* parent = nullptr);
};

#endif // CAvlTree_HPP