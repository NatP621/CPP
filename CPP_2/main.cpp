// natane.djedou@gmail.com //
#include <iostream>
#include "tree.hpp"
#include "Complex.hpp"

/*
 * This `main` class is designed to demonstrate and showcase the capabilities of the `Tree` class
 * through its usage in various forms. The primary goal of this implementation is to illustrate how
 * the `Tree` class can be utilized with different data types, such as integers and complex objects,
 * while maintaining the same structural principles.

 * In this example, the `Tree` class is used to create a tree with a maximum of three children per node.
 * The `main` function showcases several operations on the tree, including adding root and child nodes,
 * as well as performing multiple tree traversals. These traversals include:
 * - **Post-order traversal**, where child nodes are visited before their parent.
 * - **Pre-order traversal**, where each node is visited before its children.
 * - **In-order traversal**, adapted to the structure of trees with multiple children.
 * - **Breadth-First Search (BFS)** and **Depth-First Search (DFS)** traversals, each offering a different
 *   approach to exploring the tree's nodes.

 * The `main` function also demonstrates how the `Tree` class allows for the replacement of the root node
 * with a new value, illustrating the tree's dynamic adaptability to structural changes.

 * Additionally, this demonstration highlights the `Tree` class's ability to handle various data types,
 * as seen in the examples using both integers and complex numbers. This shows the versatility of the `Tree` class
 * in managing different types of content while offering robust and efficient tree manipulation features.

 * In summary, this `main` implementation serves as a demonstrative tool to explore the multiple facets
 * of the `Tree` class, including its structure, manipulation capabilities, and data traversal functionalities.
 */

/*
================================================================================================
Overall expected result:The complete program should produce an output similar to this
================================================================================================
Adding root: 10
Adding child nodes to root: 20, 30, 40
Adding child nodes to node 20: 50, 60
Adding child node to node 30: 70
Adding child node to node 70: 80

===== Post-order Traversal =====
50 60 20 80 70 30 40

===== Pre-order Traversal =====
10 20 50 60 30 70 80

===== In-order Traversal =====
50 20 60 10 80 70 30

===== Breadth-First (BFS) Traversal =====
10 20 30 40 50 60 70

===== DFS Traversal =====
10 20 50 60 30 70 80

===== Replacing the Root =====
New root: 100

==========================================================================================
==========================================================================================

Creating a tree of Complex numbers with 3 children per node
Adding root: (10 + 1i)
Adding child nodes to root: (20 + 2i), (30 + 3i), (40 + 4i)
Adding child nodes to node (20 + 2i): (50 + 5i), (60 + 6i)
Adding child node to node (30 + 3i): (70 + 7i)
Adding child node to node (70 + 7i): (80 + 8i)

===== Post-order Traversal =====
(50 + 5i) (60 + 6i) (20 + 2i) (80 + 8i) (70 + 7i) (30 + 3i) (40 + 4i)

===== Pre-order Traversal =====
(10 + 1i) (20 + 2i) (50 + 5i) (60 + 6i) (30 + 3i) (70 + 7i) (80 + 8i)

===== In-order Traversal =====
(50 + 5i) (20 + 2i) (60 + 6i) (10 + 1i) (80 + 8i) (70 + 7i) (30 + 3i)

===== Breadth-First (BFS) Traversal =====
(10 + 1i) (20 + 2i) (30 + 3i) (40 + 4i) (50 + 5i) (60 + 6i) (70 + 7i)

===== DFS Traversal =====
(10 + 1i) (20 + 2i) (50 + 5i) (60 + 6i) (30 + 3i) (70 + 7i) (80 + 8i)

===== Replacing the Root =====
New root: (100 + 10i)

==========================================================================================
==========================================================================================


===== As the myHeap function only works with binary trees, I implemented a binary tree of int to try myHeap =====

===== Starting Tree Creation =====
Adding root node with value 4
Adding first child of root with value 3
Adding second child of root with value 5
Adding children of node with value 3
- Adding first child with value 1
- Adding second child with value 2
Adding children of node with value 5
- Adding first child with value 6
- Adding second child with value 7
===== Tree Creation Completed =====

===== Applying Min-Heap Transformation =====

===== Pre-order Traversal after Heap Transformation =====
1 2 3 4 5 6

================================================================================================
================================================================================================
 */

