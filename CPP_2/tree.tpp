// natane.djedou@gmail.com
#ifndef TREE_TPP
#define TREE_TPP

namespace TreeNamespace {

// NODE STRUCTURE CONSTRUCTORS
template <typename T, size_t S>
tree<T, S>::node::node() : data(T{}) {this->children.fill(nullptr);}
template <typename T, size_t S>
tree<T, S>::node::node(T value) : data(value) {this->children.fill(nullptr);}


// TREE CLASS CONSTRUCTORS & DESTRUCTOR
template <typename T, size_t S>
tree<T, S>::tree() : root(nullptr) {}
template <typename T, size_t S>
tree<T, S>::~tree() {deleteSubtree(root);}


// tree_Iterator CONSTRUCTORS
template <typename T, size_t S>
tree<T, S>::tree_Iterator::tree_Iterator() : current_pnt(nullptr), is_bfs(false) {}
template <typename T, size_t S>
tree<T, S>::tree_Iterator::tree_Iterator(node* root, bool bfs) : current_pnt(nullptr), is_bfs(bfs) {
    if (root) {
      if (is_bfs)
      {
        queue.push(root);
      }
      else
      {
        stack.push(root);
      }
      // Initialize the iterator to the first element
    ++(*this);
    }
}


// tree_Iterator OPERATORS
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator::reference tree<T, S>::tree_Iterator::operator*() const {
    if (current_pnt == nullptr) {
        throw std::runtime_error("Dereferencing null iterator");
    }
    return *current_pnt;
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator::pointer tree<T, S>::tree_Iterator::operator->() const {
    if (current_pnt == nullptr) {
        throw std::runtime_error("Dereferencing null iterator");
    }
    return current_pnt;
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator& tree<T, S>::tree_Iterator::operator++() {
    if (is_bfs) {  // Use BFS
        if (!queue.empty()) {
            node* current = queue.front();
            queue.pop();
            current_pnt = current;

            for (auto child : current->children) {
                if (child) {
                    queue.push(child);
                }
            }
        }
        else {current_pnt = nullptr;}
    }
    else {  // Use DFS or pre-order
        if (!stack.empty()) {
            node* current = stack.top();
            stack.pop();
            current_pnt = current;

            for (auto it = current->children.rbegin(); it != current->children.rend(); ++it) {
                if (*it) {
                    stack.push(*it);
                }
            }
        }
        else {current_pnt = nullptr;}
    }
    return *this;
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::tree_Iterator::operator++(int) {
    tree_Iterator tmp = *this;
    ++(*this);
    return tmp;
}
template <typename T, size_t S>
bool tree<T, S>::tree_Iterator::operator==(const tree_Iterator& other) const {
    return current_pnt == other.current_pnt;
}
template <typename T, size_t S>
bool tree<T, S>::tree_Iterator::operator!=(const tree_Iterator& other) const {
    return !(*this == other);
}


// TREE METHODS
template <typename T, size_t S>
void tree<T, S>::deleteSubtree(node* subtree) {
    if (!subtree) return;
    for (auto child : subtree->children) {
        deleteSubtree(child);
    }
    delete subtree;
}
template <typename T, size_t S>
void tree<T, S>::add_root(node& new_root) {
    if (this->root != nullptr) {
        deleteSubtree(root);
    }
    this->root = &new_root;
}
template <typename T, size_t S>
void tree<T, S>::add_sub_node(node& parent, node& child) {
    for (size_t i = 0; i < S; ++i) {
        if (parent.children[i] == nullptr) {
            parent.children[i] = &child;
            return;
        }
    }
    throw std::runtime_error("Parent already has " + std::to_string(S) + " children");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///

///
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::begin_pre_order() {
    return tree_Iterator(root);
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::end_pre_order() {
    return tree_Iterator();
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::begin_post_order() {
    // Specific implementation for post-order
    // Placeholder
    return tree_Iterator();
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::end_post_order() {
    return tree_Iterator();
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::begin_in_order() {
    // Specific implementation for in-order
    // Placeholder
    return tree_Iterator();
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::end_in_order() {
    return tree_Iterator();
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::begin_bfs_scan() {
    return tree_Iterator(root, true);
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::end_bfs_scan() {
    return tree_Iterator();
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::begin_dfs_scan() {
    return begin_pre_order();  // Equivalent to pre-order
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::end_dfs_scan() {
    return end_pre_order();  // Equivalent to pre-order
}
template <typename T, size_t S>
typename tree<T, S>::tree_Iterator tree<T, S>::myHeap() {
    // Check if the tree is binary
    if (S != 2) {
        throw std::runtime_error("The tree must be binary to be transformed into a min-heap.");
    }
    if (!root) return end_bfs_scan(); // If the tree is empty, return the end iterator
    // Use a vector to store the nodes
    std::vector<node*> nodes;
    for (auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it) {
        nodes.push_back(&(*it));
    }
    // Build the min-heap
    auto compare = [](node* a, node* b) { return a->data > b->data; };
    std::make_heap(nodes.begin(), nodes.end(), compare);
    // Rearrange the tree nodes according to the min-heap order
    for (size_t i = 0; i < nodes.size(); ++i) {
        size_t leftChildIdx = 2 * i + 1;
        size_t rightChildIdx = 2 * i + 2;
        nodes[i]->children[0] = (leftChildIdx < nodes.size()) ? nodes[leftChildIdx] : nullptr;
        nodes[i]->children[1] = (rightChildIdx < nodes.size()) ? nodes[rightChildIdx] : nullptr;
    }
    // Update the root of the tree with the first element of the heap
    root = nodes.front();
    // Return iterators for the resulting heap
    return begin_bfs_scan();
}

} // namespace TreeNamespace
#endif // TREE_TPP