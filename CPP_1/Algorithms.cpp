/*
 * natane.djedou@gmail.com
 */
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <climits>

namespace ariel
{
    /**
     * Function: isConnected
     * Description: This function checks if a graph is connected, meaning there is a path between
     * all pairs of nodes in the graph. The method uses a Breadth-First Search (BFS) to explore the graph
     * starting from the first node (indexed at 0). If all nodes are reached during the traversal, the graph is connected.
     *
     * @param g: A Graph object representing the graph to check.
     * @return: An integer that is 1 if the graph is connected, otherwise 0.
     */
    int Algorithms::isConnected(const Graph& g) {
        int numNodes = g.getNumOfNodes();
        if (numNodes == 0) {
            // An empty graph is considered not connected
            return 0;
        }
        if (numNodes == 1) {
            // Check if there is a loop (an edge from the node to itself)
            if (g.getAdjMatrix()[0][0] != 0) {
                // If the single node has a loop, it is connected
                return 1;
            }                 // Otherwise, it is not connected
                return 0;
           
        }

        std::vector<bool> visited(numNodes, false);
        std::queue<int> q;

        // Start BFS traversal from the first node
        q.push(0);
        visited[0] = true;

        int visitedCount = 1;  // Start with the first node

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int i = 0; i < numNodes; ++i) {
                if (g.getAdjMatrix()[node][i] > 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                    visitedCount++;
                }
            }
        }

        // If all nodes have been visited, the graph is connected
        return (visitedCount == numNodes) ? 1 : 0;
    }
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
    std::string Algorithms::shortestPath(const Graph& g, int start, int end) {
        int numNodes = g.getNumOfNodes();
        if (start < 0 || start >= numNodes || end < 0 || end >= numNodes) {
            return "Invalid start or end node.";
        }

        std::vector<int> distance(numNodes, -1);
        std::vector<int> predecessor(numNodes, -1);
        std::queue<int> q;

        distance[start] = 0;
        q.push(start);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int i = 0; i < numNodes; ++i) {
                if (g.getAdjMatrix()[node][i] > 0 && distance[i] == -1) {
                    distance[i] = distance[node] + 1;
                    predecessor[i] = node;
                    q.push(i);

                    if (i == end) {
                        break;
                    }
                }
            }
        }

        if (distance[end] == -1) {
            return "-1";
        }

        std::string path;
        for (int crawl = end; crawl != -1; crawl = predecessor[crawl]) {
            path = std::to_string(crawl) + (path.empty() ? "" : "->" + path);
        }

        return path;
    }
    /**
 * Function: isContainsCycle
 * Description: This function checks if the graph contains a cycle using Depth-First Search (DFS).
 * If a cycle is detected, the function returns 1 and prints the cycle, otherwise it returns 0.
 *
 * @param g: A Graph object representing the graph to check.
 * @return: An integer that is 1 if the graph contains a cycle, otherwise 0.
 */
    int Algorithms::isContainsCycle(Graph g) {
        int numNodes = g.getNumOfNodes();
        std::vector<bool> visited(numNodes, false);
        std::vector<int> parent(numNodes, -1);
        std::vector<int> cycle;  // Used to store the detected cycle

        // Traverse each unvisited node to detect cycles
        for (int i = 0; i < numNodes; ++i) {
            if (!visited[i]) {
                if (dfs(i, visited, parent, g, cycle)) {
                    // Print the cycle
                    std::cout << "The cycle is: ";
                    for (size_t j = 0; j < cycle.size(); ++j) {
                        std::cout << cycle[j];
                        if (j != cycle.size() - 1) {
                            std::cout << "->";
                        }
                    }
                    std::cout << '\n';
                    return 1;
                }
            }
        }

        return 0;
    }
    /**
     * Function: dfs
     * Description: This function performs a Depth-First Search (DFS) to detect cycles in the graph.
     * It is called recursively to explore the neighbors of a given node.
     *
     * @param v: The node currently being explored.
     * @param visited: A vector indicating whether each node has been visited or not.
     * @param parent: A vector to track the parent of each node during the traversal.
     * @param g: A Graph object representing the graph to explore.
     * @param cycle: A vector to track the path and identify cycles.
     * @return: A boolean that is true if a cycle is detected, otherwise false.
     */
    bool Algorithms::dfs(int v, std::vector<bool>& visited, std::vector<int>& parent, Graph& g, std::vector<int>& cycle) {
        visited[v] = true;

        // Explore all neighbors of the current node
        for (int i = 0; i < g.getNumOfNodes(); ++i) {
            if (g.getAdjMatrix()[v][i] > 0) {
                if (!visited[i]) {
                    parent[i] = v;
                    if (dfs(i, visited, parent, g, cycle)) {
                        return true;  // Cycle found in the recursion
                    }
                } else if (parent[v] != i) {
                    // Cycle detected, backtrack to find the cycle path
                    cycle.clear();
                    int current = v;
                    while (current != i) {
                        cycle.push_back(current);
                        current = parent[current];
                    }
                    cycle.push_back(i);
                    cycle.push_back(v);  // To show the complete path of the cycle
                    std::reverse(cycle.begin(), cycle.end()); // Optional: To display the cycle in the correct order
                    return true;
                }
            }
        }

        return false;
    }
    /**
     * Function: isBipartite
     * Description: This function checks if a graph is bipartite using Breadth-First Search (BFS).
     * If the graph is bipartite, it returns a string indicating the sets A and B of nodes.
     * Otherwise, it returns "false".
     *
     * @param g: A Graph object representing the graph to check.
     * @return: A string describing the bipartition if the graph is bipartite, otherwise "false".
     */
    std::string Algorithms::isBipartite(const Graph& g) {
        int numNodes = g.getNumOfNodes();
        std::vector<int> color(numNodes, -1);
        std::vector<int> setA;
        std::vector<int> setB;

        // Traverse each connected component of the graph
        for (int i = 0; i < numNodes; ++i) {
            if (color[i] == -1) {  // If the node is not yet colored
                color[i] = 0;  // Start coloring with the first color (0 for A, 1 for B)
                setA.push_back(i);
                std::queue<int> q;
                q.push(i);

                // BFS traversal to check bipartition
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();

                    // Iterate over all neighbors of the current node
                    for (int j = 0; j < numNodes; ++j) {
                        if (g.getAdjMatrix()[node][j] > 0) {  // If there is an edge between node and j
                            if (color[j] == -1) {  // If the neighbor node is not yet colored
                                color[j] = 1 - color[node];  // Color with the opposite color
                                if (color[j] == 0) {
                                    setA.push_back(j);
                                } else {
                                    setB.push_back(j);
                                }
                                q.push(j);
                            } else if (color[j] == color[node]) {
                                return "0";  // If a neighbor has the same color, the graph is not bipartite
                            }
                        }
                    }
                }
            }
        }

        // Constructing the result string
        std::string result = "The graph is bipartite: A={";
        for (size_t i = 0; i < setA.size(); ++i) {
            result += std::to_string(setA[i]);
            if (i < setA.size() - 1) { result += ", ";
}
        }
        result += "}, B={";
        for (size_t i = 0; i < setB.size(); ++i) {
            result += std::to_string(setB[i]);
            if (i < setB.size() - 1) { result += ", ";
}
        }
        result += "}.";

        return result;
    }
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
    int Algorithms::negativeCycle(const Graph &graph) {
        // Copy the adjacency matrix from the graph
        std::vector<std::vector<int>> originalMatrix = graph.getAdjMatrix();
        size_t vertexCount = originalMatrix.size();

        // Create a new adjacency matrix with an additional source vertex
        std::vector<std::vector<int>> extendedMatrix(vertexCount + 1, std::vector<int>(vertexCount + 1, INT_MAX));

        // Initialize the extended matrix with the source vertex and existing edges
        size_t i = 1;
        while (i <= vertexCount) {
            extendedMatrix[0][i] = 0;  // Source vertex connected to every other vertex with weight 0
            size_t j = 1;
            while (j <= vertexCount) {
                if (originalMatrix[i - 1][j - 1] != 0) {
                    extendedMatrix[i][j] = originalMatrix[i - 1][j - 1];
                } else {
                    extendedMatrix[i][j] = INT_MAX; // Ensure unconnected paths are set to INT_MAX
                }
                j++;
            }
            i++;
        }

        // Initialize distance and parent vectors
        std::vector<int> distances(vertexCount + 1, INT_MAX);
        std::vector<int> predecessors(vertexCount + 1, -1);
        distances[0] = 0; // Distance to the source vertex is 0

        // Perform the Bellman-Ford algorithm
        size_t iter = 0;
        while (iter < vertexCount) { // Run vertexCount times
            size_t u = 0;
            while (u <= vertexCount) {
                size_t v = 0;
                while (v <= vertexCount) {
                    if (extendedMatrix[u][v] != INT_MAX && distances[u] != INT_MAX &&
                        distances[u] + extendedMatrix[u][v] < distances[v]) {
                        distances[v] = distances[u] + extendedMatrix[u][v];
                        predecessors[v] = u;
                    }
                    v++;
                }
                u++;
            }
            iter++;
        }

        // Check for negative-weight cycles
        size_t x = 0;
        while (x <= vertexCount) {
            size_t y = 0;
            while (y <= vertexCount) {
                if (extendedMatrix[x][y] != INT_MAX && distances[x] != INT_MAX &&
                    distances[x] + extendedMatrix[x][y] < distances[y]) {
                    // Negative cycle detected
                    std::string cycle;
                    std::vector<bool> visited(vertexCount + 1, false);
                    int currentVertex = x;
                    visited[y] = true;
                    while (!visited[currentVertex]) {
                        visited[currentVertex] = true;
                        currentVertex = predecessors[currentVertex];
                    }
                    cycle = std::to_string(currentVertex);
                    int nextVertex = predecessors[currentVertex];
                    while (nextVertex != currentVertex) {
                        cycle = std::to_string(nextVertex) + "->" + cycle;
                        nextVertex = predecessors[nextVertex];
                    }
                    cycle = std::to_string(currentVertex) + "->" + cycle;
                    std::cout << "The cycle is: " << cycle << '\n';
                    return 1;
                }
                y++;
            }
            x++;
        }
        // No negative cycle found
        return 0;
    }
}