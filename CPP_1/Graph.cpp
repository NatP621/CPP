/*
 * natane.djedou@gmail.com
 */

#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <sstream>
#include <limits>

namespace ariel {

    //// Constructor ////
    Graph::Graph()
        : num_of_node(0), num_of_edges(0), isOriented(false) {
        // Initializes a graph with no nodes and no edges and assumes it is not oriented.
    }
    Graph::Graph(size_t n) : num_of_node(n), adjMatrix(n, std::vector<int>(n, 0)), isOriented(false) {}

    //// Getters ////
    int Graph::getNumOfNodes() const {
        return this->num_of_node;
    }
    int Graph::getNumOfEdges() const {
        return this->num_of_edges;
    }
    bool Graph::getIsOriented() const {
        return this->isOriented;
    }
    std::vector<std::vector<int>> Graph::getAdjMatrix() const {
        return this->adjMatrix;
    }
    int Graph::getEdgeWeight(int u, int v) const {
        // Check if the indices are within bounds
        if (u < 0 || u >= num_of_node || v < 0 || v >= num_of_node) {
            throw std::out_of_range("Indices out of bounds");
        }
        return adjMatrix[static_cast<size_t>(u)][static_cast<size_t>(v)]; // Convert 'u' and 'v' to size_t
    }

    //// Setters ////
    void Graph::setNumOfNodes(int nodes) {
        this->num_of_node = nodes;
    }
    void Graph::setNumOfEdges(int edges) {
        this->num_of_edges = edges;
    }
    void Graph::setIsOriented(bool oriented) {
        this->isOriented = oriented;
    }
    void Graph::setAdjMatrix(const std::vector<std::vector<int>>& matrix) {
        if (matrix.size() != static_cast<size_t>(this->num_of_node)) {
            std::cerr << "Adjacency matrix size does not match the number of nodes." << std::endl;
            return;
        }
        this->adjMatrix = matrix;
    }
    void Graph::setEdgeWeight(int u, int v, int weight) {
        // Check if the indices are within bounds
        if (u < 0 || u >= num_of_node || v < 0 || v >= num_of_node) {
            throw std::out_of_range("Indices out of bounds");
        }
        adjMatrix[static_cast<size_t>(u)][static_cast<size_t>(v)] = weight; // Convert 'u' and 'v' to size_t

        // If the graph is not oriented, update the symmetric value
        if (!isOriented) {
            adjMatrix[static_cast<size_t>(v)][static_cast<size_t>(u)] = weight; // Convert 'v' and 'u' to size_t
        }
    }

    //// Methods ////
    void Graph::loadGraph(std::vector<std::vector<int>> random_matrix) {
        size_t numRows = random_matrix.size(); // Use size_t instead of int

        // Handle the case of an empty matrix
        if (numRows == 0) {
            std::cerr << "Error: The matrix is empty." << std::endl;
            setAdjMatrix({});
            setNumOfNodes(0);
            setNumOfEdges(0);
            setIsOriented(false);
            return;
        }

        // Handle the case of a graph with a single node
        if (numRows == 1) {
            int edges = (random_matrix[0][0] != 0) ? 1 : 0;
            setAdjMatrix(random_matrix);
            setNumOfNodes(1);
            setNumOfEdges(edges);
            setIsOriented(false);
            return;
        }

        // Check if the matrix is square
        for (size_t i = 0; i < numRows; ++i) {
            if (random_matrix[i].size() != numRows) {
                std::cerr << "Invalid graph: The graph is not a square matrix." << std::endl;
                return;
            }
        }

        // Determine if the graph is oriented and count the edges
        bool isOriented = false;
        int edges = 0;
        for (size_t i = 0; i < numRows; ++i) {
            for (size_t j = 0; j < numRows; ++j) {
                if (random_matrix[i][j] != 0) {
                    if (i == j) {
                        edges++;
                    } else {
                        if (random_matrix[i][j] != random_matrix[j][i]) {
                            isOriented = true;
                        }
                        if (isOriented) {
                            edges++;
                        } else if (i < j) {
                            edges++;
                        }
                    }
                }
            }
        }

        // Update the graph's attributes
        setIsOriented(isOriented);
        setNumOfEdges(edges);
        setNumOfNodes(numRows);
        setAdjMatrix(random_matrix);
    }
    void Graph::printGraph() {
        std::cout << "Graph with " << this->num_of_node << " vertices and " << this->num_of_edges * 2 << " edges." << std::endl;
    }

    //// Operator Overloads ////

