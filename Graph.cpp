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
	
	void DFSHelper(Node* startNode, int startDistance){
		for(int i = 0; i < startNode->outgoingEdges.size(); i++){
			if(startNode->outgoingEdges[i]->end->colour==0){
				startNode->outgoingEdges[i]->end->colour = 1;
				startNode->outgoingEdges[i]->end->parent = startNode;
				startNode->outgoingEdges[i]->end->distance = startDistance+1;
				DFSHelper(startNode->outgoingEdges[i]->end);
			}
		}
		startNode->colour=2;
		
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
		for(int i = 0; i <Nodes.size(); i++){
			Nodes[i].distance = 2^31-1;
			Node[i].colour = 0;
			Node[i].parent = NULL;
		}
		bool finishFlag = false;
		startNode->distance=0;
		Node[i].colour = 1;
		DFSHelper(startNode, 0);
		for(int i = 0; i< Nodes.size(); i++){
			if(Nodes[i].colour = 0){
				Nodes[i].colour = 1;
				Nodes[i].distance = 0; //temp while time started and finished not implemented
				DFSHelper(&(Nodes[i]), 0);
			}
		}
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