#ifndef NODE_H
#define NODE_H
using namespace std;


#include <vector>
#include "../header/edge.h"
#include <boost/shared_ptr.hpp>
#include <string>
#include "../header/Algorithm.h"
class Edge;

class Node {

	//protected Edge[] adjEdges;

public:
	vector<Node*> adjNodesList;
	vector<Edge*> adjEdgesList;
	bool isDev = false;
	int number;
	int x;
	int y;
	string name;

public:


	Node(){
		number = 0;
		setName();
	}
	Node(int i, int j){
		x = i;
		y = j;
		adjNodesList.clear();
		adjEdgesList.clear();
		//std::to_string(i);
		setName();

	}

	Node(int i)
	{
		//adjNodesList = new ArrayList<Node>();
		//coord = new Int4();
		number = i;
		setName();
	}

	void setNumber(int i) {
		number = i;
	}
	void setName(){
		name = string("x") + std::to_string(x) + string("y") + std::to_string(y);
	}

	void printMyself(){
		cout << "im node " << "x" << x <<"y" << y << endl;
	}


	void setAdjNodes(Node* node) {
		adjNodesList.push_back(node);
		//adjNodes = adjNodesList.toArray(new Node[adjNodesList.size()]);
	}

	void setCoord(int a, int b, int c, int d){
		x = a;
		y = b;

	}

	void setCoord(int a, int b){
		x = a;
		y = b;
	}

	vector<Node*>* getAdjNodes(){
		return &adjNodesList;
	}
	vector<Edge*>* getAdjEdges(){
		return &adjEdgesList;
	}





	static bool aLeftOrUnderb(Node* a, Node* b){
		if(a->x < b->x || a->y < b->y )
			return true;
		else
			return false;
	}
	static bool aLeftOrUnderb(Node a, Node b){
			if(a.x < b.x || a.y < b.y )
				return true;
			else
				return false;
		}

/*	static int hash2Int(int a, int b){
		return a * 100 + b;
	}

	static int hash4int(int a, int b, int c, int d){
		return a*100000 + b * 10000+ c*100 +d;
	}*/

	static int hash2Nodes(Node& a,Node& b){
		if(aLeftOrUnderb(a,b))
			return algo::hash4Int(a.x,a.y,b.x,b.y);

			return algo::hash4Int(b.x,b.y,a.x,a.y);
	}
	int hashValue(){
		return algo::hash2Int(x, y);
	}
};





#endif
