#ifndef NODE_H
#define NODE_H
using namespace std;


#include <iostream>
#include <vector>
#include "../header/Int4.h"



class Node {

	//protected Edge[] adjEdges;

	vector<Node> adjNodesList;
public:
	int number;
	Int4 coord;
public:
	Node(){
		number = 0;

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



	vector<Node> getAdjNodes(){
		return adjNodesList;
	}

	void setAdjNodes(Node node) {
		adjNodesList.push_back(node);
		//adjNodes = adjNodesList.toArray(new Node[adjNodesList.size()]);
	}

	void setCoord(int a, int b, int c, int d){
		coord.x = a;
		coord.y = b;
		coord.s = c;
		coord.t = d;
	}

	void setCoord(int a, int b){
		coord.x = a;
		coord.y = b;
	}

	void setCoord(Int4 a){
		coord = a;
	}


	Int4 getCoordinate(){
		return coord;
	}

	static bool aLeftOrUnderb(Node a, Node b){
		if(a.coord.x < b.coord.x || a.coord.y < b.coord.y )
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
			return hash4int(a.coord.x,a.coord.y,b.coord.x,b.coord.y);

			return hash4int(b.coord.x,b.coord.y,a.coord.x,a.coord.y);
	}
	int hashValue(){
		return hash2Int(coord.x, coord.y);
	}
};



struct Vertex {
	int x;
	int y;
};
class Line {
public:
	vector<Vertex> v;
public:
	Line(vector<Vertex> source){
		v = source;
	}

};

#endif
