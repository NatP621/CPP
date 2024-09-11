// natane.djedou@gmail.com //
// Header guards to prevent multiple inclusions of the file
#ifndef TREE_HPP
#define TREE_HPP

// Include necessary libraries
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>  // Used for graphical rendering
#include <sstream>
#include <iomanip>
#include <iostream>
#include <unistd.h>
#include <queue>
#include <limits.h>
#include <unistd.h>

// Define a namespace to encapsulate the tree-related logic
namespace TreeNamespace {

    // Template class for a tree with a configurable number of children (default is 2 for binary tree)
    template <typename T, size_t S = 2>
    class tree {
    public:
        // Inner struct to represent a tree node
        struct node {
        private:
            T data;  // Holds the data of the node
            std::array<node*, S> childrens;  // Array to hold the child nodes (up to S children)
        public:
            // Default constructor
            node() : data(T{}) {
                // Initialize all child pointers to nullptr
                for (auto& child : childrens) {
                    child = nullptr;
                }
            }

            // Constructor that accepts a value to initialize node data
            node(T value) : data(value) {
                // Initialize all child pointers to nullptr
                for (auto& child : childrens) {
                    child = nullptr;
                }
            }

            // Destructor to clean up child nodes (recursively deletes children)
            ~node() {
                for (auto& child : childrens) {
                    if (child != nullptr) {
                        delete child;
                        child = nullptr;
                    }
                }
            }

            // Getters and setters for the node's data and children
            T getData() const { return data; }
            void setData(const T& value) { data = value; }

            std::array<node*, S>& getChildrens() { return childrens; }
            const std::array<node*, S>& getChildrens() const { return childrens; }

            // Get the child node at a specific index
            node* getChildAt(size_t index) const {
                if (index < S) return childrens[index];
                return nullptr;
            }

            // Set a child node at a specific index
            void setChildAt(size_t index, node* child) {
                if (index < S) childrens[index] = child;
            }
        };

        // Pointer to the root node of the tree
        node* root;

        // Constructors and destructor for the tree class
        tree() : root(nullptr) {}  // Default constructor sets root to nullptr
        tree(node* root) : root(root) {}
        ~tree() { if (root) delete root; }  // Destructor deletes the root (and its children recursively)

        // Getter and setter for the root node
        node* get_root() { return this->root; }
        void set_root(node* root) { this->root = root; }

        // Adds a new root to the tree, replacing the existing root if necessary
        void add_root(node* new_root) {
            if (this->root != nullptr) {
                delete this->root;  // Delete the existing root (and its subtree)
                this->root = nullptr;
            }
            this->root = new_root;  // Assign the new root
        }

        // Add a child node to the parent node (in the first available slot)
        void add_sub_node(node& parent, node& child) {
            for (size_t i = 0; i < S; ++i) {
                if (parent.getChildAt(i) == nullptr) {
                    parent.setChildAt(i, &child);
                    return;
                }
            }
            // If no empty slot was found, replace the first child
            std::cerr << "Warning: No free space, replacing the first child!" << std::endl;
            delete parent.getChildAt(0);  // Delete the first child to avoid memory leak
            parent.setChildAt(0, &child);  // Set the new child in its place
        }

