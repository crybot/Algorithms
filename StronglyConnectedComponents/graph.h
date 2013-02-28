#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <stack>
#include "node.h"

typedef std::pair<int, int> Edge;

class Graph
{
public:
    typedef std::map<int, Node> NodeMap;
    typedef NodeMap::iterator iterator;
    typedef NodeMap::reverse_iterator reverse_iterator;

    Graph(const NodeMap &);
    Graph();

    Graph Reverse();
    unsigned NodeCount() const;
    void AddNode(const Node &, int);
    void AddEdge(int, int);
    void AddEdge(Edge);
    void DeleteNode(int);
    void Merge(Edge);
    void Print();
    Node& GetNode(int);
    Node& GetNode(const iterator&);
    Node& GetNode(const reverse_iterator&);
    iterator Begin();
    iterator End();
    reverse_iterator rBegin();
    reverse_iterator rEnd();
    Edge RandomEdge();
    std::vector<int> ComputeSCC();

private:
    void DFS(int, bool);
    void DFS_Loop1();
    void DFS_Loop2(std::stack<int>&);

    int dfsLeader;
    std::stack<int> ordered;
    NodeMap nodes;
};

#endif // GRAPH_H
