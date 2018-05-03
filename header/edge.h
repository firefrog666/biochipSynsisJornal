#ifndef EDGE_H
#define EDGE_H
using namespace std;


#include <vector>
#include "../header/Node.h"
#include <iostream>
#include <string>
#include "../header/Algorithm.h"




class Edge {

	//protected Edge[] adjEdges;

public:
	int number;
	int x,y,s,t;
	bool isStorage = false;
	bool isUsedAtMoment = false;
	string name = "default edge name";

	//vector<boost::shared_ptr<Node>> adjNodesList;
public:
	Edge(){
		number = 0;
		setName();

	}
	Edge(int a, int b, int c, int d){
		setCoord(a,b,c,d);
		setName();
	}

	Edge(int i)
	{
		if(i<0)
			name = "NULL_Edge";
		else{
			number = i;
			setName();
		}
	}

	void setNumber(int i) {
		number = i;
	}

	void setName(){
		name = string("x") + std::to_string(x) + string("y") + std::to_string(y)+string("s") + std::to_string(s) + string("t") + std::to_string(t);
	}



	void printMyself(){
		cout << "im edge " << "x" << x << "y" << y << "s" << s  << "t" << t << endl;

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





/*	static int hash2Int(int a, int b){
		return a * 100 + b;
	}

	static int hash4int(int a, int b, int c, int d){
		return a*100000 + b * 10000+ c*100 +d;
	}*/


	float hashValue(){
		return algo::hash4Int(x, y,s,t);
		//return 0;
	}
};



#endif
