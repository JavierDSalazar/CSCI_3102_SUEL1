//todo: handle special symbols properly https://stackoverflow.com/questions/70706794/how-to-print-superscript-3-in-c
#include <iostream>
#include <string>
#include <vector>
#include "funcs.h"

class Algorithims
{
    public:
    std::string name;
    int function_count;
    double (**f_ptrs) (int n);
    std::string *labels;
    Algorithims(
        std::string name,
        int function_count,
        double (*f_ptrs[]) (int n),
        std::string labels[]
    )
    {
        this->name           = name;
        this->function_count = function_count;
        this->f_ptrs         = f_ptrs;
        this->labels         = labels;
    };
    std::stringstream results;

    void swap(int idx1,  int idx2);
    void insertion_sort(int n);
    void print_labels();
    //todo: rename
    void test(int n);
    void write_to_file();
};

//todo: templatize
void Algorithims::swap(int idx1,  int idx2)
{
    double    (*tmp_fn_ptr)(int) = f_ptrs[idx1];
    std::string tmp_str          = labels[idx1];
    f_ptrs[idx1]                 = f_ptrs[idx2];
    labels[idx1]                 = labels[idx2];
    f_ptrs[idx2]                 = tmp_fn_ptr  ;
    labels[idx2]                 = tmp_str     ;
}

//todo: needs more testing
void Algorithims::insertion_sort(int n)
{
    bool swap_was_made = false;
    int j = 1;

    std::cout<<"Unsorted: ";
    test(n);
    while (j!=(function_count))
    {
        for (int i = 0; i < j; i++)
        {
            if (f_ptrs[i](n) > f_ptrs[j](n))
            {
                swap(i,j);
                swap_was_made = true;
            }
        }
        j++;
    }
    std::cout<<"Sorted: n="<<n<<": "; test(n);
}


void Algorithims::print_labels()
{
    for (int i = 0; i < function_count; i++)
    {
        results<<labels[i]<<',';
        std::cout<<labels[i]<<", ";
    }
    results<<'\n';
    std::cout<<'\n';
}

void Algorithims::test(int n)
{
    
    print_labels();
    for (int i = 0; i < function_count; i++)
    {
        results<<f_ptrs[i](n)<<',';
        std::cout<<f_ptrs[i](n)<<", ";
    }
    results<<'\n';
    std::cout<<'\n';
}

void Algorithims::write_to_file()
{
    std::string s;
    std::ofstream f;
    s = results.str();
    //todo: doesn't work in Excel :)
    name.append(".csv");
    f.open(name);
    f << name << "\n" << s ;
    f.close();

    std::stringstream command;
    command << "notepad " << name << "&";
    system(command.str().c_str());

}

int main()
{
    //todo: come up with way to reset this since an emergent behavior is that an accidental optimization occurred
    //beause the heavier hitting functions n!, e^n, and n^3 greatly "outmatch" the others, they tend to stay in the same order
    //since we swap functions, not values, this resulted most the runs being mostly pre-sorted
    //which is fine but doesn't illustrate the point as well
    double (*f_ptrs[7]) (int n) = {&f1, &f2, &f3, &f4, &f5, &f6, &f7};
    int     function_count      = 7;
    std::string labels[]        = {"4ˡᵍⁿ", "lgn", "n!", "√n", "eⁿ", "2ˡᵍⁿ", "n³"};
    
    Algorithims al("Module1_Discussion", function_count, f_ptrs, labels);
    for (int n = 0; n < 20; n++)
    {
        std::cout<<"n="<<n<<'\n';
        al.insertion_sort(n);
        std::cout<<"--------------\n";
    }
    al.write_to_file();
    return 0;
}