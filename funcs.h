
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
#include <sstream>
#include <fstream>

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