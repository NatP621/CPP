/*
 * natane.djedou@gmail.com
 */
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"
#include <sstream>
#include <iostream>
#include <vector>
#include <climits>
using namespace ariel;
using namespace std;

/**
 * Test: Default Constructor
 * Description: Tests if the default constructor correctly initializes member variables.
 * The result should be that `num_of_node` and `num_of_edges` are both 0, and `adjMatrix` should be empty.
 */
TEST_CASE("Graph constructor")
{
    // Create a Graph object using the default constructor
    ariel::Graph graph;
    // Check that num_of_node is equal to 0
    CHECK(graph.getNumOfNodes() == 0);
    // Check that num_of_edges is equal to 0
    CHECK(graph.getNumOfEdges() == 0);
    // Check that adjMatrix is empty
    CHECK(graph.getAdjMatrix().empty());
}
/**
 * Test: Setter and Getter for `num_of_node`, `num_of_edges`, and `adjMatrix`
 * Description: Tests if the setters correctly modify the member variables `num_of_node`, `num_of_edges`, and `adjMatrix`,
 * and if the getters return the correct corresponding values.
 * The result should be that the getters return the values set by their respective setters.
 */
TEST_CASE("Graph setters and getters")
{
    ariel::Graph graph;

    // Test for `num_of_node`
    int nodes = 5;
    graph.setNumOfNodes(nodes);
    CHECK(graph.getNumOfNodes() == nodes);  // Verify the setter and getter for `num_of_node`

    // Test for `num_of_edges`
    int edges = 3;
    graph.setNumOfEdges(edges);
    CHECK(graph.getNumOfEdges() == edges);  // Verify the setter and getter for `num_of_edges`

    // Test for `adjMatrix`
    std::vector<std::vector<int>> matrix = {{0, 1}, {1, 0}};
    graph.setNumOfNodes(matrix.size());  // Ensure that the number of nodes is set to match the matrix size NOLINT(*-narrowing-conversions)
    graph.setAdjMatrix(matrix);  // Set the adjacency matrix
    CHECK(graph.getAdjMatrix() == matrix);  // Verify that the getter returns the correct matrix
}
/**
 * Test: Loading and verifying various graphs
 * Description: This test checks the `loadGraph` method with different types of adjacency matrices.
 * It covers connected graphs, disconnected graphs, graphs with loops, fully connected graphs, and incorrect adjacency matrices.
 * The result should be that the adjacency matrix of the `Graph` object, the number of nodes, and the number of edges
 * match those defined by the input matrices.
 */
TEST_CASE("Graph loadGraph various scenarios")
{
    ariel::Graph g;

    // Test for graph1
    //     1
    //    / \
    //   2---3
    std::vector<std::vector<int>> graph1 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph1);
    CHECK(g.getIsOriented() == false);
    CHECK(g.getAdjMatrix() == graph1);
    CHECK(g.getNumOfNodes() == 3);
    CHECK(g.getNumOfEdges() == 3);

    // Test for graph2
    //    1 → 2 → 3
    //    ↑       ↓
    //    └-------┘
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph2);
    CHECK(g.getIsOriented() == true);
    CHECK(g.getAdjMatrix() == graph2);
    CHECK(g.getNumOfNodes() == 3);
    CHECK(g.getNumOfEdges() == 3);

    // Test for graph3
    // (1-2), (1-3), (1-4), (2-3), (2-4), and (3-4)
    std::vector<std::vector<int>> graph3 = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}};
    g.loadGraph(graph3);
    CHECK(g.getIsOriented() == false);
    CHECK(g.getAdjMatrix() == graph3);
    CHECK(g.getNumOfNodes() == 4);
    CHECK(g.getNumOfEdges() == 6);

    // Test for graph4
    // (1→2), (1→3), (2→4), and (3→2) (4→1)
    std::vector<std::vector<int>> graph4 = {
        {0, 1, 1, 0},
        {0, 0, 0, 1},
        {0, 1, 0, 0},
        {1, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(g.getIsOriented() == true);
    CHECK(g.getAdjMatrix() == graph4);
    CHECK(g.getNumOfNodes() == 4);
    CHECK(g.getNumOfEdges() == 5);

    // Test for graph5
    // Edges are (1-2), (2-3), (3-4) with loops on (1-1), (2-2), and (3-3).
    std::vector<std::vector<int>> graph5 = {
        {1, 1, 0, 0},
        {1, 1, 1, 0},
        {0, 1, 1, 1},
        {0, 0, 1, 1}};
    g.loadGraph(graph5);
    CHECK(g.getIsOriented() == false);
    CHECK(g.getAdjMatrix() == graph5);
    CHECK(g.getNumOfNodes() == 4);
    CHECK(g.getNumOfEdges() == 7);

    // Test for graph6
    // Directed edges are (1→2), (3→4), (4→1) with loops on (1→1) and (3→3).
    std::vector<std::vector<int>> graph6 = {
        {1, 1, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 1, 1},
        {1, 0, 0, 1}};
    g.loadGraph(graph6);
    CHECK(g.getIsOriented() == true);
    CHECK(g.getAdjMatrix() == graph6);
    CHECK(g.getNumOfNodes() == 4);
    CHECK(g.getNumOfEdges() == 7);

    // Test for graph7
    // Edges are (1-2), (1-5), (2-3), (3-4), and (4-5).
    std::vector<std::vector<int>> graph7 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };
    g.loadGraph(graph7);
    CHECK(g.getIsOriented() == false);
    CHECK(g.getAdjMatrix() == graph7);
    CHECK(g.getNumOfNodes() == 5);
    CHECK(g.getNumOfEdges() == 5);

    // Test for graph8
    // Directed edges are (1→2), (2→3), (3→4), (4→5), and (5→1).
    std::vector<std::vector<int>> graph8 = {
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0}
    };
    g.loadGraph(graph8);
    CHECK(g.getIsOriented() == true);
    CHECK(g.getAdjMatrix() == graph8);
    CHECK(g.getNumOfNodes() == 5);
    CHECK(g.getNumOfEdges() == 5);

    // Test for graph9
    // Node 0 to Node 1: There is an edge with a weight of 1.
    // Node 0 to Node 2: There is an edge with a weight of 2.
    // Node 1 to Node 2: There is an edge with a weight of -1.
    // Node 2 to Node 0: There is an edge with a weight of 1.
    // Adjacency matrix for a graph with a cycle but non-negative
    // Test for graph9
    std::vector<std::vector<int>> graph9 = {
        {0, 1, 2},
        {0, 0, -1},
        {1, 0, 0}
    };
    g.loadGraph(graph9);
    CHECK(g.getIsOriented() == true); // Correct check, since graph9 is directed
    CHECK(g.getAdjMatrix() == graph9); // Changed graph8 to graph9 to match the loaded matrix
    CHECK(g.getNumOfNodes() == 3); // Changed to 3, because graph9 has 3 nodes
    CHECK(g.getNumOfEdges() == 4); // Changed to 4, because there are 4 edges in graph9
}
/**
 * Test: Print graph with various matrix sizes
 * Description: Tests if the `printGraph` method correctly prints the adjacency matrix for different graphs.
 * The result should be that the output matches the expected matrix.
 */
