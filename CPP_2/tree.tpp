// natane.djedou@gmail.com
#ifndef TREE_TPP
#define TREE_TPP
#include <iostream>
#include <SFML/Graphics.hpp>

namespace TreeNamespace {

// NODE STRUCTURE CONSTRUCTORS
template <typename T, size_t S>
tree<T, S>::node::node() : data(T{}) {this->childrens.fill(nullptr);}
template <typename T, size_t S>
tree<T, S>::node::node(T value) : data(value) {this->childrens.fill(nullptr);}

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
      if (is_bfs){queue.push(root);}
      else{stack.push(root);}
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
    for (auto child : subtree->childrens) {
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
template <typename T, size_t S>
void drawTree(sf::RenderWindow &window,typename tree<T, S>::node* node,float x, float y, float xOffset, float yOffset) {

    // If the current node is null, return immediately (base case for recursion)
    if (!node) { return; }

    // Set the radius of the node (circle shape)
    const float nodeRadius = 25.0f;
    sf::CircleShape circle(nodeRadius);

    // Set the fill color of the circle (node)
    circle.setFillColor(sf::Color::Black);

    // Set the position of the circle in the window (coordinates x, y)
    circle.setPosition(x, y);

    // Track the index of the child node being drawn
    int childIndex = 0;

    // Loop through all possible children (since the tree has S slots for children)
    for (size_t i = 0; i < S; ++i) {
        if (node->childrens[i]) { // If the child at index i exists (not null)

            // Calculate the total number of children
            int numChildren = 0;
            for (size_t j = 0; j < S; ++j) {
                if (node->childrens[j]) numChildren++; // Increment if child exists
            }

            // Calculate the position of the current child
            float childX = x - (xOffset * (numChildren - 1)) / 2.0f + childIndex * xOffset;
            float childY = y + yOffset;

            // Draw a line from the parent node (x, y) to the child node (childX, childY)
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + nodeRadius, y + nodeRadius), sf::Color::Black),  // Parent node position
                sf::Vertex(sf::Vector2f(childX + nodeRadius, childY + nodeRadius), sf::Color::Black)  // Child node position
            };
            window.draw(line, 2, sf::Lines); // Draw the connecting line

            // Recursively draw the subtree starting from the current child
            drawTree<T, S>(window, node->childrens[i], childX, childY, xOffset / 1.5f, yOffset);

            // Increment the child index to correctly position the next child
            ++childIndex;
        }
    }

    // After all children are drawn, draw the parent node (circle)
    window.draw(circle);
}
template <typename T, size_t S>
void draw(typename tree<T, S>::node* node) {

    // Create a render window with a specified width (900) and height (800)
    sf::RenderWindow window(sf::VideoMode(900, 800), "C++ TREE");

    // Main loop that keeps the window open
    while (window.isOpen()) {

        sf::Event temp;  // Temporary variable to store events

        // Process all events (e.g., close event)
        while (window.pollEvent(temp)) {
            if (temp.type == sf::Event::Closed) window.close();  // Close window if the event is 'Closed'
        }

        window.clear(sf::Color::White);  // Clear the window with a white background

        // Call the drawTree function to recursively draw the entire tree starting from the root
        drawTree<T, S>(window, node, 450, 50, 200, 100);

        window.display();  // Display the updated window contents
    }
}
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