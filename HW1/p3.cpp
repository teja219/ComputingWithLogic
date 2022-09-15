#include <iostream>
#include <vector>
#include "dimacs.h"//Custom file for reading and writing dimacs data
using namespace std;



int main()
{
    // For getting input from input.txt file
    freopen("p3Input.txt", "r", stdin); 
    //First line contains K
    int K;
    cin>>K;

    // Printing the Output to output.txt file
    freopen("p3Output.dimacs", "w", stdout);
    //Add an additional clause which is a disjunction of all literals
    Dimacs inputDimacs = Dimacs(1);
    int N = inputDimacs.literals;

    vector<vector<int>> S(N+1,vector<int>(K+1,0));

    

    vector<vector<int>> result;
    //Copy over the initial CNF
    for(vector<int> clause: inputDimacs.clauseDefinitions){
        result.push_back(clause);
    }

    vector<int> currentPropositions;
    for(int i=0;i<=N;i++){
        currentPropositions.push_back(i);
    }
    pair<int,vector<vector<int>>> atMostKOutput = Dimacs(0).atmostKSumClauses(currentPropositions,N+1,K);

    
    int nextPropositionIndex = atMostKOutput.first;
    result.insert(std::end(result), std::begin(atMostKOutput.second), std::end(atMostKOutput.second));

    //Number of propositions = N*K+N

    cout<<"p cnf "<<nextPropositionIndex-1<<" "<<result.size()<<endl;
    for(vector<int> clause: result){
        for(int proposition: clause){
            cout<<to_string(proposition)+" ";
        }
        cout<<"0";
        cout<<endl;
    }
        
}