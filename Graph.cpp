//Created by Brandon Barnes
/*
	Contains basic Graph generation and search functions
*/
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <queue>

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
		this->weight = *(new int);
		this->weight = newWeight;
		this->start = newStart;
		this->end = newEnd;
	}
	Edge(){
		this->start=NULL;
		this->end=NULL;
		this->weight=-1;
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
		this->distance = *(new int);
		this->parent = (new Node);
		this->colour = *(new int);
		this->discoveryTime = *(new int);
		this->finishTime = *(new int);
		distance = newDistance;
		parent = newParent;
		colour = newColour;
	}
	
	
	
	//For adding an edge onto Nodes
	void addEdge(int newWeight, Node* newStart, Node* newEnd){
		Edge newEdge = Edge(newWeight, newStart, newEnd);
		this->outgoingEdges.push_back(newEdge);
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
	vector<Edge>* getVector(){
		if(this->outgoingEdges.empty()){
			//cout << "it was null" << endl;
			return NULL;
		}
		
		return &(this->outgoingEdges);
	}
	int getFinish(){
		return this->finishTime;
	}
	int getDistance(){
		return this->distance;
	}
	Node* getParent(){
		return this->parent;
	}
	~Node(){
		outgoingEdges.clear();
		//Not deleting parent since that may still be a member of the graph
	}
};



class Graph{
	
	vector<Node> Nodes; //Contains nodes for graph
	
	//Called by both the DFS functions for recursive traversal and flagging
	int DFSHelper(Node* startNode, int startDistance, int* currentTime){
		//cout << "enter helper" << endl;
		if(startNode==NULL){
			return *currentTime;
		}
		
		if(startNode->getVector() == NULL){
			startNode->setColour(2); //Flag as completely explored
			startNode->setFinish(*currentTime); //Set finish time
			return startNode->getFinish()+1;
		}
		//cout <<"does it run" << endl;
		int temp;
		for(int i = 0; i < startNode->getVector()->size(); i++){
			//cout << "how many loops  " << i << endl;
			if(startNode->getEdge(i).getEnd() != NULL){
				
				if(startNode->getEdge(i).getEnd()->getColour()==0){
					
					startNode->getEdge(i).getEnd()->setColour(1); //Flag as visited
					startNode->getEdge(i).getEnd()->setParent(startNode); //Set parent to calling node
					startNode->getEdge(i).getEnd()->setDistance(startDistance+1); //set distance
					//cout << "edge access is not it" << endl;
					//Set discovery time of node
					startNode->getEdge(i).getEnd()->setDiscovery(*currentTime);
					*currentTime = *currentTime + 1; //update timer
				
					//cout << "recursive entry is in" << endl;
					temp = DFSHelper(startNode->getEdge(i).getEnd(), startDistance+1, currentTime);
					//cout << "exit helper" << endl;
					*currentTime = temp;
			
				}
			}
			
		}
		//cout << "compare count  " << (*currentTime) <<endl;
		startNode->setColour(2); //Flag as completely explored
		startNode->setFinish(*currentTime); //Set finish time
		//cout << "does helper exit" << endl;
		return *currentTime+1;
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
		int temp = 1;
		int* time = &temp;
		
		//initialize startNode
		startNode->setDistance(0);
		startNode->setColour(1);
		startNode->setDiscovery(0);
	
		DFSHelper(startNode, 0, time);
		//cout << "exit helper" << endl;
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
		int tempTwo = 0;
		
		//for initial runthrough from star node
		*currentFinish = DFSHelper(startNode, tempTwo, currentFinish);
		
		//Checks all other untouched nodes in positional order from Graph.Nodes
		for(int i = 0; i<Nodes.size(); i++){
			
				//cout << "Current Node: " << i << endl;
				//cout << "Colour of Node: " << Nodes[i].getColour() << endl;
				
		
			if(Nodes[i].getColour() == 0){
				//cout<<"calling dfshelper from loop" << endl;
				Nodes[i].setColour(1);
				Nodes[i].setParent(NULL);
				Nodes[i].setDistance(0); //temp while time started and finished not implemented
				
				*currentFinish=DFSHelper(&(Nodes[i]), 0, currentFinish);
			}
			
		}
	}
	
	void BFS(Node* startNode){
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
		queue<Node*> toResolve;
		toResolve.push(startNode);
		startNode->setColour(1);
		Node* workingNode;
		
		while(!(toResolve.empty())){ //When empty then all reachable nodes have been visited and resolved
			
			workingNode = toResolve.front(); 
			if(workingNode->getVector()==NULL){ //Prevents overstepping of graph
				workingNode->setColour(2);
				toResolve.pop();
				return;
			}
			if(workingNode->getParent()==NULL){ //for source node
				workingNode->setDistance(0);
			}
			else{ //For non-source nodes, makes distance = parent distance + 1
				workingNode->setDistance(workingNode->getParent()->getDistance()+1);
			}
			
			
			for(int i = 0; i<workingNode->getVector()->size(); i++){ 
				
				if(workingNode->getEdge(i).getEnd()->getColour()==0){ //Only for unvisited nodes
					workingNode->getEdge(i).getEnd()->setColour(1); //set as visited
					workingNode->getEdge(i).getEnd()->setParent(workingNode); //set parent to workingNode
					toResolve.push(workingNode->getEdge(i).getEnd());  //push node onto queue
				}
			}	
			workingNode->setColour(2); //Set as resolved
			toResolve.pop(); //pop off from queue
		}
	}
	
	
	
	Graph(vector<Node> inputSet){
		this->Nodes = inputSet;
	}
	~Graph(){
		Nodes.clear();
		cout << "Successfully deleted Graph";
		return;
	}
};

int main(){ //testbed for graph functions
	
	int temp = 0;
	vector<Node> inputSet;
	for(int i = 0; i<6; i++){ //initialize graph
		inputSet.push_back(Node(temp, NULL, temp));
	}
	Graph defaultGraph = Graph(inputSet);
	for(int i = 0; i<inputSet.size()-1; i++){
		defaultGraph.getNode(i)->addEdge(i+1, defaultGraph.getNode(i), defaultGraph.getNode(i+1));
	}
	
	
	//defaultGraph.DFS(defaultGraph.getNode(0));
	//defaultGraph.allDFS(defaultGraph.getNode(3));
	defaultGraph.BFS(defaultGraph.getNode(0));
	
	
	for(int i = 0; i<6; i++){ //initialize graph
		cout << "Node " << i << " has colour " << defaultGraph.getNode(i)->getColour() << endl;
	}
	cout << "job done" << endl;
	return 0;
	
}