//Created by Brandon Barnes

#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Node;
class Edge;
class Graph;

class Edge{
	int weight;
	Node* start;
	Node* end;
	
	public:
	Edge(int newWeight, Node* newStart, Node* newEnd){
		weight = newWeight;
		start = newStart;
		end = newEnd;
	}
	
	
};

class Node{
	int distance;
	Node* parent;
	int colour;
	vector<Edge> outgoingEdges;
	
	public:
	Node(){
		distance = 0;
		parent = NULL; 
		int colour = 0;
	}
	Node(int newDistance, Node* newParent, int newColour){
		distance = newDistance;
		parent = newParent;
		colour = newColour;
	}
	void addEdge(int newWeight, Node* newStart, Node* newEnd){
		Edge newEdge = Edge(newWeight, newStart, newEnd);
		outgoingEdges.push_back(newEdge);
	}
	
	void setColour(int newColour){
		this->colour = newColour;
	}
	void setDistance(int newDistance){
		this->distance = newDistance;
	}
	
};



class Graph{
	vector<Node> Nodes;
	
	void DFSHelper(Node* startNode){
		
	}
	
	public:
	void addNode(Node newNode){
		Nodes.push_back(newNode);
	}
	
	Node* getNode(int position){
		if(position >= 0 && position < Nodes.size()){
			return &(Nodes[position]);
		}
		else {return NULL;}
	}
	
	
	void DFS(Node* startNode){
		
	}
};

int main(){
	Graph defaultGraph;
	for(int i = 0; i<10; i++){
		defaultGraph.addNode(Node());
		if(i>1){
			defaultGraph.getNode(i)->addEdge(i+1,defaultGraph.getNode(i), defaultGraph.getNode(i-1));
		}
	}
	cout << "job done" << endl;
	return 0;
	
}