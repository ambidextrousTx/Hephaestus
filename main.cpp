// Hephaestus main.cpp
// Named after the Greek god of technology
// Computational Mathematics 6933
// Fall 2010
// Term project

#include "HephHelperFuncs.h"

int main(int argc, char *argv[]) {
    
    // Variables    
    bool iterated, biased, weighted, directed, smart;
    int numRows, numIter;
    double threshold, d;
    vector<double> biasVec, personalization;
    vector <vector<v_type> > adjLists;
    
    // Variable vector for the final results
    vector<double> pageRank;
    
    // Check for arguments
    checkArguments(argc);
    
    // Get all arguments
    getArguments(iterated, biased, weighted, directed, smart,
        numRows, numIter, threshold, d, biasVec, adjLists);
    
    // Handle the personalization vector / biasing
    if(biased)
        for(int i = 0; i < biasVec.size(); i++)
            personalization.push_back(biasVec[i]);
    else
        for(int i = 0; i < adjLists.size(); i++) {
            double temp = 1/(double)adjLists.size();
            personalization.push_back(temp);
        }    
    
    
    // Create the Hephaestus object
    Hephaestus *hObject = new Hephaestus(iterated, biased, weighted,
        directed, smart,
        numRows, numIter, threshold, d, biasVec, personalization, adjLists);
    
    // Check if all's well
    hObject->check();
    
    pageRank = smart ? 
        (iterated ? hObject->iterateSmart() : hObject->convergeSmart())
        : (iterated ? hObject->iterateNaive() : hObject->convergeNaive());
       
    cout << "Hephaestus successfully completed." << endl;
    
    for(int pi = 0; pi < pageRank.size(); pi++)
        cout << pageRank[pi] << " ";
    
    cout << endl;
   
    return 0;
}