TEST_CASE("Graph printGraph with various graph sizes")
{
    ariel::Graph g;
    std::ostringstream output;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();

    // 2x2 matrix that represents a connected graph.
    std::vector<std::vector<int>> graph1 = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph1);
    std::cout.rdbuf(output.rdbuf()); // Redirect cout to output
    g.printGraph();
    std::cout.rdbuf(oldCoutStreamBuf); // Reset cout to original buffer
    std::string expectedOutput1 = "Graph with 2 vertices and 2 edges.\n";
    CHECK(output.str() == expectedOutput1);
    output.str(""); // Clear the output for the next test

    // 3x3 matrix that represents a connected graph.
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}};
    g.loadGraph(graph2);
    std::cout.rdbuf(output.rdbuf());
    g.printGraph();
    std::cout.rdbuf(oldCoutStreamBuf);
    std::string expectedOutput2 = "Graph with 3 vertices and 4 edges.\n";
    CHECK(output.str() == expectedOutput2);
    output.str("");

    // 4x4 matrix that represents a fully connected graph.
    std::vector<std::vector<int>> graph3 = {
        {0, 1, 1, 1},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {1, 1, 1, 0}};
    g.loadGraph(graph3);
    std::cout.rdbuf(output.rdbuf());
    g.printGraph();
    std::cout.rdbuf(oldCoutStreamBuf);
    std::string expectedOutput3 = "Graph with 4 vertices and 12 edges.\n";
    CHECK(output.str() == expectedOutput3);
    output.str(""); // Clear the output for the next test
}
/**
 * Test: Graph Connectivity Test
 * Description: This test checks if the graph is fully connected.
 * The result should confirm if all nodes in the graph are accessible from any other node.
 */
TEST_CASE("Graph Connectivity Test")
{
    ariel::Graph g1;

    // Test for a connected graph
    // 1 -- 2
    // |    |
    // 4 -- 3
    std::vector<std::vector<int>> graph1 = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 1},
        {0, 1, 1, 0}
    };
    g1.loadGraph(graph1);
    CHECK(ariel::Algorithms::isConnected(g1) == 1);

    // Test for a disconnected graph
    // 1    2
    // |
    // 3
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 0},
        {0, 0, 0},
        {1, 0, 0}
    };
    g1.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g1) == 0);

    // Test for a graph with a single node
    std::vector<std::vector<int>> graph3 = {
        {0}
    };
    g1.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g1) == 0);

    // Test for an empty graph
    std::vector<std::vector<int>> graph4 = {};
    g1.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g1) == 0);

    // Test for a graph with multiple connected components
    // 1 -- 2   3 -- 4
    std::vector<std::vector<int>> graph5 = {
        {0, 1, 0, 0},
        {1, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0}
    };
    g1.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g1) == 0);
}
/**
 * Test: Shortest Path Calculation Test
 * Description: This test checks the correctness of the shortest path calculation between two nodes.
 * The result should provide the shortest path as a sequence of nodes.
 */
TEST_CASE("Shortest Path Calculation Test")
{
    ariel::Graph g;

    // Adjacency matrix for a connected graph
    std::vector<std::vector<int>> graph1 = {
        {0, 1, 0, 0, 0},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}};
    g.loadGraph(graph1);

    // Test 1: Existing path between nodes 0 and 4
    std::string result = ariel::Algorithms::shortestPath(g, 0, 4);
    CHECK(result == "0->1->2->3->4");

    // Adjacency matrix for a disconnected graph
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 0, 0, 0},
        {1, 0, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {0, 0, 0, 1, 0}
    };
    g.loadGraph(graph2);

    // Test 2: No path between nodes 0 and 4 in a disconnected graph
    result = ariel::Algorithms::shortestPath(g, 0, 4);
    CHECK(result == "-1");

    // Test 3: Invalid start node
    result = ariel::Algorithms::shortestPath(g, -1, 4);
    CHECK(result == "Invalid start or end node.");

    // Test 4: Invalid end node
    result = ariel::Algorithms::shortestPath(g, 0, 5);
    CHECK(result == "Invalid start or end node.");

    // Test 5: Path between the same node
    result = ariel::Algorithms::shortestPath(g, 0, 0);
    CHECK(result == "0");
}
/**
 * Test: Cycle Detection Test
 * Description: This test checks if the graph contains cycles.
 * The result should indicate whether a cycle exists in the graph.
 */
TEST_CASE("Cycle Detection Test")
{
    ariel::Graph g;

    // Adjacency matrix for a graph without a cycle
    std::vector<std::vector<int>> graph1 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 0}
    };
    g.loadGraph(graph1);

    // Test 1: Check that a graph without a cycle is correctly detected
    CHECK(ariel::Algorithms::isContainsCycle(g) == 0);

    // Adjacency matrix for a graph with a cycle
    std::vector<std::vector<int>> graph2 = {
        {0, 1, 0, 0},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {0, 0, 1, 1}  // Adding a cycle between nodes 2, 3, and 1
    };
    g.loadGraph(graph2);

    // Test 2: Check that a graph with a cycle is correctly detected
    CHECK(ariel::Algorithms::isContainsCycle(g) == 1);

    // Adjacency matrix for a more complex graph with multiple cycles
    std::vector<std::vector<int>> graph3 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 1, 0},
        {1, 1, 0, 0, 1},
        {0, 1, 0, 0, 1},
        {0, 0, 1, 1, 0}
    };
    g.loadGraph(graph3);

    // Test 3: Check that a graph with multiple cycles is correctly detected
    CHECK(ariel::Algorithms::isContainsCycle(g) == 1);

    // Adjacency matrix for an empty graph (no nodes)
    std::vector<std::vector<int>> graph4 = {};
    g.loadGraph(graph4);

    // Test 4: Check that an empty graph does not contain a cycle
    CHECK(ariel::Algorithms::isContainsCycle(g) == 0);
}
/**
 * Test: Bipartite Graph Test
 * Description: This test checks if the graph is bipartite.
 * The result should confirm whether the graph can be divided into two disjoint sets where no vertices in the same set are adjacent.
 */
