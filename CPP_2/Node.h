#ifndef NODE_HPP
#define NODE_HPP

#include <vector> // Pour l'utilisation de std::vector pour les enfants

// Déclaration de la classe template
template <typename T>
class Node {
public:
    /// DATA ///
    T data;
    Node* parent;
    std::vector<Node*> children; // Liste des enfants sous forme de pointeurs

    /// CONSTRUCTEUR ///
    Node() : parent(nullptr) {} // Constructeur par défaut

    /// MÉTHODES ///
    void addChild(Node* child) {
        children.push_back(child);
        child->parent = this;
    }

    Node* getChild(int index) const {
        if (index >= 0 && index < children.size()) {
            return children[index];
        }
        return nullptr; // Retourne nullptr si l'index est invalide
    }

    void setData(const T& data) {
        this->data = data;
    }

    const T& getData() const {
        return data;
    }

    T& getData() {
        return data;
    }

    void clean() {
        // Libère les ressources si nécessaire
        for (Node* child : children) {
            delete child;
        }
        children.clear();
    }

    // Destructeur
    ~Node() {
        clean();
    }
};

#endif // NODE_HPP
