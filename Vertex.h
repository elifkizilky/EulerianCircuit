#include <queue>
using namespace std;

#ifndef VERTEX_H
#define VERTEX_H

class Vertex {

public:
	int ID;
	int inDegree; 
	int outDegree;
	queue<int> * adjacencyList;

	Vertex (int ID);
	Vertex (const Vertex& vertex);
	Vertex& operator=(const Vertex& vertex);
	~Vertex();

};
#endif