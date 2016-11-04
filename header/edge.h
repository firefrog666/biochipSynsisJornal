#ifndef EDGE_H
#define EDGE_H
using namespace std;


#include <vector>
#include "../header/Node.h"

#include <boost/shared_ptr.hpp>


class Edge {

	//protected Edge[] adjEdges;

public:
	int number;
	int x,y,s,t;
	bool isStorage = false;
	//vector<boost::shared_ptr<Node>> adjNodesList;
public:
	Edge(){
		number = 0;

	}
	Edge(int a, int b, int c, int d){
		setCoord(a,b,c,d);
	}

	Edge(int i)
	{
		//adjNodesList = new ArrayList<Node>();
		//coord = new Int4();
		number = i;
	}

	void setNumber(int i) {
		number = i;
	}







	void setCoord(int a, int b, int c, int d){
		x = a;
		y = b;
		s = c;
		t = d;
	}

	void setCoord(int a, int b){
		x = a;
		y = b;
	}





	static int hash2Int(int a, int b){
		return a * 100 + b;
	}

	static int hash4int(int a, int b, int c, int d){
		return a*100000 + b * 10000+ c*100 +d;
	}


	int hashValue(){
		return hash4int(x, y,s,t);
	}
};



#endif
