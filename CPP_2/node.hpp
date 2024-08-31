#ifndef NODE_HPP
#define NODE_HPP
#include <vector>
#include <iostream>
#include <algorithm>

template <typename T>
class node
{
private:

    /// DATA ///
    T data;
    node* parent;
    std::vector<node> children;

public:

    /// CONSTRUCTEURS ///
    node() : data(T()), parent(nullptr), children() {}
    node(T data, node* parent) : data(data), parent(parent), children() {}

    /// GETTER ///
    T get_Data() const {return this->data;}
    node* get_Parent() const {return this->parent;}
    const std::vector<node>& get_list_of_children() const {return this->children;}
    node* get_Child(T data) {
        for (node& child : children) {
            if (child.get_Data() == data) {
                return &child;  // Retourne un pointeur vers l'enfant trouvé
            }
        }
        return nullptr;  // Aucun enfant avec la donnée spécifiée n'a été trouvé
    }
    /// SETTER ///
    void set_Data(T newData) {this->data = newData;}
    void set_Parent(node* newParent) {
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
    void add_Child(const node& newNode) {
        this->children.push_back(newNode);
        this->children.back().parent = this;
    }
    void add_Child(T data) {
        node child(data, this);
        children.push_back(child);
    }
    ~node() {clean();}
    void clean() {
        children.clear();
    }
};
#endif NODE_HPP
