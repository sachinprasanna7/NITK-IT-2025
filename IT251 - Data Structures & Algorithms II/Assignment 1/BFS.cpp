#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <list>
#include <set>

using namespace std;

void bfs(unordered_map <int, list <int>> &adjList, unordered_map <int, bool> &visited,  vector <int> &ans, int node){

    queue <int> q;
    q.push(node);
    visited[node] = true;
    
    while (!q.empty()){
        int frontNode = q.front();
        q.pop();

        ans.push_back(frontNode);

        for(auto i : adjList[frontNode]){
            if(!visited[i]){
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

void printAdjacencyList(unordered_map <int, list<int>> &adjList){

    for(auto i : adjList){
        cout<<i.first<<" -> ";
        for(auto j : i.second){
            cout<<j<<", ";
        }
        cout<<"\n";
    }
}

vector <vector <int>> BFS (set <int> &uniqueNodes, vector <pair <int, int>> edges){
    
    vector <int> ans;
    unordered_map <int, list <int>> adjList;
    unordered_map <int, bool> visited;

    vector <vector <int>> answer;

    for(int i = 0 ; i < edges.size() ; i++){
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    cout<<"\nAdjacency List for the given edges is as follow:\n";
    printAdjacencyList(adjList);
    cout<<"\n\n";

    int component = 1;

    set<int>::iterator itr;

    cout<<"COMPONENT WISE BFS:\n\n";

    for (itr = uniqueNodes.begin(); itr != uniqueNodes.end(); itr++){
        if(!visited[*itr]){
            vector <int> ans;
            cout<<"Component Number "<<component++<<": ";
            bfs(adjList, visited, ans, *itr);

            for(int i = 0 ; i < ans.size() ; i++){
                cout<<ans[i]<<"  ";
            }
            cout<<endl;
            answer.push_back(ans);
        }
    }

    return answer;
}

bool isPresent(int edgeInitial, int edgeFinal, vector <pair <int, int>> &edges){

    for(int i = 0 ; i < edges.size() ; i++){
        if(edgeInitial == edges[i].first && edgeFinal == edges[i].second) return true;
    }
    return false;
}


int main(){

    //Carrying out BFS to a disconnected undirected graph. 

    vector <pair <int, int>> edges;

    cout<<"ENTER EDGES YOU WANT TO CONNECT ONE BY ONE:\n\n";
    cout<<"***VALID EDGES ARE ONLY INTEGERS FROM 0 TO INT_MAX***\n";
    cout<<"***ENTER -1 ON BOTH ENDS OF THE EDGE IF YOU ARE DONE INPUTTING EDGES***\n";

    int edgeInitial;
    int edgeFinal;

    cin>>edgeInitial>>edgeFinal;

    while(edgeInitial != -1 || edgeFinal != -1){

        if(edgeInitial <= -1 || edgeFinal <= -1){
            cout<<"INVALID EDGE ENTERED, RETRY!\n";
            cin>>edgeInitial>>edgeFinal;
            continue;
        }

        else if(isPresent(edgeInitial, edgeFinal, edges)){
            cout<<"EDGE IS ALREADY PRESENT!, RETRY!\n";
            cin>>edgeInitial>>edgeFinal;
            continue;
        }

        pair <int, int> edge;
        edge.first = edgeInitial;
        edge.second = edgeFinal;

        edges.push_back(edge);

        cin>>edgeInitial>>edgeFinal;
    }

    set <int> uniqueNodes;

    for(int i = 0 ; i < edges.size() ; i++){
        uniqueNodes.insert(edges[i].first);
        uniqueNodes.insert(edges[i].second);
    }

    vector <vector <int>> bfsArray = BFS(uniqueNodes, edges);

    cout<<"\nFINAL BFS: ";

    for (int i = 0; i < bfsArray.size(); i++) {
        for (int j = 0; j < bfsArray[i].size(); j++) {
            cout << bfsArray[i][j] <<" ";
        }
    }
    cout<<endl<<endl;
    
    return 0;
}