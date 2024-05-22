// ID: 3224653689
// MAIL: adam.sinale@gmail.com

#pragma once

#include <vector>
#include <iostream>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

namespace ariel {
    class Graph {
    private:
        vector<vector<int>> mat;
        int directed;

    public:
        Graph();
        int getEdge(unsigned int s, unsigned int t) const;
        unsigned int getNumV() const{ return mat.size(); }
        int getNumE() const;
        int isDirected() const{ return directed; }
        int check_borders(unsigned int start, unsigned int end) const{ return start>=0 && end < getNumV(); }
        void loadGraph(const vector<vector<int>> graph, int isDirected);
        void check_2_graphs(const Graph& g1,const Graph& g2) const; 
        string printGraph();
        Graph operator+(const Graph& other) const;
        Graph& operator+=(const Graph& other);
        Graph operator+() const;
        Graph operator-(const Graph& other) const;
        Graph& operator-=(const Graph& other);
        Graph operator-() const;
        int contains(const Graph& contained) const;
        int operator>(const Graph& other);
        int operator>=(const Graph& other);
        int operator<(const Graph& other);
        int operator<=(const Graph& other);
        int operator==(const Graph& other);
        int operator!=(const Graph& other);
        Graph& operator++();
        Graph& operator--();
        Graph operator*(int a) const;
        Graph operator*(const Graph& other);
        friend Graph operator*(int a, const Graph& main);
        Graph& operator*=(int a);
        Graph operator/(int a) const;
        Graph& operator/=(int a);
        friend Graph operator/(int a, const Graph& main);
    };

}
