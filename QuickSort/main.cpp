#include <iostream>
#include <fstream>
using namespace std;

inline void Swap (int A[], int i, int j)
{
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}
int Partition(int A[], int low, int high)
{
    int pivot;
    int middle = (high + low)/2;
    int x = A[low];
    int y = A[middle];
    int z = A[high];

    if ((x > y && x < z) || (x > z && x < y)) pivot = low;
    else if ((y > x && y < z) || (y > z && y < x)) pivot = middle;
    else pivot = high;

    Swap(A,low, pivot);
    int p = A[low];
    int i = low + 1;
    int j;
    for (j=low + 1; j<=high; j++)
    {
        if (A[j] < p)
        {
            Swap(A, i, j);
            i++;
        }
    }
    Swap(A, low, --i);
    return i;
}

int QuickSort(int A[], int low, int high)
{
    int p, x, y;
    if (low < high)
    {
        p = Partition(A, low, high);
        x = QuickSort(A, low, p-1);
        y = QuickSort(A, p+1, high);
        return x + y + (high - low);
    }
    return 0;

}

int main()
{
    int N = 10000;
    int A[N];
    fstream ff("QuickSort.txt");

    int i = 0;
    while (ff >> A[i++]);


    cout << "Numero di confronti: " <<  QuickSort(A, 0, N-1);

    return 0;
}
