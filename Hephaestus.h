// Hephaestus.h
// Named after the Greek god of technology
// Computational Mathematics 6933
// Fall 2010
// Term project

// Taher Haveliwala: Efficient computation of PageRank
// block nested-loops-join strategy to efficiently control the cost per iteration
// single-precision rank values sufficient [has been shown empirically]
// optimum number of iterations required [to be used in converge()]
    
// Assuming the matrix is square and stochastic [all rows sum up to 1]
// Assuming all nodes have at least one outgoing edge
// For N vertices, assign each link a value of 1/N, others 0
// Vector Rank, N elements; Matrix M, N X N
// Rank* obtained by repeated Rank X M (matrix-vector multiplication)
// Rank* = 'dominant eigenvector of M'
// Rank* = stationary probability distribution over pages induced by a random walk on the graph

// Convergence checked by Residual, another vector
// Dominant eigenvalue of the stochastic square matrix M = 1
// The dominant eigenvector, Rank*, has eigenvalue 1
// M X Rank* = Rank*
// Deviation from this equality for some other vector = error estimate
// For Rank_i, Residual_i
// = M X Rank_i - Rank_i
// = Rank_i+1 - Rank_i  
// For Rank*, |Residual_i| -> 0 [after a sufficient number of iterations]

// To enforce every node in G to have an outgoing edge:
//	remove nodes in G that have outdegree 0
// 	i.e. rows in adjMatrix that are completely 0

// Converge of PageRank guaranteed only if:

// 	M is aperiodic [A^k != A] 
// 	Check not implemented

// And

//	M is irreducible [G is strongly connected]
//	>Add a damping factor to the rank propogation
//	>I.e. add transition edges of probability 1-c/N between every pair
//	> M' = cM + (1-c) X [1/N]_NXN
// 	> Rank' = M' X Rank = cM X (1-c) X [1/N]_NX1

// Personalization/ biasing: Replace [1/N]_NX1 by the biasVec
// M' need not be stored; needs to be evaluated efficiently

#include<vector>
using namespace std;

#ifndef HEPHAESTUS_H
#define HEPHAESTUS_H

typedef struct v_type {
    int index;
    double value;
} v_type;

class Hephaestus {
	private:
	
	// Attributes
	int numIter;			    		    // 	number of iterations
	int numRows;			    		    // 	number of rows in the matrix
	double d;				          	    //	damping factor
	double threshold;		    		    //	threshold for stopping computation
	vector<double> biasVec;				    // 	biasing vector
    vector<double> personalization;         //  personalization vector  
	vector<vector<v_type> > adjLists;		// 	adjacency lists
							
	bool iterated, biased, weighted, directed;	//	booleans
	
	double getVectorDifference(vector<double> source, vector<double> dest) {
	    double diff = 0;
	    for(int i = 0; i < source.size(); i++)
	        diff += (source[i] - dest[i]) * (source[i] - dest[i]);
		    
	    return sqrt(diff);    
	}
    
    void naivePageRank(vector<double>& source, vector<double>& dest,
        double &residual, int &N) {
        
        for(int i = 0; i < N; i++)
            dest.push_back(0);
        
        for(int j = 0; j < N; j++) {
            int s = j;
            int n = adjLists[s].size();
            vector<int> dests;
                        
            for(int k = 0; k < n; k++)
                dests.push_back(adjLists[s][k].index);
                                       
            for(int m = 0; m < n; m++) 
                dest[dests[m]] += source[s]/n;
        }
        
        for(int i = 0; i < N; i++)
            dest[i] = d * dest[i] + (1 - d) * personalization[i];
            
        residual = getVectorDifference(source, dest);
        
        source = dest;
               
        for(int it = 0; it < dest.size(); it++) 
            cout << dest[it] << " ";
        
        cout << endl;
        
        dest.clear();       
        
    }

	public:

	// Constructors
	Hephaestus(bool iterated, bool biased, bool weighted, bool directed,
		int numRows, int numIter,
		double threshold, double d,
		vector<double> biasVec, vector<double> personalization,
		vector <vector<v_type> > adjLists);
	// Destructor
	~Hephaestus();
	// Methods
	//	check()
	void check();
	//	iteration-based naive method
	vector<double> iterateNaive();
	//	convergence-based naive method
	vector<double> convergeNaive();
    //  iteration-based block-based strategy
    vector<double> iterateSmarter();
    //  convergence-based block-based strategy
    vector<double> convergeSmarter();
	
};

Hephaestus::Hephaestus(bool iteratedP, bool biasedP, bool weightedP, bool directedP,
        int numRowsP, int numIterP,
        double thresholdP, double dP,
        vector<double> biasVecP, vector<double> personalizationP,
        vector <vector<v_type> > adjListsP) {
	
    
    iterated = iteratedP;
    biased = biasedP;
    weighted = weightedP;
    directed = directedP;
    
    numRows = numRowsP;
    numIter = numIterP;
    
    threshold = thresholdP;
    d = dP;
    
    biasVec = biasVecP;
    personalization = personalizationP;
    adjLists = adjListsP;
    
}

Hephaestus::~Hephaestus() {
    delete(this);
}

void Hephaestus::check() {
    cout << "numIter = " << numIter << endl;
    cout << "numRows = " << numRows << endl;
        
    cout << "iterated = " << boolalpha << iterated << endl;
    cout << "biased = " << boolalpha << biased << endl;
    cout << "weighted = " << boolalpha << weighted << endl;
    cout << "directed = " << boolalpha << directed << endl;
    
    cout << "threshold = " << threshold << endl;
    cout << "d = " << d << endl;
    
    for(int i = 0; i < personalization.size(); i++)
        cout << personalization[i] << " ";
    cout << endl;
    
    for(int i = 0; i < biasVec.size(); i++) 
        cout << biasVec[i] << " ";
    
    cout << endl;
    
    for(int i = 0; i < adjLists.size(); i++) {
        for(int j = 0; j < adjLists[i].size(); j++)
            cout << adjLists[i][j].index << " ";
        cout << endl;
    }
    
    cout << endl;   
    
    for(int i = 0; i < adjLists.size(); i++) {
        for(int j = 0; j < adjLists[i].size(); j++)
            cout << adjLists[i][j].value << " ";
        cout << endl;
    }
                
    cout << endl;
    
}

vector<double> Hephaestus::iterateNaive() {
    vector<double> source, dest;
    double residual = 1;
    
    int N = adjLists.size();
        
    for(int i = 0; i < N; i++) {
        double temp = 1/(double)N;
        source.push_back(temp);        
    }
    
    for(int i = 0; i < numIter; i++) {
        naivePageRank(source, dest, residual, N);
    }
    return dest;
    
}


vector<double> Hephaestus::convergeNaive() {
    
    vector<double> source, dest;
    double residual = 1;
    
    int N = adjLists.size();
        
    for(int i = 0; i < N; i++) {
        double temp = 1/(double)N;
        source.push_back(temp);        
    }
    
    while(residual > threshold) {
        naivePageRank(source, dest, residual, N);
    }
    return dest;
}


#endif