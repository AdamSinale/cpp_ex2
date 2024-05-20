// ID: 322453689
// MAIL: adam.sinale@gmail.com

#include "Graph.hpp"

namespace ariel {

    Graph::Graph() {}
    
    int Graph::getEdge(unsigned int s, unsigned int t) const {
        if (s<0 && s>=getNumV() && t < 0 && t>=getNumV()){
            return -1;
        }
        return mat[s][t]; 
    }

    void Graph::loadGraph(const vector<vector<int>> graph, int isDirected){
        if(graph.size() != graph[0].size()){
            throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        if(isDirected != 1 && isDirected != 0){
            throw std::invalid_argument("Invalid graph: Either 1 for directed or 0 for not.");
        }
        for(unsigned int i=0; i<graph.size(); i++){
            if(graph[i][i] != 0){
                throw std::invalid_argument("Invalid graph: A vertex cant have an edge with himself");
            }
        }
        if(!isDirected){
            for(unsigned int i=0; i<graph.size(); i++){
                for(unsigned int j=0; j<graph.size(); j++){
                    if(graph[j][i] != graph[i][j]){
                        throw std::invalid_argument("Invalid graph: Cant be not directed");
                    }
                }
            }
        }
        mat = graph;
        directed = isDirected;
    }

    void Graph::printGraph(){
        unsigned int numV = mat.size();
        int count = 0;
        for(unsigned int i=0; i<numV; i++){
            for(unsigned int j=0; j<numV; j++){
                if(mat[i][j] > 0){ count++; }
            }
            cout << "Graph with " << numV << " vertices and " << count << " edges." << endl;
        }
    }
}