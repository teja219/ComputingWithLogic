#include <iostream>
#include <vector>
#include "dimacs.h"//Custom file for reading and writing dimacs data
using namespace std;



int main()
{
    // For getting input from input.txt file
    freopen("p6Input.txt", "r", stdin); 
    //First line contains K
    int K;
    cin>>K;

    
    
    //Add an additional clause which is a disjunction of all literals
    Dimacs inputDimacs = Dimacs(1);
    
    int N = inputDimacs.clauseDefinitions.size();//There are N clauses

    int nextPropositionIndex = inputDimacs.literals+1;
    //We will introduce N additional propositions where N is number of clauses
    vector<int> P(N+1,0);
    for(int i=1;i<=N;i++) {
        P[i]=nextPropositionIndex;
        nextPropositionIndex++;
    }
        
    //Add corresponding clauses for each of the above proposition
    vector<vector<int>> result;
    for(int i=1;i<=N;i++){
        //ith clause
        vector<int> clause = inputDimacs.clauseDefinitions[i-1];//inputDimacs.clauseDefinition is 0th index
        
        for(int prop: clause){
            result.push_back({-P[i],-prop});
        }
        vector<int> temp;
        for(int prop: clause){
            temp.push_back(prop);
        }
        temp.push_back(P[i]);
    }
    pair<int,vector<vector<int>>> atmostKResult = Dimacs(0).atmostKSumClauses(P, nextPropositionIndex, N-K);
    nextPropositionIndex = atmostKResult.first;
    for(vector<int> clause: atmostKResult.second){
        result.push_back(clause);
    }
    freopen("p6Output.dimacs", "w", stdout);
    cout<<"p cnf "<<nextPropositionIndex-1<<" "<<result.size()<<endl;
    for(vector<int> clause: result){
        for(int proposition: clause){
            cout<<to_string(proposition)+" ";
        }
        cout<<"0";
        cout<<endl;
    }

}