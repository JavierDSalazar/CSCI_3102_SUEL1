#include <iostream>
#include <chrono>
#include <random>
#include <sstream>
#include <fstream>
#include <unordered_set>

int swapcount = 0;
auto start    = std::chrono::high_resolution_clock::now();
auto stop     = std::chrono::high_resolution_clock::now();
auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop-start);

std::random_device dev;
std::mt19937 rng(dev());

std::stringstream ss;

void print_array(int A[], int len);

void quicksort(int A[], int p, int r);
int  partition(int A[], int p, int r);
void swap     (int A[], int i, int j);

int  random_number         (int minimum, int maximum);
void random_fill           (int A[], int len, int minimum, int maximum);
void random_fill_antisorted(int A[], int len, int minimum, int maximum);
void reset_array           (int A[], int Orig[], int len);
void randomized_quicksort  (int A[], int p, int r);
int  randomized_partition  (int A[], int p, int r);

void distinct_fill             (int A[], int len, int minimum, int maximum);
int  median_of_three           (int A[], int tmp[]);
void median_of_three_quicksort (int A[], int p, int r);
int  median_of_three_partition (int A[], int p, int r);


int random_number(int minimum, int maximum)
{
    std::uniform_int_distribution<std::mt19937::result_type> dist6(minimum, maximum); // distribution in range [1, maximum]
    return dist6(rng);
}

void random_fill(int A[], int len, int minimum, int maximum)
{
    for (int i = 0; i < len; i++)
    {
        A[i] = random_number(minimum, maximum);
    }
}

void random_fill_antisorted(int A[], int len, int minimum, int maximum)
{
    for (int i = 0; i < len; i++)
    {
        A[i] = random_number(minimum, maximum);
        {
            if ((i!=0) && (A[i-1]<A[i]))
            {
                swap(A, i-1, i);
            }   
        } 
    }
}

void random_fill_solid(int A[], int len, int minimum, int maximum)
{
    int tmp = random_number(minimum, maximum);;
    for (int i = 0; i < len; i++)
    {
        A[i] = tmp;
    }
}

void random_fill_every_other_solid(int A[], int len, int minimum, int maximum)
{
    int tmp = random_number(minimum, maximum);
    
    for (int i = 0; i < len; i++)
    {
        if (i % 2 == 0)
        {
            A[i] = tmp;
        }
        else
        {
            A[i] = random_number(minimum, maximum);
        }
    }
}

void distinct_fill(int A[], int len, int minimum, int maximum)
{
    std::unordered_set<int> S;

    if ((maximum - len) < 10)
    {
        maximum *= 2;
    }

    while (S.size() != len)
    {
        S.insert(random_number(minimum, maximum));
    }

    int i = 0;
    for (auto &S_n: S)
    {
        A[i] = S_n;
        i++;
    }
}

void reset_array(int A[], int Orig[], int len)
{
    for (int i = 0; i < len; i++)
    {
        A[i] = Orig[i];
    }
}

void quicksort(int A[], int p, int r)
{    
    if (p < r)
    {
        int q = partition(A,p,r);
        quicksort(A, p, q-1);
        quicksort(A, q+1, r);
    }
}

void randomized_quicksort(int A[], int p, int r)
{    
    if (p < r)
    {
        int q = randomized_partition(A,p,r);
        randomized_quicksort(A, p, q-1);
        randomized_quicksort(A, q+1, r);
    }
}

void median_of_three_quicksort(int A[], int p, int r)
{    
    if (p < r)
    {
        int q = median_of_three_partition(A,p,r);
        median_of_three_quicksort(A, p, q-1);
        median_of_three_quicksort(A, q+1, r);
    }
}

int median_of_three(int A[], int tmp[])
{
    int i,j,k;
    i = tmp[0];
    j = tmp[1];
    k = tmp[2];
    if ((A[i] > A[j]) ^ (A[i] > A[k])) 
        return i;
    else if ((A[j] < A[i]) ^ (A[j] < A[k])) 
        return j;
    else
        return k;
}

