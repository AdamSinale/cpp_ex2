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
                for(unsigned int j=i; j<graph.size(); j++){
                    if(graph[j][i] != graph[i][j]){
                        throw std::invalid_argument("Invalid graph: Cant be not directed");
                    }
                }
            }
        }
        mat = graph;
        directed = isDirected;
    }

    void Graph::check_2_graphs(const Graph& g1,const Graph& g2) const{
        if(g1.getNumV() != g2.getNumV()){ throw std::invalid_argument("graphs are not of the same size"); }
        if(g1.isDirected() != g2.isDirected()){ throw std::invalid_argument("one is directed and the other isn't"); }
    }

    string Graph::printGraph(){
        unsigned int numV = mat.size();
        string graphS = "";
        for(unsigned int i=0; i<numV; i++){
            graphS += "[";
            for(unsigned int j=0; j<numV-1; j++){
                graphS += to_string(mat[i][j]) + ", ";
            }
            graphS += to_string(mat[i][numV-1]) + "]\n";
        }
        return graphS;
    }
    std::ostream& operator<<(std::ostream& os, Graph& g) {
        os << g.printGraph();
        return os;
    }

    Graph Graph::operator+(const Graph& other) const{
        Graph main(*this);
        check_2_graphs(main, other);
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
        Graph main(*this);
        check_2_graphs(main, other);
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
    Graph Graph::operator-(const Graph& other) const{
        Graph main(*this);
        check_2_graphs(main, other);
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
        Graph main(*this);
        check_2_graphs(main, other);
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
        if(getNumV() < contained.getNumV()){ return FALSE; }
        for(unsigned i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if((getEdge(j,i) == 0 && contained.getEdge(j,i) != 0)||(getEdge(i,j) == 0 && contained.getEdge(i,j) != 0)){
                    return FALSE;
                }
            }
        }
        return TRUE;
    }
    int Graph::equal(const Graph& other) const{
        Graph main(*this);
        try{
            check_2_graphs(main, other);
            for(unsigned i=0; i<getNumV(); i++){
                for (unsigned int j=0; j<getNumV(); j++){
                    if(mat[i][j] != other.mat[i][j]){
                        return FALSE;
                    }
                }
            }
            return TRUE;
        }
        catch(std::invalid_argument){ return FALSE; }
    }
    int Graph::operator==(const Graph& other){
        Graph main(*this);
        if(getNumV() != other.getNumV()){ return FALSE; }
        for(unsigned i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if((mat[i][j]!=0 && other.mat[i][j]==0) || (mat[i][j]==0 && other.mat[i][j]!=0)
                || (mat[j][i]!=0 && other.mat[j][i]==0) || (mat[j][i]==0 && other.mat[j][i]!=0)){
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
        if(main.contains(other) == TRUE){
            if(other.contains(main) == TRUE){ return FALSE; }
            return TRUE;
        }
        if(main.getNumE() > other.getNumE()){ return TRUE; }
        if(main.getNumE() < other.getNumE()){ return FALSE; }
        if(main.getNumV() > other.getNumV()){ return TRUE; }
        return FALSE;
    }
    int Graph::operator>=(const Graph& other){
        Graph main(*this);
        if(main > other || main==other){ return TRUE; }
        return FALSE;
    }
    int Graph::operator<(const Graph& other){
        Graph main(*this);
        Graph otherG(other);
        return otherG > main;
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
    Graph Graph::operator++(int a){
        Graph temp(*this);
        return ++temp;
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
    Graph Graph::operator--(int a){
        Graph temp(*this);
        return --temp;
    }
    Graph Graph::operator*(int a) const{
        Graph newG;
        newG.loadGraph(mat, isDirected());
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(getEdge(i,j)!=0){
                    newG.mat[i][j] *= a;
                }
            }
        }
        return newG;
    }
    Graph Graph::operator*(const Graph& other){
        Graph main(*this);
        check_2_graphs(main, other);
        Graph newG;
        newG.mat.resize(getNumV(), vector<int>(getNumV(),isDirected()));
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(j != i){
                    for (unsigned int k=0; k<getNumV(); k++){
                        newG.mat[i][j] += mat[i][k]*other.mat[k][j];
                    }
                }
            }
        }
        if(isDirected() == FALSE){
            for(unsigned int i=0; i<getNumV(); i++){
                for(unsigned int j=i; j<getNumV(); j++){
                    if(newG.mat[j][i] != newG.mat[i][j]){
                        newG.loadGraph(newG.mat, TRUE);
                    }
                }
            }
        }
        return newG;
    }
    Graph& Graph::operator*=(int a) {
        for (unsigned int i = 0; i < getNumV(); i++) {
            for (unsigned int j = 0; j < getNumV(); j++) {
                if (getEdge(i, j) != 0) {
                    mat[i][j] *= a;
                }
            }
        }
        return *this;
    }
    Graph operator*(int a, const Graph& graph) {
        return graph * a; 
    }
    Graph Graph::operator/(int a) const{
        Graph newG;
        newG.loadGraph(mat, isDirected());
        for (unsigned int i=0; i<getNumV(); i++){
            for (unsigned int j=0; j<getNumV(); j++){
                if(getEdge(i,j)!=0){
                    newG.mat[i][j] /= a;
                }
            }
        }
        return newG;
    }
    Graph& Graph::operator/=(int a) {
        for (unsigned int i = 0; i < getNumV(); i++) {
            for (unsigned int j = 0; j < getNumV(); j++) {
                if (getEdge(i, j) != 0) {
                    mat[i][j] /= a;
                }
            }
        }
        return *this;
    }
}