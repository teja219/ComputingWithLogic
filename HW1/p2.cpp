//Input format
//p cnf 3 2 --> 3 is number of distinct propositions,2 is number of clauses
//-1 2 0  --> (-P_1 or P_2)
//-2 -3 1 0 --> (-P_2 or -P_3 or P_1)
#include <iostream>
#include <vector>
#include "dimacs.h"//Custom file for reading and writing dimacs data
using namespace std;

enum PROP_TYPE { ZERO, ONE, POSITIVE_PROP, NEGATIVE_PROP };


int main()
{
    // For getting input from input.txt file
    freopen("p2Input.txt", "r", stdin); 
    
    //Add an additional clause which is a disjunction of all literals
    Dimacs inputDimacs = Dimacs(1);
    //Initializing output dimacs
    
    //One iteration per proposition, after each iteration we generate a literal, in ith iteration we generate 
    //either 0 || 1 || P_i || neg(P_i)
    vector<PROP_TYPE> result(1,ZERO);
    for(int proposition=1;proposition<=inputDimacs.literals;proposition++){
        int ones=0;
        int zeroes=0;
        int propPositives=0;
        int propNegatives=0;
        //cout<<"----------\n";
        //cout<<"Proposition:"<<proposition<<endl;
        for(vector<int> clause: inputDimacs.clauseDefinitions){
                 int onesPerClause=0;
                 int zeroesPerClause=0;
                 int propPositivesPerClause=0;
                 int propNegativesPerClause=0;

                 for(int prop: clause){
                     if(abs(prop) != proposition){
                        if(prop>0) zeroesPerClause++; //Since we are setting false
                        if(prop<0) onesPerClause++; //Since we are setting false, negation of false is true
                     }
                     else{
                        if(prop>0) propPositivesPerClause++;
                        if(prop<0) propNegativesPerClause++;
                     }
                 }
                 // //cout<<"onesPerClause:"<<onesPerClause<<"zeroesPerClause:"<<zeroesPerClause<<endl;
                 // //cout<<"propPositivesPerClause:"<<propPositivesPerClause<<"propNegativesPerClause:"<<propNegativesPerClause<<endl;
                 if(onesPerClause>0){
                     ones++;
                 }
                 else if(propPositivesPerClause!=0 || propNegativesPerClause!=0){
                     if(propPositivesPerClause>0 && propNegativesPerClause>0){
                        ones++;
                     }
                     else{
                        if(propPositivesPerClause>0){
                            propPositives++;
                        }
                        else{
                            propNegatives++;
                        }
                     }
                 }
                 else{
                    zeroes++;
                 }
        }
        //cout<<"propPositives:"<<propPositives<<endl;
        //cout<<"propNegatives:"<<propNegatives<<endl;
        //cout<<"zeroes:"<<zeroes<<endl;
        //cout<<"ones:"<<ones<<endl;
        PROP_TYPE p;
        if(zeroes>0){
            p = ZERO;
        }
        else{
            if(propPositives!=0 || propNegatives!=0){
                if(propPositives!=0 && propNegatives!=0){
                    p=ZERO;
                }  
                else{
                    if(propPositives>0){
                        p = POSITIVE_PROP;
                    }
                    else{
                        p = NEGATIVE_PROP;
                    }
                }
            }
            else{
                p = ONE;
            }
        }
        result.push_back(p);
    }

    // for(int i=1;i<=inputDimacs.literals;i++){
    //     cout<<result[i]<<" ";
    // }
    // cout<<endl;
    int ones=0;
    int zeroes=0;
    int propPositives=0;
    int propNegatives=0;

    for(int i=1;i<=inputDimacs.literals;i++){
        if(result[i]==ONE) ones++;
        else if(result[i]==ZERO) zeroes++;
        else if(result[i]==POSITIVE_PROP) propPositives++;
        else propNegatives++;
    }

    Dimacs outputDimacs = Dimacs(0);
    if(ones>0){
        cout<<"tautology"<<endl;
        outputDimacs.literals=1;
        outputDimacs.clauseDefinitions.push_back({1,-1});
    }
    else if(propPositives!=0 || propNegatives!=0){
        outputDimacs.literals = inputDimacs.literals;
        outputDimacs.clauseDefinitions = vector<vector<int>>(1,vector<int>(0));
        outputDimacs.clauses=0;
        for(int i=1;i<=inputDimacs.literals;i++){
            if(result[i]==POSITIVE_PROP){
                outputDimacs.clauseDefinitions[0].push_back(i);
                outputDimacs.clauses++;
            }
            if(result[i]==NEGATIVE_PROP){
                outputDimacs.clauseDefinitions[0].push_back(-i);
                outputDimacs.clauses++;
            }
        }
    }
    else{
        cout<<"unsatisfiable"<<endl;
        outputDimacs.literals=1;
        outputDimacs.clauses=2;
        outputDimacs.clauseDefinitions.push_back({1});
        outputDimacs.clauseDefinitions.push_back({-1});
    }
    //cout<<outputDimacs.clauses<<endl;
    // Printing the Output to output.txt file
    freopen("p2Output.dimacs", "w", stdout);
    
    cout<<"p cnf "<<outputDimacs.literals<<" "<<outputDimacs.clauseDefinitions.size()<<endl;
    for(vector<int> clause: outputDimacs.clauseDefinitions){
        for(int proposition: clause){
            cout<<to_string(proposition)+" ";
        }
        cout<<"0";
        cout<<endl;
    }
}


