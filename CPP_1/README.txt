Graph Assignment - README
Overview
This project involves creating a Graph class in C++ that represents a graph using an adjacency matrix. The graph can be directed, undirected, weighted, or unweighted. Additionally, several algorithms were implemented to perform operations on the graph, and various operators were overloaded to manipulate the graph and its representations.

Files and Their Purpose
1. Graph.cpp
This file contains the implementation of the Graph class. The main features and methods implemented in this file include:

Graph Construction and Loading:

loadGraph(const std::vector<std::vector<int>>& adjacencyMatrix): This method loads a graph from an adjacency matrix provided as input. It initializes the internal representation of the graph based on the provided matrix, allowing for directed, undirected, and weighted graphs.
Graph Display:

printGraph() const: This method outputs the graph's adjacency matrix to the console. It provides a clear visual representation of the graph, which is useful for debugging and understanding the graph's structure.
Operator Overloading:

Arithmetic operators (+, +=, -, -=): These operators are used to add or subtract graphs. The operations are defined for matrices of the same size.
Comparison operators (==, !=, <, <=, >, >=): These operators compare graphs based on their structure and edge weights, following specific rules for equality and size comparison.
Increment and Decrement operators (++, --): These operators increase or decrease all edge weights in the graph by 1.
Scalar multiplication (*): Multiplies the weights of all edges by an integer.
Graph multiplication (*): Defined as the multiplication of the adjacency matrices of two graphs. Only graphs of the same size can be multiplied.
Output operator (<<): Overloaded to print the graph in a formatted manner, making the graph's structure easy to understand.
2. Algorithms.cpp
This file includes several algorithms for graph analysis and manipulation. The algorithms implemented are:

isConnected(Graph& g): Checks if the graph is connected. If all vertices are reachable from any vertex, it returns true; otherwise, it returns false.

shortestPath(Graph& g, int start, int end): Computes the shortest path between two vertices in the graph. If the graph is weighted, it finds the path with the least total weight; if unweighted, it finds the shortest path in terms of the number of edges. If no path exists, it returns -1.

isContainsCycle(Graph& g): Detects if there is a cycle in the graph. If a cycle exists, it returns true; otherwise, it returns false.

isBipartite(Graph& g): Checks if the graph is bipartite, meaning it can be colored with two colors without two adjacent vertices sharing the same color. Returns true if the graph is bipartite, false otherwise.

negativeCycle(Graph& g): Detects if there is a negative cycle in the graph. A negative cycle is a cycle where the sum of the edge weights is negative. If such a cycle exists, it returns true; otherwise, it returns false.

3. Demo.cpp
This file contains example usages of the Graph class and its associated algorithms and operators. It demonstrates:

Loading graphs from different adjacency matrices.
Performing operations like addition, subtraction, and multiplication of graphs.
Using comparison operators to compare different graphs.
Displaying the graphs using the overloaded output operator.
4. Test Files
Comprehensive test cases were written to validate the functionality of the graph class, algorithms, and operators. These tests cover:

Edge cases for empty graphs, graphs with no edges, and fully connected graphs.
Validation of operator overloads for various matrix sizes and types.
Correctness of algorithm outputs for directed, undirected, weighted, and unweighted graphs.

//______Makefile_Commands______//
make              # Build the project
make run          # Run the demo executable
make test         # Build the test executable
./test            # Run the test executable
make tidy         # Run clang-tidy
make valgrind     # Run Valgrind
make debug        # Build in debug mode
make clean        # Clean up the project


Conclusion
This project showcases the implementation of a robust graph data structure in C++ using an adjacency matrix,
complete with various algorithms and operator overloads to manipulate and analyze graphs. The provided tests ensure the reliability and correctness of all functionalities,
making it a comprehensive solution for graph-based operations.