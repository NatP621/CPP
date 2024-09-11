// natane.djedou@gmail.com //
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <SFML/Graphics.hpp>
#include "doctest.h"
#include "tree.hpp"
#include "Complex.hpp"

TEST_CASE("Tree Node Construction") {
    SUBCASE("Default node constructor with size S") {
        // Create a default node with 3 children slots
        TreeNamespace::tree<int, 3>::node defaultNode;  // Using S = 3

        // Verify the node has exactly 3 children slots
        CHECK(defaultNode.getChildrens().size() == 3);

        // Each child should be initialized to nullptr
        for (auto child : defaultNode.getChildrens()) {
            CHECK(child == nullptr);
        }
    }
    SUBCASE("Parameterized node constructor with size S") {
        // Create a node with a value of 10 and 4 children slots
        TreeNamespace::tree<int, 4>::node paramNode(10);  // Using S = 4

        // Verify the node holds the correct data
        CHECK(paramNode.getData() == 10);

        // Verify the node has exactly 4 children slots
        CHECK(paramNode.getChildrens().size() == 4);

        // Each child should be initialized to nullptr
        for (auto child : paramNode.getChildrens()) {
            CHECK(child == nullptr);
        }
    }
}
TEST_CASE("Tree Construction and Destruction") {
    TreeNamespace::tree<int> treeInstance;
    SUBCASE("Default Constructor") {
        // Verify that the default constructor initializes the tree with no root
        CHECK(treeInstance.get_root() == nullptr);
    }
    SUBCASE("Adding a root node") {
        // Create a root node and add it to the tree
        TreeNamespace::tree<int>::node* root = new TreeNamespace::tree<int>::node(10);
        treeInstance.add_root(root);

        // Verify that the root is correctly added
        CHECK(treeInstance.get_root() == root);
        CHECK(treeInstance.get_root()->getData() == 10);
    }
    SUBCASE("Adding children to the root node") {
        // Create a root node and add it to the tree
        TreeNamespace::tree<int>::node* root = new TreeNamespace::tree<int>::node(10);
        treeInstance.add_root(root);

        // Create child nodes
        TreeNamespace::tree<int>::node* child1 = new TreeNamespace::tree<int>::node(20);
        TreeNamespace::tree<int>::node* child2 = new TreeNamespace::tree<int>::node(30);

        // Add children to the root node
        treeInstance.add_sub_node(*root, *child1);
        treeInstance.add_sub_node(*root, *child2);

        // Verify that the children were added correctly
        CHECK(root->getChildAt(0) == child1);
        CHECK(root->getChildAt(1) == child2);
        CHECK(root->getChildAt(0)->getData() == 20);
        CHECK(root->getChildAt(1)->getData() == 30);
    }
    SUBCASE("Replacing the root node") {
        // Create a root node and add it to the tree
        TreeNamespace::tree<int>::node* root1 = new TreeNamespace::tree<int>::node(10);
        treeInstance.add_root(root1);

        // Create a new root node
        TreeNamespace::tree<int>::node* root2 = new TreeNamespace::tree<int>::node(100);
        treeInstance.add_root(root2);  // This replaces the original root

        // Verify that the new root replaced the old one
        CHECK(treeInstance.get_root() == root2);
        CHECK(treeInstance.get_root()->getData() == 100);
    }
    SUBCASE("Adding a root and multiple levels of children") {
        // Create a root node
        TreeNamespace::tree<int>::node* root = new TreeNamespace::tree<int>::node(50);
        treeInstance.add_root(root);

        // Add children to the root
        TreeNamespace::tree<int>::node* child1 = new TreeNamespace::tree<int>::node(20);
        TreeNamespace::tree<int>::node* child2 = new TreeNamespace::tree<int>::node(30);
        treeInstance.add_sub_node(*root, *child1);
        treeInstance.add_sub_node(*root, *child2);

        // Add children to child1
        TreeNamespace::tree<int>::node* grandChild1 = new TreeNamespace::tree<int>::node(5);
        treeInstance.add_sub_node(*child1, *grandChild1);

        // Verify the tree structure
        CHECK(root->getChildAt(0) == child1);
        CHECK(root->getChildAt(1) == child2);
        CHECK(child1->getChildAt(0) == grandChild1);

        // Verify the node values
        CHECK(root->getData()== 50);
        CHECK(child1->getData() == 20);
        CHECK(child2->getData()== 30);
        CHECK(grandChild1->getData() == 5);
    }
}
TEST_CASE("Tree Root and Subnodes Manipulation with size S") {
        TreeNamespace::tree<int, 3> treeInstance;  // Using S = 3
        SUBCASE("Add root") {
            // Create a root node and add it to the tree
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            treeInstance.add_root(root);

            // The root should be added correctly
            CHECK(treeInstance.get_root() == root);
        }
        SUBCASE("Replace root with new root") {
            // Create two root nodes
            TreeNamespace::tree<int, 3>::node* root1 = new TreeNamespace::tree<int, 3>::node(10);
            TreeNamespace::tree<int, 3>::node* root2 = new TreeNamespace::tree<int, 3>::node(20);

            // Add the first root, then replace it with the second
            treeInstance.add_root(root1);
            treeInstance.add_root(root2);

            // The root should be replaced correctly
            CHECK(treeInstance.get_root() == root2);
        }
        SUBCASE("Add subnodes to root") {
            // Create a root node and a child node
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            TreeNamespace::tree<int, 3>::node* child = new TreeNamespace::tree<int, 3>::node(20);

            // Add root and subnode
            treeInstance.add_root(root);
            treeInstance.add_sub_node(*root, *child);

            // The root's first child should be added correctly
            CHECK(root->getChildAt(0) == child);
        }
        SUBCASE("Add subnodes to other nodes") {
            // Create a root node, child node, and grandchild node
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            TreeNamespace::tree<int, 3>::node* child = new TreeNamespace::tree<int, 3>::node(20);
            TreeNamespace::tree<int, 3>::node* grandChild = new TreeNamespace::tree<int, 3>::node(30);

            // Add the root and its subnodes
            treeInstance.add_root(root);
            treeInstance.add_sub_node(*root, *child);
            treeInstance.add_sub_node(*child, *grandChild);

            // The grandchild should be added correctly
            CHECK(child->getChildAt(0) == grandChild);
        }
        SUBCASE("Add multiple children to a node with size S") {
            // Create root and three child nodes
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(20);
            TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(30);
            TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(40);

            // Add root and its children
            treeInstance.add_root(root);
            treeInstance.add_sub_node(*root, *child1);
            treeInstance.add_sub_node(*root, *child2);
            treeInstance.add_sub_node(*root, *child3);

            // Check that the children were added correctly
            CHECK(root->getChildAt(0)== child1);
            CHECK(root->getChildAt(1)== child2);
            CHECK(root->getChildAt(2)== child3);
        }
        SUBCASE("Get root") {
            // Create and add a root node
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            treeInstance.add_root(root);

            // Check that the root is retrieved correctly
            CHECK(treeInstance.get_root() == root);
        }
    }
