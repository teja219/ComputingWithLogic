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
        cout<<"----------\n";
        cout<<"Proposition:"<<proposition<<endl;
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
                 // cout<<"onesPerClause:"<<onesPerClause<<"zeroesPerClause:"<<zeroesPerClause<<endl;
                 // cout<<"propPositivesPerClause:"<<propPositivesPerClause<<"propNegativesPerClause:"<<propNegativesPerClause<<endl;
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
        cout<<"propPositives:"<<propPositives<<endl;
        cout<<"propNegatives:"<<propNegatives<<endl;
        cout<<"zeroes:"<<zeroes<<endl;
        cout<<"ones:"<<ones<<endl;
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
    

    // Printing the Output to output.txt file
    freopen("p2Output.dimacs", "w", stdout);
    
}


