#include <iostream>
#include <vector>
#include "dimacs.h"//Custom file for reading and writing dimacs data
using namespace std;



int main()
{
    // For getting input from input.txt file
    freopen("p1Input.txt", "r", stdin); 
    // Printing the Output to output.txt file
    freopen("p1.dimacs", "w", stdout);
    //Add an additional clause which is a disjunction of all literals
    Dimacs inputDimacs = Dimacs(1);
    //Add a clause
    inputDimacs.clauses += 1;
    inputDimacs.clauseDefinitions.push_back(vector<int>(0));
    ////
    for(int i=1;i<=inputDimacs.literals;i++) {
      inputDimacs.clauseDefinitions[inputDimacs.clauses].push_back(i);
    }
    inputDimacs.printDimacs();
}