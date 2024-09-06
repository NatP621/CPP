#include "tree.hpp"

int main() {
    // Création d'un arbre avec la classe `tree`
    TreeNamespace::tree<int, 3> myTree;  // Un arbre avec 3 enfants par nœud

    // Création de la racine
    auto* root = new TreeNamespace::tree<int, 3>::node(1);

    // Niveau 1
    auto* child1 = new TreeNamespace::tree<int, 3>::node(2);
    auto* child2 = new TreeNamespace::tree<int, 3>::node(3);
    auto* child3 = new TreeNamespace::tree<int, 3>::node(4);

    // Ajout des enfants au nœud racine
    root->childrens[0] = child1;
    root->childrens[1] = child2;
    root->childrens[2] = child3;

    // Niveau 2
    auto* child1_1 = new TreeNamespace::tree<int, 3>::node(5);
    auto* child1_2 = new TreeNamespace::tree<int, 3>::node(6);
    auto* child1_3 = new TreeNamespace::tree<int, 3>::node(7);

    auto* child2_1 = new TreeNamespace::tree<int, 3>::node(8);
    auto* child2_2 = new TreeNamespace::tree<int, 3>::node(9);
    auto* child2_3 = new TreeNamespace::tree<int, 3>::node(10);

    auto* child3_1 = new TreeNamespace::tree<int, 3>::node(11);
    auto* child3_2 = new TreeNamespace::tree<int, 3>::node(12);
    auto* child3_3 = new TreeNamespace::tree<int, 3>::node(13);

    // Ajout des enfants à child1
    child1->childrens[0] = child1_1;
    child1->childrens[1] = child1_2;
    child1->childrens[2] = child1_3;

    // Ajout des enfants à child2
    child2->childrens[0] = child2_1;
    child2->childrens[1] = child2_2;
    child2->childrens[2] = child2_3;

    // Ajout des enfants à child3
    child3->childrens[0] = child3_1;
    child3->childrens[1] = child3_2;
    child3->childrens[2] = child3_3;

    // Niveau 3 (pour rendre l'arbre complet)
    auto* child1_1_1 = new TreeNamespace::tree<int, 3>::node(14);
    auto* child1_1_2 = new TreeNamespace::tree<int, 3>::node(15);
    auto* child1_1_3 = new TreeNamespace::tree<int, 3>::node(16);

    auto* child1_2_1 = new TreeNamespace::tree<int, 3>::node(17);
    auto* child1_2_2 = new TreeNamespace::tree<int, 3>::node(18);
    auto* child1_2_3 = new TreeNamespace::tree<int, 3>::node(19);

    auto* child1_3_1 = new TreeNamespace::tree<int, 3>::node(20);
    auto* child1_3_2 = new TreeNamespace::tree<int, 3>::node(21);
    auto* child1_3_3 = new TreeNamespace::tree<int, 3>::node(22);

    auto* child2_1_1 = new TreeNamespace::tree<int, 3>::node(23);
    auto* child2_1_2 = new TreeNamespace::tree<int, 3>::node(24);
    auto* child2_1_3 = new TreeNamespace::tree<int, 3>::node(25);

    auto* child2_2_1 = new TreeNamespace::tree<int, 3>::node(26);
    auto* child2_2_2 = new TreeNamespace::tree<int, 3>::node(27);
    auto* child2_2_3 = new TreeNamespace::tree<int, 3>::node(28);

    auto* child2_3_1 = new TreeNamespace::tree<int, 3>::node(29);
    auto* child2_3_2 = new TreeNamespace::tree<int, 3>::node(30);
    auto* child2_3_3 = new TreeNamespace::tree<int, 3>::node(31);

    auto* child3_1_1 = new TreeNamespace::tree<int, 3>::node(32);
    auto* child3_1_2 = new TreeNamespace::tree<int, 3>::node(33);
    auto* child3_1_3 = new TreeNamespace::tree<int, 3>::node(34);

    auto* child3_2_1 = new TreeNamespace::tree<int, 3>::node(35);
    auto* child3_2_2 = new TreeNamespace::tree<int, 3>::node(36);
    auto* child3_2_3 = new TreeNamespace::tree<int, 3>::node(37);

    auto* child3_3_1 = new TreeNamespace::tree<int, 3>::node(38);
    auto* child3_3_2 = new TreeNamespace::tree<int, 3>::node(39);
    auto* child3_3_3 = new TreeNamespace::tree<int, 3>::node(40);

    // Ajout des enfants au niveau 3
    child1_1->childrens[0] = child1_1_1;
    child1_1->childrens[1] = child1_1_2;
    child1_1->childrens[2] = child1_1_3;

    child1_2->childrens[0] = child1_2_1;
    child1_2->childrens[1] = child1_2_2;
    child1_2->childrens[2] = child1_2_3;

    child1_3->childrens[0] = child1_3_1;
    child1_3->childrens[1] = child1_3_2;
    child1_3->childrens[2] = child1_3_3;

    child2_1->childrens[0] = child2_1_1;
    child2_1->childrens[1] = child2_1_2;
    child2_1->childrens[2] = child2_1_3;

    child2_2->childrens[0] = child2_2_1;
    child2_2->childrens[1] = child2_2_2;
    child2_2->childrens[2] = child2_2_3;

    child2_3->childrens[0] = child2_3_1;
    child2_3->childrens[1] = child2_3_2;
    child2_3->childrens[2] = child2_3_3;

    child3_1->childrens[0] = child3_1_1;
    child3_1->childrens[1] = child3_1_2;
    child3_1->childrens[2] = child3_1_3;

    child3_2->childrens[0] = child3_2_1;
    child3_2->childrens[1] = child3_2_2;
    child3_2->childrens[2] = child3_2_3;

    child3_3->childrens[0] = child3_3_1;
    child3_3->childrens[1] = child3_3_2;
    child3_3->childrens[2] = child3_3_3;

    // Appel de la fonction draw pour visualiser l'arbre
    TreeNamespace::draw<int, 3>(root);

    return 0;
}