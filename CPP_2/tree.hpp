// natane.djedou@gmail.com //
#ifndef TREE_HPP
#define TREE_HPP
#include <array>
#include <stack>
#include <queue>
#include <SFML/Graphics.hpp>

namespace TreeNamespace {

    // Template class for a tree with a configurable number of children (S), default is 2 (binary tree)
    template <typename T, size_t S = 2>
    class tree {
    public:

        // DATA
        struct node {
        private:
            T data;  // Data stored in the node
            std::array<node*, S> childrens;  // Array of pointers to child nodes
        public:
            // Default constructor for node
            node() : data(T{}) {
                for (auto& child : childrens) {
                    child = nullptr;
                }
            }
            // Constructor with a value to initialize the node
            node(T value) : data(value) {
                for (auto& child : childrens) {
                    child = nullptr;
                }
            }
            // Destructor to free children nodes
            ~node() {
                for (auto& child : childrens) {
                    if (child != nullptr) {
                        delete child;
                        child = nullptr;
                    }
                }
            }

            // Getters and setters for node data and children
            const T& getData() const { return data; }
            void setData(const T& value) { data = value; }
            std::array<node*, S>& getChildrens() { return childrens; }
            const std::array<node*, S>& getChildrens() const { return childrens; }
            node* getChildAt(size_t index) const {
                if (index < S) return childrens[index];
                return nullptr;
            }
            void setChildAt(size_t index, node* child) {
                if (index < S) childrens[index] = child;
            }
        };
        node* root;

        // Constructors and destructor for the tree class
        tree() : root(nullptr) {}  // Default constructor
        ~tree() { if (root) delete root; }  // Destructor

        // Tree iterator class
        class tree_Iterator {
        public:
            node* current_pnt;
            bool is_bfs;
            std::stack<node*> stack;
            std::queue<node*> queue;

            tree_Iterator() : current_pnt(nullptr), is_bfs(false) {}
            tree_Iterator(node* root, bool bfs) : current_pnt(nullptr), is_bfs(bfs) {
                if (root) {
                    current_pnt = root;
                    if (is_bfs) {
                        queue.push(root);
                    } else {
                        stack.push(root);
                    }
                }
            }

            node& operator*() const { return *current_pnt; }
            node* operator->() const { return current_pnt; }
            tree_Iterator& operator++() {
                if (!current_pnt) return *this;

                if (is_bfs) {
                    // BFS (Breadth-First Search) - uses a queue
                    if (!queue.empty()) {
                        current_pnt = queue.front();
                        queue.pop();

                        // Add current node's children to the queue
                        for (auto* child : current_pnt->getChildrens()) {
                            if (child != nullptr) {
                                queue.push(child);  // Add children to the queue
                            }
                        }
                    } else {
                        current_pnt = nullptr;  // End of the iteration
                    }
                } else {
                    // DFS (Depth-First Search) - uses a stack
                    if (!stack.empty()) {
                        current_pnt = stack.top();
                        stack.pop();

                        // Add current node's children to the stack in reverse order (right to left)
                        for (auto it = current_pnt->getChildrens().rbegin(); it != current_pnt->getChildrens().rend(); ++it) {
                            if (*it != nullptr) {
                                stack.push(*it);
                            }
                        }
                    } else {
                        current_pnt = nullptr;  // End of the iteration
                    }
                }

                return *this;
            }
            tree_Iterator operator++(int) {
                tree_Iterator temp = *this;
                ++(*this);
                return temp;
            }
            bool operator==(const tree_Iterator& other) const {
                return current_pnt == other.current_pnt;
            }
            bool operator!=(const tree_Iterator& other) const {
                return !(*this == other);
            }
        };

