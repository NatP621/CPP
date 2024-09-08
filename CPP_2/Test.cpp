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
        CHECK(defaultNode.childrens.size() == 3);

        // Each child should be initialized to nullptr
        for (auto child : defaultNode.childrens) {
            CHECK(child == nullptr);
        }
    }
    SUBCASE("Parameterized node constructor with size S") {
        // Create a node with a value of 10 and 4 children slots
        TreeNamespace::tree<int, 4>::node paramNode(10);  // Using S = 4

        // Verify the node holds the correct data
        CHECK(paramNode.data == 10);

        // Verify the node has exactly 4 children slots
        CHECK(paramNode.childrens.size() == 4);

        // Each child should be initialized to nullptr
        for (auto child : paramNode.childrens) {
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
        treeInstance.add_root(*root);

        // Verify that the root is correctly added
        CHECK(treeInstance.get_root() == root);
        CHECK(treeInstance.get_root()->data == 10);
    }
    SUBCASE("Adding children to the root node") {
        // Create a root node and add it to the tree
        TreeNamespace::tree<int>::node* root = new TreeNamespace::tree<int>::node(10);
        treeInstance.add_root(*root);

        // Create child nodes
        TreeNamespace::tree<int>::node* child1 = new TreeNamespace::tree<int>::node(20);
        TreeNamespace::tree<int>::node* child2 = new TreeNamespace::tree<int>::node(30);

        // Add children to the root node
        treeInstance.add_sub_node(*root, *child1);
        treeInstance.add_sub_node(*root, *child2);

        // Verify that the children were added correctly
        CHECK(root->childrens[0] == child1);
        CHECK(root->childrens[1] == child2);
        CHECK(root->childrens[0]->data == 20);
        CHECK(root->childrens[1]->data == 30);
    }
    SUBCASE("Replacing the root node") {
        // Create a root node and add it to the tree
        TreeNamespace::tree<int>::node* root1 = new TreeNamespace::tree<int>::node(10);
        treeInstance.add_root(*root1);

        // Create a new root node
        TreeNamespace::tree<int>::node* root2 = new TreeNamespace::tree<int>::node(100);
        treeInstance.add_root(*root2);  // This replaces the original root

        // Verify that the new root replaced the old one
        CHECK(treeInstance.get_root() == root2);
        CHECK(treeInstance.get_root()->data == 100);
    }
    SUBCASE("Adding a root and multiple levels of children") {
        // Create a root node
        TreeNamespace::tree<int>::node* root = new TreeNamespace::tree<int>::node(50);
        treeInstance.add_root(*root);

        // Add children to the root
        TreeNamespace::tree<int>::node* child1 = new TreeNamespace::tree<int>::node(20);
        TreeNamespace::tree<int>::node* child2 = new TreeNamespace::tree<int>::node(30);
        treeInstance.add_sub_node(*root, *child1);
        treeInstance.add_sub_node(*root, *child2);

        // Add children to child1
        TreeNamespace::tree<int>::node* grandChild1 = new TreeNamespace::tree<int>::node(5);
        treeInstance.add_sub_node(*child1, *grandChild1);

        // Verify the tree structure
        CHECK(root->childrens[0] == child1);
        CHECK(root->childrens[1] == child2);
        CHECK(child1->childrens[0] == grandChild1);

        // Verify the node values
        CHECK(root->data == 50);
        CHECK(child1->data == 20);
        CHECK(child2->data == 30);
        CHECK(grandChild1->data == 5);
    }
}
TEST_CASE("Tree Root and Subnodes Manipulation with size S") {
        TreeNamespace::tree<int, 3> treeInstance;  // Using S = 3
        SUBCASE("Add root") {
            // Create a root node and add it to the tree
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            treeInstance.add_root(*root);

            // The root should be added correctly
            CHECK(treeInstance.get_root() == root);
        }
        SUBCASE("Replace root with new root") {
            // Create two root nodes
            TreeNamespace::tree<int, 3>::node* root1 = new TreeNamespace::tree<int, 3>::node(10);
            TreeNamespace::tree<int, 3>::node* root2 = new TreeNamespace::tree<int, 3>::node(20);

            // Add the first root, then replace it with the second
            treeInstance.add_root(*root1);
            treeInstance.add_root(*root2);

            // The root should be replaced correctly
            CHECK(treeInstance.get_root() == root2);
        }
        SUBCASE("Add subnodes to root") {
            // Create a root node and a child node
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            TreeNamespace::tree<int, 3>::node* child = new TreeNamespace::tree<int, 3>::node(20);

            // Add root and subnode
            treeInstance.add_root(*root);
            treeInstance.add_sub_node(*root, *child);

            // The root's first child should be added correctly
            CHECK(root->childrens[0] == child);
        }
        SUBCASE("Add subnodes to other nodes") {
            // Create a root node, child node, and grandchild node
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            TreeNamespace::tree<int, 3>::node* child = new TreeNamespace::tree<int, 3>::node(20);
            TreeNamespace::tree<int, 3>::node* grandChild = new TreeNamespace::tree<int, 3>::node(30);

            // Add the root and its subnodes
            treeInstance.add_root(*root);
            treeInstance.add_sub_node(*root, *child);
            treeInstance.add_sub_node(*child, *grandChild);

            // The grandchild should be added correctly
            CHECK(child->childrens[0] == grandChild);
        }
        SUBCASE("Add multiple children to a node with size S") {
            // Create root and three child nodes
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(20);
            TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(30);
            TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(40);

            // Add root and its children
            treeInstance.add_root(*root);
            treeInstance.add_sub_node(*root, *child1);
            treeInstance.add_sub_node(*root, *child2);
            treeInstance.add_sub_node(*root, *child3);

            // Check that the children were added correctly
            CHECK(root->childrens[0] == child1);
            CHECK(root->childrens[1] == child2);
            CHECK(root->childrens[2] == child3);
        }
        SUBCASE("Get root") {
            // Create and add a root node
            TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
            treeInstance.add_root(*root);

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

        // Build the tree
        treeInstance.add_root(*root);
        treeInstance.add_sub_node(*root, *child1);
        treeInstance.add_sub_node(*root, *child2);
        treeInstance.add_sub_node(*root, *child3);
        treeInstance.add_sub_node(*root, *child4);

        // Draw the tree using your draw function
        TreeNamespace::draw<char, 4>(treeInstance);  // Use the correct draw call
    }
    // SUBCASE("Draw tree of type <int, 3>") {
    //     // Create a 3-ary tree with integers
    //     TreeNamespace::tree<int, 3> treeInstance;
    //     TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
    //
    //     // Add 3 children to the root
    //     TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(20);
    //     TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(30);
    //     TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(40);
    //
    //     // Build the tree
    //     treeInstance.add_root(*root);
    //     treeInstance.add_sub_node(*root, *child1);
    //     treeInstance.add_sub_node(*root, *child2);
    //     treeInstance.add_sub_node(*root, *child3);
    //
    //     // Draw the tree using your draw function
    //     TreeNamespace::draw<int, 3>(treeInstance.get_root());  // Use the correct draw call
    // }
    // SUBCASE("Draw tree of type <Complex, 1>") {
    //     // Create a 1-ary tree with Complex numbers (each node has only one child)
    //     TreeNamespace::tree<Complex, 1> treeInstance;
    //     Complex rootValue(3, 4);  // Assuming Complex(a, b) = a + bi
    //     TreeNamespace::tree<Complex, 1>::node* root = new TreeNamespace::tree<Complex, 1>::node(rootValue);
    //
    //     // Add 1 child to the root
    //     Complex childValue(5, 6);
    //     TreeNamespace::tree<Complex, 1>::node* child = new TreeNamespace::tree<Complex, 1>::node(childValue);
    //
    //     // Build the tree
    //     treeInstance.add_root(*root);
    //     treeInstance.add_sub_node(*root, *child);
    //
    //     // Draw the tree using your draw function
    //     TreeNamespace::draw<Complex, 1>(treeInstance.get_root());  // Use the correct draw call
    // }
}




