#include <iostream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <queue>
#include <list>
using namespace std;



class Graph{    //Creation of an Undirected Graph using the Graph Class

    public:
    int edges = 0;
    int nodes = 0;
    int components = 0;
    map<int, list<int>> adjacencyList;
    list <int> nodeArray;

    void Add(int i, int j){ 
        if(i == j)   adjacencyList[i].push_back(j);    //Condition for the disconnected node. We dont add an edge because it is isolated
        
        else{           //Adds an edge between the specified Nodes.
        adjacencyList[i].push_back(j);
        adjacencyList[j].push_back(i);
        edges++;
        }
    }

    void print(){                         //Prints the Graph in Adjacency list form
        for(auto i : adjacencyList){
            cout<<i.first<<" -> ";
            for(auto j : i.second){
                cout<<j<<", ";
            }
            cout<<"DONE\n";
        }
    }

    int getEdges(){                  //Returns total edges present in Graph
        return edges;
    }

    int getNodes(){                 //Returns total nodes present in Graph

        for(auto i : adjacencyList) nodes++;
        return nodes;
    }

    void initialiseNodeArray(){     //Initialises an list which stores all the Nodes
        if(nodeArray.empty()){
            for(auto i : adjacencyList){
                nodeArray.push_back(i.first);
            }
            return;
        }
        else return;
    }

    void printNodes(){               //Prints all the nodes/vertices present in the map
        initialiseNodeArray();
        for (auto element : nodeArray) {
            cout <<element<<endl;
        }
    }


    /*The following Breadth First Search takes the first element of the Adjacency list map as the starting vertex.
    From there on, the vertex's are traversed in the same order they are inserted into the list(which stores all the 
    vertices which the selected vertex is in contact with.
    And then, these vertices in the list are searched one by one.
    NOTE - By node and vertex I mean the same.
    )*/

    void bfs(map<int,list<int>> &adjacencyList, map<int,bool> &visited, list <int> &answer, int node){

        queue <int> q;
        q.push(node);
        visited[node] = true;

        while(!q.empty()){
            int front = q.front();
            q.pop();

            answer.push_back(front);

            for(auto i : adjacencyList[front]){
                if(!visited[i]){
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    list <int> BFS(int nodes){
        list<int> answer;
        map <int,bool> visited;

        for(auto i : adjacencyList){
            if(!visited[i.first]){
                components++;    //Each time this loop is entered. it signifies the graph is disconnected. So components is increased.
                bfs(adjacencyList, visited, answer, i.first);
            }
        }
        return answer;
    }

    int getComponents(){
        return components;
    }
};

bool isFound(int arr[], int key, int n){

    for(int i = 0; i < n ; i++){
        if(arr[i] == key)
            return true;
    }
    return false;
}


int main(){

    Graph g;

    /*Generating 25 Distinct Random Nodes (between 1 to 100, so that we dont get abnormally large or small numbers as nodes) 
    and storing them in an array*/

    srand(time(nullptr));
    int randomNodes[25];
    for(int i = 0; i < 25; i++){
        int node;
        do{
            node = rand()%101;
        } while(isFound(randomNodes, node, i));
        randomNodes[i] = node;   
    }

    /*The Node that will make the Graph DEFINETELY disconnected is the first node of randomNodes array, 
    and no edge will be added to that node*/

    int disconnectedNode = randomNodes[0];

    /*This loop is to connect each of the other 24 nodes with another random node (except, the first node of the randomNodes array
    so that the Graph remains disconnected)*/

    int ctr = 1;
    while(ctr < 25){
        int nodeToBeConnected = rand()%101;
        if(nodeToBeConnected != randomNodes[ctr] && nodeToBeConnected != disconnectedNode){
            g.Add(randomNodes[ctr],nodeToBeConnected);
            ctr++;
        }
    }

    /*Now, 24 Edges have been added to the Graph and there are ATLEAST 25 nodes in the graph*/
    /*Adding another more edges, to satisfy the question condition of more than 100 or 100 edges*/

    while(ctr < 105){
        int nodeToBeConnected_1 = rand()%101;
        int nodeToBeConnected_2 = rand()%101;
        if(nodeToBeConnected_1 != disconnectedNode && nodeToBeConnected_2 != disconnectedNode){
            g.Add(nodeToBeConnected_1,nodeToBeConnected_2);
            ctr++;
        }
    }

    g.Add(disconnectedNode,disconnectedNode);      //Adding the disconnected node to the graph

    /*This method GUARANTEES that atleast one node WILL BE DISCONNECTED. There can be more disconnections based on the random nodes 
    and edges generated.*/

    cout<<"\n\nThe Adjacency List of the graph is:\n\n";

    g.print();

    cout<<"\n\nNODES IN GRAPH : "<<g.getNodes();
    cout<<"\n\nEDGES IN GRAPH : "<<g.getEdges();
    cout<<"\n\nDEFINETELY DISCONNECTED NODE OF THE GRAPH: "<<disconnectedNode;

    list <int> ans = g.BFS(g.getNodes());    //Storing the BFS of the graph
    cout<<"\n\nThe Breadth First Search of the Graph is (Vertex order):\n\n";
    for (auto element : ans){
        cout <<element<<", ";
    }
    
    cout<<"\n\nNumber of Components in Graph: "<<g.getComponents()<<endl<<endl;
    cout<<"**PROGRAM OVER**";

    return 0;
}