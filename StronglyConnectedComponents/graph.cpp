#include "graph.h"
typedef Node Node;
typedef Edge Edge;

Graph::Graph()
{
    srand (time(NULL));
}

Graph::Graph(const NodeMap & nodes)
{
    srand (time(NULL));
    this->nodes = nodes;
}

Graph Graph::Reverse()
{
    Graph Grev;
    for (Graph::iterator git = Begin(); git != End(); ++git)
    {
        Node node = GetNode(git);
        for (Node::iterator nit = node.Begin(); nit != node.End(); ++nit)
        {
            Grev.AddEdge(*nit, git->first);
        }
    }

    return Grev;
}

void Graph::AddNode(const Node & node, int index)
{
    nodes.insert(std::make_pair(index, node));
}

void Graph::AddEdge(int a, int b)
{
    if (nodes.find(a) == End())
    {
        AddNode(Node(), a);
    }

    if (nodes.find(b) == End())
    {
        AddNode(Node(), b);
    }

    GetNode(a).InsertNeighbour(b);
}

void Graph::AddEdge(Edge edge)
{
    int a = edge.first;
    int b = edge.second;

    if (nodes.find(a) == End())
    {
        AddNode(Node(), a);
    }

    if (nodes.find(b) == End())
    {
        AddNode(Node(), b);
    }

    GetNode(a).InsertNeighbour(b);
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

    for (unsigned i=0; i<B.Size(); i++) // if not references to B or self-loops add to A
    {
        if (B[i] != a && B[i] != b)
            A.InsertNeighbour(B[i]);
    }

    DeleteNode(b); // always delete B

    for (Graph::iterator git = Begin(); git != End(); ++git)
    {
        Node& node = GetNode(git);

        for (unsigned i=0; i<node.Size(); i++)
        {
            if (node[i] == b)
                node[i] = a;

            if (node[i] == git->first)
            {
                A.DeleteNeighbour(A.Begin() + i);
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
        for (unsigned l=0; l<GetNode(it).Size(); l++)
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
    r = rand() % it->second.Size();
    n_it = it->second.Begin();
    advance(n_it, r);
    b = *n_it;

    return Edge(a,b);
}

Node& Graph::GetNode(int index)
{
    return nodes[index];
}

Node& Graph::GetNode(const iterator& it)
{
    return it->second;
}

Node& Graph::GetNode(const reverse_iterator& it)
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

inline Graph::reverse_iterator Graph::rBegin()
{
    return nodes.rbegin();
}

inline Graph::reverse_iterator Graph::rEnd()
{
    return nodes.rend();
}

std::vector<int> Graph::ComputeSCC() // returns the sizes of the 5 largest Strongly connected components
{
    Graph Grev = Reverse();
    Grev.DFS_Loop1();
    DFS_Loop2(Grev.ordered);

    std::vector<int> cp = std::vector<int>(NodeCount(), 0);

    for (Graph::iterator it = Begin(); it != End(); ++it)
    {
        cp[GetNode(it).Leader()-1]++;
    }

    std::sort(cp.rbegin(), cp.rend());
    cp.resize(5);
    return cp;
}

void Graph::DFS_Loop1()
{
    dfsLeader = 0;
    for (Graph::iterator it = Begin(); it != End(); ++it)
    {
        GetNode(it).MarkExplored(false);
    }

    for (Graph::reverse_iterator it = rBegin(); it != rEnd(); ++it)
    {
        Node& node = GetNode(it);
        if(!node.Explored())
        {
            int node = it->first;
            dfsLeader = node;
            DFS(node, true);
        }
    }
}

void Graph::DFS_Loop2(std::stack<int>& nodes)
{
    dfsLeader = 0;
    for (Graph::iterator it = Begin(); it != End(); ++it)
    {
        GetNode(it).MarkExplored(false);
    }

    while (!nodes.empty())
    {
        int node = nodes.top();
        if(!GetNode(node).Explored())
        {
            dfsLeader = node;
            DFS(node, false);
        }
        nodes.pop();
    }
}

void Graph::DFS(int v, bool first)
{
    Node& node = GetNode(v);
    node.MarkExplored(true);
    node.SetLeader(dfsLeader);

    for (Node::iterator it = node.Begin(); it != node.End(); ++it)
    {
        if(!GetNode(*it).Explored())
        {
            DFS(*it, first);
        }
    }

    if(first)
        ordered.push(v);
}
