#include <iostream>

void quicksort(int A[], int p, int r);
int  partition(int A[], int p, int r);
void swap     (int A[], int i, int j);

void quicksort(int A[], int p, int r)
{
    if (p < r)
    {
        int q = partition(A,p,r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}

int partition(int A[], int p, int r)
{
    int x = A[r];
    int i = p-1;
    for (int j = p; j < r; j++)
    {
        if (A[j] <= x)
        {
            i++;
            swap(A, i, j);
        }
    }
    swap(A, i+1, r);
    return i+1;
}

void swap(int A[], int i, int j)
{
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

int main()
{
    int A[] = {2, 8, 7, 1, 3, 5, 6, 4};
    int r = sizeof(A)/sizeof(A[0]);
    quicksort(A, 0, r-1);
    for (int i = 0; i < r; i++)
    {
        std::cout<<A[i]<<' ';
    }
    std::cout<<'\n';
    
    return 0;
}