TEST_CASE("Bipartite Graph Test")
{
    ariel::Graph g;

    // Adjacency matrix for a simple bipartite graph
    std::vector<std::vector<int>> bipartiteGraph1 = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    g.loadGraph(bipartiteGraph1);

    // Test 1: Check that a bipartite graph is correctly detected with sets A and B
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}.");

    // Adjacency matrix for a non-bipartite graph (triangle)
    std::vector<std::vector<int>> nonBipartiteGraph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    g.loadGraph(nonBipartiteGraph);

    // Test 2: Check that a non-bipartite graph is correctly detected
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    // Adjacency matrix for a bipartite graph with a connected component
    std::vector<std::vector<int>> bipartiteGraph2 = {
        {0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0}
    };
    g.loadGraph(bipartiteGraph2);

    // Test 3: Check that a larger bipartite graph is correctly detected
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 5, 3}.");

    // Adjacency matrix for an empty graph (no nodes)
    std::vector<std::vector<int>> emptyGraph = {};
    g.loadGraph(emptyGraph);

    // Test 4: Check that an empty graph is considered bipartite
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={}, B={}.");

    // Adjacency matrix for a graph with a single node
    std::vector<std::vector<int>> singleNodeGraph = {
        {0}
    };
    g.loadGraph(singleNodeGraph);

    // Test 5: Check that a graph with a single node is bipartite
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0}, B={}.");
}
/**
 * Test: Addition Operator (+)
 * Description: This test checks if two graphs can be added correctly using the + operator.
 */
TEST_CASE("Addition Operator (+)")
{
    // Test 1: Addition of two non-empty graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 1, 2}, {1, 0, 3}, {2, 3, 0}});
        g2.loadGraph({{1, 0, 1}, {0, 1, 0}, {1, 0, 1}});

        Graph result = g1 + g2;
        Graph expected_result;
        expected_result.loadGraph({{1, 1, 3}, {1, 1, 3}, {3, 3, 1}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 2: Addition of Empty Graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;

        Graph result = g1 + g2;
        Graph expected_result;

        CHECK(result.getNumOfNodes() == 0);
        CHECK(result.getNumOfEdges() == 0);
        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 3: Addition of Graphs with Different Sizes
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 1}, {1, 0}});
        g2.loadGraph({{1, 0, 1}, {0, 1, 0}, {1, 0, 1}});

        CHECK_THROWS_AS(g1 + g2, std::invalid_argument);
    }

    // Test 4: Addition of Directed Graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.setIsOriented(true);
        g2.setIsOriented(true);

        g1.loadGraph({{0, 1, 0}, {0, 0, 1}, {1, 0, 0}});
        g2.loadGraph({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});

        Graph result = g1 + g2;
        Graph expected_result;
        expected_result.setIsOriented(true);
        expected_result.loadGraph({{1, 1, 0}, {0, 1, 1}, {1, 0, 1}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 5: Addition of Fully Connected Graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
        g2.loadGraph({{2, 2, 2}, {2, 2, 2}, {2, 2, 2}});

        Graph result = g1 + g2;
        Graph expected_result;
        expected_result.loadGraph({{3, 3, 3}, {3, 3, 3}, {3, 3, 3}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 6: Addition of Graphs with Negative Edges
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, -1, -2}, {-1, 0, -3}, {-2, -3, 0}});
        g2.loadGraph({{-1, 0, -1}, {0, -1, 0}, {-1, 0, -1}});

        Graph result = g1 + g2;
        Graph expected_result;
        expected_result.loadGraph({{-1, -1, -3}, {-1, -1, -3}, {-3, -3, -1}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }
}
/**
 * Test: Addition-Assignment Operator (+=)
 * Description: This test checks if the += operator correctly adds one graph to another.
 */
TEST_CASE("Addition-Assignment Operator (+=)")
{
    // Test 1: Addition-Assignment of two non-empty graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 1, 2}, {1, 0, 3}, {2, 3, 0}});
        g2.loadGraph({{1, 0, 1}, {0, 1, 0}, {1, 0, 1}});

        g1 += g2;

        std::vector<std::vector<int>> expected_matrix = {{1, 1, 3}, {1, 1, 3}, {3, 3, 1}};

        CHECK(g1.getAdjMatrix() == expected_matrix);
    }

    // Test 2: Addition-Assignment of an empty graph to another graph
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 1}, {1, 0}});
        g2.loadGraph({{0, 0}, {0, 0}});  // Empty graph with the same size

        g1 += g2;

        std::vector<std::vector<int>> expected_matrix = {{0, 1}, {1, 0}};

        CHECK(g1.getAdjMatrix() == expected_matrix);
    }

    // Test 3: Addition-Assignment of graphs with different sizes
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 1}, {1, 0}});
        g2.loadGraph({{1, 0, 1}, {0, 1, 0}, {1, 0, 1}});

        CHECK_THROWS_AS(g1 += g2, std::invalid_argument);
    }

    // Test 4: Addition-Assignment of directed graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.setIsOriented(true);
        g2.setIsOriented(true);

        g1.loadGraph({{0, 1, 0}, {0, 0, 1}, {1, 0, 0}});
        g2.loadGraph({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});

        g1 += g2;

        std::vector<std::vector<int>> expected_matrix = {{1, 1, 0}, {0, 1, 1}, {1, 0, 1}};

        CHECK(g1.getAdjMatrix() == expected_matrix);
    }

    // Test 5: Addition-Assignment with fully connected graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
        g2.loadGraph({{2, 2, 2}, {2, 2, 2}, {2, 2, 2}});

        g1 += g2;

        std::vector<std::vector<int>> expected_matrix = {{3, 3, 3}, {3, 3, 3}, {3, 3, 3}};

        CHECK(g1.getAdjMatrix() == expected_matrix);
    }

    // Test 6: Addition-Assignment with graphs having negative edges
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, -1, -2}, {-1, 0, -3}, {-2, -3, 0}});
        g2.loadGraph({{-1, 0, -1}, {0, -1, 0}, {-1, 0, -1}});

        g1 += g2;

        std::vector<std::vector<int>> expected_matrix = {{-1, -1, -3}, {-1, -1, -3}, {-3, -3, -1}};

        CHECK(g1.getAdjMatrix() == expected_matrix);
    }
}
/**
 * Test: Unary Plus Operator (+)
 * Description: This test checks if the unary + operator returns a copy of the graph.
 */
