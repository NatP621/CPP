// natane.djedou@gmail.com //
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <SFML/Graphics.hpp>
#include "doctest.h"
#include "tree.hpp"
#include "Complex.hpp"

// TEST_CASE("Tree Node Construction") {
//     SUBCASE("Default node constructor with size S") {
//         // Create a default node with 3 children slots
//         TreeNamespace::tree<int, 3>::node defaultNode;  // Using S = 3
//
//         // Verify the node has exactly 3 children slots
//         CHECK(defaultNode.getChildrens().size() == 3);
//
//         // Each child should be initialized to nullptr
//         for (auto child : defaultNode.getChildrens()) {
//             CHECK(child == nullptr);
//         }
//     }
//     SUBCASE("Parameterized node constructor with size S") {
//         // Create a node with a value of 10 and 4 children slots
//         TreeNamespace::tree<int, 4>::node paramNode(10);  // Using S = 4
//
//         // Verify the node holds the correct data
//         CHECK(paramNode.getData() == 10);
//
//         // Verify the node has exactly 4 children slots
//         CHECK(paramNode.getChildrens().size() == 4);
//
//         // Each child should be initialized to nullptr
//         for (auto child : paramNode.getChildrens()) {
//             CHECK(child == nullptr);
//         }
//     }
// }
// TEST_CASE("Tree Construction and Destruction") {
//     TreeNamespace::tree<int> treeInstance;
//     SUBCASE("Default Constructor") {
//         // Verify that the default constructor initializes the tree with no root
//         CHECK(treeInstance.get_root() == nullptr);
//     }
//     SUBCASE("Adding a root node") {
//         // Create a root node and add it to the tree
//         TreeNamespace::tree<int>::node* root = new TreeNamespace::tree<int>::node(10);
//         treeInstance.add_root(root);
//
//         // Verify that the root is correctly added
//         CHECK(treeInstance.get_root() == root);
//         CHECK(treeInstance.get_root()->getData() == 10);
//     }
//     SUBCASE("Adding children to the root node") {
//         // Create a root node and add it to the tree
//         TreeNamespace::tree<int>::node* root = new TreeNamespace::tree<int>::node(10);
//         treeInstance.add_root(root);
//
//         // Create child nodes
//         TreeNamespace::tree<int>::node* child1 = new TreeNamespace::tree<int>::node(20);
//         TreeNamespace::tree<int>::node* child2 = new TreeNamespace::tree<int>::node(30);
//
//         // Add children to the root node
//         treeInstance.add_sub_node(*root, *child1);
//         treeInstance.add_sub_node(*root, *child2);
//
//         // Verify that the children were added correctly
//         CHECK(root->getChildAt(0) == child1);
//         CHECK(root->getChildAt(1) == child2);
//         CHECK(root->getChildAt(0)->getData() == 20);
//         CHECK(root->getChildAt(1)->getData() == 30);
//     }
//     SUBCASE("Replacing the root node") {
//         // Create a root node and add it to the tree
//         TreeNamespace::tree<int>::node* root1 = new TreeNamespace::tree<int>::node(10);
//         treeInstance.add_root(root1);
//
//         // Create a new root node
//         TreeNamespace::tree<int>::node* root2 = new TreeNamespace::tree<int>::node(100);
//         treeInstance.add_root(root2);  // This replaces the original root
//
//         // Verify that the new root replaced the old one
//         CHECK(treeInstance.get_root() == root2);
//         CHECK(treeInstance.get_root()->getData() == 100);
//     }
//     SUBCASE("Adding a root and multiple levels of children") {
//         // Create a root node
//         TreeNamespace::tree<int>::node* root = new TreeNamespace::tree<int>::node(50);
//         treeInstance.add_root(root);
//
//         // Add children to the root
//         TreeNamespace::tree<int>::node* child1 = new TreeNamespace::tree<int>::node(20);
//         TreeNamespace::tree<int>::node* child2 = new TreeNamespace::tree<int>::node(30);
//         treeInstance.add_sub_node(*root, *child1);
//         treeInstance.add_sub_node(*root, *child2);
//
//         // Add children to child1
//         TreeNamespace::tree<int>::node* grandChild1 = new TreeNamespace::tree<int>::node(5);
//         treeInstance.add_sub_node(*child1, *grandChild1);
//
//         // Verify the tree structure
//         CHECK(root->getChildAt(0) == child1);
//         CHECK(root->getChildAt(1) == child2);
//         CHECK(child1->getChildAt(0) == grandChild1);
//
//         // Verify the node values
//         CHECK(root->getData()== 50);
//         CHECK(child1->getData() == 20);
//         CHECK(child2->getData()== 30);
//         CHECK(grandChild1->getData() == 5);
//     }
// }
// TEST_CASE("Tree Root and Subnodes Manipulation with size S") {
//         TreeNamespace::tree<int, 3> treeInstance;  // Using S = 3
//         SUBCASE("Add root") {
//             // Create a root node and add it to the tree
//             TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
//             treeInstance.add_root(root);
//
//             // The root should be added correctly
//             CHECK(treeInstance.get_root() == root);
//         }
//         SUBCASE("Replace root with new root") {
//             // Create two root nodes
//             TreeNamespace::tree<int, 3>::node* root1 = new TreeNamespace::tree<int, 3>::node(10);
//             TreeNamespace::tree<int, 3>::node* root2 = new TreeNamespace::tree<int, 3>::node(20);
//
//             // Add the first root, then replace it with the second
//             treeInstance.add_root(root1);
//             treeInstance.add_root(root2);
//
//             // The root should be replaced correctly
//             CHECK(treeInstance.get_root() == root2);
//         }
//         SUBCASE("Add subnodes to root") {
//             // Create a root node and a child node
//             TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
//             TreeNamespace::tree<int, 3>::node* child = new TreeNamespace::tree<int, 3>::node(20);
//
//             // Add root and subnode
//             treeInstance.add_root(root);
//             treeInstance.add_sub_node(*root, *child);
//
//             // The root's first child should be added correctly
//             CHECK(root->getChildAt(0) == child);
//         }
//         SUBCASE("Add subnodes to other nodes") {
//             // Create a root node, child node, and grandchild node
//             TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
//             TreeNamespace::tree<int, 3>::node* child = new TreeNamespace::tree<int, 3>::node(20);
//             TreeNamespace::tree<int, 3>::node* grandChild = new TreeNamespace::tree<int, 3>::node(30);
//
//             // Add the root and its subnodes
//             treeInstance.add_root(root);
//             treeInstance.add_sub_node(*root, *child);
//             treeInstance.add_sub_node(*child, *grandChild);
//
//             // The grandchild should be added correctly
//             CHECK(child->getChildAt(0) == grandChild);
//         }
//         SUBCASE("Add multiple children to a node with size S") {
//             // Create root and three child nodes
//             TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
//             TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(20);
//             TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(30);
//             TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(40);
//
//             // Add root and its children
//             treeInstance.add_root(root);
//             treeInstance.add_sub_node(*root, *child1);
//             treeInstance.add_sub_node(*root, *child2);
//             treeInstance.add_sub_node(*root, *child3);
//
//             // Check that the children were added correctly
//             CHECK(root->getChildAt(0)== child1);
//             CHECK(root->getChildAt(1)== child2);
//             CHECK(root->getChildAt(2)== child3);
//         }
//         SUBCASE("Get root") {
//             // Create and add a root node
//             TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
//             treeInstance.add_root(root);
//
//             // Check that the root is retrieved correctly
//             CHECK(treeInstance.get_root() == root);
//         }
//     }
// TEST_CASE("Tree Drawing with draw()") {
//     SUBCASE("Draw tree of type <char, 4>") {
//         // Create a 4-ary tree with characters
//         TreeNamespace::tree<char, 4> treeInstance;
//         TreeNamespace::tree<char, 4>::node* root = new TreeNamespace::tree<char, 4>::node('A');
//
//         // Add 4 children to the root
//         TreeNamespace::tree<char, 4>::node* child1 = new TreeNamespace::tree<char, 4>::node('B');
//         TreeNamespace::tree<char, 4>::node* child2 = new TreeNamespace::tree<char, 4>::node('C');
//         TreeNamespace::tree<char, 4>::node* child3 = new TreeNamespace::tree<char, 4>::node('D');
//         TreeNamespace::tree<char, 4>::node* child4 = new TreeNamespace::tree<char, 4>::node('E');
//
//         // Add second-generation children
//         TreeNamespace::tree<char, 4>::node* grandchild1 = new TreeNamespace::tree<char, 4>::node('F');
//         TreeNamespace::tree<char, 4>::node* grandchild2 = new TreeNamespace::tree<char, 4>::node('G');
//         // Removed unused variable 'grandchild3'
//
//         // Add third-generation children
//         TreeNamespace::tree<char, 4>::node* greatGrandchild1 = new TreeNamespace::tree<char, 4>::node('I');
//         TreeNamespace::tree<char, 4>::node* greatGrandchild2 = new TreeNamespace::tree<char, 4>::node('J');
//
//         // Build the tree
//         treeInstance.add_root(root);
//         treeInstance.add_sub_node(*root, *child1);
//         treeInstance.add_sub_node(*root, *child2);
//         treeInstance.add_sub_node(*root, *child3);
//         treeInstance.add_sub_node(*root, *child4);
//
//         treeInstance.add_sub_node(*child1, *grandchild1);
//         treeInstance.add_sub_node(*child1, *grandchild2);
//         treeInstance.add_sub_node(*grandchild1, *greatGrandchild1);
//         treeInstance.add_sub_node(*grandchild2, *greatGrandchild2);
//
//         // Draw the tree using your draw function
//         treeInstance.draw();
//     }
//     SUBCASE("Draw tree of type <int, 3>") {
//         // Create a 3-ary tree with integers
//         TreeNamespace::tree<int, 3> treeInstance;
//         TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
//
//         // Add 3 children to the root
//         TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(20);
//         TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(30);
//         TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(40);
//
//         // Add second-generation children
//         TreeNamespace::tree<int, 3>::node* grandchild1 = new TreeNamespace::tree<int, 3>::node(50);
//         TreeNamespace::tree<int, 3>::node* grandchild2 = new TreeNamespace::tree<int, 3>::node(60);
//
//         // Add third-generation children
//         TreeNamespace::tree<int, 3>::node* greatGrandchild1 = new TreeNamespace::tree<int, 3>::node(70);
//
//         // Build the tree
//         treeInstance.add_root(root);
//         treeInstance.add_sub_node(*root, *child1);
//         treeInstance.add_sub_node(*root, *child2);
//         treeInstance.add_sub_node(*root, *child3);
//
//         treeInstance.add_sub_node(*child1, *grandchild1);
//         treeInstance.add_sub_node(*child2, *grandchild2);
//         treeInstance.add_sub_node(*grandchild1, *greatGrandchild1);
//
//         // Draw the tree using your draw function
//         treeInstance.draw();
//     }
//     SUBCASE("Draw tree of type <Complex, 1>") {
//         // Create a 1-ary tree with Complex numbers (each node has only one child)
//         TreeNamespace::tree<Complex, 1> treeInstance;
//         Complex rootValue(3, 4);  // Assuming Complex(a, b) = a + bi
//         TreeNamespace::tree<Complex, 1>::node* root = new TreeNamespace::tree<Complex, 1>::node(rootValue);
//
//         // Add first child
//         Complex childValue1(5, 6);
//         TreeNamespace::tree<Complex, 1>::node* child1 = new TreeNamespace::tree<Complex, 1>::node(childValue1);
//
//         // Add second-generation child
//         Complex grandchildValue(7, 8);
//         TreeNamespace::tree<Complex, 1>::node* grandchild1 = new TreeNamespace::tree<Complex, 1>::node(grandchildValue);
//
//         // Add third-generation child
//         Complex greatGrandchildValue(9, 10);
//         TreeNamespace::tree<Complex, 1>::node* greatGrandchild1 = new TreeNamespace::tree<Complex, 1>::node(greatGrandchildValue);
//
//         // Build the tree
//         treeInstance.add_root(root);
//         treeInstance.add_sub_node(*root, *child1);
//         treeInstance.add_sub_node(*child1, *grandchild1);
//         treeInstance.add_sub_node(*grandchild1, *greatGrandchild1);
//
//         // Draw the tree using your draw function
//         treeInstance.draw();
//     }
// }
// TEST_CASE("Test tree_Iterator constructors") {
//     using Tree = TreeNamespace::tree<int>;  // Replace with your namespace if different
//
//     // Create a simple tree with a single node
//     auto root = new Tree::node(10);
//
//     // Case 1: Test the default constructor
//     Tree::tree_Iterator it_default;
//     CHECK(it_default.current_pnt == nullptr);  // The current pointer should be null
//     CHECK(it_default.is_bfs == false);  // By default, the iterator should not use BFS
//
//     // Case 2: Test the constructor with a root node and DFS
//     Tree::tree_Iterator it_dfs(root, false);  // Use DFS traversal
//     CHECK(it_dfs.current_pnt == root);  // The current pointer should be the root
//     CHECK(it_dfs.is_bfs == false);  // The iterator should use DFS
//     CHECK(!it_dfs.stack.empty());  // The DFS stack should not be empty
//     CHECK(it_dfs.stack.top() == root);  // The top of the stack should be the root
//
//     // Case 3: Test the constructor with a root node and BFS
//     Tree::tree_Iterator it_bfs(root, true);  // Use BFS traversal
//     CHECK(it_bfs.current_pnt == root);  // The current pointer should be the root
//     CHECK(it_bfs.is_bfs == true);  // The iterator should use BFS
//     CHECK(!it_bfs.queue.empty());  // The BFS queue should not be empty
//     CHECK(it_bfs.queue.front() == root);  // The front of the queue should be the root
// }
TEST_CASE("Test of * and -> operators") {
    // Create a tree with 3 children per node
    TreeNamespace::tree<int, 3> myTree;

    // Create the root node
    TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(1);

    // Level 1 children
    TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(2);
    TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(3);
    TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(4);

    // Add children to the root node
    root->setChildAt(0, child1);
    root->setChildAt(1, child2);
    root->setChildAt(2, child3);

    // Create a DFS iterator
    TreeNamespace::tree<int, 3>::tree_Iterator it(root, false);  // DFS

    // Test dereference operator
    CHECK((*it).getData() == 1);  // The root should have a value of 1
    // Test arrow operator
    CHECK(it->getData() == 1);  // The root should have a value of 1
    // Move the iterator using pre-increment and check the children
    ++it;
    CHECK((*it).getData() == 2);  // The first child should have a value of 2
    ++it;
    CHECK((*it).getData() == 3);  // The second child should have a value of 3
    ++it;
    CHECK((*it).getData() == 4);  // The third child should have a value of 4
}

