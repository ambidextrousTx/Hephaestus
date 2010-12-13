// Hephaestus main.cpp
// Named after the Greek god of technology
// Computational Mathematics 6933
// Fall 2010
// Term project

#include "HephHelperFuncs.h"

int main(int argc, char *argv[]) {
    
    // Variables    
    bool iterated, biased, weighted, directed;
    int numRows, numIter;
    double threshold, d;
    vector<double> biasVec;
    vector <vector<v_type> > adjLists;
    
    // Variable vector for the final results
    vector<double> pageRank;
    
    // Check for arguments
    checkArguments(argc);
    
    // Get all arguments
    getArguments(iterated, biased, weighted, directed,
        numRows, numIter, threshold, d, biasVec, adjLists);
    
    // Create the Hephaestus object
    Hephaestus *hObject = new Hephaestus(iterated, biased, weighted, directed,
        numRows, numIter, threshold, d, biasVec, adjLists);
    
    // Check if all's well
    // hObject->check();
    
    pageRank = hObject->converge();
   
   /* 
    for(int pi = 0; pi < pageRank.size(); pi++)
        cout << pageRank[pi] << " ";
    
    cout << endl;
   */
    /*
   
    pageRank = iterated ? hObject->iterate() : hObject->converge();
    
    for(int pi = 0; pi < pageRank.size; pi++)
        cout << pageRank[pi] << " ";
        
    cout << endl;
    */
   
    return 0;
}
