// ID: 3224653689
// MAIL: adam.sinale@gmail.com

#pragma once

#include <vector>
#include <iostream>

using std::vector;
using std::cout;
using std::endl;

namespace ariel {
    class Graph {
    private:
        vector<vector<int>> mat;
        int directed;

    public:
        Graph();
        int getEdge(unsigned int s, unsigned int t) const;
        unsigned int getNumV() const{ return mat.size(); }
        int isDirected() const{ return directed; }
        int check_borders(unsigned int start, unsigned int end) const{ return start>=0 && end < getNumV(); }
        void loadGraph(const vector<vector<int>> graph, int isDirected);
        void printGraph();
        Graph& operator+(const Graph& other);
        Graph& operator+=(const Graph& other);
        Graph operator+() const;
        Graph& operator-(const Graph& other);
        Graph& operator-=(const Graph& other);
        Graph operator-() const;
        int contains(const Graph& contained) const;
        int operator>(const Graph& other);
        int operator>=(const Graph& other);
        int operator<(const Graph& other);
        int operator<=(const Graph& other);
        int operator=(const Graph& other);
        int operator!=(const Graph& other);
        Graph& operator++();
        Graph& operator--();
        Graph& operator*(int a);
        Graph operator*(const Graph& other);
    };
}
