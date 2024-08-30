#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
class Node
{
private:
    /// DATA ///
    T data;
    Node* parent;
    std::vector<Node> children;
public:
    /// CONSTRUCTEURS ///
    Node() : data(T()), parent(nullptr), children() {}
    Node(T data, Node* parent) : data(data), parent(parent), children() {}
    /// GETTER ///
    T get_Data() const {return this->data;}
    Node* get_Parent() const {return this->parent;}
    const std::vector<Node>& get_list_of_children() const {return this->children;}
    Node* get_Child(T data) {
        for (Node& child : children) {
            if (child.get_Data() == data) {
                return &child;  // Retourne un pointeur vers l'enfant trouvé
            }
        }
        return nullptr;  // Aucun enfant avec la donnée spécifiée n'a été trouvé
    }
    /// SETTER ///
    void set_Data(T newData) {this->data = newData;}
    void set_Parent(Node* newParent) {
        if (parent != nullptr) {
            // Supprimer ce nœud de l'ancien parent
            auto& siblings = parent->children;
            siblings.erase(std::remove(siblings.begin(), siblings.end(), *this), siblings.end());
        }
        parent = newParent;
        if (newParent != nullptr) {
            // Ajouter ce nœud au nouveau parent
            newParent->add_Child(*this);
        }
    }
    /// METHODS ///
    void add_Child(const Node& newNode) {
        this->children.push_back(newNode);
        this->children.back().parent = this;
    }
    void add_Child(T data) {
        Node child(data, this);
        children.push_back(child);
    }
    ~Node() {clean();}
    void clean() {
        children.clear();
    }
};
#endif NODE_HPP
