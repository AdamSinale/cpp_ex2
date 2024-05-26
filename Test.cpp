// ID: 3224653689
// MAIL: adam.sinale@gmail.com

#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

#define FALSE 0
#define TRUE 1

using namespace std;

vector<vector<int>> graph1, graph2, graph3, expectedGraph;
ariel::Graph g1, g2, g3, eg;

TEST_CASE("Test graph not/equal")
{
    graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1, 0);
    graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2, 0);
    CHECK((g1 == g2) == TRUE);
    CHECK((g1 != g2) == FALSE);
    graph2 = {
        {0, 2, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2, 1);
    CHECK((g1 == g2) == TRUE);
    CHECK((g1 > g2) == FALSE);
    CHECK((g1 >= g2) == TRUE);
    CHECK((g1 < g2) == FALSE);
    CHECK((g1 <= g2) == TRUE);
    CHECK((g1 != g2) == FALSE);
    graph2 = {
        {0, 0, 0},
        {-1, 0, -1},
        {0, -1, 0}};
    g2.loadGraph(graph2, 1);
    CHECK((g1 == g2) == FALSE);
    CHECK((g1 > g2) == TRUE);
    CHECK((g1 >= g2) == TRUE);
    CHECK((g1 < g2) == FALSE);
    CHECK((g1 <= g2) == FALSE);
    CHECK((g1 != g2) == TRUE);
}
TEST_CASE("Test graph bigger/smaller")
{
    graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1, 1);
    graph2 = {
        {0, 0, 0},
        {2, 0, -1},
        {0, 1, 0}};
    g2.loadGraph(graph2, 1);
    CHECK((g1 > g2) == TRUE);
    CHECK((g1 >= g2) == TRUE);
    CHECK((g1 < g2) == FALSE);
    CHECK((g1 <= g2) == FALSE);
    graph2 = {
        {0, 1, 1},
        {0, 0, 1},
        {0, 0, 0}};
    g2.loadGraph(graph2, 1);
    CHECK((g1 > g2) == TRUE);
    CHECK((g1 >= g2) == TRUE);
    CHECK((g1 < g2) == FALSE);
    CHECK((g1 <= g2) == FALSE);
    graph2 = {
        {0, 0, 0, 1},
        {0, 0, 0, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 0}};
    g2.loadGraph(graph2, 1);
    CHECK((g1 < g2) == TRUE);
    CHECK((g1 <= g2) == TRUE);
    CHECK((g1 > g2) == FALSE);
    CHECK((g1 >= g2) == FALSE);
}

TEST_CASE("Test graph addition/subtraction")
{
    graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1, 0);
    graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2, 0);
    g3 = g1 + g2;
    expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    eg.loadGraph(expectedGraph, 0);
    CHECK((g3).equal(eg) == TRUE);
    CHECK((g2).equal(eg-g1) == TRUE);
    CHECK((g1).equal(eg-g2) == TRUE);
    CHECK((g2*0).equal(g2-g2) == TRUE);
    CHECK((g2*-1).equal(-g2) == TRUE);
    CHECK((g2).equal(+g2) == TRUE);
    CHECK((g2).equal(g2*2 - g2) == TRUE);
    expectedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    eg.loadGraph(expectedGraph, 0);
    CHECK((g1++).equal(eg) == TRUE);
    CHECK((g1).equal(eg--) == TRUE);
    CHECK((++g1).equal(eg) == TRUE);
    CHECK((--g1).equal(eg--) == TRUE);
}

TEST_CASE("Test graph multiplication")
{
    graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1, 0);
    graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2, 0);
    g3 = g1 * g2;
    expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    eg.loadGraph(expectedGraph, 1);
    CHECK((g3).equal(eg) == TRUE);
    expectedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    eg.loadGraph(expectedGraph, 0);
    CHECK((g1*2).equal(eg) == TRUE);
    CHECK((2*g1).equal(eg) == TRUE);
    CHECK((g1).equal(eg/2) == TRUE);
    g1.loadGraph(graph1, 0);
    CHECK((g1*=2).equal(eg) == TRUE);
    CHECK((g1/=2).equal(eg/2) == TRUE);
    CHECK(((3*g1)/2).equal(g1) == TRUE);     // checks 3%2=1 as we defined
    CHECK(((3*g1)/=2).equal(g1) == TRUE);
}

