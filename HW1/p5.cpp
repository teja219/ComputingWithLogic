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
 	ifstream H_read("graph.txt");
 	int K;
 	H_read>>K;
    int H_n,H_m;//Number of vertices and edges in H and G.
    H_read>>H_n>>H_m;
    vector<pair<int,int>> H_e;//Edges of H
    for(int i=1;i<=H_m;i++){
        int a,b;
        H_read>>a>>b;
        H_e.push_back({a,b});
    }    

    int nextPropositionIndex=1;

    vector<vector<int>> X(H_n+1,vector<int>(2,0));
    for(int i=1;i<=H_n;i++){
    	X[i][0]=nextPropositionIndex;
    	X[i][1]=nextPropositionIndex+1;
    	nextPropositionIndex = nextPropositionIndex+2;
    }

    vector<vector<int>> clauses;
    //A node cannot be in two partitions
    for(int i=1;i<=H_n;i++){
    	clauses.push_back({-X[i][0],-X[i][1]});
    }

    //A node should be present in atleast one partition
    for(int i=1;i<=H_n;i++){
    	clauses.push_back({X[i][0],X[i][1]});
    }

    //The partitions should be equal in size
    vector<int> propositions;
    for(int i=1;i<=H_n;i++){
    	propositions.push_back(X[i][0]);
    	propositions.push_back(X[i][1]);
    }
	pair<int,vector<vector<int>>> result = Dimacs(0).atmostKSumClauses(propositions, nextPropositionIndex, (H_n/2), true);
	nextPropositionIndex = result.first;
	for(vector<int> c:result.second){
		clauses.push_back(c);
	}
	//Introduce edge proposition Z[1..|E|] 
	//which is true when both of the vertices of the edge lie on the same partition
	vector<int> Z(H_m+1,0);
	for(int i=1;i<=H_m;i++){
		Z[i]=nextPropositionIndex;
		nextPropositionIndex++;
	}
	//Add clauses for the above edge propositions
	for(int k=1;k<=H_m;k++){
		int i = H_e[k].first;
		int j = H_e[k].second;
		

		clauses.push_back({
			X[i][0],X[j][0],-Z[k]
		});
		clauses.push_back({
			-X[i][0],X[j][0],Z[k]
		});
		clauses.push_back({
			X[i][0],-X[j][0],Z[k]
		});
		clauses.push_back({
			-X[i][0],-X[j][0],-Z[k]
		});
	}

	//There should be atmost K edges which are accross partitions
	result = Dimacs(0).atmostKSumClauses(Z, nextPropositionIndex, K, false);
	nextPropositionIndex = result.first;
	for(vector<int> c:result.second){
		clauses.push_back(c);
	}

	cout<<"p cnf "<<nextPropositionIndex-1<<" "<<clauses.size()<<endl;
    for(vector<int> clause: clauses){
        for(int proposition: clause){
            cout<<to_string(proposition)+" ";
        }
        cout<<"0";
        cout<<endl;
    }


}	