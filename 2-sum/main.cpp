#include <iostream>
#include <unordered_map>
#include <fstream>
#include <vector>
#include "../Dijkstra/stopwatch.h"


using namespace std;
typedef unordered_map<int,int> HashTable;

int main()
{
    StopWatch watch;
    HashTable table;
    ifstream file("HashInt.txt");
    vector<int> ints;
    const int min = 2500;
    const int max = 4000;
    int num;
    int c = 0;


    while(file >> num)
    {
        if (num <= max)
        {
            if (table.find(num) == table.end())
            {
                ints.push_back(num);
                table.insert(make_pair(num, num));
            }
        }
    }


    watch.Start();

    for (int t=min; t<=max; t++)
    {
        unsigned i=0;
        bool found = false;
        while(!found && i < ints.size())
        {
            if (ints[i] <= t)
            {
                int y = t-ints[i];
                if (table.find(y) != table.end() && y != ints[i])
                {
                    found = true;
                    c++;
                }
            }
            i++;
        }
    }

    cout << "Result: " << c << endl;
    cout << "Elapsed Time: " << watch.Stop().ElapsedMilliseconds() << endl;

    return  0;
}
