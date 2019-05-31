//Created by Brandon Barnes
/*
	Contains basic Graph generation and search functions
*/
#include <iostream>
#include <vector>
#include <stdlib.h>

using namespace std;

class Node;
class Edge;
class Graph;


//Edges for graph
class Edge{
	
	int weight;
	Node* start;
	Node* end;
	
	public:
	Edge(int newWeight, Node* newStart, Node* newEnd){
		this->weight = newWeight;
		this->start = newStart;
		this->end = newEnd;
	}
	Node* getEnd(){
		return this->end;
	}
	
	
};

//Node class for graph
class Node{
	int distance;
	Node* parent;
	int colour;
	int discoveryTime;
	int finishTime;
	vector<Edge> outgoingEdges;
	
	public:
	//Constructor for nodes
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
	
	
	
	//For adding an edge onto Nodes
	void addEdge(int newWeight, Node* newStart, Node* newEnd){
		Edge newEdge = Edge(newWeight, newStart, newEnd);
		outgoingEdges.push_back(newEdge);
	}
	
	
	//Getters and Setters for node
	void setColour(int newColour){
		this->colour = newColour;
	}
	int getColour(){
		return this->colour;
	}
	void setDistance(int newDistance){
		this->distance = newDistance;
	}
	void setDiscovery(int setValue){
		this->discoveryTime=setValue;
	}
	void setFinish(int setValue){
		this->finishTime=setValue;
	}
	Edge getEdge(int position){
		return this->outgoingEdges[position];
	}
	void setParent(Node* setValue){
		this->parent = setValue;
	}
	vector<Edge> getVector(){
		return this->outgoingEdges;
	}
	int getFinish(){
		return this->finishTime;
	}
	int getDistance(){
		return this->distance;
	}
};



class Graph{
	
	vector<Node> Nodes; //Contains nodes for graph
	
	//Called by both the DFS functions for recursive traversal and flagging
	int DFSHelper(Node* startNode, int startDistance, int* currentTime){
		cout <<"does it run" << endl;
		cout << startNode->getEdge(0).getEnd()->getColour() << endl;
		for(int i = 0; i < startNode->getVector().size(); i++){
			if(startNode->getEdge(i).getEnd()->getColour()==0){
				cout << "job not done" << endl;
				startNode->getEdge(i).getEnd()->setColour(1); //Flag as visited
				startNode->getEdge(i).getEnd()->setParent(startNode); //Set parent to calling node
				startNode->getEdge(i).getEnd()->setDistance(startDistance+1); //set distance
				
				//Set discovery time of node
				startNode->getEdge(i).getEnd()->setDiscovery(*currentTime);
				*currentTime++; //update timer
				
				*currentTime = DFSHelper(startNode->getEdge(i).getEnd(), startDistance+1, currentTime);
			}
			else{ //For minimal path back to startNode
				if(startNode->getEdge(i).getEnd()->getDistance()>startDistance+1){
					//Update distance and parent
					startNode->getEdge(i).getEnd()->setDistance(startDistance+1);
					startNode->getEdge(i).getEnd()->setParent(startNode);
				}
			}
		}
		
		startNode->setColour(2); //Flag as completely explored
		startNode->setFinish(*currentTime); //Set finish time
		return startNode->getFinish()+1;
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
	
	//DFS that traverses only nodes with path from startNode to node
	void DFS(Node* startNode){
		if(startNode==NULL){
			return;
		}
		
		//initialize graph
		for(int i = 0; i<Nodes.size(); i++){
			Nodes[i].setDistance(2^31-2);
			Nodes[i].setColour(0);
			
			Nodes[i].setParent(NULL);
		}
		//start timer
		int temp;
		int* time = &temp;
		*time = 1;
	
		//initialize startNode
		startNode->setDistance(0);
		startNode->setColour(1);
		startNode->setDiscovery(0);
		
		DFSHelper(startNode, 0, time);
		
	}
	//DFS that goes to all nodes
	void allDFS(Node* startNode){
		if(startNode==NULL){
			return;
		}
		//initialize graph for dfs
		for(int i = 0; i <Nodes.size(); i++){
			Nodes[i].setDistance(2^31-2);
			Nodes[i].setColour(0);
			Nodes[i].setParent(NULL);
		}
		//initialize start
		bool finishFlag = false;
		startNode->setDistance(0);
		startNode->setColour(1);
		startNode->setDiscovery(0);
		
		//Start timer
		int temp = 0;
		int* currentFinish = &temp; 
		
		//for initial runthrough from star node
		*currentFinish = DFSHelper(startNode, 0, currentFinish);
		
		//Checks all other untouched nodes in positional order from Graph.Nodes
		for(int i = 0; i<Nodes.size(); i++){
			
		
				cout << Nodes[i].getColour() << endl;
				
		
			if(Nodes[i].getColour() == 0){
				Nodes[i].setColour(1);
				Nodes[i].setParent(NULL);
				Nodes[i].setDistance(0); //temp while time started and finished not implemented
				*currentFinish=DFSHelper(&(Nodes[i]), 0, currentFinish);
			}
		}
	}
};

int main(){ //testbed for graph functions
	Graph defaultGraph;
	int temp = 0;
	for(int i = 0; i<20; i++){ //initialize graph
		Node* tempNode = new Node(0, NULL, temp);
		defaultGraph.addNode(*tempNode);
		if(i>0){
			defaultGraph.getNode(i)->addEdge(i+1,defaultGraph.getNode(i), defaultGraph.getNode(i-1));
		}
	}
	
	defaultGraph.DFS(defaultGraph.getNode(13));
	//defaultGraph.allDFS(defaultGraph.getNode(2));
	cout << "job done" << endl;
	return 0;
	
}