        // Draws the tree recursively using SFML (graphical rendering)
        void drawTree(sf::RenderWindow &window, node* node, float x, float y, float xOffset, float yOffset, const sf::Font& font) {
            if (!node) return;  // Base case: return if node is null

            // Draw a black circle to represent the node
            const float nodeRadius = 25.0f;  // Radius of the node circle
            sf::CircleShape circle(nodeRadius);
            circle.setFillColor(sf::Color::Black);
            circle.setPosition(x, y);
            window.draw(circle);

            // Prepare the node's data to be displayed as text inside the circle
            std::ostringstream ss;
            if (std::is_arithmetic<T>::value) {
                ss << std::fixed << std::setprecision(5) << node->getData();  // Display numeric data with precision
            } else {
                ss << node->getData();  // Display non-numeric data directly
            }

            // Create and position the text for the node
            sf::Text text;
            text.setFont(font);
            text.setString(ss.str());
            text.setCharacterSize(12);
            text.setFillColor(sf::Color(255, 255, 255, 200));

            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            text.setPosition(x + nodeRadius, y + nodeRadius);
            window.draw(text);

            // Loop through children of the node and recursively draw them
            int childIndex = 0;
            for (size_t i = 0; i < S; ++i) {
                if (node->getChildAt(i)) {
                    // Calculate position for the child node
                    int numChildren = 0;
                    for (size_t j = 0; j < S; ++j) {
                        if (node->getChildAt(j)) numChildren++;
                    }

                    float childX = x - (xOffset * (numChildren - 1)) / 2.0f + childIndex * xOffset;
                    float childY = y + yOffset;

                    // Draw a line connecting the current node to its child
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(x + nodeRadius, y + nodeRadius), sf::Color::Black),
                        sf::Vertex(sf::Vector2f(childX + nodeRadius, childY + nodeRadius), sf::Color::Black)
                    };
                    window.draw(line, 2, sf::Lines);

                    // Recursively draw the child node
                    drawTree(window, node->getChildAt(i), childX, childY, xOffset / 1.5f, yOffset, font);
                    ++childIndex;
                }
            }
        }

        // Method to render the tree using an SFML window
        void draw() {
            node* root_node = this->get_root();
            sf::RenderWindow window(sf::VideoMode(900, 800), "C++ TREE");

            // Get the executable's path to load the font
            char result[PATH_MAX];
            ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
            std::string executablePath = std::string(result, (count > 0) ? count : 0);
            size_t lastSlash = executablePath.find_last_of("/");
            std::string fontPath = executablePath.substr(0, lastSlash) + "/arial.ttf";

            // Load the font for rendering text
            sf::Font font;
            if (!font.loadFromFile(fontPath)) {
                std::cerr << "Error loading arial.ttf from: " << fontPath << std::endl;
                return;
            }

            // Main loop to render the tree and handle events
            while (window.isOpen()) {
                sf::Event temp;
                while (window.pollEvent(temp)) {
                    if (temp.type == sf::Event::Closed) window.close();  // Close the window if requested
                }
                window.clear(sf::Color::White);  // Clear the window with a white background
                drawTree(window, root_node, 450, 50, 200, 100, font);  // Recursively draw the tree
                window.display();  // Display the drawn frame
            }
        }

        // Inner class to define a tree iterator for various traversal types
        class tree_Iterator {
        public:
            // Define different traversal orders
            enum class Order {
                begin_pre_order, end_pre_order,
                begin_post_order, end_post_order,
                begin_in_order, end_in_order,
                begin_bfs_scan, end_bfs_scan,
                begin_dfs_scan, end_dfs_scan,
                Heap
            };

            size_t index;  // Current index in the traversal
            std::vector<T> vec;  // Vector to hold traversed node data

            // Constructor initializes the iterator based on the traversal type
            tree_Iterator(tree* tree_ptr, Order order_type) {
                if(tree_ptr != nullptr) {
                    index = 0;  // Start at index 0
                    switch (order_type) {
                        case Order::begin_pre_order:
                            preOrder(tree_ptr->get_root(), vec);
                            break;
                        case Order::end_pre_order:
                            preOrder(tree_ptr->get_root(), vec);
                            std::reverse(vec.begin(), vec.end());
                            break;
                        case Order::begin_post_order:
                            postOrder(tree_ptr->get_root(), vec);
                            break;
                        case Order::end_post_order:
                            postOrder(tree_ptr->get_root(), vec);
                            std::reverse(vec.begin(), vec.end());
                            break;
                        case Order::begin_in_order:
                            inOrder(tree_ptr->get_root(), vec);
                            break;
                        case Order::end_in_order:
                            inOrder(tree_ptr->get_root(), vec);
                            std::reverse(vec.begin(), vec.end());
                            break;
                        case Order::begin_bfs_scan:
                            bfs(tree_ptr->get_root(), vec);
                            break;
                        case Order::end_bfs_scan:
                            bfs(tree_ptr->get_root(), vec);
                            std::reverse(vec.begin(), vec.end());
                            break;
                        case Order::begin_dfs_scan:
                            dfs(tree_ptr->get_root(), vec);
                            break;
                        case Order::end_dfs_scan:
                            dfs(tree_ptr->get_root(), vec);
                            std::reverse(vec.begin(), vec.end());
                            break;
                        case Order::Heap:
                          Heap(tree_ptr->get_root(), vec);
                        break;
                    }
                }
            }

            // Traversal helper methods (Pre-order, Post-order, In-order, BFS, DFS)

            // Post-order traversal (left-right-root)
            void postOrder(node* root, std::vector<T>& vec) {
                if (root == nullptr) return;  // Base case
                for (size_t i = 0; i < S; ++i) {
                    postOrder(root->getChildAt(i), vec);  // Recursively visit children
                }
                vec.push_back(root->getData());  // Add current node's data after children
            }

            // Pre-order traversal (root-left-right)
            void preOrder(node* root, std::vector<T>& vec) {
                if (root == nullptr) return;  // Base case
                vec.push_back(root->getData());  // Add current node's data first
                for (size_t i = 0; i < S; ++i) {
                    preOrder(root->getChildAt(i), vec);  // Recursively visit children
                }
            }

            // In-order traversal (left-root-right)
            void inOrder(node* root, std::vector<T>& vec) {
                if (root == nullptr) return;  // Base case
                if (S > 0 && root->getChildAt(0) != nullptr) {
                    inOrder(root->getChildAt(0), vec);  // Visit the leftmost child first
                }
                vec.push_back(root->getData());  // Add current node's data
                for (size_t i = 1; i < S; ++i) {
                    if (root->getChildAt(i) != nullptr) {
                        inOrder(root->getChildAt(i), vec);  // Visit remaining children
                    }
                }
            }

            // Depth-first search traversal (DFS)
            void dfs(node* root, std::vector<T>& vec) {
                if (root == nullptr) return;  // Base case
                vec.push_back(root->getData());  // Add current node's data
                for (size_t i = 0; i < S; ++i) {
                    dfs(root->getChildAt(i), vec);  // Recursively visit children (depth-first)
                }
            }

            // Breadth-first search traversal (BFS)
            void bfs(node* root, std::vector<T>& vec) {
                if (root == nullptr) return;  // Base case
                std::queue<node*> q;  // Use a queue to traverse level by level
                q.push(root);  // Start with the root node
                while (!q.empty()) {
                    node* current = q.front();
                    q.pop();
                    vec.push_back(current->getData());  // Add current node's data
                    for (size_t i = 0; i < S; ++i) {
                        if (current->getChildAt(i) != nullptr) {
                            q.push(current->getChildAt(i));  // Add child nodes to the queue
                        }
                    }
                }
            }

            void Heap(node* root, std::vector<T>& vec) {
                if (S != 2) {
                    throw std::runtime_error("Heap transformation only supported for binary trees (S = 2).");
                }
                if (root == nullptr) return;

                // Step 1: Clear the vector and collect all node data in a vector using BFS
                vec.clear();
                bfs(root, vec);  // Use the bfs function to populate the vec with node data

                // Step 2: Create a min-heap based on the data in vec
                std::make_heap(vec.begin(), vec.end(), std::greater<T>());  // Use std::greater<T> to create a min-heap

                // Step 3: Reassign the data back to the tree nodes in BFS order
                std::queue<node*> q;
                q.push(root);
                size_t index = 0;
                while (!q.empty() && index < vec.size()) {
                    node* current = q.front();
                    q.pop();

                    // Assign the next value from the heapified vector to the current node
                    current->setData(vec[index++]);

                    // Add the children to the queue for BFS traversal
                    for (size_t i = 0; i < S; ++i) {
                        if (current->getChildAt(i) != nullptr) {
                            q.push(current->getChildAt(i));
                        }
                    }
                }
            }

            // Overloaded operators for iterator functionality

            // Dereference operator to access current element
            T& operator*() {
                return vec[index];  // Return reference to current element
            }

            // Arrow operator to access members of current element
            T* operator->() {
                return &vec[index];  // Return pointer to current element
            }

            // Pre-increment operator (moves to the next element)
            tree_Iterator& operator++() {
                if (index < vec.size() - 1) {
                    ++index;  // Advance index to next element
                }
                return *this;
            }

            // Post-increment operator (moves to the next element and returns previous state)
            tree_Iterator operator++(int) {
                tree_Iterator temp = *this;  // Copy current iterator
                ++(*this);  // Advance to the next element
                return temp;  // Return the copy (previous state)
            }

            // Pre-decrement operator (moves to the previous element)
            tree_Iterator& operator--() {
                if (index > 0) {
                    --index;  // Move to the previous element
                }
                return *this;
            }

            // Post-decrement operator (moves to the previous element and returns previous state)
            tree_Iterator operator--(int) {
                tree_Iterator temp = *this;  // Copy current iterator
                --(*this);  // Move to the previous element
                return temp;  // Return the copy (previous state)
            }

            // Equality operator (compares two iterators for equality)
            bool operator==(const tree_Iterator& other) const {
                return index == other.index && vec == other.vec;
            }

            // Inequality operator (compares two iterators for inequality)
            bool operator!=(const tree_Iterator& other) const {
                return !(*this == other);  // Return the negation of equality
            }
        };

        // Begin and end functions for various traversal types
        tree_Iterator begin_pre_order() { return tree_Iterator(this, tree_Iterator::Order::begin_pre_order); }
        tree_Iterator end_pre_order() { return tree_Iterator(this, tree_Iterator::Order::end_pre_order); }

        tree_Iterator begin_post_order() { return tree_Iterator(this, tree_Iterator::Order::begin_post_order); }
        tree_Iterator end_post_order() { return tree_Iterator(this, tree_Iterator::Order::end_post_order); }

        tree_Iterator begin_in_order() { return tree_Iterator(this, tree_Iterator::Order::begin_in_order); }
        tree_Iterator end_in_order() { return tree_Iterator(this, tree_Iterator::Order::end_in_order); }

        tree_Iterator begin_bfs_scan() { return tree_Iterator(this, tree_Iterator::Order::begin_bfs_scan); }
        tree_Iterator end_bfs_scan() { return tree_Iterator(this, tree_Iterator::Order::end_bfs_scan); }

        tree_Iterator begin_dfs_scan() { return tree_Iterator(this, tree_Iterator::Order::begin_dfs_scan); }
        tree_Iterator end_dfs_scan() { return tree_Iterator(this, tree_Iterator::Order::end_dfs_scan); }

        tree_Iterator myHeap() { return tree_Iterator(this, tree_Iterator::Order::Heap); }
    };
}

#endif // TREE_HPP