TEST_CASE("Unary Plus Operator (+)") {
    ariel::Graph originalGraph;

    // Initialize the original graph using loadGraph
    std::vector<std::vector<int>> matrix = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}
    };
    originalGraph.loadGraph(matrix);

    // Use the unary + operator to create a copy
    ariel::Graph copiedGraph = +originalGraph;

    // Check if the two graphs are identical
    CHECK(copiedGraph.getNumOfNodes() == originalGraph.getNumOfNodes());
    CHECK(copiedGraph.getNumOfEdges() == originalGraph.getNumOfEdges());
    CHECK(copiedGraph.getIsOriented() == originalGraph.getIsOriented());
    CHECK(copiedGraph.getAdjMatrix() == originalGraph.getAdjMatrix());

    // Verify that modifying the copy does not affect the original (deep copy)
    copiedGraph.setNumOfNodes(5);  // Modify the number of nodes in the copied graph
    CHECK(copiedGraph.getNumOfNodes() != originalGraph.getNumOfNodes());
}
/**
 * Test: Subtraction Operator (-)
 * Description: This test checks if one graph can be subtracted from another using the - operator.
 */
TEST_CASE("Subtraction Operator (-)")
{
    // Test 1: Subtraction of two non-empty graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{3, 2, 1}, {2, 3, 2}, {1, 2, 3}});
        g2.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
        Graph result = g1 - g2;
        Graph expected_result;
        expected_result.loadGraph({{2, 1, 0}, {1, 2, 1}, {0, 1, 2}});
        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 2: Subtraction with negative result
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
        g2.loadGraph({{2, 2, 2}, {2, 2, 2}, {2, 2, 2}});

        Graph result = g1 - g2;
        Graph expected_result;
        expected_result.loadGraph({{-1, -2, -2}, {-2, -1, -2}, {-2, -2, -1}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 3: Subtraction of graphs resulting in zero
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
        g2.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

        Graph result = g1 - g2;
        Graph expected_result;
        expected_result.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 4: Subtraction of graphs with different sizes
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 1, 1}, {1, 0, 1}});
        g2.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

        CHECK_THROWS_AS(g1 - g2, std::invalid_argument);
    }

    // Test 5: Subtraction of directed graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.setIsOriented(true);
        g2.setIsOriented(true);

        g1.loadGraph({{1, 0, 1}, {0, 1, 0}, {1, 0, 1}});
        g2.loadGraph({{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});

        Graph result = g1 - g2;
        Graph expected_result;
        expected_result.setIsOriented(true);
        expected_result.loadGraph({{1, -1, 1}, {-1, 1, -1}, {1, -1, 1}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 6: Subtraction with negative weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, -2, -4}, {-2, 0, -6}, {-4, -6, 0}});
        g2.loadGraph({{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}});

        Graph result = g1 - g2;
        Graph expected_result;
        expected_result.loadGraph({{1, -1, -3}, {-1, 1, -5}, {-3, -5, 1}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }
}
/**
 * Test: Subtraction-Assignment Operator (-=)
 * Description: This test checks if the -= operator correctly subtracts one graph from another.
 */
TEST_CASE("Subtraction-Assignment Operator (-=)")
{
    // Test 1: Subtraction-Assignment with two non-empty graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{3, 2, 1}, {2, 3, 2}, {1, 2, 3}});
        g2.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

        g1 -= g2;
        Graph expected_result;
        expected_result.loadGraph({{2, 1, 0}, {1, 2, 1}, {0, 1, 2}});

        CHECK(g1.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 2: Subtraction-Assignment with negative result
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});
        g2.loadGraph({{2, 2, 2}, {2, 2, 2}, {2, 2, 2}});

        g1 -= g2;
        Graph expected_result;
        expected_result.loadGraph({{-1, -2, -2}, {-2, -1, -2}, {-2, -2, -1}});

        CHECK(g1.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 3: Subtraction-Assignment resulting in zero
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});
        g2.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

        g1 -= g2;
        Graph expected_result;
        expected_result.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

        CHECK(g1.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 4: Subtraction-Assignment of graphs with different sizes
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 1, 1}, {1, 0, 1}});
        g2.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

        CHECK_THROWS_AS(g1 -= g2, std::invalid_argument);
    }

    // Test 5: Subtraction-Assignment of directed graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.setIsOriented(true);
        g2.setIsOriented(true);

        g1.loadGraph({{1, 0, 1}, {0, 1, 0}, {1, 0, 1}});
        g2.loadGraph({{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});

        g1 -= g2;
        Graph expected_result;
        expected_result.setIsOriented(true);
        expected_result.loadGraph({{1, -1, 1}, {-1, 1, -1}, {1, -1, 1}});

        CHECK(g1.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 6: Subtraction-Assignment with negative weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, -2, -4}, {-2, 0, -6}, {-4, -6, 0}});
        g2.loadGraph({{-1, -1, -1}, {-1, -1, -1}, {-1, -1, -1}});

        g1 -= g2;
        Graph expected_result;
        expected_result.loadGraph({{1, -1, -3}, {-1, 1, -5}, {-3, -5, 1}});

        CHECK(g1.getAdjMatrix() == expected_result.getAdjMatrix());
    }
}
/**
 * Test: Unary Minus Operator (-)
 * Description: This test checks if the unary - operator correctly negates a graph.
 */
