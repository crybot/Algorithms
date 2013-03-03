#include "graph.h"
typedef Graph::Node Node;
typedef Graph::Edge Edge;

Graph::Graph()
{
    srand (time(NULL));
}

Graph::Graph(const NodeMap & nodes)
{
    srand (time(NULL));
    this->nodes = nodes;
}

void Graph::AddNode(const Node & node, int index)
{
    nodes.insert(std::make_pair(index, node));
}

void Graph::DeleteNode(int index)
{
    nodes.erase(index);
}

unsigned Graph::NodeCount() const
{
    return nodes.size();
}

void Graph::Merge(Edge edge)
{
    int a = edge.first, b = edge.second;
    Node& A = GetNode(a);
    Node& B = GetNode(b);

    for (unsigned i=0; i<B.size(); i++) // if not references to B or self-loops add to A
    {
        if (B[i] != a && B[i] != b)
            A.push_back(B[i]);
    }

    DeleteNode(b); // always delete B

    for (Graph::iterator git = Begin(); git != End(); ++git)
    {
        Node& node = GetNode(git);

        for (unsigned i=0; i<node.size(); i++)
        {
            if (node[i] == b)
                node[i] = a;

            if (node[i] == git->first)
            {
                A.erase(A.begin() + i);
                i--;
            }
        }
    }
}

void Graph::Print()
{
    for(Graph::iterator it = Begin(); it != End(); ++it)
    {
        std::cout << it->first << " : ";
        for (unsigned l=0; l<GetNode(it).size(); l++)
        {
            std::cout << GetNode(it)[l] << " ";
        }
        std::cout << std::endl;
    }
}

Edge Graph::RandomEdge()
{
    int a,b;
    Graph::iterator it;
    Node::iterator n_it;
    int r;

    it = Begin();
    r = rand() % NodeCount();
    advance(it, r);
    a = it->first;
    r = rand() % it->second.size();
    n_it = it->second.begin();
    advance(n_it, r);
    b = *n_it;

    return Edge(a,b);
}

Node& Graph::GetNode(int index)
{
    return nodes[index];
}

Node& Graph::GetNode(iterator it)
{
    return it->second;
}

inline Graph::iterator Graph::Begin()
{
    return nodes.begin();
}

inline Graph::iterator Graph::End()
{
    return nodes.end();
}
