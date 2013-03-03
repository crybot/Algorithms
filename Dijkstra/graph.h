#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <ctime>
#include <limits>
#include <map>
#include <iostream>

typedef std::pair<int, int> Edge;
typedef std::vector<int> Node;

class Graph
{
public:
    typedef std::map<int, Node> NodeMap;
    typedef NodeMap::iterator iterator;
    typedef NodeMap::reverse_iterator reverse_iterator;

    Graph(const NodeMap &);
    Graph();

    unsigned NodeCount() const;
    void AddNode(const Node &, int);
    void AddEdge(Edge, int = 0);
    void DeleteNode(int);
    void Print();
    void ShortestPath(int);
    Node& GetNode(int);
    Node& GetNode(const iterator&);
    Node& GetNode(const reverse_iterator&);
    iterator Begin();
    iterator End();
    reverse_iterator rBegin();
    reverse_iterator rEnd();

private:
    std::map<Edge, int> lengths;
    NodeMap nodes;
};

#endif // GRAPH_H
