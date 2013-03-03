#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <iostream>

class Graph
{
public:
    typedef std::vector<int> Node;
    typedef std::pair<int,int> Edge;
    typedef std::map<int, Node> NodeMap;
    typedef NodeMap::iterator iterator;

    Graph(const NodeMap &);
    Graph();


    unsigned NodeCount() const;
    void AddNode(const Node &, int index);
    void DeleteNode(int);
    void Merge(Edge);
    void Print();
    Node& GetNode(int);
    Node& GetNode(iterator);
    iterator Begin();
    iterator End();
    Edge RandomEdge();

private:
    NodeMap nodes;
};

#endif // GRAPH_H
