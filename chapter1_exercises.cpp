#include "Algorithims.hpp"
#include "chapter1_exercises.h"

int main()
{
	double (*f_ptrs_1pt2_2[2]) (int n) = {&f1_chap1_excercise1pt2_2, &f2_chap1_excercise1pt2_2};
	int     function_count_1pt2_2      = 2;
	std::string labels_1pt2_2[2]                {"8n²", "64nlgn"};
	double (*f_ptrs_1pt2_3[2]) (int n) = {&f1_chap1_excercise1pt2_3, &f2_chap1_excercise1pt2_3};
	int     function_count_1pt2_3      = 2;
	std::string labels_1pt2_3[2]              = {"100n²", "2ⁿ"};
    
    Algorithims al_1pt2_2 ("Chapter1exercise_1pt2_2 ", function_count_1pt2_2, f_ptrs_1pt2_2, labels_1pt2_2); //n=[2,27] is when 8n² is smaller
    for (int n = 0; n < 100; n++)
    {
        std::cout<<"n="<<n<<'\n';
        al_1pt2_2.multifunction_insertion_sort(n);
        std::cout<<"--------------\n";
    }
    al_1pt2_2.write_to_file();
	Algorithims al_1pt2_3 ("Chapter1exercise_1pt2_3 ", function_count_1pt2_3, f_ptrs_1pt2_3, labels_1pt2_3); //n==15 is the first value that 2ⁿ overtakes 100n² (n==0 probably doesn't count bc a program can't[?] run in 0 seconds -- i'd call it the trivial case)
    for (int n = 0; n < 20; n++)
    {
        std::cout<<"n="<<n<<'\n';
        al_1pt2_3.multifunction_insertion_sort(n);
        std::cout<<"--------------\n";
    }
    al_1pt2_3.write_to_file();
    return 0;
}