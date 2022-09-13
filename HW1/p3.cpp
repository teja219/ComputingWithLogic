#include <iostream>
#include <vector>
#include "dimacs.h"//Custom file for reading and writing dimacs data
using namespace std;



int main()
{
    // For getting input from input.txt file
    freopen("input.txt", "r", stdin); 
    // Printing the Output to output.txt file
    freopen("output.dimacs", "w", stdout);
    //Add an additional clause which is a disjunction of all literals
    Dimacs inputDimacs = Dimacs(1);
        
}