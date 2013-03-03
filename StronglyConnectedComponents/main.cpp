#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "graph.h"
using namespace std;

Edge Split(string & str)
{
    Edge edge;
    string str2 = "";

    unsigned i=str.find_first_of(' ');
    str2.append(str, i+1, str.size());
    str.erase(i, str.size());
    edge.first = atoi(str.c_str());
    edge.second = atoi(str2.c_str());

    return edge;
}

int main()
{
    string str;
    Graph InitialGraph;

    ifstream ff("SCC.txt");

    while(ff.good())
    {
        getline(ff, str);
        InitialGraph.AddEdge(Split(str));
    }
    ff.close();

    vector<int> SCCs = InitialGraph.ComputeSCC();

    cout << "Compoments: " << endl;
    for (unsigned i=0; i<SCCs.size(); i++)
    {
        cout << SCCs[i] << " ";
    }

    return 0;
}
