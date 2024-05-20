
// ID: 322453689
// MAIL: adam.sinale@gmail.com

#include "Algorithms.hpp"
#include <limits>

#define TRUE "1"
#define FALSE "0"

#define WHITE -1
#define GRAY 0
#define BLACK 1

// #define INFINITY std::numeric_limits<int>::max()     //maximum integer posibble
#define INFINITY INT_MAX     //maximum integer posibble
namespace ariel {

    vector<unsigned int> Algorithms::bfs(const Graph& graph, unsigned int start){
        unsigned int numV = graph.getNumV();
        queue<unsigned int> q;
        vector<int> colors(numV, WHITE);
        vector<int> dist(numV, INFINITY);
        vector<unsigned int> parent(numV, UINT_MAX);
        q.push(start);
        colors[start] = GRAY;
        dist[start] = 0;
        while(!q.empty()){
            unsigned int u = q.front();
            q.pop();
            for(unsigned int v=0; v<numV; v++){
                if(graph.getEdge(u,v) != 0 && colors[v] == WHITE){
                    parent[v] = u;
                    colors[v] = GRAY;
                    q.push(v);
                }
            }
            colors[u] = BLACK;
        }
        return parent;
    }
    vector<unsigned int> Algorithms::dfs_h(const Graph& graph, unsigned int start, vector<int>& colors, vector<unsigned int>& parent){
        unsigned int numV = graph.getNumV();
        colors[start] = BLACK;
        for(unsigned int v=0; v<numV; v++){
            if(graph.getEdge(start,v) != 0 && colors[v] == WHITE){
                parent[v] = start;
                dfs_h(graph, v, colors, parent);
            }
        }
        return parent;
    }
    vector<unsigned int> Algorithms::dfs(const Graph& graph, unsigned int start){
        unsigned int numV = graph.getNumV();
        queue<unsigned int> q;
        vector<int> colors(numV, WHITE);
        vector<unsigned int> parent(numV, UINT_MAX);
        return dfs_h(graph, start, colors, parent);
    }
    vector<unsigned int> Algorithms::bellman_ford(const Graph& graph, unsigned int start){
        unsigned int numV = graph.getNumV();
        vector<int> dist(numV, INFINITY);
        vector<unsigned int> parent(numV, UINT_MAX);
        dist[start] = 0;
        for(unsigned int u=0; u<numV-1; u++){
            for(unsigned int i=0; i<numV; i++){
                for(unsigned int j=0; j<numV; j++){
                    if(dist[j] > dist[i] + graph.getEdge(i,j)){
                        dist[j] = dist[i] + graph.getEdge(i,j);
                        parent[j] = i;
                    }
                }
            }
        }
        for(unsigned int i=0; i<numV; i++){
            for(unsigned int j=0; j<numV; j++){
                if(dist[j] > dist[i] + graph.getEdge(i,j)){
                    vector<unsigned int> parent(numV, UINT_MAX);
                    return parent;
                }
            }
        }
        return parent;
    }
    
    string Algorithms::isConnected(const Graph& graph){
        unsigned int numV = graph.getNumV();
        for(unsigned int i=0; i<numV; i++){
            vector<unsigned int> parent = bfs(graph, i);
            for(unsigned int j=0; j<numV; j++){
                if(i != j && parent[j] == UINT_MAX){ return FALSE; }
            }
        }
        return TRUE;
    }

    string Algorithms::shortestPath(const Graph& graph, unsigned int start, unsigned int end){
        if(!graph.check_borders(start, end)){
            throw std::invalid_argument("Invalid vertex: start/end out of range.");
        }
        unsigned int numV = graph.getNumV();
        vector<int> dist(numV, INFINITY);
        vector<unsigned int> parent(numV, UINT_MAX);
        dist[start] = 0;
        for(unsigned int u=0; u<numV-1; u++){
            for(unsigned int i=0; i<numV; i++){
                for(unsigned int j=0; j<numV; j++){
                    if(graph.getEdge(i,j)!=0 && dist[j]>dist[i]+graph.getEdge(i,j)){
                        if(!graph.isDirected() && parent[i] == j){ continue; }
                        dist[j] = dist[i] + graph.getEdge(i,j);
                        parent[j] = i;
                    }
                }
            }
        }
        if(parent[end] == UINT_MAX){ return "-1"; }

        for(unsigned int i=0; i<numV; i++){
            for(unsigned int j=0; j<numV; j++){
                if(!graph.isDirected() && parent[i] == j){ continue; }
                if(graph.getEdge(i,j)!=0 && dist[i]!=INFINITY && dist[j]>dist[i]+graph.getEdge(i,j)){
                    unsigned int cur = parent[end];
                    while(cur != start){ 
                        if (j == cur){ return "-1"; } 
                        cur = parent[cur];
                    }
                }
            }
        }
        unsigned int cur = end;
        string path = to_string(cur);
        while(parent[cur] != UINT_MAX){
            path = to_string(parent[cur]) + "->" + path;
            cur = parent[cur];
        }
        return path;
    }

