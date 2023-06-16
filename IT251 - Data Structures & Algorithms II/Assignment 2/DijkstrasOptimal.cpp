#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <unordered_map>
#include <chrono>
#include <set>
#include <limits.h>

using namespace std::chrono;

using namespace std;

unordered_map<int, int> dijkstra(vector<vector<int>> &vec, int vertices, int edges, int source, set<int> &uniqueNodes){

    unordered_map<int, list<pair<int, int>>> adj;

    for(int i = 0 ; i < edges ; i++){
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];

        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    unordered_map<int, int> dist;

    for(int value : uniqueNodes){
        dist[value] = INT_MAX;
    }

    dist[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push(make_pair(0, source));

    while(!pq.empty()){

        auto top = pq.top();

        int nodeDistance = top.first;
        int topNode = top.second;

        pq.pop();

        if(nodeDistance > dist[topNode]) continue;

        for(auto neighbour : adj[topNode]){

            if(nodeDistance + neighbour.second < dist[neighbour.first]){

                dist[neighbour.first] = nodeDistance + neighbour.second;

                pq.push(make_pair(dist[neighbour.first], neighbour.first));
            }
        }
    }

    cout<<"\n\nADJACENCY LIST OF GRAPH (NODE -> {NODE,WEIGHT}\n\n";
    
    for (auto const& [edgeInitial, value] : adj) {
        cout << edgeInitial << " -> ";
        for (auto const& [edgeFinal, weight] : value) {
            cout << "{" << edgeFinal << ", " << weight << "}, ";
        }
        cout<<endl;
    }

    return dist;

}

bool isPresent(int edgeInitial, int edgeFinal, vector<vector<int>> &vec){

    for(int i = 0 ; i < vec.size() ; i++){
        if(edgeInitial == vec[i][0] && edgeFinal == vec[i][1]) return true;
    }
    return false;
}

int main(){

     vector<vector<int>> vec;

    cout<<"ENTER EDGES YOU WANT TO CONNECT ONE BY ONE:\n\n";
    cout<<"***VALID EDGES ARE ONLY INTEGERS FROM 0 TO INT_MAX***\n";
    cout<<"FORMAT IS -> \"edgeStart edgeEnd weightOfEdge\"\n";
    cout<<"***ENTER -1 ON BOTH ENDS OF THE EDGE IF YOU ARE DONE INPUTTING EDGES***\n";


    int edgeInitial;
    int edgeFinal;
    int weight;

    cin>>edgeInitial>>edgeFinal>>weight;

    while(edgeInitial != -1 || edgeFinal != -1){

        if(edgeInitial <= -1 || edgeFinal <= -1){
            cout<<"INVALID EDGE ENTERED, RETRY!\n";
            cin>>edgeInitial>>edgeFinal;
            continue;
        }

        else if(isPresent(edgeInitial, edgeFinal, vec)){
            cout<<"EDGE IS ALREADY PRESENT!, RETRY!\n";
            cin>>edgeInitial>>edgeFinal;
            continue;
        }

        vector<int> edge;
        edge.push_back(edgeInitial);
        edge.push_back(edgeFinal);
        edge.push_back(weight);
        vec.push_back(edge);

        cin>>edgeInitial>>edgeFinal>>weight;
    }

    set<int> uniqueNodes;

    for(int i = 0 ; i < vec.size() ; i++){
        uniqueNodes.insert(vec[i][0]);
        uniqueNodes.insert(vec[i][1]);
    }

    int startVertex;
    cout<<"\nEnter Staring Vertex: ";
    cin>>startVertex;

    unordered_map<int, int> mpp  = dijkstra(vec, uniqueNodes.size(), vec.size(), startVertex, uniqueNodes);

    cout << "\nShortest Distances are as follows:\n";

    cout<<"NODE -> DISTANCE\n\n";
    for (auto itr = mpp.begin(); itr != mpp.end(); ++itr) {
        cout << itr->first << " -> " << itr->second << endl;
    }


  return 0;
}