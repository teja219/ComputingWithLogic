//Subgraph isomorphism
#include <iostream>
#include <vector>
#include <math.h>
#include <set>
#include <string>
#include  <fstream>
#include "dimacs.h"//Custom file for reading and writing dimacs data
using namespace std;



int main()
{
	//zero index
	vector<int> X(1,0);
	////
	X.push_back(1);
	X.push_back(2);
	X.push_back(3);
	////
	pair<int,vector<vector<int>>> result = Dimacs(0).equalToK(X, 4, 2);
	vector<vector<int>> clauses = result.second;
	int nextPropositionIndex = result.first;
	clauses.push_back({-1});
	clauses.push_back({-2});
		
	// clauses.push_back({-3});
	freopen("testOutput.dimacs", "w", stdout);
	cout<<"p cnf "<<nextPropositionIndex-1<<" "<<clauses.size()<<endl;
    for(vector<int> clause: clauses){
        for(int proposition: clause){
            cout<<to_string(proposition)+" ";
        }
        cout<<"0";
        cout<<endl;
    }
}	