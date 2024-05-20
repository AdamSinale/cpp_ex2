// ID: 322453689
// MAIL: adam.sinale@gmail.com

#pragma once

#include "Graph.hpp"
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <climits>

using std::cout;
using std::endl;
using std::queue;
using std::string;
using std::vector;
using std::to_string;
using namespace ariel;

namespace ariel
{

    class Algorithms
    {
    public:
        static vector<unsigned int> bfs(const Graph &graph, unsigned int start);
        static vector<unsigned int> dfs_h(const Graph &graph, unsigned int start, vector<int>& colors, vector<unsigned int>& parent);
        static vector<unsigned int> dfs(const Graph &graph, unsigned int start);
        static vector<unsigned int> bellman_ford(const Graph &graph, unsigned int start);

        static string isConnected(const Graph &graph);

        static string shortestPath(const Graph &graph, unsigned int start, unsigned int end);

        static string isContainsCycle(const Graph &graph);

        static string isBipartite(const Graph &graph);

        static string negativeCycle(const Graph &graph);
    };
}
