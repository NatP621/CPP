/*
 * natane.djedou@gmail.com
 */

#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"
#include <string>
#include <vector>

namespace ariel {
    class Algorithms {
    public:
        /**
         * Function: isConnected
         * Description: This function checks if a graph is connected, meaning there is a path between
         * all pairs of nodes in the graph. It uses a Breadth-First Search (BFS) to explore the graph
         * starting from the first node (indexed at 0). If all nodes are reached during the traversal, the graph is connected.
         *
         * @param g: A Graph object representing the graph to check.
         * @return: An integer that is 1 if the graph is connected, otherwise 0.
         */
        static int isConnected(const Graph& g);
        /**
         * Function: shortestPath
         * Description: This function determines the shortest path between two nodes in a graph using
         * Breadth-First Search (BFS). If a path exists between the start node and the end node, the function returns
         * a string representing the path in the form "start -> ... -> end". If no path exists or if the nodes are invalid,
         * the function returns an appropriate message.
         *
         * @param g: A Graph object representing the graph in which to search for the path.
         * @param start: An integer representing the starting node.
         * @param end: An integer representing the ending node.
         * @return: A string representing the shortest path, or an error message if the path does not exist.
         */
        static std::string shortestPath(const Graph& g, int start, int end);
        /**
         * Function: isContainsCycle
         * Description: This function checks if the graph contains a cycle using Depth-First Search (DFS).
         * If a cycle is detected, the function returns 1, otherwise it returns 0.
         *
         * @param g: A Graph object representing the graph to check.
         * @return: An integer that is 1 if the graph contains a cycle, otherwise 0.
         */
        static int isContainsCycle(Graph g);
        /**
         * Function: dfs
         * Description: This function performs a Depth-First Search (DFS) to detect cycles in the graph.
         * It is called recursively to explore the neighbors of a given node.
         *
         * @param v: The node currently being explored.
         * @param visited: A vector indicating whether each node has been visited or not.
         * @param parent: A vector to track the parent of each node during the traversal.
         * @param g: A Graph object representing the graph to explore.
         * @param cycle: A vector to track the path and identify cycles (currently unused parameter).
         * @return: A boolean that is true if a cycle is detected, otherwise false.
         */
        static bool dfs(int v, std::vector<bool>& visited, std::vector<int>& parent, Graph& g, std::vector<int>& cycle);
        /**
         * Function: isBipartite
         * Description: This function checks if a graph is bipartite using Breadth-First Search (BFS).
         * A graph is bipartite if it is possible to color it with two colors such that two adjacent nodes never have the same color.
         * The function returns "true" if the graph is bipartite, otherwise "false".
         *
         * @param g: A Graph object representing the graph to check.
         * @return: A string "true" if the graph is bipartite, otherwise "false".
         */
        static std::string isBipartite(const Graph& g);
         /**
         * Function: negativeCycle
         * Description: This function checks if a graph contains a negative weight cycle using the Bellman-Ford algorithm.
         * The Bellman-Ford algorithm is used to find the shortest path from a source vertex to all other vertices
         * in a weighted graph. In addition to finding the shortest path, this algorithm can detect the existence of negative weight cycles.
         * A negative weight cycle is a cycle in which the sum of the edge weights is negative, meaning that the path
         * can be indefinitely reduced by traversing the cycle.
         *
         * @param g: A Graph object representing the weighted graph to check.
         * @return: An integer that is 1 if the graph contains a negative weight cycle, otherwise 0.
         */
         static int negativeCycle(const Graph &g);
    };
} // namespace ariel

#endif // ALGORITHMS_HPP
