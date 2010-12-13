// Hephaestus HephHelperFuncs.h
// Named after the Greek god of technology
// Computational Mathematics 6933
// Fall 2010
// Term project

#include "HephIncludes.h"

#ifndef HEPHHELPERFUNCS_H
#define HEPHHELPERFUNCS_H

void checkArguments(int argc) {
    if(argc != 1) {
            cout << "Hephaestus:: A comprehensive PageRank package." << endl;
            cout << "Error: Invalid number of arguments" << endl;
            cout << "Compile: g++ main.cpp -o main" << endl;
            cout << "Run: ./main" << endl;
            cout << "Exiting ..." << endl;
            exit(1);
    }
    return;
}

vector<vector<v_type> > getAdjLists(ifstream &fsIn) {

    //declarations
    int j=0;

    string line;
    string buf;
    stringstream ss;

    v_type struct_buff;
 
    vector<vector<struct v_type> > adj_list;
    vector<struct v_type> row;
    
    //statements
    if(fsIn.is_open()){

        getline(fsIn, line);
        while(fsIn.good()) {

            //tokenize values
            stringstream ss(line);  
            j=0;
            while(ss >> buf){
                //update index value
                struct_buff.index = j;
                
                std::istringstream stm;
                stm.str(buf);
                stm >> struct_buff.value;
                
                //insert into verctor
                if(struct_buff.value != 0)
                    row.push_back(struct_buff);
                
                j++; 
                buf.clear();
            }
            
            adj_list.push_back(row);
            row.clear();
            getline(fsIn, line);
            
        } //while
    } else {
        cout << "Unable to open file. Exiting ...\n";        
    } 

    return adj_list;
}


vector<double> getBiasVector(ifstream &biasFileStream) {

    string line;
    vector<double> biasVec;
    
    if(biasFileStream.is_open()) {
        while(biasFileStream.good()) {
            getline(biasFileStream, line);
    
            stringstream ss(line);
            string buffer;
    
            while(ss >> buffer)
                    biasVec.push_back(atof(buffer.c_str()));

        }
        
    } else {
        cout << "Unable to open file. Exiting ...\n";        
    }
    
    return(biasVec);
}

void getArguments(bool &iterated, bool &biased, bool &weighted, bool &directed,
        int &numRows, int &numIter,
        double &threshold, double &d,
        vector<double>& biasVec, 
        vector <vector<v_type> >& adjLists) {
    
    string fileName, biasFile;
    string line;
    stringstream ss;
    cout << "Enter the name of the file containing the adjacency matrix (weighted or unweighted): ";
    getline(cin, line);
    ss << line;
    ss >> fileName;
    
    cout << "Please enter '1' for true or '0' for false [quotes for clarity] for the following:" << endl;
    cout << "Iterated? ";
    getline(cin, line);
    iterated = atoi(line.c_str()) ? true : false ;
    
    cout << "Biased? ";
    getline(cin, line);
    biased = atoi(line.c_str()) ? true : false;
    
    cout << "Weighted? ";
    getline(cin, line);
    weighted = atoi(line.c_str()) ? true : false;
    
    cout << "Directed? ";
    getline(cin, line);
    directed = atoi(line.c_str()) ? true : false;
    
    ifstream fst;
    fst.open(fileName.c_str());
    adjLists = getAdjLists(fst);
    fst.close();
    
    numRows = adjLists.size();
    
    if(iterated) {
        cout << "Please enter an integer value for the number of iterations: ";
        getline(cin, line);
        numIter = atoi(line.c_str());
        
    } else {
        numIter = 0;
        cout << "Please enter a real value for the threshold: ";
        getline(cin, line);
        threshold = atof(line.c_str());
        
    }
    
    cout << "Please enter a real value for the damping factor: ";
    getline(cin, line);
    d = atof(line.c_str());
    
    if(biased) {
        cout << "Enter the name of the file containing the bias vector: ";
        // Does stringstream only work in one scope and not in nested ones?
        stringstream s;
        getline(cin, line);
        
        s << line;
        s >> biasFile;
        
        ifstream bst;
        bst.open(biasFile.c_str());        
        biasVec = getBiasVector(bst);
        bst.close();
                
    } else
        biasVec.push_back(0.0);
        
    
}

void buildGraph(vector< vector<v_type> > adj_list, vector<double> pageScore, ofstream& fsOut, string graph_name){

    int i=0, j=0;

    //do a basic stream check
    if(!fsOut.is_open()) {
        cout << "Output file is not open. Function exiting\n";
        return;
    }
    
    /*print the basics -may extend this as an option*/
    fsOut << "digraph " << graph_name << " {" << endl;
    fsOut << setw(20) << "rankdir=LR;" << endl << setw(20) << "size = \"7,7\";" << endl << endl;

    //main loop
    for(i=0; i<adj_list.size(); i++){
        fsOut << "\"" << i << ":" << pageScore[i] << "\"  -> {"; 
        for(j=0; j<adj_list[i].size(); j++)
			fsOut << "\"" << adj_list[i][j].index << ":" << pageScore[adj_list[i][j].index] << "\"; ";
            
        fsOut << "}" << endl;
	}//main_loop
    fsOut << "}" << endl;
}



#endif