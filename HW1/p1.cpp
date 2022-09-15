#include <iostream>
#include <vector>
#include "dimacs.h"//Custom file for reading and writing dimacs data
using namespace std;



int main()
{
    // For getting input from input.txt file
    freopen("p1Input.txt", "r", stdin); 
    // Printing the Output to output.txt file
    freopen("p1Output.dimacs", "w", stdout);
    //Add an additional clause which is a disjunction of all literals
    Dimacs inputDimacs = Dimacs(1);
    //Add a clause
    
    vector<int> orClause;
    for(int i=1;i<=inputDimacs.literals;i++) {
      orClause.push_back(i);
    }
    inputDimacs.clauseDefinitions.push_back(orClause);
    cout<<"p cnf "<<inputDimacs.literals<<" "<<inputDimacs.clauseDefinitions.size()<<endl;
    for(vector<int> clause: inputDimacs.clauseDefinitions){
        for(int proposition: clause){
            cout<<to_string(proposition)+" ";
        }
        cout<<"0";
        cout<<endl;
    }
}