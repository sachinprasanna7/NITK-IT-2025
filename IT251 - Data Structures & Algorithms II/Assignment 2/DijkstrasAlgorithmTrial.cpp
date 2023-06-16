
/***************/

/*IMPORTANT: Implementation of the Fibonacci Heap was done through the #include <boost/heap/fibonacci_heap.hpp> command. 
This has to be downloaded to be able to run on a local computer. 
Hence, please run the code on onlinegdb compiler to see results.
*/


/***********/


#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <unordered_map>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <limits.h>
#include <boost/heap/fibonacci_heap.hpp>

using namespace std::chrono;
using namespace std;
using boost::heap::fibonacci_heap;
using boost::heap::compare;

struct Node{
    int node;
    int distance;

    Node(int node, int distance){
        this->node = node;
        this->distance = distance;
    }
};

struct compareNodes{
    bool operator()(const Node& a, const Node& b) const{
        return a.distance > b.distance;
    }
};


//DIJKSTRA USING SET DATA STRUCTURE 

unordered_map <int, int> dijkstraS (vector <vector <int>> &vec, int vertices, int edges, int source, set <int> &uniqueNodes){

    unordered_map <int, list < pair <int,int>>> adj;

    for(int i = 0 ; i < edges ; i++){
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];

        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    unordered_map <int, int> distance;

    for(int value : uniqueNodes){
        distance[value] = INT_MAX;
    }

    set <pair <int, int>> setDS;

    distance[source] = 0;

    setDS.insert(make_pair(0, source));

    while(!setDS.empty()){

        auto top = *(setDS.begin());

        int nodeDistance = top.first;
        int topNode = top.second;

        setDS.erase(setDS.begin());

        for(auto neighbour : adj[topNode]){

            if(nodeDistance + neighbour.second < distance[neighbour.first]){

                auto record = setDS.find(make_pair(distance[neighbour.first], neighbour.first));

                if(record != setDS.end()){
                    setDS.erase(record);
                }

                distance[neighbour.first] = nodeDistance + neighbour.second;

                setDS.insert(make_pair(distance[neighbour.first], neighbour.first));
            }
        }
    }

    return distance;

}

//DIJKSTRA USING VECTOR DATA STRUCTURE