TEST_CASE("Tree Drawing with draw()") {
    SUBCASE("Draw tree of type <char, 4>") {
        // Create a 4-ary tree with characters
        TreeNamespace::tree<char, 4> treeInstance;
        TreeNamespace::tree<char, 4>::node* root = new TreeNamespace::tree<char, 4>::node('A');

        // Add 4 children to the root
        TreeNamespace::tree<char, 4>::node* child1 = new TreeNamespace::tree<char, 4>::node('B');
        TreeNamespace::tree<char, 4>::node* child2 = new TreeNamespace::tree<char, 4>::node('C');
        TreeNamespace::tree<char, 4>::node* child3 = new TreeNamespace::tree<char, 4>::node('D');
        TreeNamespace::tree<char, 4>::node* child4 = new TreeNamespace::tree<char, 4>::node('E');

        // Add second-generation children
        TreeNamespace::tree<char, 4>::node* grandchild1 = new TreeNamespace::tree<char, 4>::node('F');
        TreeNamespace::tree<char, 4>::node* grandchild2 = new TreeNamespace::tree<char, 4>::node('G');
        // Removed unused variable 'grandchild3'

        // Add third-generation children
        TreeNamespace::tree<char, 4>::node* greatGrandchild1 = new TreeNamespace::tree<char, 4>::node('I');
        TreeNamespace::tree<char, 4>::node* greatGrandchild2 = new TreeNamespace::tree<char, 4>::node('J');

        // Build the tree
        treeInstance.add_root(root);
        treeInstance.add_sub_node(*root, *child1);
        treeInstance.add_sub_node(*root, *child2);
        treeInstance.add_sub_node(*root, *child3);
        treeInstance.add_sub_node(*root, *child4);

        treeInstance.add_sub_node(*child1, *grandchild1);
        treeInstance.add_sub_node(*child1, *grandchild2);
        treeInstance.add_sub_node(*grandchild1, *greatGrandchild1);
        treeInstance.add_sub_node(*grandchild2, *greatGrandchild2);

        // Draw the tree using your draw function
        treeInstance.draw();
    }
    SUBCASE("Draw tree of type <int, 3>") {
        // Create a 3-ary tree with integers
        TreeNamespace::tree<int, 3> treeInstance;
        TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);

        // Add 3 children to the root
        TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(20);
        TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(30);
        TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(40);

        // Add second-generation children
        TreeNamespace::tree<int, 3>::node* grandchild1 = new TreeNamespace::tree<int, 3>::node(50);
        TreeNamespace::tree<int, 3>::node* grandchild2 = new TreeNamespace::tree<int, 3>::node(60);

        // Add third-generation children
        TreeNamespace::tree<int, 3>::node* greatGrandchild1 = new TreeNamespace::tree<int, 3>::node(70);

        // Build the tree
        treeInstance.add_root(root);
        treeInstance.add_sub_node(*root, *child1);
        treeInstance.add_sub_node(*root, *child2);
        treeInstance.add_sub_node(*root, *child3);

        treeInstance.add_sub_node(*child1, *grandchild1);
        treeInstance.add_sub_node(*child2, *grandchild2);
        treeInstance.add_sub_node(*grandchild1, *greatGrandchild1);

        // Draw the tree using your draw function
        treeInstance.draw();
    }
    SUBCASE("Draw tree of type <Complex, 1>") {
        // Create a 1-ary tree with Complex numbers (each node has only one child)
        TreeNamespace::tree<Complex, 1> treeInstance;
        Complex rootValue(3, 4);  // Assuming Complex(a, b) = a + bi
        TreeNamespace::tree<Complex, 1>::node* root = new TreeNamespace::tree<Complex, 1>::node(rootValue);

        // Add first child
        Complex childValue1(5, 6);
        TreeNamespace::tree<Complex, 1>::node* child1 = new TreeNamespace::tree<Complex, 1>::node(childValue1);

        // Add second-generation child
        Complex grandchildValue(7, 8);
        TreeNamespace::tree<Complex, 1>::node* grandchild1 = new TreeNamespace::tree<Complex, 1>::node(grandchildValue);

        // Add third-generation child
        Complex greatGrandchildValue(9, 10);
        TreeNamespace::tree<Complex, 1>::node* greatGrandchild1 = new TreeNamespace::tree<Complex, 1>::node(greatGrandchildValue);

        // Build the tree
        treeInstance.add_root(root);
        treeInstance.add_sub_node(*root, *child1);
        treeInstance.add_sub_node(*child1, *grandchild1);
        treeInstance.add_sub_node(*grandchild1, *greatGrandchild1);

        // Draw the tree using your draw function
        treeInstance.draw();
    }
}
TEST_CASE("tree_Iterator traversal tests for tree with 3 children") {
    // Create a tree with 3 children per node
/*
                         4

                     /   |  \
                   /.    |.  \
                  3      5     6
                /|\    /|\     |
               1 2 7  8 9 10   11

*/
    TreeNamespace::tree<int, 3> testTree;
    auto* root = new TreeNamespace::tree<int, 3>::node(4);
    auto* child1 = new TreeNamespace::tree<int, 3>::node(3);
    auto* child2 = new TreeNamespace::tree<int, 3>::node(5);
    auto* child3 = new TreeNamespace::tree<int, 3>::node(6);
    auto* grandchild1 = new TreeNamespace::tree<int, 3>::node(1);
    auto* grandchild2 = new TreeNamespace::tree<int, 3>::node(2);
    auto* grandchild3 = new TreeNamespace::tree<int, 3>::node(7);
    auto* grandchild4 = new TreeNamespace::tree<int, 3>::node(8);
    auto* grandchild5 = new TreeNamespace::tree<int, 3>::node(9);
    auto* grandchild6 = new TreeNamespace::tree<int, 3>::node(10);
    auto* grandchild7 = new TreeNamespace::tree<int, 3>::node(11);
    // Construct the tree
    root->setChildAt(0, child1);
    root->setChildAt(1, child2);
    root->setChildAt(2, child3);
    child1->setChildAt(0, grandchild1);
    child1->setChildAt(1, grandchild2);
    child1->setChildAt(2, grandchild3);
    child2->setChildAt(0, grandchild4);
    child2->setChildAt(1, grandchild5);
    child2->setChildAt(2, grandchild6);
    child3->setChildAt(0, grandchild7);
    testTree.set_root(root);

    SUBCASE("Pre-Order Traversal (begin_pre_order)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::begin_pre_order);
    std::vector<int> expected_pre_order = {4, 3, 1, 2, 7, 5, 8, 9, 10, 6, 11};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_pre_order[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_pre_order.size()-1);
}
    SUBCASE("Post-Order Traversal (begin_post_order)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::begin_post_order);
    std::vector<int> expected_post_order = {1, 2, 7, 3, 8, 9, 10, 5, 11, 6, 4};
    int index = 0;
        while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_post_order[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_post_order.size()-1);
}
    SUBCASE("In-Order Traversal (begin_in_order)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::begin_in_order);
    std::vector<int> expected_in_order = {1, 3, 2, 7, 4, 8, 5, 9, 10, 11, 6};
    int index = 0;
        while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_in_order[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_in_order.size()-1);
}
    SUBCASE("BFS Traversal (begin_bfs_scan)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::begin_bfs_scan);
    std::vector<int> expected_bfs = {4, 3, 5, 6, 1, 2, 7, 8, 9, 10, 11};
    int index = 0;
        while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_bfs[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_bfs.size()-1);
}
    SUBCASE("DFS Traversal (begin_dfs_scan)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::begin_dfs_scan);
    std::vector<int> expected_dfs = {4, 3, 1, 2, 7, 5, 8, 9, 10, 6, 11};
    int index = 0;
        while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_dfs[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_dfs.size()-1);
}
    SUBCASE("Pre-Order Traversal (end_pre_order)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::end_pre_order);
    std::vector<int> expected_pre_order_reverse = {11, 6, 10, 9, 8, 5, 7, 2, 1, 3, 4};
    int index = 0;
        while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_pre_order_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_pre_order_reverse.size()-1);
}
    SUBCASE("Post-Order Traversal (end_post_order)") {
        TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::end_post_order);
        std::vector<int> expected_post_order_reverse = {4, 6, 11, 5, 10, 9, 8, 3, 7, 2, 1};  // Corrected sequence
        int index = 0;
        while (it.index != it.vec.size()-1) {  // Updated condition for complete traversal
            CHECK(*it == expected_post_order_reverse[index]);
            ++index;
            ++it;
        }
        CHECK(index == expected_post_order_reverse.size()-1);
    }
    SUBCASE("In-Order Traversal (end_in_order)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::end_in_order);
    std::vector<int> expected_in_order_reverse = {6,11, 10, 9, 5, 8, 4, 7, 2, 3, 1};
    int index = 0;
        while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_in_order_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_in_order_reverse.size()-1);
}
    SUBCASE("BFS Traversal (end_bfs_scan)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::end_bfs_scan);
    std::vector<int> expected_bfs_reverse = {11, 10, 9, 8, 7, 2, 1, 6, 5, 3, 4};
    int index = 0;
        while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_bfs_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_bfs_reverse.size()-1);
}
    SUBCASE("DFS Traversal (end_dfs_scan)") {
    TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::end_dfs_scan);
    std::vector<int> expected_dfs_reverse = {11, 6, 10, 9, 8, 5, 7, 2, 1, 3, 4};
    int index = 0;
        while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_dfs_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_dfs_reverse.size()-1);
}
    SUBCASE("Iterator operators test (++ and --)") {
        TreeNamespace::tree<int,3>::tree_Iterator it(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::begin_in_order);
        CHECK(*it == 1);  // First element in in-order traversal
        ++it;
        CHECK(*it == 3);  // Second element
        ++it;
        CHECK(*it == 2);  // Third element

        --it;  // Move back to 3
        CHECK(*it == 3);
        --it;  // Move back to 1
        CHECK(*it == 1);
    }
    SUBCASE("Iterator equality and inequality operators (==, !=)") {
        TreeNamespace::tree<int,3>::tree_Iterator it1(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::begin_pre_order);
        TreeNamespace::tree<int,3>::tree_Iterator it2(&testTree, TreeNamespace::tree<int,3>::tree_Iterator::Order::begin_pre_order);

        CHECK(it1 == it2);  // Both iterators start at the same position
        ++it1;
        CHECK(it1 != it2);  // Now they point to different positions
    }
}
TEST_CASE("tree_Iterator traversal tests for binary tree with 2 children") {
    // Create a binary tree with 2 children per node
/*
                         4
                       /   \
                      3     5
                    /  \   /  \
                   1    2 6    7

*/
    TreeNamespace::tree<int, 2> testTree;
    auto* root = new TreeNamespace::tree<int, 2>::node(4);
    auto* child1 = new TreeNamespace::tree<int, 2>::node(3);
    auto* child2 = new TreeNamespace::tree<int, 2>::node(5);
    auto* grandchild1 = new TreeNamespace::tree<int, 2>::node(1);
    auto* grandchild2 = new TreeNamespace::tree<int, 2>::node(2);
    auto* grandchild3 = new TreeNamespace::tree<int, 2>::node(6);
    auto* grandchild4 = new TreeNamespace::tree<int, 2>::node(7);
    // Construct the tree
    root->setChildAt(0, child1);
    root->setChildAt(1, child2);
    child1->setChildAt(0, grandchild1);
    child1->setChildAt(1, grandchild2);
    child2->setChildAt(0, grandchild3);
    child2->setChildAt(1, grandchild4);
    testTree.set_root(root);

    SUBCASE("Pre-Order Traversal (begin_pre_order)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::begin_pre_order);
    std::vector<int> expected_pre_order = {4, 3, 1, 2, 5, 6, 7};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_pre_order[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_pre_order.size()-1);
}
    SUBCASE("Post-Order Traversal (begin_post_order)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::begin_post_order);
    std::vector<int> expected_post_order = {1, 2, 3, 6, 7, 5, 4};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_post_order[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_post_order.size()-1);
}
    SUBCASE("In-Order Traversal (begin_in_order)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::begin_in_order);
    std::vector<int> expected_in_order = {1, 3, 2, 4, 6, 5, 7};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_in_order[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_in_order.size()-1);
}
    SUBCASE("BFS Traversal (begin_bfs_scan)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::begin_bfs_scan);
    std::vector<int> expected_bfs = {4, 3, 5, 1, 2, 6, 7};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_bfs[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_bfs.size()-1);
}
    SUBCASE("DFS Traversal (begin_dfs_scan)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::begin_dfs_scan);
    std::vector<int> expected_dfs = {4, 3, 1, 2, 5, 6, 7};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_dfs[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_dfs.size()-1);
}
    SUBCASE("Pre-Order Traversal (end_pre_order)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::end_pre_order);
    std::vector<int> expected_pre_order_reverse = {7, 6, 5, 2, 1, 3, 4};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_pre_order_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_pre_order_reverse.size()-1);
}
    SUBCASE("Post-Order Traversal (end_post_order)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::end_post_order);
    std::vector<int> expected_post_order_reverse = {4, 5, 7, 6, 3, 2, 1};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_post_order_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_post_order_reverse.size()-1);
}
    SUBCASE("In-Order Traversal (end_in_order)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::end_in_order);
    std::vector<int> expected_in_order_reverse = {7, 5, 6, 4, 2, 3, 1};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_in_order_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_in_order_reverse.size()-1);
}
    SUBCASE("BFS Traversal (end_bfs_scan)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::end_bfs_scan);
    std::vector<int> expected_bfs_reverse = {7, 6, 2, 1, 5, 3, 4};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_bfs_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_bfs_reverse.size()-1);
}
    SUBCASE("DFS Traversal (end_dfs_scan)") {
    TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::end_dfs_scan);
    std::vector<int> expected_dfs_reverse = {7, 6, 5, 2, 1, 3, 4};
    int index = 0;
    while (it.index != it.vec.size()-1) {
        CHECK(*it == expected_dfs_reverse[index]);
        ++index;
        ++it;
    }
    CHECK(index == expected_dfs_reverse.size()-1);
}
    SUBCASE("Iterator operators test (++ and --)") {
        TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::begin_in_order);
        CHECK(*it == 1);  // First element in in-order traversal
        ++it;
        CHECK(*it == 3);  // Second element
        ++it;
        CHECK(*it == 2);  // Third element

        --it;  // Move back to 3
        CHECK(*it == 3);
        --it;  // Move back to 1
        CHECK(*it == 1);
    }
    SUBCASE("Iterator equality and inequality operators (==, !=)") {
        TreeNamespace::tree<int,2>::tree_Iterator it1(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::begin_pre_order);
        TreeNamespace::tree<int,2>::tree_Iterator it2(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::begin_pre_order);

        CHECK(it1 == it2);  // Both iterators start at the same position
        ++it1;
        CHECK(it1 != it2);  // Now they point to different positions
    }
}