TEST_CASE("Unary Minus Operator (-)")
{
    // Test 1: Negating a graph with positive weights
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {2, 1, 2}, {3, 2, 1}});

        Graph result = -g;
        Graph expected_result;
        expected_result.loadGraph({{-1, -2, -3}, {-2, -1, -2}, {-3, -2, -1}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 2: Negating a graph with negative weights
    {
        ariel::Graph g;
        g.loadGraph({{-1, -2, -3}, {-2, -1, -2}, {-3, -2, -1}});

        Graph result = -g;
        Graph expected_result;
        expected_result.loadGraph({{1, 2, 3}, {2, 1, 2}, {3, 2, 1}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 3: Negating a graph with mixed weights
    {
        ariel::Graph g;
        g.loadGraph({{0, -1, 2}, {-1, 0, -3}, {2, -3, 0}});

        Graph result = -g;
        Graph expected_result;
        expected_result.loadGraph({{0, 1, -2}, {1, 0, 3}, {-2, 3, 0}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 4: Negating a graph with zero weights
    {
        ariel::Graph g;
        g.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

        Graph result = -g;
        Graph expected_result;
        expected_result.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }

    // Test 5: Negating a graph with a non-square adjacency matrix (if applicable)
    {
        ariel::Graph g;
        g.loadGraph({{1, 2}, {3, 4}});

        Graph result = -g;
        Graph expected_result;
        expected_result.loadGraph({{-1, -2}, {-3, -4}});

        CHECK(result.getAdjMatrix() == expected_result.getAdjMatrix());
    }
}
/**
 * Test: Equality Operator (==)
 * Description: This test checks if two graphs are correctly compared for equality using the == operator.
 */
TEST_CASE("Equality Operator (==)")
{
    // Test 1: Comparing two identical graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2, 3}, {2, 1, 2}, {3, 2, 1}});
        g2.loadGraph({{1, 2, 3}, {2, 1, 2}, {3, 2, 1}});

        CHECK(g1 == g2);
    }

    // Test 2: Comparing two graphs with different weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2, 3}, {2, 1, 2}, {3, 2, 1}});
        g2.loadGraph({{1, 2, 4}, {2, 1, 2}, {3, 2, 1}});

        CHECK_FALSE(g1 == g2);
    }

    // Test 3: Comparing two graphs with different sizes
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2}, {2, 1}});
        g2.loadGraph({{1, 2, 3}, {2, 1, 4}, {3, 4, 1}});

        CHECK_FALSE(g1 == g2);
    }

    // Test 4: Comparing a graph with itself
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {2, 1, 2}, {3, 2, 1}});

        CHECK(g == g);
    }

    // Test 5: Comparing graphs with negative weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{-1, -2, -3}, {-2, -1, -2}, {-3, -2, -1}});
        g2.loadGraph({{-1, -2, -3}, {-2, -1, -2}, {-3, -2, -1}});

        CHECK(g1 == g2);
    }

    // Test 6: Comparing graphs with zero weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
        g2.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

        CHECK(g1 == g2);
    }
}
/**
 * Test: Inequality Operator (!=)
 * Description: This test checks if two graphs are correctly compared for inequality using the != operator.
 */
TEST_CASE("Inequality Operator (!=)")
{
    // Test 1: Comparing two different graphs
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2, 3}, {2, 1, 2}, {3, 2, 1}});
        g2.loadGraph({{1, 2, 4}, {2, 1, 2}, {3, 2, 1}});

        CHECK(g1 != g2);
    }

    // Test 2: Comparing two graphs with different sizes
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2}, {2, 1}});
        g2.loadGraph({{1, 2, 3}, {2, 1, 4}, {3, 4, 1}});

        CHECK(g1 != g2);
    }

    // Test 3: Comparing a graph with itself
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {2, 1, 2}, {3, 2, 1}});

        CHECK_FALSE(g != g);
    }

    // Test 4: Comparing graphs with negative weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{-1, -2, -3}, {-2, -1, -2}, {-3, -2, -1}});
        g2.loadGraph({{-1, -2, -4}, {-2, -1, -2}, {-3, -2, -1}});

        CHECK(g1 != g2);
    }

    // Test 5: Comparing graphs with zero weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});
        g2.loadGraph({{0, 0, 1}, {0, 0, 0}, {0, 0, 0}});

        CHECK(g1 != g2);
    }
}
/**
 * Test: Less Than Operator (<)
 * Description: This test checks if one graph is correctly identified as being less than another using the < operator.
 */
TEST_CASE("Less Than Operator (<)") {
    // Test 1: Comparing two graphs with different edge weight sums
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 3}, {0, 0, 0}});

        REQUIRE(g1 < g2); // g1 has a total weight of 3, g2 has a total weight of 4
    }

    // Test 2: Comparing two graphs with different sizes
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1}, {0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 0}, {0, 0, 0}});

        REQUIRE(g1 < g2); // g1 has fewer nodes than g2
    }

    // Test 3: Comparing graphs with the same matrices but different weights
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 1}, {0, 0, 0}});

        REQUIRE(!(g1 < g2)); // g1 is not less than g2 because the edge weights in g1 are greater or equal
    }

    // Test 4: Comparing a graph with itself
    {
        Graph g1;
        g1.loadGraph({{0, 1, 0}, {0, 0, 0}, {0, 0, 0}});

        REQUIRE(!(g1 < g1)); // A graph should not be less than itself
    }

    // Test 5: Comparing with empty graphs
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({});
        g2.loadGraph({});

        REQUIRE(!(g1 < g2)); // Two empty graphs should not be less than each other
    }
}
/**
 * Test: Less Than or Equal To Operator (<=)
 * Description: This test checks if one graph is correctly identified as being less than or equal to another using the <= operator.
 */
TEST_CASE("Less Than or Equal To Operator (<=)") {
    // Test 1: Comparing two graphs with different edge weight sums
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 3}, {0, 0, 0}});

        REQUIRE(g1 <= g2); // g1 has a total weight of 3, g2 has a total weight of 4
    }

    // Test 2: Comparing two graphs with the same edge weight sums
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});

        REQUIRE(g1 <= g2); // g1 is equal to g2
    }

    // Test 3: Comparing graphs with different sizes
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1}, {0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 0}, {0, 0, 0}});

        REQUIRE(g1 <= g2); // g1 has fewer nodes than g2
    }

    // Test 4: Comparing a graph with itself
    {
        Graph g1;
        g1.loadGraph({{0, 1, 0}, {0, 0, 0}, {0, 0, 0}});

        REQUIRE(g1 <= g1); // A graph should be equal to itself
    }

    // Test 5: Comparing with empty graphs
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({});
        g2.loadGraph({});

        REQUIRE(g1 <= g2); // Two empty graphs should be equal
    }
}
/**
 * Test: Greater Than Operator (>)
 * Description: This test checks if one graph is correctly identified as being greater than another using the > operator.
 */
TEST_CASE("Greater Than Operator (>)") {
    // Test 1: Comparing two graphs with different edge weight sums
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 3}, {0, 0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});

        REQUIRE(g1 > g2); // g1 has a total weight of 4, g2 has a total weight of 3
    }

    // Test 2: Comparing two graphs with the same edge weight sums
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});

        REQUIRE(!(g1 > g2)); // g1 is equal to g2
    }

    // Test 3: Comparing graphs with different sizes
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 0}, {0, 0, 0}});
        g2.loadGraph({{0, 1}, {0, 0}});

        REQUIRE(g1 > g2); // g1 has more nodes than g2
    }

    // Test 4: Comparing a graph with itself
    {
        Graph g1;
        g1.loadGraph({{0, 1, 0}, {0, 0, 0}, {0, 0, 0}});

        REQUIRE(!(g1 > g1)); // A graph should not be greater than itself
    }

    // Test 5: Comparing with empty graphs
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({});
        g2.loadGraph({});

        REQUIRE(!(g1 > g2)); // Two empty graphs should not be greater than each other
    }
}
/**
 * Test: Greater Than or Equal To Operator (>=)
 * Description: This test checks if one graph is correctly identified as being greater than or equal to another using the >= operator.
 */