    // Addition operators
    Graph Graph::operator+(const Graph &other) const {
        // Check if both graphs have the same number of nodes
        if (this->getNumOfNodes() != other.getNumOfNodes()) {
            throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
        }
        // Get the number of nodes
        size_t numNodes = static_cast<size_t>(this->getNumOfNodes());
        // Retrieve adjacency matrices
        auto this_matrix = this->getAdjMatrix();  // Using auto to copy the matrix
        auto other_matrix = other.getAdjMatrix(); // Using auto to copy the matrix
        // Initialize the result matrix with the same size as the adjacency matrices
        std::vector<std::vector<int>> result_matrix(numNodes, std::vector<int>(numNodes, 0));
        // Add the matrices element-wise
        for (size_t i = 0; i < numNodes; ++i) {
            for (size_t j = 0; j < numNodes; ++j) {
                result_matrix[i][j] = this_matrix[i][j] + other_matrix[i][j];
            }
        }
        // Create the resulting graph and load the result matrix
        Graph result_graph;
        result_graph.loadGraph(result_matrix);
        return result_graph;
    }
    Graph& Graph::operator+=(const Graph &other) {
        // Check if both graphs have the same number of nodes
        if (this->getNumOfNodes() != other.getNumOfNodes()) {
            throw std::invalid_argument("Graphs must have the same number of vertices to be added.");
        }
        // Get the number of nodes
        size_t numNodes = static_cast<size_t>(this->getNumOfNodes());
        // Retrieve the adjacency matrix of the other graph
        const auto& other_matrix = other.getAdjMatrix();
        // Add the matrices element-wise
        for (size_t i = 0; i < numNodes; ++i) {
            for (size_t j = 0; j < numNodes; ++j) {
                this->adjMatrix[i][j] += other_matrix[i][j];
            }
        }
        // Return the current graph object with updated values
        return *this;
    }

    // Subtraction operators
    Graph Graph::operator-(const Graph &other) const {
        if (this->getNumOfNodes() != other.getNumOfNodes()) {
            throw std::invalid_argument("Graphs must have the same number of vertices to be subtracted.");
        }

        const auto& this_matrix = this->getAdjMatrix();
        const auto& other_matrix = other.getAdjMatrix();
        size_t numNodes = static_cast<size_t>(this->getNumOfNodes());
        std::vector<std::vector<int>> result_matrix(numNodes, std::vector<int>(numNodes, 0));

        for (size_t i = 0; i < numNodes; ++i) {
            for (size_t j = 0; j < numNodes; ++j) {
                result_matrix[i][j] = this_matrix[i][j] - other_matrix[i][j];
            }
        }

        Graph result_graph;
        result_graph.loadGraph(result_matrix);
        return result_graph;
    }
    Graph& Graph::operator-=(const Graph &other) {
        if (this->getNumOfNodes() != other.getNumOfNodes()) {
            throw std::invalid_argument("Graphs must have the same number of vertices to be subtracted.");
        }

        const auto& other_matrix = other.getAdjMatrix();
        auto& this_matrix = this->adjMatrix;
        size_t numNodes = static_cast<size_t>(this->getNumOfNodes());

        for (size_t i = 0; i < numNodes; ++i) {
            for (size_t j = 0; j < numNodes; ++j) {
                this_matrix[i][j] -= other_matrix[i][j];
            }
        }

        this->loadGraph(this_matrix);
        return *this;
    }

    // Unary operators
    Graph Graph::operator+() const {
        return *this;
    }
    Graph Graph::operator-() const {
        const auto& this_matrix = this->getAdjMatrix();
        size_t numNodes = static_cast<size_t>(this->getNumOfNodes());
        std::vector<std::vector<int>> negated_matrix(numNodes, std::vector<int>(numNodes, 0));

        for (size_t i = 0; i < numNodes; ++i) {
            for (size_t j = 0; j < numNodes; ++j) {
                negated_matrix[i][j] = -this_matrix[i][j];
            }
        }

        Graph negated_graph;
        negated_graph.loadGraph(negated_matrix);
        return negated_graph;
    }

