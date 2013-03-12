#include <iostream>
#include <string>
#include <fstream>
#include "graph.h"
#include "stopwatch.h"

using namespace std;


pair<int,int> Split(string str)
{
    pair<int,int> tuple;
    string str2 = "";

    unsigned i=str.find_first_of(',');
    str2.append(str, i+1, str.size());
    str.erase(i, str.size());
    tuple.first = atoi(str.c_str());
    tuple.second = atoi(str2.c_str());

    return tuple;
}

vector<string> Tokenize(const string & str)
{
    vector<string> tokens;
    string token = "";

    for(unsigned i=0; i<str.size(); i++)
    {
        if (isspace(str[i]))
        {
            if(!token.empty())
                tokens.push_back(token);
            token = "";
        }
        else
            token += str[i];
    }
    if (token.size() > 1)
        tokens.push_back(token);

    return tokens;
}

int main()
{
    int vertex;
    string str;
    Graph InitialGraph;
    pair<int, int> tuple;
    vector<string> tokens;
    StopWatch watch;

    ifstream ff("dijkstraData.txt");

    while(ff.good())
    {
        getline(ff, str);
        tokens = Tokenize(str);
        vertex = atoi(tokens[0].c_str());
        for (unsigned i = 1; i<tokens.size(); i++)
        {
            tuple = Split(tokens[i]);
            InitialGraph.AddEdge(Edge(vertex, tuple.first), tuple.second);
        }
    }
    ff.close();

    watch.Start();

    InitialGraph.ShortestPath(1);

    watch.Stop();

    cout << "Tempo impiegato: " << watch.ElapsedMilliseconds() << endl;

//    clock_t end = clock();
//    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
//    cout << "Tempo impiegato: " << elapsed_secs << endl;

    return 0;
}