        // Method to get & set the root node of the tree
        node* get_root() { return this->root; }
        void set_root(node* root) { this->root = root; }
        // Adds a root to the tree, replacing the current root if one exists
        void add_root(node* new_root) {
            if (this->root != nullptr) {
                delete this->root;  // Delete the current root and its subtree
                this->root = nullptr;
            }
            this->root = new_root;  // Set the new root
        }
        // Adds a child node to the parent node
        void add_sub_node(node& parent, node& child) {
            for (size_t i = 0; i < S; ++i) {
                if (parent.getChildAt(i) == nullptr) {
                    parent.setChildAt(i, &child);
                    return;
                }
            }
            std::cerr << "Warning: No free space, replacing the first child!" << std::endl;
            delete parent.getChildAt(0);  // Delete the first child before replacing
            parent.setChildAt(0, &child);  // Replace with the new child
        }
        // Recursively draws the tree using SFML
        void drawTree(sf::RenderWindow &window, node* node, float x, float y, float xOffset, float yOffset, const sf::Font& font) {
            if (!node) return;

            const float nodeRadius = 25.0f;
            sf::CircleShape circle(nodeRadius);
            circle.setFillColor(sf::Color::Black);
            circle.setPosition(x, y);
            window.draw(circle);

            std::ostringstream ss;
            if (std::is_arithmetic<T>::value) {
                ss << std::fixed << std::setprecision(5) << node->getData();
            } else {
                ss << node->getData();
            }

            sf::Text text;
            text.setFont(font);
            text.setString(ss.str());
            text.setCharacterSize(12);
            text.setFillColor(sf::Color(255, 255, 255, 200));

            sf::FloatRect textBounds = text.getLocalBounds();
            text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
            text.setPosition(x + nodeRadius, y + nodeRadius);
            window.draw(text);

            int childIndex = 0;
            for (size_t i = 0; i < S; ++i) {
                if (node->getChildAt(i)) {
                    int numChildren = 0;
                    for (size_t j = 0; j < S; ++j) {
                        if (node->getChildAt(j)) numChildren++;
                    }

                    float childX = x - (xOffset * (numChildren - 1)) / 2.0f + childIndex * xOffset;
                    float childY = y + yOffset;

                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(x + nodeRadius, y + nodeRadius), sf::Color::Black),
                        sf::Vertex(sf::Vector2f(childX + nodeRadius, childY + nodeRadius), sf::Color::Black)
                    };
                    window.draw(line, 2, sf::Lines);

                    drawTree(window, node->getChildAt(i), childX, childY, xOffset / 1.5f, yOffset, font);
                    ++childIndex;
                }
            }
        }
        // Draw the tree in a window using SFML
        void draw() {
            node* root_node = this->get_root();
            sf::RenderWindow window(sf::VideoMode(900, 800), "C++ TREE");

            char result[PATH_MAX];
            ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
            std::string executablePath = std::string(result, (count > 0) ? count : 0);
            size_t lastSlash = executablePath.find_last_of("/");
            std::string fontPath = executablePath.substr(0, lastSlash) + "/arial.ttf";

            sf::Font font;
            if (!font.loadFromFile(fontPath)) {
                std::cerr << "Error loading arial.ttf from: " << fontPath << std::endl;
                return;
            }

            while (window.isOpen()) {
                sf::Event temp;
                while (window.pollEvent(temp)) {
                    if (temp.type == sf::Event::Closed) window.close();
                }
                window.clear(sf::Color::White);
                drawTree(window, root_node, 450, 50, 200, 100, font);
                window.display();
            }
        }
        // Iterators for different tree traversal orders
        tree_Iterator begin_pre_order();
        tree_Iterator end_pre_order();
        tree_Iterator begin_post_order();
        tree_Iterator end_post_order();
        tree_Iterator begin_in_order();
        tree_Iterator end_in_order();
        tree_Iterator begin_bfs_scan();
        tree_Iterator end_bfs_scan();
        tree_Iterator begin_dfs_scan();
        tree_Iterator end_dfs_scan();
        // Convert the tree into a min-heap
        tree_Iterator myHeap() {
            if (S != 2) {
                throw std::runtime_error("The tree must be binary to be transformed into a min-heap.");
            }
            if (!root) return end_bfs_scan();

            std::vector<node*> nodes;
            for (auto it = begin_bfs_scan(); it != end_bfs_scan(); ++it) {
                nodes.push_back(&(*it));
            }

            auto compare = [](node* a, node* b) { return a->data > b->data; };
            std::make_heap(nodes.begin(), nodes.end(), compare);

            for (size_t i = 0; i < nodes.size(); ++i) {
                size_t leftChildIdx = 2 * i + 1;
                size_t rightChildIdx = 2 * i + 2;
                nodes[i]->children[0] = (leftChildIdx < nodes.size()) ? nodes[leftChildIdx] : nullptr;
                nodes[i]->children[1] = (rightChildIdx < nodes.size()) ? nodes[rightChildIdx] : nullptr;
            }

            root = nodes.front();
            return begin_bfs_scan();
        }
    };
}
#endif // TREE_HPP