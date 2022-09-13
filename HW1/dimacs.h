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
};