/*
 * natane.djedou@gmail.com
 */

#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>
#include <ostream>

namespace ariel
{
    class Graph
    {
    private:
        // Adjacency matrix to represent the graph
        std::vector<std::vector<int>> adjMatrix;

        // Number of nodes in the graph
        int num_of_node;

        // Number of edges in the graph
        int num_of_edges;

        // Boolean to indicate if the graph is oriented
        bool isOriented;

    public:
        //// Constructor ////
        Graph();
        Graph(size_t n);

        //// Getters ////
        int getNumOfNodes() const; // Returns the number of nodes
        int getNumOfEdges() const; // Returns the number of edges
        bool getIsOriented() const; // Returns true if the graph is oriented
        std::vector<std::vector<int>> getAdjMatrix() const; // Returns the adjacency matrix
        int getEdgeWeight(int u, int v) const; // Returns the weight of the edge between nodes u and v

        //// Setters ////
        void setNumOfNodes(int nodes); // Sets the number of nodes
        void setNumOfEdges(int edges); // Sets the number of edges
        void setIsOriented(bool oriented); // Sets whether the graph is oriented
        void setAdjMatrix(const std::vector<std::vector<int>>& matrix); // Sets the adjacency matrix
        void setEdgeWeight(int u, int v, int weight);

        //// Methods ////
        void loadGraph(std::vector<std::vector<int>> random_matrix); // Loads the graph from an adjacency matrix
        void printGraph(); // Prints the adjacency matrix of the graph

        //// Operator Overloads ////

        // Arithmetic operators
        Graph operator+(const Graph &other) const; // Adds two graphs
        Graph& operator+=(const Graph &other); // Adds another graph to this one
        Graph operator-() const; // Unary minus operator (negates the graph)
        Graph operator-(const Graph &other) const; // Subtracts one graph from another
        Graph& operator-=(const Graph &other); // Subtracts another graph from this one
        Graph operator+() const; // Unary plus operator (does not change the graph)

        // Comparison operators
        bool operator==(const Graph &other) const; // Checks if two graphs are equal
        bool operator!=(const Graph& other) const; // Checks if two graphs are not equal
        bool operator<(const Graph& other) const; // Checks if this graph is less than another graph
        bool operator<=(const Graph& other) const; // Checks if this graph is less than or equal to another graph
        bool operator>(const Graph& other) const; // Checks if this graph is greater than another graph
        bool operator>=(const Graph& other) const; // Checks if this graph is greater than or equal to another graph

        // Increment and decrement operators
        Graph& operator++(); // Prefix increment operator
        Graph operator++(int); // Postfix increment operator
        Graph& operator--(); // Prefix decrement operator
        Graph operator--(int); // Postfix decrement operator

        // Multiplication and division operators
        Graph operator*(int number) const; // Multiplies the graph by a scalar
        Graph operator*(const Graph& other) const; // Multiplies two graphs element-wise
        Graph& operator*=(int number); // Multiplies the graph by a scalar and assigns the result
        Graph& operator/=(int number); // Divides the graph by a scalar and assigns the result
        Graph operator/(int scalar) const ;
        //// Friend Functions ////
        // Overload the << operator to output the graph
        friend std::ostream& operator<<(std::ostream& os, const Graph& graph);
    };
}

#endif
