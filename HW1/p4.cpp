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
    //For getting input from input.txt file
    ifstream H_read("graphH.txt");
    int H_n,H_m,G_n,G_m;//Number of vertices and edges in H and G.
    H_read>>H_n>>H_m;
    vector<pair<int,int>> H_e,G_e;//Edges of H and G.
    for(int i=1;i<=H_m;i++){
        int a,b;
        H_read>>a>>b;
        H_e.push_back({a,b});
    }
    

    cout<<"Read graph H inputs\n";
    ifstream G_read("graphG.txt");
    G_read>>G_n>>G_m;
    set<pair<int,int>> G_e_set;
    for(int i=1;i<=G_m;i++){
        int a,b;
        G_read>>a>>b;
        G_e.push_back({a,b});
        G_e_set.insert({a,b});
        G_e_set.insert({b,a});
    }    
    
    cout<<"Read graph G inputs\n";
    //Mapping between H and G
    //X[i][j] denotes the proposition representation of the variable which maps ith node in H to jth node in G.
    vector<vector<int>> X(H_n+1,vector<int>(G_n+1,0));
    int count=1;
    for(int i=1;i<=H_n;i++){
        for(int j=1;j<=G_n;j++){
            X[i][j]=count;
            count++;
        }
    }
    cout<<"Sizes:"<<H_n<<" "<<H_m<<" "<<G_n<<" "<<G_m<<" "<<H_e.size()<<" "<<G_e.size()<<endl;
    cout<<"Numbered the clauses\n";
    vector<vector<int>> result;
    //Every node in H map to atleast one node in G
    for(int i=1;i<=H_n;i++){
        vector<int> clause;
        for(int j=1;j<=G_n;j++){
            clause.push_back(X[i][j]);
        }
        result.push_back(clause);
    }
    cout<<"Done with condition 1\n";
    //No two vertices in H can be mapped to same vertex in G
    for(int i=1;i<=H_n;i++){
        for(int j=1;j<=H_n;j++){
            if(i!=j){
                for(int k=1;k<=G_n;k++){
                    vector<int> clause;
                    clause.push_back(-X[i][k]);
                    clause.push_back(-X[j][k]);
                    result.push_back(clause);
                }
            }
        }
    }      
    cout<<"Done with condition 2\n";
    //A vertex in H can't be mapped to more than 1 vertex in G
    for(int k1=1;k1<=G_n;k1++){
        for(int k2=1;k2<=G_n;k2++){
            if(k1!=k2){
                for(int i=1;i<=H_n;i++){
                    vector<int> clause;
                    clause.push_back(-X[i][k1]);
                    clause.push_back(-X[i][k2]);
                    result.push_back(clause);
                }
            }
        }
    }
    cout<<"Done with condition 3\n";
    //Every edge in H should be mapped to some edge in G => Every edge in H should not be mapped to any non edge in G.

    for(int a=0;a<H_e.size();a++){
        int i = min(H_e[a].first,H_e[a].second);
        int j = max(H_e[a].first,H_e[a].second);
        
        for(int k=1;k<=G_n;k++){
            for(int l=1;l<=G_n;l++){
                if(k!=l){
                    //If it is not an edge in G
                    if(G_e_set.find({k,l})==G_e_set.end()){
                        vector<int> clause;
                        clause.push_back(-X[i][k]);
                        clause.push_back(-X[j][l]);
                        result.push_back(clause);
                    }    
                }
            }
        }
    }
    cout<<"Done with condition 4\n";


    // Printing the Output to output.txt file
    freopen("p4Output.dimacs", "w", stdout);
    cout<<"p cnf "<<H_n*G_n<<" "<<result.size()<<endl;
    for(vector<int> clause: result){
        for(int proposition: clause){
            cout<<to_string(proposition)+" ";
        }
        cout<<"0";
        cout<<endl;
    }
}