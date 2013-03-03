#include "graph.h"
typedef std::pair<int,int> pairInt;

Graph::Graph()
{

}

Graph::Graph(const NodeMap & nodes)
{
    this->nodes = nodes;
}

void Graph::AddNode(const Node & node, int index)
{
    nodes.insert(std::make_pair(index, node));
}

void Graph::AddEdge(Edge edge, int length)
{
    int a = edge.first;
    int b = edge.second;

    if (nodes.find(a) == End())
        AddNode(Node(), a);

    if (nodes.find(b) == End())
        AddNode(Node(), b);

    GetNode(a).push_back(b);

    lengths.insert(std::make_pair(edge, length));
}

void Graph::DeleteNode(int index)
{
    nodes.erase(index);
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

void Graph::ShortestPath(int source)
{
    int path, min, W, V;
    std::vector<int> X;
    int *Xutil = new int[NodeCount()+1];
    int *A = new int[NodeCount()+1];

    X.reserve(NodeCount());
    X.push_back(source);
    A[source] = 0;

    for (unsigned i=0; i<NodeCount(); i++)
        Xutil[i] = 0;

    Xutil[source] = 1;

    while(X.size() != NodeCount())
    {
        min = std::numeric_limits<int>::max();
        path = false;
        for (std::vector<int>::iterator it = X.begin(); it != X.end(); ++it)
        {
            int v = *it;
            Node node = GetNode(v);

            for (unsigned l=0; l<node.size(); l++)
            {
                int w = node[l];
                if (Xutil[w] != 1)
                {
                    Edge vw = pairInt(v,w);
                    int score = A[v] + lengths[vw];

                    if (score < min)
                    {
                        path = true;
                        min = score;
                        W = w;
                        V = v;
                    }
                }
            }
        }

        if (path)
        {
            A[W] = A[V] + lengths[pairInt(V, W)];
            X.push_back(W);
            Xutil[W] = 1;
        }
        else
        {
            for (Graph::iterator it = Begin(); it != End(); ++it)
            {
                int node = it->first;
                if (Xutil[node] != 1)
                {
                    A[node] = 1000000;
                    X.push_back(node);
                    Xutil[node] = 1;
                }
            }
        }
    }

    int B[] = {7,37,59,82,99,115,133,165,188,197};
    for (int i=0; i<10; i++)
    {
        std::cout << A[B[i]] << " ";
    }
    std::cout << std::endl;
}

unsigned Graph::NodeCount() const
{
    return nodes.size();
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
