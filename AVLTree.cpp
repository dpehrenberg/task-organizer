#include <algorithm> // For std::max
#include <limits>    // For std::numeric_limits<unsigned int>::max()

#include "AVLTree.hpp"

CAvlTree::CAvlTree()
    : m_root(nullptr), m_size(0)
{
    // Manually build the two dummy nodes: START and END
    // END will be the root, START will be the left child
    auto endNode = std::make_unique<SNode>(
        CTask("END", std::numeric_limits<unsigned int>::max()), nullptr, 2, 2);// height 2, size 2
    auto startNode = std::make_unique<SNode>(CTask("START", 0), endNode.get());
    endNode->left = std::move(startNode);
    m_root = std::move(endNode);
    m_size = 2;
}
/*
CAvlTree::~CAvlTree()
{
    Clear();
}

void CAvlTree::Clear()
{
    m_root.reset();
    m_size = 0;
}

int CAvlTree::size() const {
    return m_size;
}

bool CAvlTree::empty() const {
    return m_size == 0;
}

// Helper to update height and size of a node
template<typename NodePtr>
static void update(NodePtr& node) {
    if (!node) return;
    int lh = node->left ? node->left->height : 0;
    int rh = node->right ? node->right->height : 0;
    node->height = std::max(lh, rh) + 1;
    int lsize = node->left ? node->left->size : 0;
    int rsize = node->right ? node->right->size : 0;
    node->size = lsize + rsize + 1;
}

// Rotations and balancing helpers would go here (not implemented for brevity)

// Insert a new node before the given iterator (in in-order traversal)
CAvlTree::CIterator CAvlTree::InsertBefore(const CTask& task, CIterator pos) {
    SNode* inserted = nullptr;
    m_root.reset(insert_before(m_root.release(), task, pos.m_SNode, inserted));
    if (inserted) ++m_size;
    return CIterator(inserted);
}

// Recursive helper to insert before a given node
CAvlTree::SNode* CAvlTree::insert_before(SNode* root, const CTask& task, SNode* before, SNode*& inserted, SNode* parent) {
    if (!root || root == before) {
        auto new_node = std::make_unique<SNode>(task, parent);
        inserted = new_node.get();
        new_node->right.reset(root);
        if (root) root->parent = new_node.get();
        return new_node.release();
    }
    if (task.GetPriority() < root->task.GetPriority() || root == before) {
        root->left.reset(insert_before(root->left.release(), task, before, inserted, root));
    } else {
        root->right.reset(insert_before(root->right.release(), task, before, inserted, root));
    }
    update(root);
    return root;
}

// Find k-th smallest (0-based)
CAvlTree::CIterator CAvlTree::find_by_index(int idx) const {
    SNode* node = m_root.get();
    while (node) {
        int left_size = node->left ? node->left->size : 0;
        if (idx < left_size) {
            node = node->left.get();
        } else if (idx == left_size) {
            return CIterator(node);
        } else {
            idx -= left_size + 1;
            node = node->right.get();
        }
    }
    return end();
}

// In-order begin (leftmost)
CAvlTree::CIterator CAvlTree::begin() const {
    SNode* node = m_root.get();
    while (node && node->left) node = node->left.get();
    return CIterator(node);
}

// End iterator (nullptr)
CAvlTree::CIterator CAvlTree::end() const {
    return CIterator(nullptr);
}

CTask& CAvlTree::operator[](int idx) {
    auto it = FindByIndex(idx);
    if (it == End()) throw std::out_of_range("CAvlTree::operator[]: index out of range");
    return *it;
}

const CTask& CAvlTree::operator[](int idx) const {
    auto it = FindByIndex(idx);
    if (it == End()) throw std::out_of_range("CAvlTree::operator[]: index out of range");
    return *it;
}
*/