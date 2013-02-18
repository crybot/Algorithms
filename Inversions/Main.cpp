#include <iostream>
#include <fstream>
using namespace std;

long Merge(long V3[], long start, long middle, long end)
{
    long N1 = middle - start + 1;
    long N2 = end - middle;
    long V1[N1];
    long V2[N2];
    long i=0, j=0, k=start;
    long total = 0;

    for (i=0; i<N1; i++)
        V1[i] = V3[start + i];

    for (i=0; i<N2; i++)
        V2[i] = V3[middle + i + 1];

    i = 0;
    while((i < N1) && (j < N2))
    {
        if (V1[i] <= V2[j])
        {
            V3[k] = V1[i];
            i++;
        }
        else
        {
            V3[k] = V2[j];
            total += N1 - i;
            j++;
        }
        k++;
    }

    if (i >= N1)
    {
        for(;j<N2; j++, k++)
            V3[k] = V2[j];
    }

    else
    {
        for(;i<N1; i++, k++)
            V3[k] = V1[i];
    }

    return total;
}

long Sort(long A[], long start, long end)
{
    long middle, x,y,z;
    if (start < end)
    {
        middle = (end + start)/2;
        x = Sort(A, start, middle);
        y = Sort(A, middle+1, end);
        z = Merge(A, start, middle, end);

        return x + y + z;
    }
    return 0;
}

int main()
{
    long N = 100000;
    long arr[N];
    long start = 0;
    long end = N-1;
    long i = 0;

    ifstream infile;
    infile.open("IntegerArray.txt");


    while (infile >> arr[i++]);

    infile.close();

    cout << "# of Inversions: " << Sort(arr, start, end) << endl;

    cin.get();

}
