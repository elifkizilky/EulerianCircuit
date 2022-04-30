#include <iostream>
#include <queue>
#include <fstream>
#include "Vertex.h"

using namespace std;

void myMerge(vector<int*> &circuit, vector<int*> &tour, int index);
Vertex* findVertex (vector<int*>& circuit, vector<Vertex*>& vertex, int& index);
bool isEulerian(vector<Vertex*> &vertex);

int main(int argc, char const *argv[]) {	

	int lengthEdge = 0; // holds the number of edges
	std::vector<Vertex*> vertices;

	string infile_name = argv[1];
	string outfile_name = argv[2];

	ifstream infile;
	infile.open(infile_name);

	ofstream outfile;
	outfile.open(outfile_name);  

	int totVertices;
	infile >> totVertices;
	vertices.reserve(totVertices);
	
	for (int i = 0; i < totVertices; i++) //creating the vertices
	{
		vertices.push_back(new Vertex(i));
	}

	int id, out, sinkID;
	for (int i = 0; i < totVertices; i++)
	{
		infile >> id;
		infile >> out;
		lengthEdge += out;
		vertices[id]->outDegree = out;
		if(vertices[id]->inDegree > vertices[id]->outDegree){
			for(auto p : vertices){
    	     delete p;
           }
				outfile << "no path";
				infile.close();
				outfile.close();
				return 0;
			}

		for (int i = 0; i < out; i++)
		{
			infile >> sinkID; 
			vertices[id]->adjacencyList->push(sinkID);
			vertices[sinkID]->inDegree++;
    	}
	}

	int startIndex;
	infile >> startIndex ;

	if(!isEulerian(vertices)){
		outfile << "no path";
		for(auto p : vertices){
    	delete p;
    }
		infile.close();
		outfile.close();
		return 0;
	}

	vector<int*> circuit;
	circuit.reserve(lengthEdge + 1);
	circuit.push_back(&startIndex);
	Vertex* temp = vertices[startIndex];
	int index = 0;

	while(circuit.size() <= lengthEdge){
		vector<int*> tour;
		while(!temp->adjacencyList->empty()){
			int edge = temp->adjacencyList->front();
			temp->adjacencyList->pop();
			temp = vertices[edge];
			tour.push_back(&temp->ID);
		}
		myMerge(circuit,tour,index);
	  
	    if(circuit.size() <= lengthEdge){
		temp = findVertex(circuit,vertices,index);
		}
	}
		
	
	for(int i = 0; i < circuit.size(); i++){
		outfile << *circuit[i] << " ";
	}

    infile.close();
    outfile.close();    
    
    for(auto p : vertices){
    	delete p;
    }

	return 0;
}

void myMerge(vector<int*> &circuit, vector<int*> &tour, int index){

	vector<int*> temp;
	for(int i = 0; i <= index ; i++){
		temp.push_back(circuit[i]);
	}
	for (int i = 0; i < tour.size() ; i++)
	{
		temp.push_back(tour[i]);
	}
	for(int i = index + 1; i < circuit.size() ; i++ ){
		temp.push_back(circuit[i]);
	}

	circuit = temp;
}

Vertex* findVertex (vector<int*> &circuit, vector<Vertex*> &vertex, int &index){ 
	for(int i = 0; i < circuit.size() ; i++){
		int* id = circuit[i];
		if(!vertex[*id]->adjacencyList->empty()){
			index = i;
			return vertex[*id];
		}
	}
}

bool isEulerian(vector<Vertex*> &vertex){
	for (int i = 0; i < vertex.size(); i++)
	{
		if(vertex[i]->inDegree != vertex[i]->outDegree){
			return false;
		}
	}
	return true;
}
