/*****************************************
 * Instructions
 *  - Replace 'uwuserid' with your uWaterloo User ID
 *  - Select the current calendar term and enter the year
 *  - List students with whom you had discussions and who helped you
 *
 * uWaterloo User ID:  uwuserid @uwaterloo.ca
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 201N
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *
 * The following is a list of uWaterloo User IDs of those students
 * I had discussions with in preparing this project:
 *    -
 *
 * The following is a list of uWaterloo User IDs of those students
 * who helped me with this project (describe their help; e.g., debugging):
 *    -
 *****************************************/

#ifndef WEIGHTED_GRAPH_H
#define WEIGHTED_GRAPH_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"
#include "Disjoint_sets.h"

using namespace std;

class Weighted_graph {
	private:
		static const double INF;
		double** graph;
		int num_nodes;
		int num_edges;
		

		// Do not implement these functions!
		// By making these private and not implementing them, any attempt
		// to make copies or assignments will result in errors
		Weighted_graph( Weighted_graph const & );
		Weighted_graph &operator=( Weighted_graph );

		// your choice

	public:
		Weighted_graph( int = 10 );
		~Weighted_graph();

		int degree( int ) const;
		int edge_count() const;
		std::pair<double, int> minimum_spanning_tree() const;

		bool insert_edge( int, int, double );
		bool erase_edge( int, int );
		void clear_edges();

	// Friends

	friend std::ostream &operator<<( std::ostream &, Weighted_graph const & );
};

const double Weighted_graph::INF = std::numeric_limits<double>::infinity();

Weighted_graph::Weighted_graph(int n ) {
    //check for input
    if(n < 0){
        throw illegal_argument();
    }
    //initiate number of edges and nodes
    num_edges = 0;
    num_nodes = n;
    
    //initiate the adjacency matrix and assign all the crossing point to infinity
    graph = new double*[n];
    for(int i = 0; i < n; i++){
        graph[i] = new double[n];
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            graph[i][j] = INF;
        }
    }
}

Weighted_graph::~Weighted_graph() {
    //delete every index in each row
    for(int i = 0; i < num_nodes; i++){
        delete [] graph[i];
    }
    delete [] graph;
}

int Weighted_graph::degree(int u) const {
    int degrees = 0;
    
    //check for input
    if(u < 0 || u > (num_nodes - 1)){
        throw illegal_argument();
    }
    
    //count the number of degree of this vertex u
    for(int i = 0; i < num_nodes; i++){
        if(graph[i][u] != INF){
            degrees++;
        }
    }
	return degrees;
}

int Weighted_graph::edge_count() const {
	return num_edges;
}

bool Weighted_graph::erase_edge(int i, int j) {
    //check for input
    if(i < 0 || j < 0 || i >= num_nodes || j >= num_nodes){
        throw illegal_argument();
    }
    
    if(i == j){
        return true;
    }
    
    //delete the edge between ij if there is a edge exist
    if(graph[i][j] != INF || graph[j][i] != INF){
        num_edges--;
        graph[i][j] = INF;
        graph[j][i] = INF;
    }
    else{
        return false;
    }
	return true;
}

void Weighted_graph::clear_edges() {
    //reset the all the crossing point to infinity
    for(int i = 0; i < num_nodes; i++){
        for(int j = 0; j < num_nodes; j++){
            graph[i][j] = INF;
        }
    }
    //reset the number of edges
    num_edges = 0;
	return;
}

bool Weighted_graph::insert_edge( int i, int j, double d ) {
    //check for input
    if(i < 0 || j < 0 || i >= num_nodes || j >= num_nodes || d <= 0){
        throw illegal_argument();
    }
    
    if(i == j){
        return false;
    }
    
    //if there is no edge then insert one
    if(graph[i][j] == INF && graph[j][i] == INF){
        num_edges++;
    }
    //update the weight of the edge wether if there is edge or just inserted one
    graph[i][j] = d;
    graph[j][i] = d;
    
	return true;
}

std::pair<double, int> Weighted_graph::minimum_spanning_tree() const {
    //initiate 3 same size array to store two vertices and weights in between
    int* vertexI = new int[num_edges];
    int* vertexJ = new int[num_edges];
    double* weight = new double[num_edges];
    
    //initiate the minimum edges and total weight after mst
    int minEdges = 0;
    double totalWeight = 0;
    
    //create a disjoint data structure
    Disjoint_set S(num_nodes);
    
    //loop through the graph to get the vertices and weights
    int index = 0;
    for(int i = 0; i < num_nodes; i++){
        for(int j = i + 1; j < num_nodes; j++){
            if(graph[i][j] != INF){
                vertexI[index] = i;
                vertexJ[index] = j;
                weight[index] = graph[i][j];
                index++;
            }
        }
    }
    
    //using bubble sort to sort from smallest to largest for weights array
    int tempI;
    int tempJ;
    double tempW;
    
    for(int i = 0; i < num_edges - 1; i++){
        for(int j = 0; j < num_edges - 1 - i; j++){
            if(weight[j] > weight[j+1]){
                tempI = vertexI[j];
                vertexI[j] = vertexI[j+1];
                vertexI[j+1] = tempI;
                
                tempJ = vertexJ[j];
                vertexJ[j] = vertexJ[j+1];
                vertexJ[j+1] = tempJ;
                
                tempW = weight[j];
                weight[j] = weight[j+1];
                weight[j+1] = tempW;
            }
        }
    }
    
    //using Kruskal's algorithm
    for(int i = 0; i < num_edges; i++){
        if(S.num_sets() > 1){
            if(S.find_set(vertexI[i]) != S.find_set(vertexJ[i])){
                S.union_sets(vertexI[i], vertexJ[i]);
                totalWeight = totalWeight + weight[i];
            }
        minEdges++;
        }
    }
    
    //delete all three arrays after mst
    delete[] vertexI;
    delete[] vertexJ;
    delete[] weight;

	return std::pair<double, int>( totalWeight, minEdges );
}

std::ostream &operator<<( std::ostream &out, Weighted_graph const &graph ) {
	

	return out;
}


#endif
