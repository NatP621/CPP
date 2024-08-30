#ifndef TREE_HPP
#define TREE_HPP
#include "Node.hpp"
#include <memory>
using std::unique_ptr;

/**
 * @brief A template class representing a Tree data structure.
 * This class implements a generic tree structure where each node can store data of any type.
 * @tparam T The type of data stored in the tree nodes.
 */
template <typename T>
class Tree
{
private:

    /// DATA
    unique_ptr<Node<T>> root;

public:

    /// CONSTRUCTOR
    Tree() : root(nullptr) {}
    Tree(unique_ptr<Node<T>> root_node) : root(std::move(root_node)) {}
    Tree(T root_value) : root(std::make_unique<Node<T>>(root_value)) {}

    /// DESTRUCTOR
    ~Tree() = default;

    /// GETTER
    Node<T>* get_root() const {return this->root;}
    /// SETTER
    void set_root(unique_ptr<Node<T>> new_root) {this->root = std::move(new_root);}

    /// METHODS
    void add_root(unique_ptr<Node<T>> new_root) {this->root = std::move(new_root);}
};
#endif // TREE_HPP