// // Test de l'opérateur de pré-incrément (++it)
// TEST_CASE("Test de l'opérateur ++ (pré-incrément)") {
//     TreeNamespace::tree<int, 3> myTree;
//
//     // Création de la racine
//     TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(10);
//
//     // Niveau 1
//     TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(20);
//     TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(30);
//     TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(40);
//
//     // Ajout des enfants au nœud racine
//     root->childrens[0] = child1;
//     root->childrens[1] = child2;
//     root->childrens[2] = child3;
//
//     // Itérateur DFS
//     TreeNamespace::tree<int, 3>::tree_Iterator it(root, false);  // DFS
//
//     CHECK(it->data == 10);  // La racine est 10
//
//     ++it;  // Pré-incrément
//     CHECK(it->data == 20);  // Le premier enfant est 20
//
//     ++it;  // Pré-incrément
//     CHECK(it->data == 30);  // Le deuxième enfant est 30
//
//     ++it;  // Pré-incrément
//     CHECK(it->data == 40);  // Le troisième enfant est 40
// }
// // Test de l'opérateur de post-incrément (it++)
// TEST_CASE("Test de l'opérateur ++ (post-incrément)") {
//     TreeNamespace::tree<int, 3> myTree;
//
//     // Création de la racine
//     TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(50);
//
//     // Niveau 1
//     TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(60);
//     TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(70);
//     TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(80);
//
//     // Ajout des enfants au nœud racine
//     root->childrens[0] = child1;
//     root->childrens[1] = child2;
//     root->childrens[2] = child3;
//
//     // Itérateur DFS
//     TreeNamespace::tree<int, 3>::tree_Iterator it(root, false);  // DFS
//
//     CHECK(it->data == 50);  // Racine
//
//     TreeNamespace::tree<int, 3>::tree_Iterator old_it = it++;  // Post-incrément
//     CHECK(old_it->data == 50);  // Ancien itérateur doit pointer vers 50
//     CHECK(it->data == 60);  // Nouveau itérateur doit pointer vers 60
//
//     old_it = it++;
//     CHECK(old_it->data == 60);  // Ancien itérateur doit pointer vers 60
//     CHECK(it->data == 70);  // Nouveau itérateur doit pointer vers 70
// }
// // Test pour les opérateurs == et !=
// TEST_CASE("Test des opérateurs == et !=") {
//     TreeNamespace::tree<int, 3> myTree;
//
//     // Création de la racine
//     TreeNamespace::tree<int, 3>::node* root = new TreeNamespace::tree<int, 3>::node(100);
//
//     // Niveau 1
//     TreeNamespace::tree<int, 3>::node* child1 = new TreeNamespace::tree<int, 3>::node(110);
//     TreeNamespace::tree<int, 3>::node* child2 = new TreeNamespace::tree<int, 3>::node(120);
//     TreeNamespace::tree<int, 3>::node* child3 = new TreeNamespace::tree<int, 3>::node(130);
//
//     // Ajout des enfants au nœud racine
//     root->childrens[0] = child1;
//     root->childrens[1] = child2;
//     root->childrens[2] = child3;
//
//     // Itérateur DFS
//     TreeNamespace::tree<int, 3>::tree_Iterator it1(root, false);  // DFS
//     TreeNamespace::tree<int, 3>::tree_Iterator it2(root, false);  // DFS
//
//     CHECK(it1 == it2);  // Les deux itérateurs doivent pointer vers la racine au départ
//
//     ++it1;
//     CHECK(it1 != it2);  // Après l'incrémentation de it1, ils ne doivent plus être égaux
// }