void intTree() {
    // Creating a tree of type int with 3 children per node
    TreeNamespace::tree<int, 3> tree;
    // Adding the root node
    std::cout << "Adding root: 10" << std::endl;
    TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
    tree.add_root(root);
    // Adding child nodes to the root
    std::cout << "Adding child nodes to root: 20, 30, 40" << std::endl;
    TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(20);
    TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(30);
    TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(40);
    tree.add_sub_node(*root, *child1);
    tree.add_sub_node(*root, *child2);
    tree.add_sub_node(*root, *child3);
    // Adding child nodes to node 20
    std::cout << "Adding child nodes to node 20: 50, 60" << std::endl;
    TreeNamespace::tree<int, 3>::node* grandchild1 = new TreeNamespace::tree<int, 3>::node(50);
    TreeNamespace::tree<int, 3>::node* grandchild2 = new TreeNamespace::tree<int, 3>::node(60);
    tree.add_sub_node(*child1, *grandchild1);
    tree.add_sub_node(*child1, *grandchild2);
    // Adding child node to node 30
    std::cout << "Adding child node to node 30: 70" << std::endl;
    TreeNamespace::tree<int, 3>::node* grandchild3 = new TreeNamespace::tree<int, 3>::node(70);
    tree.add_sub_node(*child2, *grandchild3);
    tree.draw();
    // Adding child node to node 70
    std::cout << "Adding child node to node 70: 80" << std::endl;
    TreeNamespace::tree<int, 3>::node* greatGrandchild = new TreeNamespace::tree<int, 3>::node(80);
    tree.add_sub_node(*grandchild3, *greatGrandchild);
    // Post-order traversal
    std::cout << "\n===== Post-order Traversal =====" << std::endl;
    for (auto it = tree.begin_post_order(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // Pre-order Traversal
    std::cout << "\n===== Pre-order Traversal =====" << std::endl;
    for (auto it = tree.begin_pre_order(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // In-order Traversal
    std::cout << "\n===== In-order Traversal =====" << std::endl;
    for (auto it = tree.begin_in_order(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // Breadth-first (BFS) traversal
    std::cout << "\n===== Breadth-First (BFS) Traversal =====" << std::endl;
    for (auto it = tree.begin_bfs_scan(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // DFS traversal
    std::cout << "\n===== DFS Traversal =====" << std::endl;
    for (auto it = tree.begin_dfs_scan(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // Replacing the root
    std::cout << "\n===== Replacing the Root =====" << std::endl;
    TreeNamespace::tree<int, 3>::node* newRoot = new TreeNamespace::tree<int, 3>::node(100);
    tree.add_root(newRoot);
    std::cout << "New root: " << newRoot->getData() << std::endl;
}

void complexTree() {
    // Creating a tree of type Complex with 3 children per node
    std::cout << "Creating a tree of Complex numbers with 3 children per node" << std::endl;
    TreeNamespace::tree<Complex, 3> tree;
    // Adding the root node
    std::cout << "Adding root: (10 + 1i)" << std::endl;
    TreeNamespace::tree<Complex, 3>::node* root = new TreeNamespace::tree<Complex, 3>::node(Complex(10, 1));
    tree.add_root(root);
    // Adding child nodes to the root
    std::cout << "Adding child nodes to root: (20 + 2i), (30 + 3i), (40 + 4i)" << std::endl;
    TreeNamespace::tree<Complex, 3>::node* child1 = new TreeNamespace::tree<Complex, 3>::node(Complex(20, 2));
    TreeNamespace::tree<Complex, 3>::node* child2 = new TreeNamespace::tree<Complex, 3>::node(Complex(30, 3));
    TreeNamespace::tree<Complex, 3>::node* child3 = new TreeNamespace::tree<Complex, 3>::node(Complex(40, 4));
    tree.add_sub_node(*root, *child1);
    tree.add_sub_node(*root, *child2);
    tree.add_sub_node(*root, *child3);
    // Adding child nodes to node (20 + 2i)
    std::cout << "Adding child nodes to node (20 + 2i): (50 + 5i), (60 + 6i)" << std::endl;
    TreeNamespace::tree<Complex, 3>::node* grandchild1 = new TreeNamespace::tree<Complex, 3>::node(Complex(50, 5));
    TreeNamespace::tree<Complex, 3>::node* grandchild2 = new TreeNamespace::tree<Complex, 3>::node(Complex(60, 6));
    tree.add_sub_node(*child1, *grandchild1);
    tree.add_sub_node(*child1, *grandchild2);
    // Adding child node to node (30 + 3i)
    std::cout << "Adding child node to node (30 + 3i): (70 + 7i)" << std::endl;
    TreeNamespace::tree<Complex, 3>::node* grandchild3 = new TreeNamespace::tree<Complex, 3>::node(Complex(70, 7));
    tree.add_sub_node(*child2, *grandchild3);
    tree.draw(); // Assuming this draws the current tree structure
    // Adding child node to node (70 + 7i)
    std::cout << "Adding child node to node (70 + 7i): (80 + 8i)" << std::endl;
    TreeNamespace::tree<Complex, 3>::node* greatGrandchild = new TreeNamespace::tree<Complex, 3>::node(Complex(80, 8));
    tree.add_sub_node(*grandchild3, *greatGrandchild);
    // Post-order traversal
    std::cout << "\n===== Post-order Traversal =====" << std::endl;
    for (auto it = tree.begin_post_order(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // Pre-order Traversal
    std::cout << "\n===== Pre-order Traversal =====" << std::endl;
    for (auto it = tree.begin_pre_order(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // In-order Traversal
    std::cout << "\n===== In-order Traversal =====" << std::endl;
    for (auto it = tree.begin_in_order(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // Breadth-first (BFS) traversal
    std::cout << "\n===== Breadth-First (BFS) Traversal =====" << std::endl;
    for (auto it = tree.begin_bfs_scan(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // DFS traversal
    std::cout << "\n===== DFS Traversal =====" << std::endl;
    for (auto it = tree.begin_dfs_scan(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    // Replacing the root
    std::cout << "\n===== Replacing the Root =====" << std::endl;
    TreeNamespace::tree<Complex, 3>::node* newRoot = new TreeNamespace::tree<Complex, 3>::node(Complex(100, 10));
    tree.add_root(newRoot);
    std::cout << "New root: " << newRoot->getData() << std::endl;
}

void binary_tree_For_myHeap(){
  std::cout << "\n===== As the myHeap function only works with binary trees, I implemented a binary tree of int to try myHeap =====\n" << std::endl;
  std::cout << "===== Starting Tree Creation =====" << std::endl;

    // Create a binary tree with 2 children per node
    /*
                         4
                       /   \
                      3     5
                    /  \   /  \
                   1    2 6    7
    */
    TreeNamespace::tree<int, 2> testTree;
    // Adding root node
    std::cout << "Adding root node with value 4" << std::endl;
    auto* root = new TreeNamespace::tree<int, 2>::node(4);
    testTree.set_root(root);
    // Adding first level children
    std::cout << "Adding first child of root with value 3" << std::endl;
    auto* child1 = new TreeNamespace::tree<int, 2>::node(3);
    std::cout << "Adding second child of root with value 5" << std::endl;
    auto* child2 = new TreeNamespace::tree<int, 2>::node(5);
    // Attach children to root
    root->setChildAt(0, child1);
    root->setChildAt(1, child2);
    // Adding second level children for child1
    std::cout << "Adding children of node with value 3" << std::endl;
    auto* grandchild1 = new TreeNamespace::tree<int, 2>::node(1);
    std::cout << "- Adding first child with value 1" << std::endl;
    auto* grandchild2 = new TreeNamespace::tree<int, 2>::node(2);
    std::cout << "- Adding second child with value 2" << std::endl;
    // Attach grandchildren to child1
    child1->setChildAt(0, grandchild1);
    child1->setChildAt(1, grandchild2);
    // Adding second level children for child2
    std::cout << "Adding children of node with value 5" << std::endl;
    auto* grandchild3 = new TreeNamespace::tree<int, 2>::node(6);
    std::cout << "- Adding first child with value 6" << std::endl;
    auto* grandchild4 = new TreeNamespace::tree<int, 2>::node(7);
    std::cout << "- Adding second child with value 7" << std::endl;
    // Attach grandchildren to child2
    child2->setChildAt(0, grandchild3);
    child2->setChildAt(1, grandchild4);
    testTree.draw();
    std::cout << "===== Tree Creation Completed =====" << std::endl;
    // Apply MinHeap transformation using myHeap
    std::cout << "\n===== Applying Min-Heap Transformation =====" << std::endl;
    std::vector<int> vec;
    testTree.myHeap();  // Assuming Heap function transforms the tree into a Min-Heap
    testTree.draw();
    // Verify the result with a pre-order traversal (should reflect min-heap properties)
    std::cout << "\n===== Pre-order Traversal after Heap Transformation =====" << std::endl;
    for (auto it = testTree.begin_pre_order(); it.index != it.vec.size() - 1; ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main() {
    intTree();
    std::cout << "\n==========================================================================================" << std::endl;
    std::cout << "==========================================================================================\n" << std::endl;
    complexTree();
    std::cout << "\n==========================================================================================" << std::endl;
    std::cout << "==========================================================================================\n" << std::endl;
    binary_tree_For_myHeap();
    return 0;
}