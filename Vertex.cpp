#include "Vertex.h"
using namespace std;

    Vertex::Vertex (int ID){
		this->ID = ID;
		this->inDegree = 0;
		this->outDegree = 0;
		this->adjacencyList = new queue<int>();
	}

	Vertex::Vertex (const Vertex& vertex){
		this->ID = vertex.ID;
		this->inDegree = vertex.inDegree;
		this->outDegree = vertex.outDegree;
		this->adjacencyList = vertex.adjacencyList;
	}
	Vertex& Vertex::operator=(const Vertex& vertex){
		if(this == &vertex){
			return *this;
		}

		this->ID = vertex.ID;
		this->inDegree = vertex.inDegree;
		this->outDegree = vertex.outDegree;
		this->adjacencyList = vertex.adjacencyList;

		return *this;

	}
	Vertex::~Vertex(){
		delete this->adjacencyList;
	}