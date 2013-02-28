#include "node.h"

Node::Node() { }

int& Node::operator[](int a)
{
    return adjacency[a];
}

unsigned Node::Size() const
{
    return adjacency.size();
}

void Node::InsertNeighbour(int node)
{
    adjacency.push_back(node);
}

void Node::DeleteNeighbour(iterator it)
{
    adjacency.erase(it);
}

Node::iterator Node::Begin()
{
    return adjacency.begin();
}

Node::iterator Node::End()
{
    return adjacency.end();
}

void Node::MarkExplored(bool explored)
{
    this->explored = explored;
}

void Node::SetLeader(int leader)
{
    this->leader = leader;
}

bool Node::Explored()
{
    return explored;
}

int Node::Leader()
{
    return leader;
}
