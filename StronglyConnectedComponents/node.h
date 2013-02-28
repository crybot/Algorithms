#ifndef NODE_H
#define NODE_H
#include <vector>

class Node
{
public:
    typedef std::vector<int>::iterator iterator;

    Node();
    int & operator[](int a);
    unsigned Size() const;
    void InsertNeighbour(int node);
    void DeleteNeighbour(iterator it);
    iterator Begin();
    iterator End();
    void MarkExplored(bool explored);
    void SetLeader(int leader);
    void SetFinishingTime(int time);
    bool Explored();
    int Leader();
    int FinishingTime();

private:
    std::vector<int> adjacency;
    bool explored;
    int leader;
};

#endif // NODE_H
