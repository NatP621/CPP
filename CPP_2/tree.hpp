// natane.djedou@gmail.com
#ifndef TREE_HPP
#define TREE_HPP
#include <array>
#include <iterator>
#include <stack>
#include <queue>
#include <SFML/Graphics.hpp>

namespace TreeNamespace {

template <typename T, size_t S = 2>
class tree {
public:
    // DATA OF TREE
    // node structure for tree
    struct node {
        // NODE DATA
        T data;
        std::array<node*, S> children;
        // NODE CONSTRUCTOR
        node();
        node(T value);
    };
    // tree attributes
    node* root;

    // TREE CONSTRUCTORS & DESTRUCTORS
    tree();
    ~tree();

    // METHODS
    node* get_root(){return this->root;}
    void deleteSubtree(node* subtree);  // Deletes all nodes in the subtree rooted at the given node
    void add_root(node& new_root);      // Sets a new root for the tree, deleting the existing tree if it exists
    void add_sub_node(node& parent, node& child);  // Adds a child node to the specified parent node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ITERATORS FOR TREE
    // Pre-order iterators
    class tree_Iterator;
    tree_Iterator begin_pre_order();
    tree_Iterator end_pre_order();
    // Post-order iterators
    tree_Iterator begin_post_order();
    tree_Iterator end_post_order();
    // In-order iterators
    tree_Iterator begin_in_order();
    tree_Iterator end_in_order();
    // BFS scan iterators
    tree_Iterator begin_bfs_scan();
    tree_Iterator end_bfs_scan();
    // DFS scan iterators (equivalent to pre-order for trees)
    tree_Iterator begin_dfs_scan();
    tree_Iterator end_dfs_scan();
    // METHOD TO TRANSFORM THE TREE INTO A MIN-HEAP
    tree_Iterator myHeap();


    // ITERATOR CLASS FOR TREE TRAVERSAL
    class tree_Iterator {
    public:
        // DATA OF ITERATOR
        using iterator_category = std::forward_iterator_tag;
        using value_type = node;
        using difference_type = std::ptrdiff_t;
        using pointer = node*;
        using reference = node&;
    private:
        node* current_pnt;
        bool is_bfs;
        std::stack<node*> stack;
        std::queue<node*> queue;

    public:
        // CONSTRUCTORS OF ITERATOR
        tree_Iterator();
        tree_Iterator(node* root, bool is_bfs = false);

        // OPERATORS OF ITERATOR
        reference operator*() const;
        pointer operator->() const;
        tree_Iterator& operator++();
        tree_Iterator operator++(int);
        bool operator==(const tree_Iterator& other) const;
        bool operator!=(const tree_Iterator& other) const;
    };
};
};
class tree_Iterator;
#include "tree.tpp"
#endif // TREE_HPP