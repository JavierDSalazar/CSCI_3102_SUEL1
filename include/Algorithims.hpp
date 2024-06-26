#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <time.h>


double factorial(int n);

double f1(int n);
double f2(int n);
double f3(int n);
double f4(int n);
double f5(int n);
double f6(int n);
double f7(int n);

class Algorithims
{
    public:
    std::string name;
    int function_count;
    int arr_len;
    double (**f_ptrs) (int n);
    double *arr;
    std::string *labels;
    //when functions are compared
    Algorithims(
        std::string name,
        int         function_count,
        double      (*f_ptrs[]) (int n),
        std::string labels[]
    )
    {
        this->name           = name;
        this->function_count = function_count;
        this->f_ptrs         = f_ptrs;
        this->labels         = labels;
    };

    //when one sort needs to be used
    Algorithims(
    std::string name,
    int         arr_len
    )
    {
        this->name           = name;
        this->arr_len        = arr_len;
        this->arr            = (double*) malloc(arr_len * sizeof(double));
    };
    std::stringstream results;
    
    //for singular arrays only
    void arr_swap              (int idx1, int idx2);
    void generate_random_array ();
    void print_arr             ();
    int  find_smallest         ();
    void insertion_sort        ();
    
    //multifunction comparision only
    void swap (int idx1, int idx2);
    void multifunction_insertion_sort(int n);
    void print_labels();
    //todo: rename
    void test(int n);

    void write_to_file();
};