#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <list>
#include <set>

using namespace std;

// CHECK FOR CYCLIC LOOP
bool checkCycleDFS(int node, unordered_map<int, bool> &visited, unordered_map<int, bool> &dfsVisited, unordered_map<int, list<int>> &adjList)
{

    visited[node] = true;
    dfsVisited[node] = true;

    for (auto neighbour : adjList[node])
    {
        if (!visited[neighbour])
        {
            bool cycleDetected = checkCycleDFS(neighbour, visited, dfsVisited, adjList);

            if (cycleDetected)
                return true;
        }
        else if (dfsVisited[neighbour])
        {
            return true;
        }
    }

    dfsVisited[node] = false;
    return false;
}

bool detectCycleDirected(set<int> &uniqueNodes, vector<pair<int, int>> &edges)
{

    unordered_map<int, list<int>> adjList;

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].push_back(v);
    }

    unordered_map<int, bool> visited;
    unordered_map<int, bool> dfsVisited;

    set<int>::iterator itr;

    for (itr = uniqueNodes.begin(); itr != uniqueNodes.end(); itr++)
    {
        if (!visited[*itr])
        {
            bool cycleDetect = checkCycleDFS(*itr, visited, dfsVisited, adjList);
            if (cycleDetect)
                return true;
        }
    }

    return false;
}

// EDGE CLASSIFICATION

int t;
void classifyEdgeDFS(int node, vector<int> &startTime, vector<int> &endTime, vector<bool> &visited, vector<int> &traversal, unordered_map<int, list<int>> adjList)
{
    visited[node] = true;
    traversal.push_back(node);
    startTime[node] = t++;
    for (int neighbour : adjList[node])
    {
        if (!visited[neighbour])
        {
            cout << "Tree Edge: " << node << "->" << neighbour << endl;
            classifyEdgeDFS(neighbour, startTime, endTime, visited, traversal, adjList);
        }
        else
        {
            if (startTime[node] < startTime[neighbour] && endTime[node] > endTime[neighbour])
            {
                cout << "Forward Edge: " << node << "->" << neighbour << endl;
            }
            else
            {
                cout << "Cross Edge: " << node << "->" << neighbour << endl;
            }
        }
    }
    endTime[node] = t++;
}

void classifyEdges(set<int> uniqueNodes, unordered_map<int, list<int>> adjList)
{

    vector<int> startTime(uniqueNodes.size(), 0);
    vector<int> endTime(uniqueNodes.size(), 0);
    vector<bool> visited(uniqueNodes.size(), false);
    vector<int> traversal;

    set<int>::iterator itr;

    for (itr = uniqueNodes.begin(); itr != uniqueNodes.end(); itr++)
    {
        if (!visited[*itr])
        {
            classifyEdgeDFS(*itr, startTime, endTime, visited, traversal, adjList);
        }
    }
}

// DEPTH FIRST SEARCH
void dfs(int node, unordered_map<int, bool> &visited, unordered_map<int, list<int>> &adjList, vector<int> &ans)
{

    ans.push_back(node);
    visited[node] = true;

    for (auto i : adjList[node])
    {
        if (!visited[i])
        {
            dfs(i, visited, adjList, ans);
        }
    }
}

void printAdjacencyList(unordered_map<int, list<int>> &adjList)
{

    for (auto i : adjList)
    {
        cout << i.first << " -> ";
        for (auto j : i.second)
        {
            cout << j << ", ";
        }
        cout << "\n";
    }
}

vector<vector<int>> depthFirstSearch(set<int> &uniqueNodes, vector<pair<int, int>> edges)
{
    unordered_map<int, list<int>> adjList;

    for (int i = 0; i < edges.size(); i++)
    {
        int u = edges[i].first;
        int v = edges[i].second;

        adjList[u].push_back(v);
    }

    vector<vector<int>> answer;

    unordered_map<int, bool> visited;

    cout << "\nAdjacency List for the given edges is as follow:\n";
    printAdjacencyList(adjList);
    cout << "\n\n";

    int component = 1;

    cout << "EDGE CLASSIFICATION:\n";

    classifyEdges(uniqueNodes, adjList);
    set<int>::iterator itr;

    cout << "\nCOMPONENT WISE DFS:\n\n";

    for (itr = uniqueNodes.begin(); itr != uniqueNodes.end(); itr++)
    {
        if (!visited[*itr])
        {
            vector<int> ans;
            cout << "Component Number " << component++ << ": ";
            dfs(*itr, visited, adjList, ans);

            for (int i = 0; i < ans.size(); i++)
            {
                cout << ans[i] << "  ";
            }
            cout << endl;
            answer.push_back(ans);
        }
    }

    return answer;
}

bool isPresent(int edgeInitial, int edgeFinal, vector<pair<int, int>> &edges)
{

    for (int i = 0; i < edges.size(); i++)
    {
        if (edgeInitial == edges[i].first && edgeFinal == edges[i].second)
            return true;
    }
    return false;
}

int main()
{

    // Carrying out DFS to a Directed Acyclic Graph (DAG)

    vector<pair<int, int>> edges;

    cout << "ENTER EDGES YOU WANT TO CONNECT ONE BY ONE:\n\n";
    cout << "***VALID EDGES ARE ONLY INTEGERS FROM 0 TO INT_MAX***\n";
    cout << "***ENTER -1 ON BOTH ENDS OF THE EDGE IF YOU ARE DONE INPUTTING EDGES***\n";

    int edgeInitial;
    int edgeFinal;

    cin >> edgeInitial >> edgeFinal;

    set<int> uniqueNodes;

    while (edgeInitial != -1 || edgeFinal != -1)
    {

        if (edgeInitial <= -1 || edgeFinal <= -1)
        {
            cout << "INVALID EDGE ENTERED, RETRY!\n";
            cin >> edgeInitial >> edgeFinal;
            continue;
        }

        else if (isPresent(edgeInitial, edgeFinal, edges))
        {
            cout << "EDGE IS ALREADY PRESENT!, RETRY!\n";
            cin >> edgeInitial >> edgeFinal;
            continue;
        }

        pair<int, int> edge;
        edge.first = edgeInitial;
        edge.second = edgeFinal;

        edges.push_back(edge);

        bool detectCycle = detectCycleDirected(uniqueNodes, edges);

        if (detectCycle)
        {
            cout << "THE EDGE YOU INPUTTED WILL CAUSE A CYCLE, SO IT CANNOT BE INPUTTED.\nPLEASE RE ENTER AN EDGE:\n";
            edges.pop_back();
        }

        uniqueNodes.insert(edge.first);
        uniqueNodes.insert(edge.second);

        cin >> edgeInitial >> edgeFinal;
    }

    vector<vector<int>> dfsArray = depthFirstSearch(uniqueNodes, edges);

    cout << "\nFINAL DFS: ";

    for (int i = 0; i < dfsArray.size(); i++)
    {
        for (int j = 0; j < dfsArray[i].size(); j++)
        {
            cout << dfsArray[i][j] << " ";
        }
    }

    cout << endl;

    return 0;
}