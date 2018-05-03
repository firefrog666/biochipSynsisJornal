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
		center = g.getNode(centerX,centerY);

	}
public:
	vector<Edge*> edges;
	vector<Node*> nodes;
	Node* center;
	vector<int> port0offsite;
	vector<int> port1offsite;
	Node* port0Node;
	Node* port1Node;
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
		minX = 0;
		minY = 0;
		getCornerPos();
	}
	Square(const Grid& g){
		minX = 0;
		minY = 0;
		getCornerPos();
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
		/*left = 10000;
		down = 10000;
		right = 0;
		up = 0;
		for(Node* node:nodes){
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
		}*/
	}

public:
	int left,down,up,right;

public:
	int minX,minY;
	int rowNum;
	int columnNum;
	vector<Node*> nodes;
	vector<Edge*> edges;
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
	vector<string> bounds;

	vector<Pd_ptr> phyDevs;
	vector<Pd_ptr> verPhyDevs;
	vector<Pd_ptr> horPhyDevs;
	map<Node*,Pd_ptr> nodesDev;
	map<Node*,Pd_ptr> nodesVerDev;
	map<Node*,Pd_ptr> nodesHorDev;

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
	void trueGraph();
	vector<int> setDeviceLocation(Node* devNodeInputgrid);

	vector<Node*> availebleNodes(const vector<Sqr_ptr>& squares);
	vector<Edge*> availebleEdges(const vector<Sqr_ptr>& squares);
	vector<Edge*> getLegitEdges(Edge* e); //all the legit edges from output grid a path from a input grid can hold
	vector<Node*> getLegitNodes(Edge* e);//all the legit nodes from output grid a path from a input grid can hold
	vector<Node*> getLegitNodesForDev(Node* devNode);
	vector<Node*> devLegitNodes(const vector<Sqr_ptr>& squares);

	vector<int> squareLocOutputgrid(Sqr_ptr square);
	vector<Sqr_ptr> getLegitSquareInOutputGrid(Edge* e);
	vector<Sqr_ptr> getSquareOutputGridContainNode(Node* node);
	vector<Sqr_ptr> getSquareInputGridContainNode(Node* node);
	vector<int> nodeLocInOutputgrid(Node* node);

	void setDevPos(Node* inputDevNode);
	void writeToFile(string fileName);
	void setRowColumnRank();

	Grid getGridFromSquare(Sqr_ptr sqr);

};




#endif