    // Comparison operators
    bool Graph::operator==(const Graph &other) const {
        return this->getNumOfNodes() == other.getNumOfNodes() &&
               this->getNumOfEdges() == other.getNumOfEdges() &&
               this->getAdjMatrix() == other.getAdjMatrix();
    }
    bool Graph::operator!=(const Graph& other) const {
        return !(*this == other);
    }
    bool Graph::operator<(const Graph& other) const {
        int this_total_weight = 0, other_total_weight = 0;

        // Calculate the total sum of edge weights for both graphs
        for (size_t u = 0; u < static_cast<size_t>(this->num_of_node); ++u) {
            for (size_t v = 0; v < static_cast<size_t>(this->num_of_node); ++v) {
                this_total_weight += this->getEdgeWeight(static_cast<int>(u), static_cast<int>(v));
            }
        }

        for (size_t u = 0; u < static_cast<size_t>(other.num_of_node); ++u) {
            for (size_t v = 0; v < static_cast<size_t>(other.num_of_node); ++v) {
                other_total_weight += other.getEdgeWeight(static_cast<int>(u), static_cast<int>(v));
            }
        }

        if (this_total_weight < other_total_weight) {
            return true;
        } else if (this_total_weight > other_total_weight) {
            return false;
        }

        // If total weights are equal, compare the number of nodes
        return this->num_of_node < other.num_of_node;
    }
    bool Graph::operator>(const Graph& other) const {
        int this_total_weight = 0, other_total_weight = 0;

        // Calculate the total sum of edge weights for both graphs
        for (size_t u = 0; u < static_cast<size_t>(this->num_of_node); ++u) {
            for (size_t v = 0; v < static_cast<size_t>(this->num_of_node); ++v) {
                this_total_weight += this->getEdgeWeight(static_cast<int>(u), static_cast<int>(v));
            }
        }

        for (size_t u = 0; u < static_cast<size_t>(other.num_of_node); ++u) {
            for (size_t v = 0; v < static_cast<size_t>(other.num_of_node); ++v) {
                other_total_weight += other.getEdgeWeight(static_cast<int>(u), static_cast<int>(v));
            }
        }

        if (this_total_weight > other_total_weight) {
            return true;
        } else if (this_total_weight < other_total_weight) {
            return false;
        }

        // If total weights are equal, compare the number of nodes
        return this->num_of_node > other.num_of_node;
    }
    bool Graph::operator<=(const Graph& other) const {
        return !(*this > other);
    }
    bool Graph::operator>=(const Graph& other) const {
        return !(*this < other);
    }

    // Increment and decrement operators
    Graph& Graph::operator++() {
        for (auto& row : this->adjMatrix) {
            for (auto& weight : row) {
                ++weight;
            }
        }
        this->loadGraph(this->adjMatrix);
        return *this;
    }
    Graph Graph::operator++(int) {
        Graph temp = *this;
        ++(*this);
        return temp;
    }
    Graph& Graph::operator--() {
        for (auto& row : this->adjMatrix) {
            for (auto& weight : row) {
                --weight;
            }
        }
        this->loadGraph(this->adjMatrix);
        return *this;
    }
    Graph Graph::operator--(int) {
        Graph temp = *this;
        --(*this);
        return temp;
    }

    // Multiplication operators
    Graph Graph::operator*(int number) const {
        Graph result = *this;
        for (auto& row : result.adjMatrix) {
            for (auto& weight : row) {
                weight *= number;
            }
        }
        result.loadGraph(result.adjMatrix);
        return result;
    }

    // Graph multiplication
    Graph Graph::operator*(const Graph& other) const {
        // Retrieve adjacency matrices
        const auto& adjMatrix1 = this->getAdjMatrix();
        const auto& adjMatrix2 = other.getAdjMatrix();
        // Check if matrices can be multiplied
        if (adjMatrix1.empty() || adjMatrix2.empty() || adjMatrix1[0].size() != adjMatrix2.size()) {
            throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }
        // Initialize the result matrix with zeros
        std::vector<std::vector<int>> result(adjMatrix1.size(), std::vector<int>(adjMatrix2[0].size(), 0));
        // Perform matrix multiplication
        for (size_t i = 0; i < adjMatrix1.size(); ++i) {
            for (size_t j = 0; j < adjMatrix2[0].size(); ++j) {
                for (size_t k = 0; k < adjMatrix2.size(); ++k) {
                    result[i][j] += this->getEdgeWeight(static_cast<int>(i), static_cast<int>(k)) * other.getEdgeWeight(static_cast<int>(k), static_cast<int>(j));
                }
            }
        }
        // Create the resulting graph from the result matrix
        Graph result_graph;
        result_graph.loadGraph(result);
        return result_graph;
    }

    Graph& Graph::operator*=(int number) {
        for (auto& row : this->adjMatrix) {
            for (auto& weight : row) {
                weight *= number;
            }
        }
        this->loadGraph(this->adjMatrix);
        return *this;
    }

    Graph& Graph::operator/=(int number) {
        if (number == 0) {
            throw std::invalid_argument("Cannot divide by zero.");
        }
        // Divide each weight by the given number
        for (auto& row : this->adjMatrix) {
            for (auto& weight : row) {
                weight = static_cast<double>(weight) / number; // Convert to double for division
            }
        }
        // Load the matrix into the graph if necessary
        this->loadGraph(this->adjMatrix);
        return *this;
    }

    //// Friend Functions ////
    std::ostream& operator<<(std::ostream& os, const Graph& graph) {
        if (graph.adjMatrix.empty()) {
            return os << "[]";
        }

        for (size_t i = 0; i < graph.adjMatrix.size(); ++i) {
            os << "[";
            for (size_t j = 0; j < graph.adjMatrix[i].size(); ++j) {
                os << graph.adjMatrix[i][j];
                if (j < graph.adjMatrix[i].size() - 1) {
                    os << ", ";
                }
            }
            os << "]";
            if (i < graph.adjMatrix.size() - 1) {
                os << ", ";
            }
        }
        return os;
    }
} // namespace ariel