TEST_CASE("Greater Than or Equal To Operator (>=)") {
    // Test 1: Comparing two graphs with different edge weight sums
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 3}, {0, 0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});

        REQUIRE(g1 >= g2); // g1 has a total weight of 4, g2 has a total weight of 3
    }

    // Test 2: Comparing two graphs with the same edge weight sums
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});
        g2.loadGraph({{0, 1, 0}, {0, 0, 2}, {0, 0, 0}});

        REQUIRE(g1 >= g2); // g1 is equal to g2
    }

    // Test 3: Comparing graphs with different sizes
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({{0, 1, 0}, {0, 0, 0}, {0, 0, 0}});
        g2.loadGraph({{0, 1}, {0, 0}});

        REQUIRE(g1 >= g2); // g1 has more nodes than g2
    }

    // Test 4: Comparing a graph with itself
    {
        Graph g1;
        g1.loadGraph({{0, 1, 0}, {0, 0, 0}, {0, 0, 0}});

        REQUIRE(g1 >= g1); // A graph should be equal to itself
    }

    // Test 5: Comparing with empty graphs
    {
        Graph g1;
        Graph g2;
        g1.loadGraph({});
        g2.loadGraph({});

        REQUIRE(g1 >= g2); // Two empty graphs should be equal
    }
}
/**
 * Test: Prefix Increment Operator (++)
 * Description: This test checks if the prefix increment operator (++) correctly increments all edge weights by 1.
 */
TEST_CASE("Prefix Increment Operator (++)")
{
    // Test 1: Incrementing edge weights in a graph
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        // Apply the ++ operator
        ++g;

        // Expected adjacency matrix after increment
        ariel::Graph expected_result;
        expected_result.loadGraph({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});

        // Check if the adjacency matrix of the graph after increment matches the expected matrix
        CHECK(g == expected_result);
    }

    // Test 2: Incrementing a graph with negative weights
    {
        ariel::Graph g;
        g.loadGraph({{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}});

        // Apply the ++ operator
        ++g;

        // Expected adjacency matrix after increment
        ariel::Graph expected_result;
        expected_result.loadGraph({{0, -1, -2}, {-3, -4, -5}, {-6, -7, -8}});

        // Check if the adjacency matrix of the graph after increment matches the expected matrix
        CHECK(g == expected_result);
    }

    // Test 3: Incrementing a graph with zero weights
    {
        ariel::Graph g;
        g.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

        // Apply the ++ operator
        ++g;

        // Expected adjacency matrix after increment
        ariel::Graph expected_result;
        expected_result.loadGraph({{1, 1, 1}, {1, 1, 1}, {1, 1, 1}});

        // Check if the adjacency matrix of the graph after increment matches the expected matrix
        CHECK(g == expected_result);
    }

    // Test 4: Incrementing an empty graph
    {
        ariel::Graph g;

        // Apply the ++ operator to an empty graph
        ++g;

        // Expected adjacency matrix after increment (still empty)
        ariel::Graph expected_result;

        // Check that the graph remains empty
        CHECK(g == expected_result);
    }
}
/**
 * Test: Postfix Increment Operator (++)
 * Description: This test checks if the postfix increment operator (++) correctly increments all edge weights by 1.
 */
TEST_CASE("Postfix Increment Operator (++)")
{
    // Test 1: Incrementing edge weights in a non-empty graph
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        // Create a copy of the graph before increment to verify the result
        ariel::Graph g_before = g;

        // Apply postfix increment
        g++;

        // Define the expected values after increment
        ariel::Graph expected;
        expected.loadGraph({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});

        // Compare graphs before and after increment
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 2: Incrementing edge weights in a graph with negative weights
    {
        ariel::Graph g;
        g.loadGraph({{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}});

        // Create a copy of the graph before increment to verify the result
        ariel::Graph g_before = g;

        // Apply postfix increment
        g++;

        // Define the expected values after increment
        ariel::Graph expected;
        expected.loadGraph({{0, -1, -2}, {-3, -4, -5}, {-6, -7, -8}});

        // Compare graphs before and after increment
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 3: Incrementing an empty graph
    {
        ariel::Graph g;

        // Create a copy of the graph before increment to verify the result
        ariel::Graph g_before = g;

        // Apply postfix increment
        g++;

        // An empty graph should remain empty after increment
        CHECK(g_before.getAdjMatrix() == g.getAdjMatrix());
    }

    // Test 4: Comparing after incrementing a graph
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2}, {3, 4}});

        // Increment the edges of the first graph
        g1++;

        // Define the expected result
        ariel::Graph expected;
        expected.loadGraph({{2, 3}, {4, 5}});

        // Compare the modified graph with the expected graph
        CHECK(g1.getAdjMatrix() == expected.getAdjMatrix());
    }
}
/**
 * Test: Prefix Decrement Operator (--)
 * Description: This test checks if the prefix decrement operator (--) correctly decrements all edge weights by 1.
 */
