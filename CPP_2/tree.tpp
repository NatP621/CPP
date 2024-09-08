// natane.djedou@gmail.com
#ifndef TREE_TPP
#define TREE_TPP
#include <iostream>
#include <SFML/Graphics.hpp>

namespace TreeNamespace {

// NODE STRUCTURE CONSTRUCTORS
template <typename T, size_t S>
tree<T, S>::node::node() : data(T{}) {
    for (auto& child : childrens) {
        child = nullptr;
    }
}
template <typename T, size_t S>
tree<T, S>::node::node(T value):data(value) {
    for (auto& child : childrens) {
        child = nullptr;
    }
}
template <typename T, size_t S>
tree<T, S>::node::~node() {
   for (auto& child : childrens) {
       if (child != nullptr) {
           delete child;
           child = nullptr;
       }
   }
}

// TREE CLASS CONSTRUCTORS & DESTRUCTOR
template <typename T, size_t S>
tree<T, S>::tree() : root(nullptr) {}
template <typename T, size_t S>
tree<T, S>::~tree() {delete root; }

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
typename tree<T, S>::node* tree<T, S>::get_root() {return this->root;}
template <typename T, size_t S>
void tree<T, S>::add_root(node& new_root) {
    if (this->root != nullptr) {
        delete this->root;
        this->root = nullptr;
    }
    this->root = &new_root;
}
template <typename T, size_t S>
void tree<T, S>::add_sub_node(node& parent, node& child) {
    for (size_t i = 0; i < S; ++i) {
        if (parent.childrens[i] == nullptr) {
            parent.childrens[i] = &child;
            return;
        }
    }
    std::cerr << "Warning: No free space, replacing the first child!" << std::endl;
    delete parent.childrens[0];
    parent.childrens[0] = &child;
}
template <typename T, size_t S>
void drawTree(sf::RenderWindow &window, typename tree<T, S>::node* node, float x, float y, float xOffset, float yOffset) {
    // If the current node is null, return immediately (base case for recursion)
    if (!node) { return; }
    // Set the radius of the node (circle shape)
    const float nodeRadius = 25.0f;
    sf::CircleShape circle(nodeRadius);
    circle.setFillColor(sf::Color::Black); // Set the fill color of the node
    circle.setPosition(x, y);              // Set the position of the circle
    // Draw the current node (circle)
    window.draw(circle);
    // Format the data of the current node
    std::ostringstream ss;
    // Check if the data is numeric (int, float, double, etc.)
    if (std::is_arithmetic<T>::value) {
        ss << std::fixed << std::setprecision(5) << node->data;
    } else {
        ss << node->data; // Default formatting for non-numeric types
    }
    // Create a text object to display the data in the node
    sf::Font font;
    if (!font.loadFromFile("../Arial.ttf")) {
        // Handle the error if the font cannot be loaded
        std::cerr << "Error loading Arial.ttf" << std::endl;
    }
    sf::Text text;
    text.setFont(font);
    text.setString(ss.str());               // Set the formatted data as the text string
    text.setCharacterSize(14);              // Set the character size
    text.setFillColor(sf::Color::White);    // Set the text color
    text.setPosition(x + nodeRadius / 2, y + nodeRadius / 2); // Position the text on the node
    // Draw the data (text) inside the node
    window.draw(text);
    // Track the index of the child node being drawn
    int childIndex = 0;
    // Loop through all possible children
    for (size_t i = 0; i < S; ++i) {
        if (node->childrens[i]) { // If the child at index i exists
            int numChildren = 0;
            for (size_t j = 0; j < S; ++j) {
                if (node->childrens[j]) numChildren++;
            }
            // Calculate the position of the current child
            float childX = x - (xOffset * (numChildren - 1)) / 2.0f + childIndex * xOffset;
            float childY = y + yOffset;
            // Draw a line from the parent node to the child node
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(x + nodeRadius, y + nodeRadius), sf::Color::Black),
                sf::Vertex(sf::Vector2f(childX + nodeRadius, childY + nodeRadius), sf::Color::Black)
            };
            window.draw(line, 2, sf::Lines); // Draw the connecting line
            // Recursively draw the subtree starting from the current child
            drawTree<T, S>(window, node->childrens[i], childX, childY, xOffset / 1.5f, yOffset);
            ++childIndex; // Increment the child index for the next child
        }
    }
}
template <typename T, size_t S>
void draw(tree<T, S>& my_tree) {
    // Get the root node from the tree
    typename tree<T, S>::node* root_node = my_tree.get_root();
    // Create a render window with specified width (900) and height (800)
    sf::RenderWindow window(sf::VideoMode(900, 800), "C++ TREE");
    // Main loop to keep the window open
    while (window.isOpen()) {
        sf::Event temp;  // Temporary variable to store events
        // Process all events (e.g., close event)
        while (window.pollEvent(temp)) {
            if (temp.type == sf::Event::Closed) window.close();  // Close window if 'Closed' event
        }
        window.clear(sf::Color::White);  // Clear the window with a white background
        // Call the drawTree function to recursively draw the entire tree starting from the root
        drawTree<T, S>(window, root_node, 450, 50, 200, 100);
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