TEST_CASE("Min-Heap for binary tree") {
        SUBCASE("Integers") {
            SUBCASE("Tree 1") {
            }
            SUBCASE("Tree 2") {
            }
        }

        SUBCASE("Complex") {
            SUBCASE("Tree 1") {
            }
            SUBCASE("Tree 2") {
            }
        }
    }
TEST_CASE("Tree Iterators for binary tree of integers") {

    SUBCASE("Pre-order Traversal") {
        }

        SUBCASE("In-order Traversal") {
        }

        SUBCASE("Post-order Traversal") {
        }

        SUBCASE("BFS Traversal") {
        }

        SUBCASE("DFS Traversal") {
        }

        SUBCASE("MIN Heap iterator") {
        }

        SUBCASE("Iterator operations") {
            SUBCASE("operator*") {
            }
            SUBCASE("operator->") {
            }
            SUBCASE("operator++") {
            }
            SUBCASE("operator== and operator!=") {
            }
        }

        SUBCASE("Traverse an empty tree") {
        }
    }
TEST_CASE("Tree Iterators for binary tree of Complex") {
        SUBCASE("Pre-order Traversal") {
        }

        SUBCASE("In-order Traversal") {
        }

        SUBCASE("Post-order Traversal") {
        }

        SUBCASE("BFS Traversal") {
        }

        SUBCASE("DFS Traversal") {
        }

        SUBCASE("MIN Heap iterator") {
        }

        SUBCASE("Iterator operations") {
            SUBCASE("operator*") {
            }
            SUBCASE("operator->") {
            }
            SUBCASE("operator++") {
            }
            SUBCASE("operator== and operator!=") {
            }
        }

        SUBCASE("Traverse an empty tree") {
        }
    }
TEST_CASE("Tree Iterators for 4-ary tree of integers") {
        SUBCASE("Pre-order Traversal") {
        }

        SUBCASE("In-order Traversal") {
        }

        SUBCASE("Post-order Traversal") {
        }

        SUBCASE("BFS Traversal") {
        }

        SUBCASE("DFS Traversal") {
        }

        SUBCASE("MIN Heap iterator (should be as DFS)") {
        }
    }
TEST_CASE("Tree Iterators for 4-ary tree of Complex") {
        SUBCASE("Pre-order Traversal") {
        }

        SUBCASE("In-order Traversal") {
        }

        SUBCASE("Post-order Traversal") {
        }

        SUBCASE("BFS Traversal") {
        }

        SUBCASE("DFS Traversal") {
        }

        SUBCASE("MIN Heap iterator (should be as DFS)") {
        }
    }
TEST_CASE("Edge cases") {
        SUBCASE("Attempt to add a subnode to a null parent") {
        }

        SUBCASE("Attempt to traverse an empty tree") {
        }

        SUBCASE("Test large tree with multiple levels") {
        }
    }