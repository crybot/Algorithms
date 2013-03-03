#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include "graph.h"
using namespace std;

void Split(vector<int> &arr, const string & str)
{
    bool first = true;
    string temp = "";

    for(size_t i=0; i<str.size(); i++)
    {
        if (str[i] == ' ' || str[i] == '\t')
        {
            if (first)
                first = false;
            else
                arr.push_back(atoi(temp.c_str()));
            temp = "";
        }
        else
            temp += str[i];

        if (i == str.size()-1)
        {
            arr.push_back(atoi(temp.c_str()));
        }
    }
}

int main()
{
    string str;
    Graph InitialGraph;

    ifstream ff("kargerMinCut.txt");

    int i = 1;
    int min = 32767;
    while(ff.good())
    {
        Graph::Node node;
        getline(ff, str);
        Split(node, str);
        InitialGraph.AddNode(node, i++);
    }

    for (int i=0; i<100; i++)
    {

        Graph graph = InitialGraph;

        while(graph.NodeCount() > 2)
        {
            Graph::Edge edge = graph.RandomEdge();
            graph.Merge(edge);
        }

        if (graph.Begin()->second.size() < min)
            min = graph.Begin()->second.size();

    }


    cout << endl << endl << "Minimum cut: " << min << endl;

    return 0;
}
