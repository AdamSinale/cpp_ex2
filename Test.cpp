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
    g1.loadGraph(graph1, 1);
    graph2 = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2, 1);
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
        {0, -1, 0},
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
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g2.loadGraph(graph2, 0);
    CHECK_THROWS(g1 == g2);
    CHECK_THROWS(g1 != g2);
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
    CHECK((g3 == eg) == TRUE);
    CHECK((g2 == eg-g1) == TRUE);
    CHECK((g1 == eg-g2) == TRUE);
    CHECK((g2*0 == g2-g2) == TRUE);
    CHECK((g2*-1 == -g2) == TRUE);
    CHECK((g2 == g2*2 - g2) == TRUE);
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
    CHECK((g3 == eg) == TRUE);
    expectedGraph = {
        {0, 2, 0},
        {2, 0, 2},
        {0, 2, 0}};
    eg.loadGraph(expectedGraph, 0);
    CHECK((g1*2 == eg) == TRUE);
    CHECK((g1 == eg/2) == TRUE);
}

TEST_CASE("Invalid operations")
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
    CHECK_THROWS(g1 + g3);
}