#include "Algorithims.hpp"

int main()
{
    std::string name    = "exercise_3.1-1";
    int         arr_len = 6;
    Algorithims al_3pt1_1(name, arr_len);
    al_3pt1_1.generate_random_array();
    al_3pt1_1.insertion_sort();
    return 0;
}