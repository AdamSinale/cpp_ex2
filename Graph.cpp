// ID: 322453689
// MAIL: adam.sinale@gmail.com

#include "Graph.hpp"

#define FALSE 0
#define TRUE 1

namespace ariel {

    Graph::Graph() {}
    
    int Graph::getEdge(unsigned int s, unsigned int t) const {
        if (s<0 && s>=getNumV() && t < 0 && t>=getNumV()){
            return -1;
        }
        return mat[s][t]; 
    }
    
    int Graph::getNumE() const {
        int count = 0;
        for(unsigned i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(getEdge(i, j) != 0){
                    count++;
                }
            }
        }
        return count;
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

    Graph& Graph::operator+(const Graph& other){
        if(getNumV() != other.getNumV() || isDirected() != other.isDirected()){ throw std::invalid_argument("graphs are not of the same size"); }
        Graph newG;
        newG.loadGraph(mat, isDirected());
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                newG.mat[i][j] += other.mat[i][j];
            }
        }
        return newG;
    }
    Graph& Graph::operator+=(const Graph& other){
        if(getNumV() != other.getNumV() || isDirected() != other.isDirected()){ throw std::invalid_argument("graphs are not of the same size"); }
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                mat[i][j] += other.mat[i][j];
            }
        }
        return *this;
    }
    Graph Graph::operator+() const{
        return *this;
    }
    Graph& Graph::operator-(const Graph& other){
        if(getNumV() != other.getNumV() || isDirected() != other.isDirected()){ throw std::invalid_argument("graphs are not of the same size"); }
        Graph newG;
        newG.loadGraph(mat, isDirected());
        for(unsigned int i=0; i<getNumV(); i++){
            for(unsigned int j=0; j<getNumV(); j++){
                newG.mat[i][j] -= other.mat[i][j];
            }
        }
        return newG;
    }
    Graph& Graph::operator-=(const Graph& other){
        if(getNumV() != other.getNumV() || isDirected() != other.isDirected()){ throw std::invalid_argument("graphs are not of the same size"); }
        for(unsigned int i=0; i<getNumV(); i++){
            for(unsigned int j=0; j<getNumV(); j++){
                mat[i][j] -= other.mat[i][j];
            }
        }
        return *this;
    }
    Graph Graph::operator-() const{
        Graph result(*this);
        for(unsigned i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                result.mat[i][j] = -mat[i][j];
            }
        }
        return result;
    }
    
    int Graph::contains(const Graph& contained) const{
        for(unsigned i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(getEdge(i,j) != contained.getEdge(i,j) && contained.getEdge(i,j) != 0){
                    return FALSE;
                }
            }
        }
        return TRUE;
    }
    int Graph::operator==(const Graph& other){
        if(getNumV() != other.getNumV() || isDirected() != other.isDirected()){ throw std::invalid_argument("graphs are not of the same size"); }
        for(unsigned i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(mat[i][j] != other.mat[i][j]){
                    return FALSE;
                }
            }
        }
        return TRUE;
    }
    int Graph::operator!=(const Graph& other){
        Graph main(*this);
        if(main == other){ return FALSE; }
        return TRUE;
    }
    int Graph::operator>(const Graph& other){
        Graph main(*this);
        if(getNumV() != other.getNumV() || isDirected() != other.isDirected()){ throw std::invalid_argument("graphs are not of the same size"); }
        if(main.contains(other) == TRUE){ return TRUE; }
        if(main.contains(other) == TRUE){ return FALSE; }
        if(main.getNumE() > other.getNumE()){ return TRUE; }
        if(main.getNumE() < other.getNumE()){ return FALSE; }
        // if(main.seder_godel() > other.seder_godel()){ reuturn TRUE; }
        return FALSE;
    }
    int Graph::operator>=(const Graph& other){
        Graph main(*this);
        if(main < other){ return FALSE; }
        return TRUE;
    }
    int Graph::operator<(const Graph& other){
        Graph main(*this);
        if(main > other || main == other){ return FALSE; }
        return TRUE;
    }
    int Graph::operator<=(const Graph& other){
        Graph main(*this);
        if(main > other){ return FALSE; }
        return TRUE;
    }
    Graph& Graph::operator++(){
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(getEdge(i,j)!=0){
                    mat[i][j]++;
                }
            }
        }
        return *this;
    }
    Graph& Graph::operator--(){
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(getEdge(i,j)!=0){
                    mat[i][j]--;
                }
            }
        }
        return *this;
    }
    Graph& Graph::operator*(int a){
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(getEdge(i,j)!=0){
                    mat[i][j] *= a;
                }
            }
        }
        return *this;
    }
    Graph Graph::operator*(const Graph& other){
        if(getNumV() != other.getNumV() || isDirected() != other.isDirected()){ throw std::invalid_argument("graphs are not of the same size"); }
        Graph newG;
        newG.mat.resize(getNumV(), vector<int>(getNumV(),0));
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                for (unsigned int k=0; k<getNumV(); k++){
                    newG.mat[i][j] += mat[i][k]*other.mat[k][j];
                }
            }
        }
        return newG;
    }
}