TEST_CASE("Prefix Decrement Operator (--)")
{
    // Test 1: Decrementing edge weights in a non-empty graph
    {
        ariel::Graph g;
        g.loadGraph({{3, 4, 5}, {6, 7, 8}, {9, 10, 11}});

        // Create a copy of the graph before decrement to verify the result
        ariel::Graph g_before = g;

        // Apply prefix decrement
        --g;

        // Define the expected values after decrement
        ariel::Graph expected;
        expected.loadGraph({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});

        // Compare graphs before and after decrement
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 2: Decrementing edge weights in a graph with negative weights
    {
        ariel::Graph g;
        g.loadGraph({{0, -1, -2}, {-3, -4, -5}, {-6, -7, -8}});

        // Create a copy of the graph before decrement to verify the result
        ariel::Graph g_before = g;

        // Apply prefix decrement
        --g;

        // Define the expected values after decrement
        ariel::Graph expected;
        expected.loadGraph({{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}});

        // Compare graphs before and after decrement
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 3: Decrementing an empty graph
    {
        ariel::Graph g;

        // Create a copy of the graph before decrement to verify the result
        ariel::Graph g_before = g;

        // Apply prefix decrement
        --g;

        // An empty graph should remain empty after decrement
        CHECK(g_before.getAdjMatrix() == g.getAdjMatrix());
    }

    // Test 4: Comparing after decrementing a graph
    {
        ariel::Graph g1;
        g1.loadGraph({{2, 3}, {4, 5}});

        // Decrement the edges of the first graph
        --g1;

        // Define the expected result
        ariel::Graph expected;
        expected.loadGraph({{1, 2}, {3, 4}});

        // Compare the modified graph with the expected graph
        CHECK(g1.getAdjMatrix() == expected.getAdjMatrix());
    }
}
/**
 * Test: Postfix Decrement Operator (--)
 * Description: This test checks if the postfix decrement operator (--) correctly decrements all edge weights by 1.
 */
TEST_CASE("Postfix Decrement Operator (--)")
{
    // Test 1: Decrementing edge weights in a non-empty graph
    {
        ariel::Graph g;
        g.loadGraph({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});

        // Create a copy of the graph before decrement to verify the result
        ariel::Graph g_before = g;

        // Apply postfix decrement
        g--;

        // Define the expected values after decrement
        ariel::Graph expected;
        expected.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        // Compare graphs before and after decrement
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 2: Decrementing edge weights in a graph with negative weights
    {
        ariel::Graph g;
        g.loadGraph({{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}});

        // Create a copy of the graph before decrement to verify the result
        ariel::Graph g_before = g;

        // Apply postfix decrement
        g--;

        // Define the expected values after decrement
        ariel::Graph expected;
        expected.loadGraph({{-2, -3, -4}, {-5, -6, -7}, {-8, -9, -10}});

        // Compare graphs before and after decrement
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 3: Decrementing an empty graph
    {
        ariel::Graph g;

        // Create a copy of the graph before decrement to verify the result
        ariel::Graph g_before = g;

        // Apply postfix decrement
        g--;

        // An empty graph should remain empty after decrement
        CHECK(g_before.getAdjMatrix() == g.getAdjMatrix());
    }

    // Test 4: Comparing after decrementing a graph
    {
        ariel::Graph g1;
        g1.loadGraph({{3, 4}, {5, 6}});

        // Decrement the edges of the first graph
        g1--;

        // Define the expected result
        ariel::Graph expected;
        expected.loadGraph({{2, 3}, {4, 5}});

        // Compare the modified graph with the expected graph
        CHECK(g1.getAdjMatrix() == expected.getAdjMatrix());
    }
}
/**
 * Test: Multiplication by Integer Operator (*)
 * Description: This test checks if a graph can be multiplied by an integer using the * operator.
 */
TEST_CASE("Multiplication by Integer Operator (*)")
{
    // Test 1: Multiplication by a positive integer
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        // Create a copy of the graph before multiplication to verify the result
        ariel::Graph g_before = g;

        // Multiply the graph by 2
        g = g * 2;

        // Define the expected values after multiplication
        ariel::Graph expected;
        expected.loadGraph({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});

        // Compare graphs before and after multiplication
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 2: Multiplication by a negative integer
    {
        ariel::Graph g;
        g.loadGraph({{2, 3, 4}, {5, 6, 7}, {8, 9, 10}});

        // Create a copy of the graph before multiplication to verify the result
        ariel::Graph g_before = g;

        // Multiply the graph by -1
        g = g * -1;

        // Define the expected values after multiplication
        ariel::Graph expected;
        expected.loadGraph({{-2, -3, -4}, {-5, -6, -7}, {-8, -9, -10}});

        // Compare graphs before and after multiplication
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 3: Multiplication by zero
    {
        ariel::Graph g;
        g.loadGraph({{3, 4, 5}, {6, 7, 8}, {9, 10, 11}});

        // Create a copy of the graph before multiplication to verify the result
        ariel::Graph g_before = g;

        // Multiply the graph by 0
        g = g * 0;

        // Define the expected values after multiplication
        ariel::Graph expected;
        expected.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

        // Compare graphs before and after multiplication
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 4: Multiplication by 1 (no change expected)
    {
        ariel::Graph g;
        g.loadGraph({{1, 1}, {1, 1}});

        // Create a copy of the graph before multiplication to verify the result
        ariel::Graph g_before = g;

        // Multiply the graph by 1
        g = g * 1;

        // Compare graphs before and after multiplication
        CHECK(g_before.getAdjMatrix() == g.getAdjMatrix());
    }

    // Test 5: Multiplication of a graph with negative weights by a positive integer
    {
        ariel::Graph g;
        g.loadGraph({{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}});

        // Create a copy of the graph before multiplication to verify the result
        ariel::Graph g_before = g;

        // Multiply the graph by 3
        g = g * 3;

        // Define the expected values after multiplication
        ariel::Graph expected;
        expected.loadGraph({{-3, -6, -9}, {-12, -15, -18}, {-21, -24, -27}});

        // Compare graphs before and after multiplication
        CHECK_FALSE(g_before.getAdjMatrix() == g.getAdjMatrix());
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }
}
/**
 * Test: Graph Multiplication Operator (*)
 * Description: This test checks if two graphs can be multiplied together using the * operator.
 */
TEST_CASE("Graph Multiplication Operator (*)")
{
    // Test 1: Multiplication of two graphs with positive weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
        g2.loadGraph({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});

        // Create the expected graph after multiplication
        ariel::Graph expected;
        expected.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        // Multiply the graphs
        ariel::Graph result = g1 * g2;

        // Compare the resulting graphs
        CHECK(result.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 2: Multiplication with negative weights
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}});
        g2.loadGraph({{0, 1, 0}, {1, 0, 1}, {0, 1, 0}});

        // Create the expected graph after multiplication
        ariel::Graph expected;
        expected.loadGraph({{-2, -4, -2}, {-5, -10, -5}, {-8, -16, -8}});

        // Multiply the graphs
        ariel::Graph result = g1 * g2;

        // Compare the resulting graphs
        CHECK(result.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 3: Multiplication with a null graph
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2}, {3, 4}});
        g2.loadGraph({{0, 0}, {0, 0}});  // Null graph

        // Create the expected graph after multiplication
        ariel::Graph expected;
        expected.loadGraph({{0, 0}, {0, 0}});

        // Multiply the graphs
        ariel::Graph result = g1 * g2;

        // Compare the resulting graphs
        CHECK(result.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 4: Multiplication of graphs with different sizes
    {
        ariel::Graph g1;
        ariel::Graph g2;
        g1.loadGraph({{1, 2}, {3, 4}});
        g2.loadGraph({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}});

        // Check that multiplication fails with different sizes
        CHECK_THROWS_AS(g1 * g2, std::invalid_argument);
    }
}
/**
 * Test: Output Stream Operator (<<) with Various Graphs
 * Description: This test checks if the << operator correctly outputs the adjacency matrix
 * for various graph configurations.
 */
TEST_CASE("Output Stream Operator (<<) with Various Graphs") {
    // Test 1: Output with a non-empty graph
    ariel::Graph g1;
    std::vector<std::vector<int>> graph1 = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}
    };
    g1.loadGraph(graph1);

    std::ostringstream oss1;
    oss1 << g1;
    std::string expected_output1 = "[0, 1, 1], [1, 0, 1], [1, 1, 0]";
    CHECK(oss1.str() == expected_output1);

    // Test 2: Output with a graph with zeros
    ariel::Graph g2;
    std::vector<std::vector<int>> graph2 = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    g2.loadGraph(graph2);

    std::ostringstream oss2;
    oss2 << g2;
    std::string expected_output2 = "[0, 0, 0], [0, 0, 0], [0, 0, 0]";
    CHECK(oss2.str() == expected_output2);

    // Test 3: Output with a graph with multiple nodes and negative weights
    ariel::Graph g4;
    std::vector<std::vector<int>> graph4 = {
        {0, -2, 3},
        {-2, 0, 4},
        {3, 4, 0}
    };
    g4.loadGraph(graph4);

    std::ostringstream oss4;
    oss4 << g4;
    std::string expected_output4 = "[0, -2, 3], [-2, 0, 4], [3, 4, 0]";
    CHECK(oss4.str() == expected_output4);
}
/**
 * Test: Multiplication-Assignment by Integer Operator (*=)
 * Description: This test checks if the *= operator correctly multiplies a graph by an integer.
 */
