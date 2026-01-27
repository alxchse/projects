// alexandra chase
// amchas26@g.holycross.edu
// 26 april 2024
// csci 235
// homework 6

#include<utility>
#include<map>
#include<vector>
#include<string>
#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;

/* helper function
input: vector v, item a
output: returns true if a is in v
*/
template <class NodeType>
bool contains(vector<NodeType> v, NodeType a){
    return (find(v.begin(), v.end(), a) != v.end());
}

/*
Graph class
template implementation so you can
  use this to make a graph with most 
  common item types.
  E.g., Graph<int>, Graph<string> etc.
Comment about the graph structure
  this is a lazily coded up class where client code
  has access to the Graph nodes and edge information directly.
  E.g., for a graph G, client code can directly access G.nodes
  which is a vector of nodes.
*/
template <class NodeType>
class Graph{
protected:
    /* 
    visited will contain nodes that has been visited
      in the current search. Will be cleared before every
      new search.
    */
    vector<NodeType> visited;
    /*
    keeps track of current time, useful for calculating
      pre (starting) and post (ending) times in DFS trees.
    */
    int time;

public:

    /*
    vector of all nodes
    */
    vector<NodeType> nodes;
    /*
    map is a special C++ standard data structure. AdjacencyList
      maps a node to it's list of edges. For example, if 
      edges (a,b) and (a,c) exist, AdjacencyList[a] = vector({b, c}).
    */
    map<NodeType, vector<NodeType> > AdjacencyList;

    /*
    pre, post, and distances will contain information found from
      DFS or BFS searches
    */
    map<NodeType, int> pre;
    map<NodeType, int> post;
    map<pair<NodeType, NodeType>, int> distances;

    // default constructor
    Graph(){time = 0;}
    // constructor that takes in a vector of items as input
    Graph(vector<NodeType> items){
        time = 0;
        addNodes(items);
    }

    // addNodes starts
    /*
    adds all items to the nodes vector and creates empty lists for each node
      in the adjacencyList.

    AdjacencyList[node] gives a vector that contains the neighboring nodes from node
    */
    void addNodes(vector<NodeType> items){
        for(int i = 0; i < items.size(); i++){
            cout << "Adding node: " << items[i] << endl;;
            nodes.push_back(items[i]);
            AdjacencyList.insert(make_pair(items[i], vector<NodeType>()));
        }        
    } //addNodes ends

    // addEdge starts
    /*
      input: edge start and end nodes
      postCondition: add a corresponding entry for end in
        start's adjacencyList
    */
    void addEdge(NodeType start, NodeType end){
        if(contains(nodes, start) && contains(nodes, end)){
            cout << "Inserting edge: " << start << "," << end << endl;
            AdjacencyList[start].push_back(end);
        }
    } //addEdge ends

    // preCondition: start is a valid node in the graph
    // postCondition: 
        // 1. all nodes reachable from start will be in the visited vector
        // 2. the pre and post times for all visited nodes will be updated
    void Explore(NodeType start){
        startNewSearch();
        cout << "Exploring " << start << endl;
        visited[start] = true; 
        time[start] = 1;
        pre[start] = time[start];
        for (int v = 0; v < nodes.size(); v++) {
          if (!visited[v]) { 
              Explore(v);
          }
        }
        post[start] = time[start]++; 
  
        //  if v has not been visited, visit v
        // Note: you can access the neighboring nodes from start
        //  with AdjacencyList[start]
        // AdjacencyList[start][0] gives you the first neighbor from start and so on

    } //Explore ends

    //DFS starts
    // Once Explore(start) has been implemented, this should automatically work
    void DepthFirstSearch(){
        startNewSearch();
        for (int v = 0; v < nodes.size(); v++){
            if(!inVisited(nodes[v]))
                Explore(nodes[v]);
        }
    } //DFS ends

    // BFS starts
    /*
    preCondition: start is a valid node in the graph
    postCondition: all nodes reachable from start are put into the visited vector

    Hint: 
      I suggest you to use C++'s standard queue for this. (but you can change it if you want)
      queue has functions push and pop that do the same thing as enqueue/dequeue  
    */
    void BreadthFirstSearch(NodeType start){
        startNewSearch();
        cout << "Starting from node: " << start << endl;
        queue<NodeType> Q;
        Q.push(start);
        distances[make_pair(start, start)] = 0;

        //  Hint: The distance between two nodes u, v can be accessed by
        //      distances[make_pair(u, v)]
        
        while (!Q.isEmpty()) {
            NodeType u = Q.front();
            Q.pop();
            for (int v = 0; v < AdjacencyList.size(); v++) {
                if (distances.find(make_pair(u,v)) == distances.end()) {
                    Q.push(v);
                    distances[makepair(start, v)] = distances[make_pair(start, u)] + 1;
                }
            }
        }
    } // BFS ends

    // helper function to be started at the beginning of every new search to clear
    //  all relevant variables
    void startNewSearch(){
        time = 0;
        visited.clear();
        pre.clear();
        post.clear();
        distances.clear();
    }

    // helper function to see if a node has been visited already 
    bool inVisited(NodeType u){
        return contains(visited, u);
    }

}