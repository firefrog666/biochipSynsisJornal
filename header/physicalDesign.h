#ifndef PHYSICALDESIGN_H
#define PHYSICALdESIGN_H

#include <vector>
#include <string>
#include <map>
#include "../header/Node.h"
#include "../header/edge.h"
#include "../header/Algorithm.h"
#include "../header/grid.h"
#include <boost/shared_ptr.hpp>


typedef boost::shared_ptr<Node> Node_ptr;
typedef boost::shared_ptr<Edge> Edge_ptr;

#define STORESIZE 5
using namespace std;

enum dir{
	north,
	west,
	east,
	south,
	final
};


struct phyDev{
public:
	phyDev(){

	}

	void setGrid(Grid& grid){
		g = grid;
	}

	void setDevCenterofGrid(int x, int y){
		centerX = x;
		centerY = y;
	}


	void setNodesoffsetFromCorner(){

	}

	void setNodesOffsetFromCenter(){
		if(vertical){
			vector<int> v{0,-2,
						-1,-1,
						0,-1,
						1,-1,
						-1,0,
						0,0,
						1,0,
						-1,1,
						0,1,
						1,1,
						0,2
						};
			nodesOffsiteFromCenter = v;

			vector<int> port0{0,-2};
			vector<int> port1{0,2};
			port0offsite = port0;
			port1offsite = port1;
		}

		else{
			vector<int> v{-1,-1,
					0,-1,
					1,-1,
					-2,0,
					-1,0,
					0,0,
					1,0,
					2,0,
					-1,1,
					0,1,
					1,1
					};
		nodesOffsiteFromCenter = v;

		vector<int> port0{-2,0};
		vector<int> port1{2,0};
		port0offsite = port0;
		port1offsite = port1;
		}
	}

	void setNodesInGrid(){
		vector<int> nodeOffsiteFromCorner;
		for(int i = 0; i <= nodesOffsiteFromCenter.size()-1; i+=2){
			int xInG = nodesOffsiteFromCenter.at(i)  + centerX;
			int yInG = nodesOffsiteFromCenter.at(i + 1) + centerY;
			nodeOffsiteFromCorner.push_back(xInG);
			nodeOffsiteFromCorner.push_back(yInG);
		}

		nodes= g.getNodesByOffsite(nodeOffsiteFromCorner);
		edges= g.getEdgesByNodes(nodes);
		port0Node = g.getNode(port0offsite[0]+centerX,port0offsite[1]+centerY);
		port1Node = g.getNode(port1offsite[0]+centerX,port1offsite[1]+centerY);


	}
public:
	vector<Edge_ptr> edges;
	vector<Node_ptr> nodes;
	Node_ptr center;
	vector<int> port0offsite;
	vector<int> port1offsite;
	Node_ptr port0Node;
	Node_ptr port1Node;
	int centerX = 0;
	int centerY = 0;
	vector<int> nodesOffsiteFromCenter;
	Grid g;

	bool vertical = false;
	bool horizontal = false;


};

class Square{
public:
	Square(){

	}
	Square(const Grid& g){

	}

	void getMinXY(){

	}

	void setMinXY(int x, int y){
		minX = x;
		minY = y;
	}


	void reshapeGrid(int X, int Y){
		Grid g(X,Y);
		grid = g;
	}

	void getCornerPos(){
		left = 10000;
		down = 10000;
		right = 0;
		up = 0;
		for(Node_ptr node:nodes){
			int x = node->x;
			int y = node->y;

			if(x <= left)
				left = x;
			if(x >= right)
				right = x;

			if(y <= down)
				down = y;

			if(y >= up)
				up = y;
		}
	}

public:
	int left,down,up,right;

public:
	int minX,minY;
	int rowNum;
	int columnNum;
	vector<Node_ptr> nodes;
	vector<Edge_ptr> edges;
	Grid grid;
	map<int,int> rowRank;
	map<int,int> columnRank;
};

typedef boost::shared_ptr<Square> Sqr_ptr;

typedef boost::shared_ptr<phyDev>  Pd_ptr;

class PhysicalDesign{
public:
	PhysicalDesign(){
		sizeX = 0;
		sizeY = 0;
	}


public:

	vector<Sqr_ptr> squaresInput;
	map<int,Sqr_ptr> hashInputSquare;
	vector<Grid> squareGrid;
	map<string,int> ILPresults;

	Grid inputGrid;
	Grid outputGrid;
	vector<string> constraint;
	vector<string> varName;
	vector<string> varType;
	vector<string> OBJ;

	vector<Pd_ptr> phyDevs;
	vector<Pd_ptr> verPhyDevs;
	vector<Pd_ptr> horPhyDevs;
	map<Node_ptr,Pd_ptr> nodesDev;
	map<Node_ptr,Pd_ptr> nodesVerDev;
	map<Node_ptr,Pd_ptr> nodesHorDev;

	//for

public:
	int sizeX;
	int sizeY;


public:
	void fromGridToSqaures();
	void joinSquares();
	void pressGrid(bool vertical);
	Grid join2Grid(Grid& g1,Grid& g2);

	void genILP();
	void paths();
	void nodeBind();
	void nodeBindSqaure();
	void pathSquare();
	void pathSquareWithDev();
	void pathSquareFixCrossDev();
	void writeGraphFile();
	vector<int> setDeviceLocation(Node_ptr devNodeInputgrid);

	vector<Node_ptr> availebleNodes(const vector<Sqr_ptr>& squares);
	vector<Edge_ptr> availebleEdges(const vector<Sqr_ptr>& squares);
	vector<Edge_ptr> getLegitEdges(Edge_ptr e); //all the legit edges from output grid a path from a input grid can hold
	vector<Node_ptr> getLegitNodes(Edge_ptr e);//all the legit nodes from output grid a path from a input grid can hold
	vector<Node_ptr> getLegitNodesForDev(Node_ptr devNode);
	vector<Node_ptr> devLegitNodes(const vector<Sqr_ptr>& squares);

	vector<int> squareLocOutputgrid(Sqr_ptr square);
	vector<Sqr_ptr> getLegitSquareInOutputGrid(Edge_ptr e);
	vector<Sqr_ptr> getSquareOutputGridContainNode(Node_ptr node);
	vector<Sqr_ptr> getSquareInputGridContainNode(Node_ptr node);
	vector<int> nodeLocInOutputgrid(Node_ptr node);

	void setDevPos(Node_ptr inputDevNode);
	void writeToFile(string fileName);
	void setRowColumnRank();

	Grid getGridFromSquare(Sqr_ptr sqr);

};




#endif
