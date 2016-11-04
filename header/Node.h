#ifndef NODE_H
#define NODE_H
using namespace std;


#include <vector>
#include "../header/edge.h"
#include <boost/shared_ptr.hpp>

class Edge;

class Node {

	//protected Edge[] adjEdges;

public:
	vector<boost::shared_ptr<Node>> adjNodesList;
	vector<boost::shared_ptr<Edge>> adjEdgesList;
	bool isDev = false;
	int number;
	int x;
	int y;


public:
	Node(){
		number = 0;

	}
	Node(int i, int j){
		x = i;
		y = j;

	}

	Node(int i)
	{
		//adjNodesList = new ArrayList<Node>();
		//coord = new Int4();
		number = i;
	}

	void setNumber(int i) {
		number = i;
	}





	void setAdjNodes(boost::shared_ptr<Node> node) {
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






	static bool aLeftOrUnderb(boost::shared_ptr<Node> a, boost::shared_ptr<Node> b){
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

	static int hash2Int(int a, int b){
		return a * 100 + b;
	}

	static int hash4int(int a, int b, int c, int d){
		return a*100000 + b * 10000+ c*100 +d;
	}

	static int hash2Nodes(Node& a,Node& b){
		if(aLeftOrUnderb(a,b))
			return hash4int(a.x,a.y,b.x,b.y);

			return hash4int(b.x,b.y,a.x,a.y);
	}
	int hashValue(){
		return hash2Int(x, y);
	}
};





#endif