    string Algorithms::isContainsCycle(const Graph& graph){
        unsigned int numV = graph.getNumV();
        for(unsigned int u=0; u<numV; u++){
            vector<unsigned int> parent = dfs(graph, u);
            for(unsigned int v=0; v<numV; v++){ // for every neighbor with a path to him but not direct
                if(graph.getEdge(v,u) != 0 && parent[v] != UINT_MAX && (parent[v] != u || graph.isDirected())){
                    unsigned int cur = v;
                    string path = to_string(cur); // start from end
                    while(parent[cur] != UINT_MAX){  // until we get to first
                        path = to_string(parent[cur]) + "->" + path;  // add to path
                        cur = parent[cur];
                    }
                    path += "->" + to_string(u);
                    return "The cycle is " + path;
                }
            }
        }
        return "0";
    }

    string Algorithms::isBipartite(const Graph& graph){
        unsigned int numV = graph.getNumV();
        queue<unsigned int> q;
        vector<int> colors(numV, WHITE);
        vector<int> groups(numV, -1);
        for(unsigned int i=0; i<numV; i++){
            if(colors[i] == WHITE){
                groups[i] = 0;
                q.push(i);
                colors[i] = GRAY;
                while(!q.empty()){
                    unsigned int u = q.front();
                    q.pop();
                    for(unsigned int v=0; v<numV; v++){
                        if(graph.getEdge(u,v) != 0){
                            if(colors[v] == WHITE){
                                groups[v] = !groups[u];
                                colors[v] = GRAY;
                                q.push(v);
                            } else if(v != u && groups[v] == groups[u]){ return "0"; }
                        }
                    }
                    colors[u] = BLACK;
                }
            }
        }
        string A = "";
        string B = "";
        for(unsigned int i=0; i<numV; i++){
            if(groups[i] == 0){ 
                if (A.empty()) { A += to_string(i); }
                else{ A += ", " + to_string(i); }
            }
            else{ 
                if (B.empty()) { B += to_string(i); }
                else{ B += ", " + to_string(i); }
            }
        }
        return "The graph is bipartite A={"+A+"}, B={"+B+"}";
    }

    string Algorithms::negativeCycle(const Graph& graph){
        unsigned int numV = graph.getNumV();
        vector<int> dist(numV, INFINITY);
        vector<unsigned int> parent(numV, INFINITY);

        for(unsigned int v=0; v<numV; v++){
            if(dist[v] == INFINITY){
                dist[v] = 0;
                for(unsigned int u=0; u<numV-1; u++){
                    for(unsigned int i=0; i<numV; i++){
                        for(unsigned int j=0; j<numV; j++){
                            if(graph.getEdge(i,j)!=0 && dist[j]>dist[i]+graph.getEdge(i,j)){
                                if(!graph.isDirected() && parent[i] == j){ continue; }
                                dist[j] = dist[i] + graph.getEdge(i,j);
                                parent[j] = i;
                            }
                        }
                    }
                }
                for(unsigned int i=0; i<numV; i++){
                    for(unsigned int j=0; j<numV; j++){
                        if(!graph.isDirected() && parent[i] == j){ continue; }
                        if(graph.getEdge(i,j)!=0 && dist[i]!=INFINITY && dist[j]>dist[i]+graph.getEdge(i,j)){
                            vector<int> visited(numV, 0);
                            dist[j] = dist[i] + graph.getEdge(i,j);
                            parent[j] = i;
                            string path = to_string(i); // start from end
                            unsigned int cur = parent[i];
                            int for_2nd_visit =0;
                            while(cur != i){  // until we get to first
                                path = to_string(cur) + "->" + path;  // add to path
                                visited[cur] = 1;
                                cur = parent[cur];
                                if(visited[cur] && !for_2nd_visit){
                                    for_2nd_visit = 1;
                                    path = to_string(parent[cur]);
                                    i = parent[cur];
                                    // return to_string(parent[parent[parent[i]]])+"->"+to_string(parent[parent[i]])+"->"+to_string(parent[i])+"->"+to_string(i);
                                }
                            }
                            path = to_string(i) + "->" + path;
                            return "The negative cycle is " + path;
                        }
                    }
                }
            }
        }
        return "No negative cycle found";
    }
}
