
#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

struct Edge{
    int src, dest, weight;
};

void bellmanFord(int V, int E, const vector<Edge>& edges, int src){
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for(int i = 1; i <= V-1; ++i){
        for(int j = 0; j < E; ++j){
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;

            if(dist[u] != INT_MAX && dist[u] + weight < dist[v]){
                dist[v] = dist[u] + weight;
            }
        }
    }

    bool hasNegativeCycle = false;

    for(int j = 0; j < E; ++j){
        int u = edges[j].src;
        int v = edges[j].dest;
        int weight = edges[j].weight;

        if(dist[u] != INT_MAX && dist[u] + weight < dist[v]){
            hasNegativeCycle = true;
            break;
        }
    }

    if(hasNegativeCycle){
        cout << "\nGraph contains a negative weight cycle:";
        cout << "Shortest paths cannot be uniquely determined" << endl;
    }
    else{
        cout << "\nVertex Distance from source(" << src << "):" << endl;

        for(int i = 0; i < V; ++i){
            if(dist[i] == INT_MAX){
                cout << i << "\t" << "INF" << endl;
            }
            else{
                cout << i << "\t" << dist[i] << endl;
            }
        }
    }
}

int main(){
    int V, E;

    cout << "Enter the number of vertices:";
    cin >> V;

    cout << "Enter the number of edges:";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter edges details(source, destination, weight):" << endl;

    for(int i = 0; i < E; ++i){
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    int source;

    cout << "Enter the source vertex:";
    cin >> source;

    bellmanFord(V, E, edges, source);

    return 0;
}
