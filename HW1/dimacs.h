#include <iostream>
#include <vector>
using namespace std;

class Dimacs { 
  public:             
    int clauses;
    int literals;        
    vector< vector<int>> clauseDefinitions; // 2D array representing definitions of each clause
    //Read dimacs from input file;
    Dimacs(int readFromInput){
      //Strip out p and cnf strings;
      if(readFromInput==1){
        string temp;
        cin>>temp;
        cin>>temp;
        cin>>literals>>clauses;
        
        //Output whatever is there in the input Clauses;
        vector<vector<int>> clauseDefinitionsTemp(clauses,vector<int>(0));
        for(int i=0;i<clauses;i++){
            int proposition;
            cin>>proposition;
            while(proposition!=0){
                clauseDefinitionsTemp[i].push_back(proposition);
                cin>>proposition;
            }
        }
        clauseDefinitions = clauseDefinitionsTemp;  
      }
      else{
        clauses=0;
        literals=0;
        clauseDefinitions = vector<vector<int>>(0);
      }
    }
    //Print dimacs to output file
    void printDimacs(){
        cout<<"p cnf "<<literals<<" "<<clauses<<endl;
        for(int i=0;i<clauses;i++){
           for(int j=0;j<clauseDefinitions[i].size();j++){
              cout<<clauseDefinitions[i][j]<<" ";
           }
           cout<<"0"<<endl;
        }
    }
    //indexed at 1
    static pair<int,vector<vector<int>>> atmostKSumClauses(vector<int> propositions,int nextPropositionIndex,int K){
        int N = propositions.size()-1;//As it is indexed from 1, its size is N+1
        vector<vector<int>> S(N+1,vector<int>(K+1,0));

        for(int i=1;i<=N;i++){
            for(int j=1;j<=K;j++){
                S[i][j]=nextPropositionIndex;
                nextPropositionIndex++;
            }
        }
        vector<vector<int>> result;
        //Condition 1 - neg(x_1) or S[1][1]
        result.push_back({-propositions[1],S[1][1]});

        //Condition 2 -  neg(S[1][j]) for all 1<j<=K

        for(int j=2;j<=K;j++){
            result.push_back({-S[1][j]});
        }
        // for 1<i<N;
        //Condition 3 - neg(i) or S[i][1] 
        //Condition 4 - neg(S[i-1][1]) or S[i][1]
        //Condition 7 - neg(i) or neg(S[i-1][K])
        for(int i=2;i<N;i++){
            result.push_back({-propositions[i],S[i][1]});
            result.push_back({-S[i-1][1],S[i][1]});
            result.push_back({-propositions[i],-S[i-1][K]});
        }

        //Condition 8 - neg(n) or neg(S[n-1][k])
        result.push_back({-propositions[N],S[N-1][K]});
        
        //for 1<i<n and 1<j<=k
        //Condition 5 - neg(i) or neg(S[i-1][j-1]) or S[i][j]
        //Condition 6 - neg(S[i-1][j]) or S[i][j]
        for(int i=2;i<N;i++){
            for(int j=2;j<=K;j++){
                result.push_back({-propositions[i],-S[i-1][j-1],S[i][j]});
                result.push_back({-S[i-1][j],-S[i][j]});
            }
        }
        return make_pair(nextPropositionIndex, result);
    }
};