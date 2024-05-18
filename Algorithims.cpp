//todo: handle special symbols properly https://stackoverflow.com/questions/70706794/how-to-print-superscript-3-in-c
#include "Algorithims.hpp"

double factorial(int n)
{
    if ((n == 0) || (n == 1))
    {
        return 1;
    }
    else
    {
        return n*factorial(n-1);
    }
}

double f1(int n)
{
    return pow(4,log(n));
}

double f2(int n)
{
    return log(n);
}

double f3(int n)
{
    return factorial(n); 
}

double f4(int n)
{
    return sqrt(n);
}

double f5(int n)
{
    return exp(n);
}

double f6(int n)
{
    return pow(2,log(n));
}

double f7(int n)
{
    return pow(n, 3);
}

void Algorithims::generate_random_array()
{
    srand(time(0));
    for (int i = 0; i < arr_len; i++)
    {
        arr[i] = rand() % 100;
    }
    for (int i = 0; i < arr_len; i++)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
    
    
}
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

void Algorithims::insertion_sort(double arr[], int arr_len)
{
    double key;
    int j;
    for (int i = 1; i < arr_len ; i++)
    {
        key = arr[i];
        j   = i - 1;
        while ((j > 0) && (arr[j]))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;   
    }
}
//todo: needs more testing
void Algorithims::multifunction_insertion_sort(int n)
{
    bool swap_was_made = false;
    int j = 1;

    // std::cout<<"Unsorted: ";
    // test(n);
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
    #ifdef _WIN32
        command << "notepad " << name << &;
    #else
        command << "nano " << name; // On Unix-like systems, use xdg-open
    #endif
    system(command.str().c_str());

}

// int main()
// {
//     //todo: come up with way to reset this since an emergent behavior is that an accidental optimization occurred
//     //beause the heavier hitting functions n!, e^n, and n^3 greatly "outmatch" the others, they tend to stay in the same order
//     //since we swap functions, not values, this resulted most the runs being mostly pre-sorted
//     //which is fine but doesn't illustrate the point as well
//     double (*f_ptrs[7]) (int n) = {&f1, &f2, &f3, &f4, &f5, &f6, &f7};
//     int     function_count      = 7;
//     std::string labels[]        = {"4ˡᵍⁿ", "lgn", "n!", "√n", "eⁿ", "2ˡᵍⁿ", "n³"};
    
//     Algorithims al("Module1_Discussion", function_count, f_ptrs, labels);
//     for (int n = 0; n < 20; n++)
//     {
//         std::cout<<"n="<<n<<'\n';
//         al.insertion_sort(n);
//         std::cout<<"--------------\n";
//     }
//     al.write_to_file();
//     return 0;
// }