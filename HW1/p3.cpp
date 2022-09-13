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

    int id = N+1;
    for(int i=1;i<=N;i++){
        for(int j=1;j<=K;j++){
            S[i][j]=id;
            id++;
        }
    }

    vector<vector<int>> result;
    //Copy over the initial CNF
    for(vector<int> clause: inputDimacs.clauseDefinitions){
        result.push_back(clause);
    }


    //Condition 1 - neg(x_1) or S[1][1]
    result.push_back({-1,S[1][1]});

    //Condition 2 -  neg(S[1][j]) for all 1<j<=K

    for(int j=2;j<=K;j++){
        result.push_back({-S[1][j]});
    }
    // for 1<i<N;
    //Condition 3 - neg(i) or S[i][1] 
    //Condition 4 - neg(S[i-1][1]) or S[i][1]
    //Condition 7 - neg(i) or neg(S[i-1][K])
    for(int i=2;i<N;i++){
        result.push_back({-i,S[i][1]});
        result.push_back({-S[i-1][1],S[i][1]});
        result.push_back({-i,-S[i-1][K]});
    }

    //Condition 8 - neg(n) or neg(S[n-1][k])
    result.push_back({-N,S[N-1][K]});

    //for 1<i<n and 1<j<=k
    //Condition 5 - neg(i) or neg(S[i-1][j-1]) or S[i][j]
    //Condition 6 - neg(S[i-1][j]) or S[i][j]
    for(int i=2;i<N;i++){
        for(int j=2;j<=K;j++){
            result.push_back({-i,-S[i-1][j-1],S[i][j]});
            result.push_back({-S[i-1][j],-S[i][j]});
        }
    }


    //Number of propositions = N*K+N

    cout<<"p cnf "<<N*K+N<<" "<<result.size()<<endl;
    for(vector<int> clause: result){
        for(int proposition: clause){
            cout<<to_string(proposition)+" ";
        }
        cout<<"0";
        cout<<endl;
    }
        
}