TEST_CASE("Multiplication-Assignment by Integer Operator (*=)")
{
    // Test 1: Multiplication by a positive integer
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        // Multiply the graph by 2
        g *= 2;

        // Create the expected graph after multiplication
        ariel::Graph expected;
        expected.loadGraph({{2, 4, 6}, {8, 10, 12}, {14, 16, 18}});

        // Compare the adjacency matrices
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 2: Multiplication by zero
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        // Multiply the graph by 0
        g *= 0;

        // Create the expected graph after multiplication
        ariel::Graph expected;
        expected.loadGraph({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}});

        // Compare the adjacency matrices
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 3: Multiplication by a negative integer
    {
        ariel::Graph g;
        g.loadGraph({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

        // Multiply the graph by -1
        g *= -1;

        // Create the expected graph after multiplication
        ariel::Graph expected;
        expected.loadGraph({{-1, -2, -3}, {-4, -5, -6}, {-7, -8, -9}});

        // Compare the adjacency matrices
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 4: Multiplication with an empty graph
    {
        ariel::Graph g;
        // Create an empty graph
        ariel::Graph empty_graph;

        // Multiply the empty graph by 3
        empty_graph *= 3;

        // Compare the adjacency matrices
        CHECK(empty_graph.getAdjMatrix() == empty_graph.getAdjMatrix());
    }
}
/**
 * Test: Division by Integer Operator (/=)
 * Description: This test checks if the /= operator correctly divides a graph by an integer.
 */
TEST_CASE("Division by Integer Operator (/=)")
{
    // Test 1: Division by a positive integer
    {
        ariel::Graph g;
        g.loadGraph({{10, 20, 30}, {40, 50, 60}, {70, 80, 90}});

        // Divide the graph by 2
        g /= 2;

        // Create the expected graph after division
        ariel::Graph expected;
        expected.loadGraph({{5, 10, 15}, {20, 25, 30}, {35, 40, 45}});

        // Compare the adjacency matrices
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 2: Division by a negative integer
    {
        ariel::Graph g;
        g.loadGraph({{10, 20, 30}, {40, 50, 60}, {70, 80, 90}});

        // Divide the graph by -2
        g /= -2;

        // Create the expected graph after division
        ariel::Graph expected;
        expected.loadGraph({{-5, -10, -15}, {-20, -25, -30}, {-35, -40, -45}});

        // Compare the adjacency matrices
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 3: Division by one (should not change the graph)
    {
        ariel::Graph g;
        g.loadGraph({{10, 20, 30}, {40, 50, 60}, {70, 80, 90}});

        // Divide the graph by 1
        g /= 1;

        // Create the expected graph after division
        ariel::Graph expected;
        expected.loadGraph({{10, 20, 30}, {40, 50, 60}, {70, 80, 90}});

        // Compare the adjacency matrices
        CHECK(g.getAdjMatrix() == expected.getAdjMatrix());
    }

    // Test 4: Division by zero (should handle gracefully, for example, by not changing the graph or throwing an exception)
    {
        ariel::Graph g;
        g.loadGraph({{10, 20, 30}, {40, 50, 60}, {70, 80, 90}});

        // Division by zero should ideally throw an exception or be handled gracefully
        CHECK_THROWS_AS(g /= 0, std::invalid_argument);
    }

    // Test 5: Division with an empty graph
    {
        ariel::Graph g;
        // Create an empty graph
        ariel::Graph empty_graph;

        // Divide the empty graph by 3
        empty_graph /= 3;

        // Compare the adjacency matrices
        CHECK(empty_graph.getAdjMatrix() == empty_graph.getAdjMatrix());
    }
}
TEST_CASE("Graph without negative cycle") {
    std::vector<std::vector<int>> matrix = {
        {0, 1, 4},
        {INT_MAX, 0, 2},
        {INT_MAX, INT_MAX, 0}
    };

    ariel::Graph g;
    g.loadGraph(matrix); // Load the graph with the adjacency matrix
    REQUIRE(Algorithms::negativeCycle(g) == 0);
}
TEST_CASE("Undirected graph without negative cycle") {
    std::vector<std::vector<int>> matrix = {
        {0, 1, INT_MAX},
        {1, 0, 2},
        {INT_MAX, 2, 0}
    };

    ariel::Graph g;
    g.loadGraph(matrix); // Load the graph with the adjacency matrix
    REQUIRE(Algorithms::negativeCycle(g) == 0);
}
TEST_CASE("Undirected graph with negative cycle") {
    std::vector<std::vector<int>> matrix = {
        {0, -1, INT_MAX},
        {-1, 0, -2},
        {INT_MAX, -2, 0}
    };

    ariel::Graph g;
    g.loadGraph(matrix); // Load the graph with the adjacency matrix
    REQUIRE(Algorithms::negativeCycle(g) == 1);
}
TEST_CASE("Graph with a single vertex and no edges") {
    std::vector<std::vector<int>> matrix = {
        {0}
    };

    ariel::Graph g;
    g.loadGraph(matrix); // Load the graph with the adjacency matrix
    REQUIRE(Algorithms::negativeCycle(g) == 0);
}