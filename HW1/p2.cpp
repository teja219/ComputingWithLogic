#include <iostream>
#include <vector>
#include "dimacs.h"//Custom file for reading and writing dimacs data
using namespace std;



int main()
{
    // For getting input from input.txt file
    freopen("p2Input.txt", "r", stdin); 
    // Printing the Output to output.txt file
    freopen("p2Output.dimacs", "w", stdout);
    //Add an additional clause which is a disjunction of all literals
    Dimacs inputDimacs = Dimacs(1);
    //Initializing output dimacs
    Dimacs outputDimacs = Dimacs(0);
    outputDimacs.clauses=1;
    outputDimacs.literals=0;
    outputDimacs.clauseDefinitions.push_back(vector<int>(0));
    bool tautology=false, unsatisfiable=false;
    //One iteration per proposition, after each iteration we generate a literal, in ith iteration we generate 
    //either 0 || 1 || P_i || neg(P_i)
    for(int proposition=1;proposition<=inputDimacs.literals;proposition++){
        int ones=0;
        int zeroes=0;
        int propPositives=0;
        int propNegatives=0;
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

        if(zeroes>0){
            unsatisfiable = true;
        }
        else{
            if(propPositives!=0 || propNegatives!=0){
                if(propPositives!=0 && propNegatives!=0){
                    unsatisfiable=true;
                }  
                else{
                    outputDimacs.literals++;
                    if(propPositives>0){
                        outputDimacs.clauseDefinitions[0].push_back(proposition);
                    }
                    else{
                        outputDimacs.clauseDefinitions[0].push_back(-proposition);
                    }
                }
            }
            else{
                tautology = true;
            }
        }
    }
    if(tautology){
        outputDimacs.literals=1;
        outputDimacs.clauseDefinitions[0] = {1,-1};
    }
    else if(unsatisfiable){
        outputDimacs.literals=1;
        outputDimacs.clauseDefinitions[0] = {1};
        outputDimacs.clauseDefinitions.push_back({-1});
    }
    outputDimacs.printDimacs();
}