TEST_CASE("Prints and Invalid operations")
{
    graph1 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph1, 0);
    graph2 = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(graph2, 1);
    graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g3.loadGraph(graph3, 0);
    CHECK_THROWS(g3 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g3.loadGraph(graph3, 0);
    CHECK((g3+g3).printGraph() == "[0, 2, 0, 0, 2]\n[2, 0, 2, 0, 0]\n[0, 2, 0, 2, 0]\n[0, 0, 2, 0, 2]\n[2, 0, 0, 2, 0]\n");
    CHECK((g3-g3).printGraph() == "[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n");
    CHECK((g3-g3).printGraph() != "[0, 1, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n[0, 0, 0, 0, 0]\n");
    CHECK_THROWS(g1 + g3);
}

vector<vector<int>> graph;

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    graph = { // checks if returns true when needed
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::isConnected(g) == "1");

    graph = { // checks if returns false when needed
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::isConnected(g) == "0");

    graph = { // checks if returns false when from a certain vertex not connected 
        {0, 1, 1},
        {0, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isConnected(g) == "0");

    graph = { // checks if returns true for a circled graph
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isConnected(g) == "1");

}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    graph = { // checks if returns true when needed
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    CHECK_THROWS(Algorithms::shortestPath(g, 0, 3)); // Checks if allows going out of limits

    graph = { // checks if returns false when no path to him
        {0, 1, 1, 0},
        {1, 0, 1, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::shortestPath(g, 0, 3) == "-1");

    graph = { // checks if finds the shortest path even with more vertices and negatives
        {0, 1, 0, 2},
        {0, 0, 1, 0},
        {0, 0, 0, -1},
        {0, 0, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::shortestPath(g, 0, 3) == "0->1->2->3"); 

    graph = { // checks if returns false with negative cycle in the path
        {0, 1, 0},
        {0, 0, 1},
        {-3, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "-1");

    graph = { // checks if finds the shortest path even with a negative cycle(outside the path)
        {0, 0, -2, 0, 0},
        {0, 0, 0, 2, 3},
        {-2, 0, 0, 0, 0},
        {0, 0, -1, 0, 0},
        {0, 0, 0, -2, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::shortestPath(g, 1, 3) == "1->4->3");

    graph = { // checks if will return the shortest path with a negative and a 0 weighted cycle
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, -3},
        {1, 0, -3, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");

    graph = { // checks if returns false with negative cycle in the path
        {0, -2, 1, 0},
        {-2, 0, -1, 0},
        {1, -1, 0, 0},
        {0, 0, 0, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "-1");

    graph = { // checks if true when the path itself = 0
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, -2},
        {1, 0, -2, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");

    graph = { // the shortest path for a clique
        {0, 1, 3, 5, 8},
        {1, 0, 1, 3, 5},
        {3, 1, 0, 1, 3},
        {5, 3, 1, 0, 1},
        {8, 5, 3, 1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::shortestPath(g, 0, 4) == "0->1->2->3->4");
}

TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    graph = { // checks if returns false when no cycle in undirected
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::isContainsCycle(g) == "0");

    graph = { // checks if returns true when cycle in directed(smallest cycle)
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isContainsCycle(g) == "The cycle is 0->1->0");

    graph = { // checks if returns true when cycle in undrected graph with more unincluded vertices
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::isContainsCycle(g) == "The cycle is 0->1->2->0");

    graph = { // checks if returns false in directed graph without a cycle
        {0, 0, -1},
        {1, 0, 2},
        {0, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isContainsCycle(g) == "0");

    graph = { // I consider a directed graph with 2 edges a cycle
        {0, 0, 0},
        {0, 0, -1},
        {0, 1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isContainsCycle(g) == "The cycle is 1->2->1");

    graph = { // checks if returns a negative cycle as well
        {0, 0, 1},
        {-5, 0, 0},
        {0, 2, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isContainsCycle(g) == "The cycle is 0->2->1->0");
}

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    graph = { // checks if returns true when there is a bipartite
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite A={0, 2}, B={1}");

    graph = { // checks if returns false when there is no bipartite
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::isBipartite(g) == "0");

    graph = { // checks if true when bipatite graph with a 2 directed edge
        {0, 1, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite A={0, 2, 4}, B={1, 3}");

    graph = { // hecks if false when an odd cycle
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isBipartite(g) == "0");

    graph = { // hecks if true when an even cycle
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite A={0, 2}, B={1, 3}");
}

TEST_CASE("Test NegativeCycle")
{
    ariel::Graph g;
    graph = { // Directed graph with a negative cycle
        {0, 0, 0, 1, 0},
        {-3, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::negativeCycle(g) == "The negative cycle is 0->3->1->0");

    graph = { // Directed graph without a negative cycle
        {0, -1, 2, 0},
        {0, 0, 0, -1},
        {0, 0, 0, -1},
        {0, 0, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::negativeCycle(g) == "No negative cycle found");
    
    graph = { // Undirected graph without a negative cycle
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::negativeCycle(g) == "No negative cycle found");

    graph = { // Undirected graph with a negative cycle
        {0, -1, 0, 4},
        {-1, 0, 3, 0},
        {0, 3, 0, -7},
        {4, 0, -7, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::negativeCycle(g) == "The negative cycle is 0->1->2->3->0");

    graph = { // Undirected graph with a negative cycle (not from 0)
        {0, 0, 0, 0},
        {0, 0, -1, -1},
        {0, -1, 0, -1},
        {0, -1, -1, 0}};
    g.loadGraph(graph, 0);
    CHECK(Algorithms::negativeCycle(g) == "The negative cycle is 1->2->3->1");

    graph = { // Undirected graph with a negative even cycle in a negative cycle(2 common vertices)
        {0, -1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, -1},
        {0, 0, 0, -1, 0, 0, 0, 0},
        {-1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, -10, 0, 0},
        {0, 0, 0, 0, 0, 0, -10, 0},
        {0, 0, 0, 0, 0, 0, 0, -10},
        {0, 0, 0, 0, -10, 0, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::negativeCycle(g) == "The negative cycle is 4->5->6->7->4");

    graph = { // Undirected graph with a negative even cycle in a negative cycle(1 common vertex)
        {0, -1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, -1, 0, 0, 0},
        {0, 0, 0, -1, 0, 0, 0, 0},
        {-1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, -10, 0, 0},
        {0, 0, 0, 0, 0, 0, -10, 0},
        {0, 0, 0, 0, 0, 0, 0, -10},
        {0, 0, 0, 0, -10, 0, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::negativeCycle(g) == "The negative cycle is 4->5->6->7->4");

    graph = { // Undirected graph with a negative odd cycle in a negative cycle(2 common vertices)
        {0, -1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, -1},
        {0, 0, 0, -1, 0, 0, 0},
        {-1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, -10, 0},
        {0, 0, 0, 0, 0, 0, -10},
        {0, 0, 0, 0, -10, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::negativeCycle(g) == "The negative cycle is 4->5->6->4");

    graph = { // Undirected graph with a negative odd cycle in a negative cycle(1 common vertex)
        {0, -1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, -1, 0, 0},
        {0, 0, 0, -1, 0, 0, 0},
        {-1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, -10, 0},
        {0, 0, 0, 0, 0, 0, -10},
        {0, 0, 0, 0, -10, 0, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::negativeCycle(g) == "The negative cycle is 4->5->6->4");

    graph = { // graph with a positive clique
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::negativeCycle(g) == "No negative cycle found");

    graph = { // graph with a negative clique
        {0, -1, -1, -1, -1},
        {-1, 0, -1, -1, -1},
        {-1, -1, 0, -1, -1},
        {-1, -1, -1, 0, -1},
        {-1, -1, -1, -1, 0}};
    g.loadGraph(graph, 1);
    CHECK(Algorithms::negativeCycle(g) == "The negative cycle is 3->4->3");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    graph = { // Invalid size (not a square matrix)
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph, 1));

    graph = { // Invalid self edge
        {0, 1, 1},
        {1, 1, 1},
        {1, 1, 0}};
    CHECK_THROWS(g.loadGraph(graph, 0));

    graph = { // Invalid undirected graph
        {0, 1, 0},
        {1, 0, 1},
        {0, 0, 0}};
    CHECK_THROWS(g.loadGraph(graph, 0));
}