unordered_map<int, int> dijkstraV(vector<vector<int>>& vec, int vertices, int edges, int source, set <int>& uniqueNodes) {
    unordered_map<int, list<pair<int, int>>> adj;
    for (int i = 0; i < edges; i++) {
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    unordered_map<int, int> distance;
    for (int value : uniqueNodes) {
        distance[value] = INT_MAX;
    }

    vector<pair<int, int>> vectorDS;
    distance[source] = 0;
    vectorDS.push_back(make_pair(0, source));

    while (!vectorDS.empty()) {
        int index = 0;
        for (int i = 1; i < vectorDS.size(); i++) {
            if (vectorDS[i].first < vectorDS[index].first) {
                index = i;
            }
        }

        int nodeDistance = vectorDS[index].first;
        int topNode = vectorDS[index].second;
        vectorDS.erase(vectorDS.begin() + index);

        for (auto neighbour : adj[topNode]) {
            if (nodeDistance + neighbour.second < distance[neighbour.first]) {
                int newDist = nodeDistance + neighbour.second;
                distance[neighbour.first] = newDist;

                bool found = false;
                for (int i = 0; i < vectorDS.size(); i++) {
                    if (vectorDS[i].second == neighbour.first) {
                        vectorDS[i].first = newDist;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    vectorDS.push_back(make_pair(newDist, neighbour.first));
                }
            }
        }
    }

    return distance;
}


//DIJKSTRA USING PRIORITY QUEUE DATA STRUCTURE

unordered_map<int, int> dijkstraQ(vector<vector<int>> &vec, int vertices, int edges, int source, set<int> &uniqueNodes){

    unordered_map<int, list<pair<int, int>>> adj;

    for(int i = 0 ; i < edges ; i++){
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];

        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    unordered_map<int, int> distance;

    for(int value : uniqueNodes){
        distance[value] = INT_MAX;
    }

    distance[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push(make_pair(0, source));

    while(!pq.empty()){

        auto top = pq.top();

        int nodeDistance = top.first;
        int topNode = top.second;

        pq.pop();

        if(nodeDistance > distance[topNode]) continue;

        for(auto neighbour : adj[topNode]){

            if(nodeDistance + neighbour.second < distance[neighbour.first]){

                distance[neighbour.first] = nodeDistance + neighbour.second;

                pq.push(make_pair(distance[neighbour.first], neighbour.first));
            }
        }
    }

    return distance;

}

//DIJKSTRA USING FIBONACCI HEAP DATA STRUCTURE

unordered_map<int, int> dijkstraH(vector<vector<int>> &vec, int vertices, int edges, int source, set<int> &uniqueNodes){

    unordered_map<int, list<pair<int, int>>> adj;

    for(int i = 0 ; i < edges ; i++){
        int u = vec[i][0];
        int v = vec[i][1];
        int w = vec[i][2];

        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    }

    unordered_map<int, int> distance;

    for(int value : uniqueNodes){
        distance[value] = INT_MAX;
    }

    distance[source] = 0;

    fibonacci_heap<Node, compare<compareNodes>> pq;

    pq.push(Node(source, 0));

    while(!pq.empty()){

        Node top = pq.top();

        int nodeDistance = top.distance;
        int topNode = top.node;

        pq.pop();

        if(nodeDistance > distance[topNode]) continue;

        for(auto neighbour : adj[topNode]){

            if(nodeDistance + neighbour.second < distance[neighbour.first]){

                distance[neighbour.first] = nodeDistance + neighbour.second;

                pq.push(Node(neighbour.first, distance[neighbour.first]));
            }
        }
    }


    return distance;

}



bool isPresent(int edgeInitial, int edgeFinal, vector < vector <int>>  &vec){

    for(int i = 0 ; i < vec.size() ; i++){
        if(edgeInitial == vec[i][0] && edgeFinal == vec[i][1]) return true;
    }
    return false;
}



int generateRandom(){

    return (rand() % 25) + 1;
}

int main(){

     vector <vector <int>> vec;

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

        vector <int> edge;
        edge.push_back(edgeInitial);
        edge.push_back(edgeFinal);
        edge.push_back(weight);
        vec.push_back(edge);

        cin>>edgeInitial>>edgeFinal>>weight;
    }
    
    set <int> uniqueNodes;

    for(int i = 0 ; i < vec.size() ; i++){
        uniqueNodes.insert(vec[i][0]);
        uniqueNodes.insert(vec[i][1]);
    }


    cout<<"\nENTER START VERTEX: ";
    int started;
    cin>>started;


    //DIJSKSTRA USING SET 
    auto start = high_resolution_clock::now();

    unordered_map <int, int> mpp  = dijkstraS(vec, uniqueNodes.size(), vec.size(), started, uniqueNodes);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);


    //DIJSKSTRA USING VECTOR
    auto start1 = high_resolution_clock::now();

    unordered_map <int, int> mpp1  = dijkstraV(vec, uniqueNodes.size(), vec.size(), started, uniqueNodes);

    auto stop1 = high_resolution_clock::now();

    auto duration1 = duration_cast<microseconds>(stop1 - start1);


    //DIJSKSTRA USING PRIORITY QUEUE
    auto start2 = high_resolution_clock::now();

    unordered_map <int, int> mpp2  = dijkstraQ(vec, uniqueNodes.size(), vec.size(), started, uniqueNodes);

    auto stop2 = high_resolution_clock::now();

    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    
    
    //DIJSKSTRA USING FIBONACCI HEAP    
    auto start3 = high_resolution_clock::now();

    unordered_map <int, int> mpp3  = dijkstraH(vec, uniqueNodes.size(), vec.size(), started, uniqueNodes);

    auto stop3 = high_resolution_clock::now();

    auto duration3 = duration_cast<microseconds>(stop3 - start3);


    cout << "\nShortest Distances are as follows:\n";

    cout<<"NODE -> DISTANCE\n\n";
    for (auto itr = mpp.begin(); itr != mpp.end(); ++itr) {
        cout << itr->first << " -> " << itr->second << endl;
    }
  
    cout << "\nRuntime SET : " << duration.count() << " microseconds" << endl;
    cout << "\nRuntime VECTOR : " << duration1.count() << " microseconds" << endl;
    cout << "\nRuntime PRIORITY QUEUE : " << duration2.count() << " microseconds" << endl;
    cout << "\nRuntime FIBONACCI HEAP : " << duration3.count() << " microseconds" << endl;
    
  return 0;
}