TEST_CASE("tree_Iterator traversal tests for binary tree with 2 children and MinHeap") {
    // Create a binary tree with 2 children per node
    /*
                         4
                       /   \
                      3     5
                    /  \   /  \
                   1    2 6    7
    */
    TreeNamespace::tree<int, 2> testTree;
    auto* root = new TreeNamespace::tree<int, 2>::node(4);
    auto* child1 = new TreeNamespace::tree<int, 2>::node(3);
    auto* child2 = new TreeNamespace::tree<int, 2>::node(5);
    auto* grandchild1 = new TreeNamespace::tree<int, 2>::node(1);
    auto* grandchild2 = new TreeNamespace::tree<int, 2>::node(2);
    auto* grandchild3 = new TreeNamespace::tree<int, 2>::node(6);
    auto* grandchild4 = new TreeNamespace::tree<int, 2>::node(7);

    // Construct the tree
    root->setChildAt(0, child1);
    root->setChildAt(1, child2);
    child1->setChildAt(0, grandchild1);
    child1->setChildAt(1, grandchild2);
    child2->setChildAt(0, grandchild3);
    child2->setChildAt(1, grandchild4);
    testTree.set_root(root);

    SUBCASE("Heap Order Verification") {
        // Create the tree iterator with MinHeap order
        TreeNamespace::tree<int,2>::tree_Iterator it(&testTree, TreeNamespace::tree<int,2>::tree_Iterator::Order::Heap);

        // Traverse the tree in Heap order and check MinHeap properties
        std::vector<int> heap_order;
        while (it.index != it.vec.size()-1) {
            heap_order.push_back(*it);
            ++it;
        }

        // Verify that each parent is less than or equal to its children (MinHeap property)
        for (size_t i = 0; i < heap_order.size() / 2; ++i) {
            size_t leftChildIdx = 2 * i + 1;
            size_t rightChildIdx = 2 * i + 2;

            if (leftChildIdx < heap_order.size()) {
                CHECK(heap_order[i] <= heap_order[leftChildIdx]);
            }
            if (rightChildIdx < heap_order.size()) {
                CHECK(heap_order[i] <= heap_order[rightChildIdx]);
            }
        }
    }
}