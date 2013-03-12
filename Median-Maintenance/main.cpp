#include <iostream>
#include <queue>
#include <fstream>
#include <cmath>
using namespace std;

typedef priority_queue<int, vector<int>, greater<int> > MinHeap;
typedef priority_queue<int, vector<int>, less<int> > MaxHeap;

int main()
{
    int x;
    int m = 0;
    MinHeap High;
    MaxHeap Low;

    fstream file("Median.txt");

    file >> x;
    High.push(x);
    m = x;

    int sum = m;

    while(file >> x)
    {
        if (x > m)
            High.push(x);
        else
            Low.push(x);

        if(abs(High.size() - Low.size()) > 1)
        {
            if (High.size() > Low.size())
            {
                int root = High.top();
                High.pop();
                Low.push(root);
            }
            else
            {
                int root = Low.top();
                Low.pop();
                High.push(root);
            }
        }

        if (High.size() > Low.size())
            m = High.top();
        else
            m = Low.top();

        sum += m;
    }

    cout << sum % 10000;

    return 0;
}