int median_of_three_partition(int A[], int p, int r)
{
    int tmp[3] = {random_number(p,r), random_number(p,r), random_number(p,r)};
    for (int i = 1; i < 3; i++)
    {
        if (A[tmp[i-1]] == A[tmp[i]])
        {
            tmp[i] = random_number(p,r);
            i--; //re-rolls have a cost here!
        }
    }
    int i = median_of_three(A, tmp);
    swap(A, r, i);
    return partition(A, p, r);
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

int randomized_partition(int A[], int p, int r)
{
    int i = random_number(p,r);
    swap(A, r, i);
    return partition(A, p, r);
}

void swap(int A[], int i, int j)
{
    int tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
    swapcount++;
}

void print_array(int A[], int len)
{
    for (int i = 0; i < len; i++)
    {
        ss << A[i] << ' ';
    }
    ss <<'\n';
    
}

void stopwatch(bool toggle)
{
    if (toggle == true)
    {
        start    = std::chrono::high_resolution_clock::now();
    }
    
    else
    {
        stop     = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    }
}

void write_to_file()
{
    std::ofstream f("output.txt"); 
    f << ss.str();
    f.close();
}

int trialcount = 1;
bool trial(int maximum)
{
    //----------------------------------------------------Initilization Phase--------------------------------------------------------------------------------------
    ss<<"----------------------------------------Start Trial "<<trialcount<<"----------------------------------------\n";
    int r       = 100;
    int A[r]    = {0};
    int Orig[r] = {0};
    distinct_fill(A, r, 1, maximum);
    reset_array(Orig, A, r);
    print_array(A, r);
    // for (int i = 0; i < r; i++)
    // {
    //     std::cout<<A[i]<<' ';
    // }
    // std::cout<<'\n';
    
    //-----------------------------------------------------"Naive" Quicksort Phase------------------------------------------------------------------------------------

    stopwatch(1);
    quicksort(A, 0, r-1);
    stopwatch(0);
    
    auto leftmost_pivot_selction_duration = duration.count();
    ss<<"Sorting the array with leftmost element as pivot " << "took " << duration.count() << "µs (Swaps: " << swapcount << ") ";
    print_array(A, r);

    swapcount = 0;
    reset_array(A, Orig, r);

    //-------------------------------------------------Randomized Pivot Quicksort Phase-----------------------------------------------------------------------------------------

    stopwatch(1);
    randomized_quicksort(A, 0, r-1);
    stopwatch(0);

    auto randomized_pivot_selction_duration = duration.count();
    ss<<"Sorting the array with randomized pivot " << "took " << duration.count() << "µs (Swaps: " << swapcount << ") ";
    print_array(A, r);

    swapcount = 0;
    reset_array(A, Orig, r);

    //-----------------------------------------------median-of-three Pivot Quicksort Phase-------------------------------------------------------------------------------------------

    stopwatch(1);
    median_of_three_quicksort(A, 0, r-1);
    stopwatch(0);

    auto median_of_three_pivot_selction_duration = duration.count();
    ss<<"Sorting the array with median-of-three pivot " << "took " << duration.count() << "µs (Swaps: " << swapcount << ") ";
    print_array(A, r);

    swapcount = 0;
    ss<<"----------------------------------------End Trial "<<trialcount<<"----------------------------------------\n\n";
    if (
        (leftmost_pivot_selction_duration > median_of_three_pivot_selction_duration)
        &&
        (randomized_pivot_selction_duration > median_of_three_pivot_selction_duration)
        || 
        (trialcount > 10000)
        )
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    while (trial(100) != true)
    {
        trialcount+=1;
    }
    if (trialcount > 10000)
    {
        std::cout<<"warning: 10k trials exceeded, don't check output.txt\n";
    }
    
    write_to_file();
    return 0;
}