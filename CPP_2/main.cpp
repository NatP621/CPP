#include "tree.hpp"

int main() {
    // Créer un arbre avec des noeuds de type entier
    TreeNamespace::tree<int, 2> myTree;

    // Créer des noeuds de l'arbre
    auto root = new TreeNamespace::tree<int, 2>::node(1);  // Racine avec la valeur 1
    auto child1 = new TreeNamespace::tree<int, 2>::node(2); // Enfant 1 avec la valeur 2
    auto child2 = new TreeNamespace::tree<int, 2>::node(3); // Enfant 2 avec la valeur 3
    auto child3 = new TreeNamespace::tree<int, 2>::node(4); // Enfant du noeud 2 avec la valeur 4

    // Ajouter la racine à l'arbre
    myTree.add_root(*root);

    // Ajouter des sous-noeuds
    myTree.add_sub_node(*root, *child1);
    myTree.add_sub_node(*root, *child2);
    myTree.add_sub_node(*child1, *child3);

    return 0;
}
