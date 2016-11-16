/*
 * ListAlgorithm.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: ga63quk
 */



#include<vector>

#include "../header/edge.h"
#include "../header/Node.h"
#include "../header/writeILP.h"
#include "../header/physicalDesign.h"


#include <stdlib.h>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <string>
#include <sstream>
#include "../header/ILP.h"







using namespace std;
#define M 10000
#ifndef	 STORAGESIZE
#define STORAGESIZE 5

#endif
#define NODESOFFSITE 2
typedef boost::shared_ptr<Node> Node_ptr;
typedef boost::shared_ptr<Edge> Edge_ptr;
typedef boost::shared_ptr<phyDev>  Pd_ptr;

string a(int i){
	stringstream ss;
	ss<<i;
	return ss.str();
}
string a(const char* s){
	stringstream ss;
	ss<<s;
	return ss.str();
}
string a(string s){
	stringstream ss;
	ss<<s;
	return ss.str();
}

__inline__ bool flowComeInNode(Edge_ptr flow,Node_ptr node){
	bool result = true;
	if(flow->x == node->x && flow->y == node->y)
		return false;
	return true;

}

__inline__ string nodeName(Node_ptr n){
	return a("n") + a("x") +a(n->x)+ a("y") + a(n->y);
}
__inline__ string edgeName(Edge_ptr e){
	return a("e") + a("x") +a(e->x)+ a("y") + a(e->y)+ a("s") +a(e->s)+ a("t") + a(e->t);
}

__inline__ string devHor(Node_ptr devNode){
	return nodeName(devNode) + a("Hor");
}

__inline__ string devVer(Node_ptr devNode){
	return nodeName(devNode)+a("Ver");
}

__inline__ string pathSuperFlow(Edge_ptr path){
	return edgeName(path) + a("SuperFlow");
}
__inline__ string pathUseVerDev(Edge_ptr path, Node_ptr devNode){
	return edgeName(path) + a("U") +nodeName(devNode) + a("VerDev");
}

__inline__ string pathUseHorDev(Edge_ptr path, Node_ptr devNode){
	return edgeName(path) + a("U") +nodeName(devNode) + a("HorDev");
}

__inline__ string pathUseDevPort0(Edge_ptr path, Node_ptr devNode){
	return edgeName(path) + a("U")+ nodeName(devNode) + a("Port0");
}

__inline__ string pathUseDevPort1(Edge_ptr path, Node_ptr devNode){
	return edgeName(path) + a("U")+ nodeName(devNode) + a("Port1");
}


__inline__ string nodeBNode(Node_ptr nFrom, Node_ptr nTo){
	return  nodeName(nFrom) + a("B") + nodeName(nTo);
}


__inline__ string edgeUseEdge(Edge_ptr eFrom, Edge_ptr eTo){
	return  edgeName(eFrom) + a("U") + edgeName(eTo);
}
__inline__ string edgeUseNode(Edge_ptr eFrom, Node_ptr nTo){
	return  edgeName(eFrom) + a("U") + nodeName(nTo);
}
__inline__ string  flowOnEdge(Edge_ptr path, Edge_ptr edge){
	return edgeName(path) + a("FlowOn") + edgeName(edge);
}

__inline__ string edgeStartNode(Edge_ptr eFrom, Node_ptr nTo){
	return  edgeName(eFrom) + a("S") + nodeName(nTo);
}
__inline__ string edgeEndNode(Edge_ptr eFrom, Node_ptr nTo){
	return  edgeName(eFrom) + a("E") + nodeName(nTo);
}

__inline__ string nodeUseNode(Node_ptr inputNode, Node_ptr outputNode){
	return nodeName(inputNode) + a("U") + nodeName(outputNode);
}
__inline__ int hash2Int(int i, int j){
	return i * 100 + j;
}

__inline__ int getDistance(Node_ptr n0,Node_ptr n1){
	return (n0->x-n1->x)*(n0->x-n1->x)+(n0->y-n1->y)*(n0->y-n1->y);
}
bool ifContainNode(vector<Node_ptr>& v, Node_ptr n){
	for(Node_ptr t:v){
		if(n == t)
			return true;
	}

	return false;
}

void PhysicalDesign::nodeBindSqaure(){

}

bool ifContainEdge(const vector<Edge_ptr> edgesV, Edge_ptr edge){

	for(Edge_ptr e:edgesV){
		if(e->x == edge->x && e->y == edge->y && e->s == edge->s && e->t == edge->t)
			return true;
	}

	return false;
}


Grid PhysicalDesign::getGridFromSquare(Sqr_ptr sqr){
	Node_ptr node0 = sqr->nodes[0];
	Node_ptr node2 = sqr->nodes[2];

	int x = nodeLocInOutputgrid(node0).at(0);
	int y = nodeLocInOutputgrid(node0).at(1);

	int s = nodeLocInOutputgrid(node2).at(0);
	int t = nodeLocInOutputgrid(node2).at(1);

	int sizeX = s - x + 1;
	int sizeY = t - y + 1;

	Grid g(sizeX,sizeY);

	vector<Sqr_ptr> sqrs;
	sqrs.push_back(sqr);

	vector<Node_ptr> nodes = availebleNodes(sqrs);
	vector<Edge_ptr> edges = availebleEdges(sqrs);
	g.nodes = nodes;
	g.edges = edges;
	return g;




}


vector<int> PhysicalDesign::setDeviceLocation(Node_ptr devNodeInputgrid){
	vector<int> result;
	//if on the corner
	int nodeBelongToSquares = 0;
	vector<Sqr_ptr> whichSqrBelong;
	for(Sqr_ptr sqr:squaresInput){
		if(find(sqr->nodes.begin(),sqr->nodes.end(),devNodeInputgrid) != sqr->nodes.end()){
			nodeBelongToSquares++;
			whichSqrBelong.push_back(sqr);
		}
	}
	if(nodeBelongToSquares == 0){
		return result;
	}
	else if (nodeBelongToSquares == 1){
		Sqr_ptr sqr = whichSqrBelong.at(0);
		Grid g = getGridFromSquare(sqr);
		//left down
		if(devNodeInputgrid == sqr->nodes[0]){


		}
		//left up
		else if(devNodeInputgrid == sqr->nodes[1]){

		}
		//right down
		else if(devNodeInputgrid == sqr->nodes[2]){

		}
		//right up
		else if(devNodeInputgrid == sqr->nodes[3]){

		}

		return result;
	}
	else if(nodeBelongToSquares == 2){
		return result;
	}
	else{
		return result;
	}



	return result;
}
vector<int> PhysicalDesign::nodeLocInOutputgrid(Node_ptr nodeInputGrid){
	vector<int> result;
	int xOutGrid = 0;
	int yOutGrid = 0;



	for(int i = 0; i < nodeInputGrid->y; i++){
			//find a square in this row
			Sqr_ptr sqrThisRow;
			for(Sqr_ptr sqr:squaresInput){
				if(sqr->rowNum == i){
					sqrThisRow = sqr;
					break;
				}
			}
			int height = sqrThisRow->minY;
			yOutGrid += height;

		}

	for(int j = 0; j < nodeInputGrid->x; j++){
			//find a square in this row
			Sqr_ptr sqrThisCol;
			for(Sqr_ptr sqr:squaresInput){
				if(sqr->columnNum == j){
					sqrThisCol = sqr;
					break;
				}
			}
			int width = sqrThisCol->minX;
			xOutGrid += width;
		}
	result.push_back(xOutGrid);
	result.push_back(yOutGrid);
	return result;
}

vector<int> PhysicalDesign::squareLocOutputgrid(Sqr_ptr square){
	vector<int> result;
	int xOutGrid = 0;
	int yOutGrid = 0;
	for(int i = 0; i < square->rowNum; i++){
		//find a square in this row
		Sqr_ptr sqrThisRow;
		for(Sqr_ptr sqr:squaresInput){
			if(sqr->rowNum == i){
				sqrThisRow = sqr;
				break;
			}
		}
		int height = sqrThisRow->minY;
		yOutGrid += height;

	}

	for(int j = 0; j < square->columnNum; j++){
			//find a square in this row
			Sqr_ptr sqrThisCol;
			for(Sqr_ptr sqr:squaresInput){
				if(sqr->columnNum == j){
					sqrThisCol = sqr;
					break;
				}
			}
			int width = sqrThisCol->minX;
			xOutGrid += width;

		}

	result.push_back(xOutGrid);
	result.push_back(yOutGrid);
	result.push_back(xOutGrid+square->minX);
	result.push_back(yOutGrid+square->minY);

	return result;
}

vector<Edge_ptr> PhysicalDesign::availebleEdges(const vector<Sqr_ptr>& squares){
	vector<Edge_ptr> result;
	for(Sqr_ptr sqr:squares){
		vector<int> loc = squareLocOutputgrid(sqr);
		int x = loc[0];
		int y = loc[1];
		int s = loc[2];
		int t = loc[3];
		for(Edge_ptr e:outputGrid.edges){
			if((e->x >= x && e->x <=s
				&& e->s>=x && e->s <=s
				&& e->y>=y && e->y <= t
				&& e->t>=y && e->t <= t)&&
				(e->x <= x+NODESOFFSITE || e->x >= s-NODESOFFSITE || e->y <= y+NODESOFFSITE || e->y >= t-NODESOFFSITE)&&
				(e->s <= x+NODESOFFSITE || e->s >= s-NODESOFFSITE || e->t <= y+NODESOFFSITE || e->t >= t-NODESOFFSITE)
				){

				//not in any dev
				bool edgeInDev = false;
				for(Pd_ptr pd: phyDevs){
					if(find(pd->edges.begin(),pd->edges.end(),e)!=pd->edges.end()){
						edgeInDev = true;
						break;
					}
				}

				//not edge around device
				bool edgeAroundDev = false;
				/*if(e->x == 1 && e->y == 2 && e->s == 1 && e->t == 3){
					cout << "got ya" << endl;
				}*/

				for(Pd_ptr pd: phyDevs){
					for(Node_ptr n:pd->nodes){
						if(n == pd->port0Node || n == pd->port1Node)
							continue;
						if(find(n->adjEdgesList.begin(),n->adjEdgesList.end(),e)!=n->adjEdgesList.end()){
							edgeAroundDev = true;
							break;
						}
					}
					if(edgeAroundDev)
						break;
				}

				if(find(result.begin(),result.end(),e) == result.end() && !edgeInDev && !edgeAroundDev)
					result.push_back(e);
			}
		}


	}

	return result;
}

//where are device can be put
vector<Node_ptr> PhysicalDesign::devLegitNodes(const vector<Sqr_ptr>& squares){
	vector<Node_ptr> result;
	for(Sqr_ptr sqr:squares){
		vector<int> loc = squareLocOutputgrid(sqr);
		int x = loc[0];
		int y = loc[1];
		int s = loc[2];
		int t = loc[3];
		for(Node_ptr n:outputGrid.nodes){
			if(n->x == x || n->x ==s
				|| n->y==y || n->y == t){

				//node in dev
				bool nodeInDev = false;
				for(Pd_ptr pd: phyDevs){
					if(find(pd->nodes.begin(),pd->nodes.end(),n)!=pd->nodes.end()){
						if(!(n == pd->port0Node || n == pd->port1Node)){
							nodeInDev = true;
							break;
						}
					}
				}
				if(find(result.begin(),result.end(),n) == result.end() && !nodeInDev)
					result.push_back(n);
			}
		}


	}

	return result;
}

vector<Node_ptr> PhysicalDesign::availebleNodes(const vector<Sqr_ptr>& squares){
	vector<Node_ptr> result;
	for(Sqr_ptr sqr:squares){
		vector<int> loc = squareLocOutputgrid(sqr);
		int x = loc[0];
		int y = loc[1];
		int s = loc[2];
		int t = loc[3];
		for(Node_ptr n:outputGrid.nodes){
			if((n->x >= x && n->x <=s
				&& n->y>=y && n->y <= t)
					&&((n->x <= x+NODESOFFSITE || n->x >= s-NODESOFFSITE) || (n->y <= y+NODESOFFSITE || n->y >= t-NODESOFFSITE))


			){

				//node in dev
				bool nodeInDev = false;
				for(Pd_ptr pd: phyDevs){
					if(find(pd->nodes.begin(),pd->nodes.end(),n)!=pd->nodes.end()){
						if(!(n == pd->port0Node || n == pd->port1Node)){
							nodeInDev = true;
							break;
						}
					}
				}
				if(find(result.begin(),result.end(),n) == result.end() && !nodeInDev)
					result.push_back(n);
			}
		}


	}

	return result;
}

vector<Sqr_ptr> PhysicalDesign::getSquareOutputGridContainNode(Node_ptr node){
	vector<Sqr_ptr> result;
	for(Sqr_ptr sqr:squaresInput){
		//if(find(sqr->edges.begin(),sqr->edges.end(),e) != sqr->edges.end()){
		if(ifContainNode(sqr->nodes,node)){
			result.push_back(sqr);
		}
	}
	return result;
}

vector<Sqr_ptr> PhysicalDesign::getSquareInputGridContainNode(Node_ptr node){
	vector<Sqr_ptr> result;
	for(Sqr_ptr sqr:squaresInput){
		//if(find(sqr->edges.begin(),sqr->edges.end(),e) != sqr->edges.end()){
		if(ifContainNode(sqr->nodes,node)){
			result.push_back(sqr);
		}
	}
	return result;
}

vector<Node_ptr> PhysicalDesign::getLegitNodesForDev(Node_ptr devNode){
	vector<Node_ptr> result;
		vector<Sqr_ptr> sqrsContainNode = getSquareInputGridContainNode(devNode);
		result = devLegitNodes(sqrsContainNode);
		return result;
}


vector<Edge_ptr> PhysicalDesign::getLegitEdges(Edge_ptr edge){
	vector<Edge_ptr> result;
	vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(edge);
	result = availebleEdges(sqrsContainE);
	return result;
}

vector<Node_ptr> PhysicalDesign::getLegitNodes(Edge_ptr edge){
	vector<Node_ptr> result;
	vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(edge);
	result = availebleNodes(sqrsContainE);
	return result;
}

bool ifContain(vector<Edge_ptr>& v, Edge_ptr e){
	for(Edge_ptr t:v){
		if(e == t)
			return true;
	}

	return false;
}



//a collection of sqrs which contain e
vector<Sqr_ptr> PhysicalDesign::getLegitSquareInOutputGrid(Edge_ptr e){
	vector<Sqr_ptr> result;
	for(Sqr_ptr sqr:squaresInput){
		//if(find(sqr->edges.begin(),sqr->edges.end(),e) != sqr->edges.end()){
		if(ifContain(sqr->edges,e)){
			result.push_back(sqr);
		}
	}
	return result;
}

void PhysicalDesign::pathSquareFixCrossDev(){
	for(Edge_ptr path:inputGrid.edges){
		for(Edge_ptr eTo:getLegitEdges(path)){
			string pathUseE = edgeUseEdge(path,eTo);
			varName.push_back(pathUseE); varType.push_back("1");
			string flowEdge = flowOnEdge(path,eTo);
			varName.push_back(flowEdge); varType.push_back("0");
			//if pathUseE = 0 then flowEdge = 0

			constraint.push_back(flowEdge + a(" + ") + a(M) + a(" ") + pathUseE + a(" >= ") + a(0));
			constraint.push_back(flowEdge + a(" - ") + a(M) + a(" ") + pathUseE + a(" <= ") + a(0));

		}

		for(Node_ptr nTo:getLegitNodes(path)){
			string pathUseNode = edgeUseNode(path,nTo);
			//cout<< "path " << path->x << path->y << path->s << path->t<<" availe nodes are" << nTo->x << nTo->y<<endl;
			varName.push_back(pathUseNode); varType.push_back("1");
		}



		/*for(Node_ptr nTo:getLegitNodes(path)){
			string pathStartNode = edgeStartNode(path,nTo);
			varName.push_back(pathStartNode); varType.push_back("1");
		}

		for(Node_ptr nTo:getLegitNodes(path)){
			string pathEndNode = edgeEndNode(path,nTo);
			varName.push_back(pathEndNode); varType.push_back("1");
		}*/
	}

	//decide awre devices are ver or hor
	for(Node_ptr n:inputGrid.nodes){
		if(!n->isDev)
			continue;

		string devIsHor = devHor(n);
		varName.push_back(devIsHor); varType.push_back("1");
		string devIsVer = devVer(n);
		varName.push_back(devIsVer); varType.push_back("1");
		constraint.push_back(devIsVer + a(" + ") + devIsHor + a(" = 1"));
	}
	for(Edge_ptr path:inputGrid.edges){
			Node_ptr n0 = inputGrid.hashNodes.at(Node::hash2Int(path->x,path->y));
			Node_ptr n1 = inputGrid.hashNodes.at(Node::hash2Int(path->s,path->t));

			string flowFromSuper = pathSuperFlow(path);
			varName.push_back(flowFromSuper); varType.push_back("0");

			vector<Edge_ptr> pathLegitEdges = getLegitEdges(path);
			vector<Node_ptr> pathLegitNodes = getLegitNodes(path);
			for(Node_ptr nTo:pathLegitNodes){
				cout<< "path " << path->x << path->y << path->s << path->t<<" availe nodes are" << nTo->x << nTo->y<<endl;
			}
			for(Edge_ptr legtE : getLegitEdges(path)){
				cout<<" legit e " << "x" << legtE->x << "y" << legtE->y<< "s" <<legtE->s << "t" << legtE->t<<endl;
			}
			//vector<Node_ptr> pathLegitNodes = getLegitNodes(path);
			if(!n0->isDev && !n1->isDev){


				vector<int> n0Loc = nodeLocInOutputgrid(n0);
				vector<int> n1Loc = nodeLocInOutputgrid(n1);
				cout << "n0Loc[0] " << n0Loc[0] << endl;
				cout << "n0Loc[1] " << n0Loc[1] << endl;
				cout << "n1Loc[0] " <<  n1Loc[0] << endl;
				cout << "n1Loc[1] " <<  n1Loc[1] << endl;
				Node_ptr node0Outgrid = outputGrid.getNode(n0Loc[0],n0Loc[1]);
				Node_ptr node1Outgrid = outputGrid.getNode(n1Loc[0],n1Loc[1]);


				//path must start n0 and end with n1
				string edgeAroudN0Used = "";
				vector<Edge_ptr> legitEdges = getLegitEdges(path);
				for(Edge_ptr eTo:node0Outgrid->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudN0Used += a(" + ") + eBindE;
				}

				constraint.push_back(edgeAroudN0Used + (" = 1"));

				string edgeAroudN1Used = "";
				for(Edge_ptr eTo:node1Outgrid->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE = edgeUseEdge(path,eTo);
					edgeAroudN1Used += a(" + ") + eBindE;
				}

				constraint.push_back(edgeAroudN1Used + (" = 1"));

				//must be a simple path
				for(Node_ptr nTo:getLegitNodes(path)){
					if(nTo == node0Outgrid || nTo == node1Outgrid)
						continue;
					string eUseNode = edgeUseNode(path,nTo);
					string edgeAroudUsed = "";
					for(Edge_ptr eTo:nTo->adjEdgesList){
						//eTo must be a legit Edge
						if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
						string eBindE= edgeUseEdge(path,eTo);
						edgeAroudUsed += a(" + ") + eBindE;
					}

					//if n0BindN = 0 && n1Bind = 0, edge used = 2 or 0

					constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" = ") + a(0));

				}

				//flow to no circle
				string flowOnOneNode = "";
				Node_ptr superNode = node0Outgrid;

				for(Edge_ptr e:superNode->adjEdgesList){
					if(!ifContainEdge(pathLegitEdges,e))
						continue;
					string flowEdge = flowOnEdge(path,e);

					if(flowComeInNode(e,superNode)){
						flowOnOneNode += a(" + ")  + flowEdge;
					}
					else{
						flowOnOneNode += a(" - ") + flowEdge;
					}
				}
				constraint.push_back(flowOnOneNode + a(" + ") + flowFromSuper + a(" = 1"));


				for(Node_ptr n:outputGrid.nodes){
					if(!ifContainNode(pathLegitNodes,n))
						continue;
					string pathUseNode = edgeUseNode(path,n);
					if(n == superNode)
						continue;
					flowOnOneNode = "";

					for(Edge_ptr e:n->adjEdgesList){
						if(!ifContainEdge(pathLegitEdges,e))
							continue;
						string flowEdge = flowOnEdge(path,e);

						if(flowComeInNode(e,n)){
							flowOnOneNode += a(" + ")  + flowEdge;
						}
						else{
							flowOnOneNode += a(" - ") + flowEdge;
						}
					}
					if(n == node1Outgrid)
						constraint.push_back(flowOnOneNode + a(" = 1"));
					else
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" = 0"));
				}

				//all superFlow = edgeNumber + 1
				string edgeNumber = "";
				for(Edge_ptr e:pathLegitEdges){
					edgeNumber +=a(" + ") + edgeUseEdge(path,e);
				}
				constraint.push_back(edgeNumber + a(" - ") + flowFromSuper + a(" = -1"));
			}

			else if (n0->isDev && !n1->isDev){

				vector<int> n0Loc = nodeLocInOutputgrid(n0);
				vector<int> n1Loc = nodeLocInOutputgrid(n1);
				cout << "n0Loc[0] " << n0Loc[0] << endl;
				cout << "n0Loc[1] " << n0Loc[1] << endl;
				cout << "n1Loc[0] " <<  n1Loc[0] << endl;
				cout << "n1Loc[1] " <<  n1Loc[1] << endl;
				Node_ptr node1Outgrid = outputGrid.getNode(n1Loc[0],n1Loc[1]);

				Pd_ptr verPd = nodesVerDev[n0];
				Pd_ptr horPd = nodesHorDev[n0];

				Node_ptr n0Port0Ver = verPd->port0Node;
				Node_ptr n0Port1Ver = verPd->port1Node;

				Node_ptr n0Port0Hor = horPd->port0Node;
				Node_ptr n0Port1Hor = horPd->port1Node;

				string N0Ver = devVer(n0);
				string N0Hor = devHor(n0);

				string pathUseN0Port0 = pathUseDevPort0(path,n0);
				varName.push_back(pathUseN0Port0); varType.push_back("1");
				string pathUseN0Port1 = pathUseDevPort1(path,n0);
				varName.push_back(pathUseN0Port1);varType.push_back("1");
				constraint.push_back(pathUseN0Port0+ a(" + ") + pathUseN0Port1+ a(" = 1"));

				//path must start n0 and end with n1
				string edgeAroudUsed = "";

				vector<Edge_ptr> legitEdges = getLegitEdges(path);
				for(Edge_ptr eTo:n0Port0Ver->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN0Ver and pathUseN0Port0

				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N0Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0)  + (" >= ") + a(1-2*M));

				//path must start n0 and end with n1
				edgeAroudUsed = "";

				for(Edge_ptr eTo:n0Port0Hor->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN0Hor and pathUseN0Port0
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N0Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0)  + (" >= ") + a(1-2*M));

				edgeAroudUsed = "";

				for(Edge_ptr eTo:n0Port1Ver->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN0Ver and pathUseN0Port1
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N0Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1)  + (" >= ") + a(1-2*M));

				edgeAroudUsed = "";

				for(Edge_ptr eTo:n0Port1Hor->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN0hor and pathUseN0Port1
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N0Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1)  + (" >= ") + a(1-2*M));





				string edgeAroudN1Used = "";
				for(Edge_ptr eTo:node1Outgrid->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE = edgeUseEdge(path,eTo);
					edgeAroudN1Used += a(" + ") + eBindE;
				}

				constraint.push_back(edgeAroudN1Used + (" = 1"));

				//must be a simple path
				for(Node_ptr nTo:getLegitNodes(path)){
					if(nTo == node1Outgrid)
						continue;

					string eUseNode = edgeUseNode(path,nTo);
					string edgeAroudUsed = "";
					for(Edge_ptr eTo:nTo->adjEdgesList){
						//eTo must be a legit Edge
						if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
						string eBindE= edgeUseEdge(path,eTo);
						edgeAroudUsed += a(" + ") + eBindE;
					}

					//if n0BindN = 0 && n1Bind = 0, edge used = 2 or 0

					if( nTo == n0Port0Ver){
						//if not use n0Port0Ver what ever
						//if pathUseN0Ver = 0 then = 2
						//if pathUseN0Port0 = 0 then = 2
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N0Ver) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port0) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port0) + a(" <= ") + a(0));
					}
					else if(nTo == n0Port1Ver){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N0Ver) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port1) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port1) + a(" <= ") + a(0));

					}
					else if(nTo == n0Port0Hor){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N0Hor) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port0) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port0) + a(" <= ") + a(0));

					}
					else if(nTo == n0Port1Hor){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N0Hor) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port1) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port1) + a(" <= ") + a(0));

					}
					else{
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode) +a(" = ") + a(0));

					}

				}

				//flow to no circle
				string flowOnOneNode = "";
				Node_ptr superNode = node1Outgrid;

				for(Edge_ptr e:superNode->adjEdgesList){
					if(!ifContainEdge(pathLegitEdges,e))
						continue;
					string flowEdge = flowOnEdge(path,e);

					if(flowComeInNode(e,superNode)){
						flowOnOneNode += a(" + ")  + flowEdge;
					}
					else{
						flowOnOneNode += a(" - ") + flowEdge;
					}
				}
				constraint.push_back(flowOnOneNode + a(" + ") + flowFromSuper + a(" = 1"));


				for(Node_ptr n:outputGrid.nodes){
					if(!ifContainNode(pathLegitNodes,n))
						continue;
					if(n == superNode)
						continue;

					string pathUseNode = edgeUseNode(path,n);
					flowOnOneNode = "";

					for(Edge_ptr e:n->adjEdgesList){
						if(!ifContainEdge(pathLegitEdges,e))
							continue;
						string flowEdge = flowOnEdge(path,e);

						if(flowComeInNode(e,n)){
							flowOnOneNode += a(" + ")  + flowEdge;
						}
						else{
							flowOnOneNode += a(" - ") + flowEdge;
						}
					}

					if( n== n0Port0Ver){
						//if use n0Port0Ver then pathusenode = 0 flow = 1
						constraint.push_back(flowOnOneNode +  a(" + ") + a(M) + a(" ") + a(N0Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0)+(" <= ") + a(2*M + 1));
						constraint.push_back(flowOnOneNode +  a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0)+(" >= ") + a(-2*M + 1));
						// else pathusenode = 1	 flow = 0
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(N0Ver) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode+ a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" <= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port0) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port0) + a(" <= ") + a(0));


										}
					else if(n== n0Port1Ver){
						//if use n0Port0Ver then pathusenode = 0 flow = 1
						constraint.push_back(flowOnOneNode +  a(" + ") + a(M) + a(" ") + a(N0Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1)+(" <= ") + a(2*M + 1));
						constraint.push_back(flowOnOneNode +  a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1)+(" >= ") + a(-2*M + 1));
						// else pathusenode = 1	 flow = 0
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(N0Ver) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" <= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1) + a(" <= ") + a(0));

					}
					else if(n == n0Port0Hor){
						//if use n0Port0Ver then pathusenode = 0 flow = 1
						constraint.push_back(flowOnOneNode +  a(" + ") + a(M) + a(" ") + a(N0Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0)+(" <= ") + a(2*M + 1));
						constraint.push_back(flowOnOneNode +  a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0)+(" >= ") + a(-2*M + 1));
						// else pathusenode = 1	 flow = 0
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(N0Hor) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" <= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0) + a(" <= ") + a(0));

					}
					else if(n == n0Port1Hor){
						//if use n0Port0Ver then pathusenode = 0 flow = 1
						constraint.push_back(flowOnOneNode +  a(" + ") + a(M) + a(" ") + a(N0Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1)+(" <= ") + a(2*M + 1));
						constraint.push_back(flowOnOneNode +  a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1)+(" >= ") + a(-2*M + 1));
						// else pathusenode = 1	 flow = 0
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(N0Hor) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" <= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode+ a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1) + a(" <= ") + a(0));

					}
					else{
						constraint.push_back(flowOnOneNode +  a(" - ") + pathUseNode + a(" = 0"));
					}


				}

				//all superFlow = edgeNumber + 1

				string edgeNumber = "";
				for(Edge_ptr e:pathLegitEdges){
					edgeNumber +=a(" + ") + edgeUseEdge(path,e);
				}
				constraint.push_back(edgeNumber + a(" - ") + flowFromSuper + a(" = -1"));
				//flow no circle end



			}
			else if (!n0->isDev && n1->isDev){
				vector<int> n1Loc = nodeLocInOutputgrid(n1);
				vector<int> n0Loc = nodeLocInOutputgrid(n0);
				cout << "n1Loc[0] " << n1Loc[0] << endl;
				cout << "n1Loc[1] " << n1Loc[1] << endl;
				cout << "n0Loc[0] " <<  n0Loc[0] << endl;
				cout << "n0Loc[1] " <<  n0Loc[1] << endl;
				Node_ptr node1Outgrid = outputGrid.getNode(n0Loc[0],n0Loc[1]);

				Pd_ptr verPd = nodesVerDev[n1];
				Pd_ptr horPd = nodesHorDev[n1];

				Node_ptr n1Port0Ver = verPd->port0Node;
				Node_ptr n1Port1Ver = verPd->port1Node;

				Node_ptr n1Port0Hor = horPd->port0Node;
				Node_ptr n1Port1Hor = horPd->port1Node;

				string N1Ver = devVer(n1);
				string N1Hor = devHor(n1);

				string pathUseN1Port0 = pathUseDevPort0(path,n1);
				varName.push_back(pathUseN1Port0); varType.push_back("1");
				string pathUseN1Port1 = pathUseDevPort1(path,n1);
				varName.push_back(pathUseN1Port1);varType.push_back("1");
				constraint.push_back(pathUseN1Port0+ a(" + ") + pathUseN1Port1+ a(" = 1"));

				//path must start n1 and end with n0
				string edgeAroudUsed = "";

				vector<Edge_ptr> legitEdges = getLegitEdges(path);
				for(Edge_ptr eTo:n1Port0Ver->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN1Ver and pathUseN1Port0

				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N1Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN1Port0)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N1Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN1Port0)  + (" >= ") + a(1-2*M));

				//path must start n1 and end with n0
				edgeAroudUsed = "";

				for(Edge_ptr eTo:n1Port0Hor->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN1Hor and pathUseN1Port0
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N1Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN1Port0)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N1Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN1Port0)  + (" >= ") + a(1-2*M));

				edgeAroudUsed = "";

				for(Edge_ptr eTo:n1Port1Ver->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN1Ver and pathUseN1Port1
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N1Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN1Port1)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N1Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN1Port1)  + (" >= ") + a(1-2*M));

				edgeAroudUsed = "";

				for(Edge_ptr eTo:n1Port1Hor->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN1hor and pathUseN1Port1
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N1Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN1Port1)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N1Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN1Port1)  + (" >= ") + a(1-2*M));





				string edgeAroudN1Used = "";
				for(Edge_ptr eTo:node1Outgrid->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE = edgeUseEdge(path,eTo);
					edgeAroudN1Used += a(" + ") + eBindE;
				}

				constraint.push_back(edgeAroudN1Used + (" = 1"));

				//must be a simple path
				for(Node_ptr nTo:getLegitNodes(path)){
					if(nTo == node1Outgrid)
						continue;

					string eUseNode = edgeUseNode(path,nTo);
					string edgeAroudUsed = "";
					for(Edge_ptr eTo:nTo->adjEdgesList){
						//eTo must be a legit Edge
						if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
						string eBindE= edgeUseEdge(path,eTo);
						edgeAroudUsed += a(" + ") + eBindE;
					}

					//if n1BindN = 0 && n0Bind = 0, edge used = 2 or 0

					if( nTo == n1Port0Ver){
						//if not use n1Port0Ver what ever
						//if pathUseN1Ver = 0 then = 2
						//if pathUseN1Port0 = 0 then = 2
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N1Ver) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N1Ver) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN1Port0) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN1Port0) + a(" <= ") + a(0));
					}
					else if(nTo == n1Port1Ver){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N1Ver) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N1Ver) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN1Port1) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN1Port1) + a(" <= ") + a(0));

					}
					else if(nTo == n1Port0Hor){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N1Hor) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N1Hor) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN1Port0) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN1Port0) + a(" <= ") + a(0));

					}
					else if(nTo == n1Port1Hor){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N1Hor) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N1Hor) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN1Port1) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN1Port1) + a(" <= ") + a(0));

					}
					else{
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+a(" = ") + a(0));

						}

					}

		/*		//flow to no circle
				string flowOnOneNode = "";
				Node_ptr superNode = node1Outgrid;

				for(Edge_ptr e:superNode->adjEdgesList){
					if(!ifContainEdge(pathLegitEdges,e))
						continue;
					string flowEdge = flowOnEdge(path,e);

					if(flowComeInNode(e,superNode)){
						flowOnOneNode += a(" + ")  + flowEdge;
					}
					else{
						flowOnOneNode += a(" - ") + flowEdge;
					}
				}
				constraint.push_back(flowOnOneNode + a(" + ") + flowFromSuper + a(" = 1"));


				for(Node_ptr n:outputGrid.nodes){
					if(!ifContainNode(pathLegitNodes,n))
						continue;
					if(n == superNode)
						continue;

					string pathUseNode = edgeUseNode(path,n);
					flowOnOneNode = "";

					for(Edge_ptr e:n->adjEdgesList){
						if(!ifContainEdge(pathLegitEdges,e))
							continue;
						string flowEdge = flowOnEdge(path,e);

						if(flowComeInNode(e,n)){
							flowOnOneNode += a(" + ")  + flowEdge;
						}
						else{
							flowOnOneNode += a(" - ") + flowEdge;
						}
					}

					if( n== n0Port0Ver){
						//if use n0Port0Ver then pathusenode = 0 flow = 1
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" + ") + a(M) + a(" ") + a(N0Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0)+(" <= ") + a(2*M + 1));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0)+(" >= ") + a(-2*M + 1));
						// else pathusenode = 1	 flow = 0
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(N0Ver) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" <= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0) + a(" <= ") + a(0));


										}
					else if(n== n0Port1Ver){
						//if use n0Port0Ver then pathusenode = 0 flow = 1
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" + ") + a(M) + a(" ") + a(N0Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1)+(" <= ") + a(2*M + 1));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1)+(" >= ") + a(-2*M + 1));
						// else pathusenode = 1	 flow = 0
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(N0Ver) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" <= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1) + a(" <= ") + a(0));

					}
					else if(n == n0Port0Hor){
						//if use n0Port0Ver then pathusenode = 0 flow = 1
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" + ") + a(M) + a(" ") + a(N0Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0)+(" <= ") + a(2*M + 1));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0)+(" >= ") + a(-2*M + 1));
						// else pathusenode = 1	 flow = 0
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(N0Hor) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" <= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0) + a(" <= ") + a(0));

					}
					else if(n == n0Port1Hor){
						//if use n0Port0Ver then pathusenode = 0 flow = 1
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" + ") + a(M) + a(" ") + a(N0Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1)+(" <= ") + a(2*M + 1));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode +  a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1)+(" >= ") + a(-2*M + 1));
						// else pathusenode = 1	 flow = 0
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(N0Hor) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" <= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1) +a(" >= ") + a(0));
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1) + a(" <= ") + a(0));

					}
					else{
						constraint.push_back(flowOnOneNode + a(" - ") + pathUseNode + a(" = 0"));
					}


				}

				//all superFlow = edgeNumber + 1
				string edgeNumber = "";
				for(Edge_ptr e:pathLegitEdges){
					edgeNumber +=a(" + ") + edgeUseEdge(path,e);
				}
				constraint.push_back(edgeNumber + a(" - ") + flowFromSuper + a(" = -1"));
				//flow no circle end*/

			}
			else if(n0->isDev && n1->isDev){
				vector<int> n1Loc = nodeLocInOutputgrid(n1);
				vector<int> n0Loc = nodeLocInOutputgrid(n0);
				cout << "n1Loc[0] " << n1Loc[0] << endl;
				cout << "n1Loc[1] " << n1Loc[1] << endl;
				cout << "n0Loc[0] " <<  n0Loc[0] << endl;
				cout << "n0Loc[1] " <<  n0Loc[1] << endl;
				Node_ptr node1Outgrid = outputGrid.getNode(n0Loc[0],n0Loc[1]);

				Pd_ptr verPd0 = nodesVerDev[n0];
				Pd_ptr horPd0 = nodesHorDev[n0];

				Node_ptr n0Port0Ver = verPd0->port0Node;
				Node_ptr n0Port1Ver = verPd0->port1Node;

				Node_ptr n0Port0Hor = horPd0->port0Node;
				Node_ptr n0Port1Hor = horPd0->port1Node;

				string N0Ver = devVer(n0);
				string N0Hor = devHor(n0);

				string pathUseN0Port0 = pathUseDevPort0(path,n0);
				varName.push_back(pathUseN0Port0); varType.push_back("1");
				string pathUseN0Port1 = pathUseDevPort1(path,n0);
				varName.push_back(pathUseN0Port1);varType.push_back("1");
				constraint.push_back(pathUseN0Port0+ a(" + ") + pathUseN0Port1+ a(" = 1"));

				Pd_ptr verPd1 = nodesVerDev[n1];
				Pd_ptr horPd1 = nodesHorDev[n1];

				Node_ptr n1Port0Ver = verPd1->port0Node;
				Node_ptr n1Port1Ver = verPd1->port1Node;

				Node_ptr n1Port0Hor = horPd1->port0Node;
				Node_ptr n1Port1Hor = horPd1->port1Node;

				string N1Ver = devVer(n1);
				string N1Hor = devHor(n1);

				string pathUseN1Port0 = pathUseDevPort0(path,n1);
				varName.push_back(pathUseN1Port0); varType.push_back("1");
				string pathUseN1Port1 = pathUseDevPort1(path,n1);
				varName.push_back(pathUseN1Port1);varType.push_back("1");
				constraint.push_back(pathUseN1Port0+ a(" + ") + pathUseN1Port1+ a(" = 1"));

				//path must start n0 and end with n1
				string edgeAroudUsed = "";

				vector<Edge_ptr> legitEdges = getLegitEdges(path);
				for(Edge_ptr eTo:n0Port0Ver->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN0Ver and pathUseN0Port0

				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N0Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0)  + (" >= ") + a(1-2*M));

				//path must start n0 and end with n1
				edgeAroudUsed = "";

				for(Edge_ptr eTo:n0Port0Hor->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN0Hor and pathUseN0Port0
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N0Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port0)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port0)  + (" >= ") + a(1-2*M));

				edgeAroudUsed = "";

				for(Edge_ptr eTo:n0Port1Ver->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN0Ver and pathUseN0Port1
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N0Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1)  + (" >= ") + a(1-2*M));

				edgeAroudUsed = "";

				for(Edge_ptr eTo:n0Port1Hor->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN0hor and pathUseN0Port1
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N0Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN0Port1)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN0Port1)  + (" >= ") + a(1-2*M));




				//path must start n1 and end with n0
				edgeAroudUsed = "";

				for(Edge_ptr eTo:n1Port0Ver->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN1Ver and pathUseN1Port0

				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N1Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN1Port0)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N1Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN1Port0)  + (" >= ") + a(1-2*M));

				//path must start n1 and end with n0
				edgeAroudUsed = "";

				for(Edge_ptr eTo:n1Port0Hor->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN1Hor and pathUseN1Port0
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N1Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN1Port0)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N1Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN1Port0)  + (" >= ") + a(1-2*M));

				edgeAroudUsed = "";

				for(Edge_ptr eTo:n1Port1Ver->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN1Ver and pathUseN1Port1
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N1Ver) + a(" + ") + a(M) + a(" ") + a(pathUseN1Port1)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N1Ver) + a(" - ") + a(M) + a(" ") + a(pathUseN1Port1)  + (" >= ") + a(1-2*M));

				edgeAroudUsed = "";

				for(Edge_ptr eTo:n1Port1Hor->adjEdgesList){
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if pathUseN1hor and pathUseN1Port1
				constraint.push_back(edgeAroudUsed + a(" + ") + a(M) + a(" ") + a(N1Hor) + a(" + ") + a(M) + a(" ") + a(pathUseN1Port1)  + (" <= ") + a(1+2*M));
				constraint.push_back(edgeAroudUsed + a(" - ") + a(M) + a(" ") + a(N1Hor) + a(" - ") + a(M) + a(" ") + a(pathUseN1Port1)  + (" >= ") + a(1-2*M));




				//must be a simple path
				for(Node_ptr nTo:getLegitNodes(path)){

					string eUseNode = edgeUseNode(path,nTo);
					string edgeAroudUsed = "";
					for(Edge_ptr eTo:nTo->adjEdgesList){
						//eTo must be a legit Edge
						if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
							continue;
						string eBindE= edgeUseEdge(path,eTo);
						edgeAroudUsed += a(" + ") + eBindE;
					}

					//if n1BindN = 0 && n0Bind = 0, edge used = 2 or 0

					//if n0BindN = 0 && n1Bind = 0, edge used = 2 or 0

					if( nTo == n0Port0Ver){
						//if not use n0Port0Ver what ever
						//if pathUseN0Ver = 0 then = 2
						//if pathUseN0Port0 = 0 then = 2
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N0Ver) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port0) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port0) + a(" <= ") + a(0));
					}
					else if(nTo == n0Port1Ver){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N0Ver) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N0Ver) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port1) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port1) + a(" <= ") + a(0));

					}
					else if(nTo == n0Port0Hor){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N0Hor) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port0) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port0) + a(" <= ") + a(0));

					}
					else if(nTo == n0Port1Hor){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N0Hor) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N0Hor) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN0Port1) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN0Port1) + a(" <= ") + a(0));

					}


					else if( nTo == n1Port0Ver){
						//if not use n1Port0Ver what ever
						//if pathUseN1Ver = 0 then = 2
						//if pathUseN1Port0 = 0 then = 2
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N1Ver) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N1Ver) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN1Port0) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN1Port0) + a(" <= ") + a(0));
					}
					else if(nTo == n1Port1Ver){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N1Ver) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N1Ver) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN1Port1) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN1Port1) + a(" <= ") + a(0));

					}
					else if(nTo == n1Port0Hor){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N1Hor) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N1Hor) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN1Port0) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN1Port0) + a(" <= ") + a(0));

					}
					else if(nTo == n1Port1Hor){
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(N1Hor) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(N1Hor) + a(" <= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(pathUseN1Port1) +a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" - ") + a(M) + a(" ") + a(pathUseN1Port1) + a(" <= ") + a(0));

					}
					else{
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode) +a(" = ") + a(0));

						}

					}


			}


			//path cannot tress pass any dev
			//path cannot use any node in side a dev
			for(Node_ptr dev:inputGrid.nodes){
				if(!dev->isDev)
					continue;

				Pd_ptr horDev = nodesHorDev[dev];
				Pd_ptr verDev = nodesVerDev[dev];
				string devIsHor = devHor(dev);
				string devIsVer = devVer(dev);
				vector<Node_ptr> horDevNodes = horDev->nodes;
				vector<Node_ptr> verDevNodes = verDev->nodes;

				for(Node_ptr horDevNode:horDevNodes){
					if(!ifContainNode(pathLegitNodes,horDevNode))
						continue;

					string pathUseNode = edgeUseNode(path,horDevNode);
					//if dev is hor, cannot use any node in this

					constraint.push_back(pathUseNode + a(" - ") + a(M) + a(" ") + devIsHor + a(" >= ")  + a(-M));
					constraint.push_back(pathUseNode + a(" + ") + a(M) + a(" ") + devIsHor + a(" <= ") + a(M));

				}


				for(Node_ptr verDevNode:verDevNodes){
					if(!ifContainNode(pathLegitNodes,verDevNode))
						continue;

					string pathUseNode = edgeUseNode(path,verDevNode);
					//if dev is hor, cannot use any node in this

					constraint.push_back(pathUseNode + a(" - ") + a(M) + a(" ") + devIsVer+ a(" >= ")  + a(-M));
					constraint.push_back(pathUseNode + a(" + ") + a(M) + a(" ") + devIsVer + a(" <= ") + a(M));

				}




			}

			/*	//edge number = node number -1
				vector<Edge_ptr> legitEdges = getLegitEdges(path);
				string alledge = "";
				for(Edge_ptr e:legitEdges){
					alledge += a(" - ")+ edgeName(e);
				}

				vector<Node_ptr> legitNodes = getLegitNodes(path);
				string allnode = "";
				for(Node_ptr n:legitNodes){
					allnode += a(" + ") + nodeName(n);
				}

				constraint.push_back(allnode + alledge + a(" = 1"));
	*/
	}// for path must start n0 and end with n1z



	//one node can only be used in one path
	for(Node_ptr nTo:outputGrid.nodes){


		/*bool isDevNode = false;
		for(Pd_ptr pd:verPhyDevs){
			Node_ptr port0 = pd->port0Node;
			Node_ptr port1 = pd->port1Node;
			if(port0 == nTo){
				isDevNode = true;
				break;
			}
			if(port1 == nTo){
				isDevNode = true;
				break;
			}

		}
		for(Pd_ptr pd:horPhyDevs){
			Node_ptr port0 = pd->port0Node;
			Node_ptr port1 = pd->port1Node;
			if(port0 == nTo){
				isDevNode = true;
				break;
			}
			if(port1 == nTo){
				isDevNode = true;
				break;
			}

		}

		if(isDevNode)
			continue;*/

		string nodeUsedInAllE = "";
		for(Edge_ptr path:inputGrid.edges){
			vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
			vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
			vector<Node_ptr> legitNodes = availebleNodes(sqrsContainE);
			//if path's legit nodes doesnt contain nTo; continue
			if(!ifContainNode(legitNodes,nTo))
					continue;





			string pathUseNode = edgeUseNode(path,nTo);
			nodeUsedInAllE += a(" + ") +pathUseNode;
		}
		constraint.push_back(nodeUsedInAllE + a(" <= 1"));
	}

	// edge number == node number - 1

/*	//no small loop
	for(int i = 0; i<= outputGrid.sizeX-2; i++){
		for(int j = 0; j<=outputGrid.sizeY-2;j++){
			Node_ptr n0 = outputGrid.getNode(i,j);
			Node_ptr n1 = outputGrid.getNode(i,j+1);
			Node_ptr n2 = outputGrid.getNode(i+1,j+1);
			Node_ptr n3 = outputGrid.getNode(i+1,j);

			Edge_ptr e0 = outputGrid.getEdge(i,j,i,j+1);
			Edge_ptr e1 = outputGrid.getEdge(i,j+1,i+1,j+1);
			Edge_ptr e2 = outputGrid.getEdge(i+1,j,i+1,j+1);
			Edge_ptr e3 = outputGrid.getEdge(i,j,i+1,j);

			for(Edge_ptr path:inputGrid.edges){
				vector<Node_ptr> pathLNodes = getLegitNodes(path);
				vector<Edge_ptr> pathLEdges = getLegitEdges(path);
				if(!ifContainNode(pathLNodes,n0))
					continue;
				if(!ifContainNode(pathLNodes,n1))
					continue;
				if(!ifContainNode(pathLNodes,n2))
					continue;
				if(!ifContainNode(pathLNodes,n3))
					continue;

				if(!ifContain(pathLEdges,e0))
					continue;
				if(!ifContain(pathLEdges,e1))
					continue;

				if(!ifContain(pathLEdges,e2))
					continue;
				if(!ifContain(pathLEdges,e3))
					continue;

				string pathUe0 = edgeUseEdge(path,e0);
				string pathUe1 = edgeUseEdge(path,e1);
				string pathUe2 = edgeUseEdge(path,e2);
				string pathUe3 = edgeUseEdge(path,e2);

				constraint.push_back(pathUe0 + a(" + ") +pathUe1 + a(" + ") +pathUe2 + a(" + ") +pathUe3 + a(" <= 3 "));
			}
		}
	}*/

	/*//one Edge can only be used in one path
	for(Edge_ptr eTo:outputGrid.edges){

		bool legitEdge = false;

		for(Edge_ptr path:inputGrid.edges){
			vector<Edge_ptr> pathLegitEdges = getLegitEdges(path);
			if(ifContain(pathLegitEdges,eTo)){
				legitEdge = true;
				break;
			}
		}

		if(!legitEdge)
			continue;

		string pathsUseEdge= "";
		for(Edge_ptr path:inputGrid.edges){
			vector<Edge_ptr> pathLegitEdges = getLegitEdges(path);
			if(!ifContain(pathLegitEdges,eTo))
				continue;
			string pathUseEdge= edgeUseEdge(path,eTo);
			pathsUseEdge += a(" + ") + pathUseEdge;
		}
		constraint.push_back(pathsUseEdge + a(" <= 1"));
	}*/


	//path is longer than storage
	for(Edge_ptr path:inputGrid.edges){
		if(!path->isStorage)
			continue;
		string str = "";
		vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
		vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
		for(Edge_ptr eTo:legitEdges){
			string eBindE= edgeUseEdge(path,eTo);
			str+= a(" + ") + a(eBindE);
		}
		str += a(" >= ") + a(STORAGESIZE);
		constraint.push_back(str);
	}

	//OBJ
/*	OBJ.push_back("Minimize");
	string str = "";
	for(Edge_ptr path:inputGrid.edges){

			vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
			vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
			for(Edge_ptr eTo:legitEdges){
				string eBindE= edgeUseEdge(path,eTo);
				str+= a(" + ") + a(eBindE);
			}
	}
	OBJ.push_back(str);*/
}

void PhysicalDesign::pathSquare(){


	for(Edge_ptr path:inputGrid.edges){


		for(Edge_ptr eTo:getLegitEdges(path)){
			string eBindE = edgeUseEdge(path,eTo);
			varName.push_back(eBindE); varType.push_back("1");
		}

		for(Node_ptr nTo:getLegitNodes(path)){
			string pathUseNode = edgeUseNode(path,nTo);
			varName.push_back(pathUseNode); varType.push_back("1");
		}
	}



	for(Edge_ptr path:inputGrid.edges){
			Node_ptr n0 = inputGrid.hashNodes.at(Node::hash2Int(path->x,path->y));
			Node_ptr n1 = inputGrid.hashNodes.at(Node::hash2Int(path->s,path->t));
			cout << "n0" << n0->x << " " <<n0->y<<endl ;
			cout << "n1" << n1->x << " " << n1->y << endl;

			vector<int> n0Loc = nodeLocInOutputgrid(n0);
			vector<int> n1Loc = nodeLocInOutputgrid(n1);
			cout << "n0Loc[0] " << n0Loc[0] << endl;
			cout << "n0Loc[1] " << n0Loc[1] << endl;
			cout << "n1Loc[0] " <<  n1Loc[0] << endl;
			cout << "n1Loc[1] " <<  n1Loc[1] << endl;
			Node_ptr node0Outgrid = outputGrid.getNode(n0Loc[0],n0Loc[1]);
			Node_ptr node1Outgrid = outputGrid.getNode(n1Loc[0],n1Loc[1]);

			//path must start n0 and end with n1
			string edgeAroudN0Used = "";
			vector<Edge_ptr> legitEdges = getLegitEdges(path);
			for(Edge_ptr eTo:node0Outgrid->adjEdgesList){
				if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
						continue;
				string eBindE= edgeUseEdge(path,eTo);
				edgeAroudN0Used += a(" + ") + eBindE;
			}

			constraint.push_back(edgeAroudN0Used + (" = 1"));

			string edgeAroudN1Used = "";
			for(Edge_ptr eTo:node1Outgrid->adjEdgesList){
				if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
						continue;
				string eBindE = edgeUseEdge(path,eTo);
				edgeAroudN1Used += a(" + ") + eBindE;
			}

			constraint.push_back(edgeAroudN1Used + (" = 1"));

			//must be a simple path
			for(Node_ptr nTo:getLegitNodes(path)){
				if(nTo == node0Outgrid || nTo == node1Outgrid)
					continue;
				string eUseNode = edgeUseNode(path,nTo);
				string edgeAroudUsed = "";
				for(Edge_ptr eTo:nTo->adjEdgesList){
					//eTo must be a legit Edge
					if(find(legitEdges.begin(),legitEdges.end(),eTo) == legitEdges.end())
						continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudUsed += a(" + ") + eBindE;
				}

				//if n0BindN = 0 && n1Bind = 0, edge used = 2 or 0

				constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" = ") + a(0));

			}

	}// for path must start n0 and end with n1z

	//one node can only be used in one path
	for(Node_ptr nTo:outputGrid.nodes){


		string nodeUsedInAllE = "";
		for(Edge_ptr path:inputGrid.edges){
			vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
			vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
			vector<Node_ptr> legitNodes = availebleNodes(sqrsContainE);
			//if path's legit nodes doesnt contain nTo; continue
			if(find(legitNodes.begin(),legitNodes.end(),nTo) == legitNodes.end())
				continue;



			string pathUseNode = edgeUseNode(path,nTo);
			nodeUsedInAllE += a(" + ") +pathUseNode;
		}
		constraint.push_back(nodeUsedInAllE + a(" <= 1"));
	}


	//path is longer than storage
	for(Edge_ptr path:inputGrid.edges){
		if(!path->isStorage)
			continue;
		string str = "";
		vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
		vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
		for(Edge_ptr eTo:legitEdges){
			string eBindE= edgeUseEdge(path,eTo);
			str+= a(" + ") + a(eBindE);
		}
		str += a(" >= ") + a(STORAGESIZE);
		constraint.push_back(str);
	}

	//OBJ
	OBJ.push_back("Minimize");
	string str = "";
	for(Edge_ptr path:inputGrid.edges){

			vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
			vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
			for(Edge_ptr eTo:legitEdges){
				string eBindE= edgeUseEdge(path,eTo);
				str+= a(" + ") + a(eBindE);
			}
	}
	OBJ.push_back(str);

}


void PhysicalDesign::pathSquareWithDev(){


	for(Edge_ptr path:inputGrid.edges){


		for(Edge_ptr eTo:getLegitEdges(path)){
			string eBindE = edgeUseEdge(path,eTo);
			varName.push_back(eBindE); varType.push_back("1");
		}

		for(Node_ptr nTo:getLegitNodes(path)){
			string pathUseNode = edgeUseNode(path,nTo);
			varName.push_back(pathUseNode); varType.push_back("1");
		}


		/*for(Node_ptr nTo:getLegitNodes(path)){
			string pathStartNode = edgeStartNode(path,nTo);
			varName.push_back(pathStartNode); varType.push_back("1");
		}

		for(Node_ptr nTo:getLegitNodes(path)){
			string pathEndNode = edgeEndNode(path,nTo);
			varName.push_back(pathEndNode); varType.push_back("1");
		}*/
	}



	for(Edge_ptr path:inputGrid.edges){
			Node_ptr n0 = inputGrid.hashNodes.at(Node::hash2Int(path->x,path->y));
			Node_ptr n1 = inputGrid.hashNodes.at(Node::hash2Int(path->s,path->t));
			Node_ptr node0Outgrid;
			Node_ptr node1Outgrid;

			vector<Edge_ptr> pathLegitEdges = getLegitEdges(path);
			for(Edge_ptr legtE : getLegitEdges(path)){
				cout<<" legit e " << "x" << legtE->x << "y" << legtE->y<< "s" <<legtE->s << "t" << legtE->t<<endl;
			}
			vector<Node_ptr> pathLegitNodes = getLegitNodes(path);
			if(!n0->isDev && !n1->isDev){
				//n1 use one node
				string n0useOneNode ="";
				for(Node_ptr nTo:getLegitNodesForDev(n0)){
					string n0UseNto = nodeUseNode(n0,nTo);
					varName.push_back(n0UseNto);varType.push_back("1");
					n0useOneNode += a(" + ") + n0UseNto;
					cout<<" legit node " << "x" << nTo->x << "y" << nTo->y<<endl;
				}

				constraint.push_back(n0useOneNode  + a(" = 1"));

				//n1 use one node
				string n1useOneNode ="";
				for(Node_ptr nTo:getLegitNodesForDev(n1)){
					string n1UseNto = nodeUseNode(n1,nTo);
					varName.push_back(n1UseNto);varType.push_back("1");
					n1useOneNode += a(" + ") + n1UseNto;
				}



				constraint.push_back(n1useOneNode  + a(" = 1"));

				//path must start n0 and end with n1

				//if n0 use nTo
				for(Node_ptr nTo:getLegitNodesForDev(n0)){
					string n0UseNto = nodeUseNode(n0,nTo);
					string edgeAroudNToUsed = "";
					for(Edge_ptr eTo:nTo->adjEdgesList){
						if(eTo->x == 1 && eTo->y == 2 && eTo->s == 1 && eTo->t == 3){
							cout << "got ya" << endl;
						}
						if(!ifContain(pathLegitEdges,eTo))
							continue;
						string eBindE= edgeUseEdge(path,eTo);
						edgeAroudNToUsed += a(" + ") + eBindE;
					}
					constraint.push_back(edgeAroudNToUsed+ a(" - ") + a(M) + a(" ") + a(n0UseNto) + a(" >= ") + a(1-M));
					constraint.push_back(edgeAroudNToUsed + a(" + ") + a(M) + a(" ") + a(n0UseNto) + a(" <= ") + a(1+M));

				}

				//if n1 use nTo
				for(Node_ptr nTo:getLegitNodesForDev(n1)){
					string n1UseNto = nodeUseNode(n1,nTo);
					string edgeAroudNToUsed = "";
					for(Edge_ptr eTo:nTo->adjEdgesList){
						if(!ifContain(pathLegitEdges,eTo))
							continue;
						string eBindE= edgeUseEdge(path,eTo);
						edgeAroudNToUsed += a(" + ") + eBindE;
					}
					constraint.push_back(edgeAroudNToUsed+ a(" - ") + a(M) + a(" ") + a(n1UseNto) + a(" >= ") + a(1-M));
					constraint.push_back(edgeAroudNToUsed + a(" + ") + a(M) + a(" ") + a(n1UseNto) + a(" <= ") + a(1+M));

				}



				//must be a simple path
				vector<Node_ptr> n0LegitNodes = getLegitNodesForDev(n0);
				vector<Node_ptr> n1LegitNodes = getLegitNodesForDev(n1);
				for(Node_ptr nTo:getLegitNodes(path)){
					bool nToMayN0 = false;
					bool nToMayN1 = false;
					if(ifContainNode(n0LegitNodes,nTo) ){
						nToMayN0 = true;
					}
					if(ifContainNode(n1LegitNodes,nTo)){
						nToMayN1 = true;
					}

					//if nTo can be used as n0

					if(nToMayN0 && !nToMayN1){
						string n0UseNto = nodeUseNode(n0,nTo);
						string eUseNode = edgeUseNode(path,nTo);
						string edgeAroudUsed = "";
						for(Edge_ptr eTo:nTo->adjEdgesList){
							//eTo must be a legit Edge
							if(!ifContain(pathLegitEdges,eTo))
								continue;
							string eBindE= edgeUseEdge(path,eTo);
							edgeAroudUsed += a(" + ") + eBindE;
						}

						//if not port0 or port1 and not n1UseThisNode, edge used = 2 or 0

						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" + ")+ a(M) + a(" ") + a(n0UseNto) + a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" - ")+a(M) + a(" ") + a(n0UseNto)+ a(" <= ") + a(0));

					}

					//else if nTo can be used as n1
					else if(!nToMayN0 && nToMayN1){
						string n1UseNto = nodeUseNode(n1,nTo);
						string eUseNode = edgeUseNode(path,nTo);
						string edgeAroudUsed = "";
						for(Edge_ptr eTo:nTo->adjEdgesList){
							//eTo must be a legit Edge
							if(!ifContain(pathLegitEdges,eTo))
								continue;
							string eBindE= edgeUseEdge(path,eTo);
							edgeAroudUsed += a(" + ") + eBindE;
						}

						//if not port0 or port1 and not n1UseThisNode, edge used = 2 or 0

						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" + ")+ a(M) + a(" ") + a(n1UseNto) + a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" - ")+a(M) + a(" ") + a(n1UseNto)+ a(" <= ") + a(0));

					}
					//else if nTo can be used as n0 and n1
					else if(nToMayN0 && nToMayN1){
						string n0UseNto = nodeUseNode(n0,nTo);
						string n1UseNto = nodeUseNode(n1,nTo);
						string eUseNode = edgeUseNode(path,nTo);
						string edgeAroudUsed = "";
						for(Edge_ptr eTo:nTo->adjEdgesList){
							//eTo must be a legit Edge
							if(!ifContain(pathLegitEdges,eTo))
								continue;
							string eBindE= edgeUseEdge(path,eTo);
							edgeAroudUsed += a(" + ") + eBindE;
						}

						//if not port0 or port1 and not n1UseThisNode, edge used = 2 or 0

						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" + ")  + a(M) + a(" ") + a(n1UseNto)+a(" + ")  + a(M) + a(" ") + a(n0UseNto) + a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" - ")+a(M) + a(" ") + a(n1UseNto)+ a(" - ")+a(M) + a(" ") + a(n0UseNto)+ a(" <= ") + a(0));

					}
					//else if nTo can be used as none
					else {

						string eUseNode = edgeUseNode(path,nTo);
						string edgeAroudUsed = "";
						for(Edge_ptr eTo:nTo->adjEdgesList){
							//eTo must be a legit Edge
							if(!ifContain(pathLegitEdges,eTo))
								continue;
							string eBindE= edgeUseEdge(path,eTo);
							edgeAroudUsed += a(" + ") + eBindE;
						}

						//if not port0 or port1 and not n1UseThisNode, edge used = 2 or 0

						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)   + a(" = ") + a(0));




					}

		}
			}

			else if (n0->isDev && !n1->isDev){
				vector<Node_ptr> n1LegitNodes = getLegitNodesForDev(n1);
				//path use port 0 or port 1
				Pd_ptr pd = nodesDev[n0];
				Node_ptr port0 = pd->port0Node;
				Node_ptr port1 = pd->port1Node;

				string pathEndPort0 = edgeEndNode(path,port0);
				varName.push_back(pathEndPort0);varType.push_back("1");
				string pathEndPort1 = edgeEndNode(path,port1);
				varName.push_back(pathEndPort1);varType.push_back("1");

				constraint.push_back(pathEndPort1 + a(" + ")+ pathEndPort0 + a(" = 1"));


				//n1 use one node
				string n1useOneNode ="";
				for(Node_ptr nTo:n1LegitNodes){
					string n1UseNto = nodeUseNode(n1,nTo);
					varName.push_back(n1UseNto);varType.push_back("1");
					n1useOneNode += a(" + ") + n1UseNto;
				}

				constraint.push_back(n1useOneNode  + a(" = 1"));

				//path must start n0 and end with n1

				//end with port0 or port1
				string edgeAroudPort0Used = "";
				for(Edge_ptr eTo:port0->adjEdgesList){
					if(!ifContain(pathLegitEdges,eTo))
						continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudPort0Used += a(" + ") + eBindE;

				}

				constraint.push_back(edgeAroudPort0Used + a(" - ") + a(M) + a(" ") + a(pathEndPort0) + a(" >= ") + a(1-M));
				constraint.push_back(edgeAroudPort0Used + a(" + ") + a(M) + a(" ") + a(pathEndPort0) + a(" <= ") + a(1+M));
				//if use port1, edge around Port0 cannot be used
				constraint.push_back(edgeAroudPort0Used + a(" - ") + a(M) + a(" ") + a(pathEndPort1) + a(" >= ") + a(-M));
				constraint.push_back(edgeAroudPort0Used + a(" + ") + a(M) + a(" ") + a(pathEndPort1) + a(" <= ") + a(+M));



				string edgeAroudPort1Used = "";
				for(Edge_ptr eTo:port1->adjEdgesList){
					if(!ifContain(pathLegitEdges,eTo))
						continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudPort1Used += a(" + ") + eBindE;

				}

				constraint.push_back(edgeAroudPort1Used + a(" - ") + a(M) + a(" ") + a(pathEndPort1) + a(" >= ") + a(1-M));
				constraint.push_back(edgeAroudPort1Used + a(" + ") + a(M) + a(" ") + a(pathEndPort1) + a(" <= ") + a(1+M));
				//if use port0, edge around Port1 cannot be used
				constraint.push_back(edgeAroudPort1Used + a(" - ") + a(M) + a(" ") + a(pathEndPort0) + a(" >= ") + a(-M));
				constraint.push_back(edgeAroudPort1Used + a(" + ") + a(M) + a(" ") + a(pathEndPort0) + a(" <= ") + a(+M));

				//if use nTo
				for(Node_ptr nTo:n1LegitNodes){
					string n1UseNto = nodeUseNode(n1,nTo);
					string edgeAroudNToUsed = "";
					for(Edge_ptr eTo:nTo->adjEdgesList){
						if(eTo->x == 1 && eTo->y == 2 && eTo->s == 1 && eTo->t == 3){
							cout << "got ya" << endl;
						}
						if(!ifContain(pathLegitEdges,eTo))
							continue;
						string eBindE= edgeUseEdge(path,eTo);
						edgeAroudNToUsed += a(" + ") + eBindE;
					}
					constraint.push_back(edgeAroudNToUsed+ a(" - ") + a(M) + a(" ") + a(n1UseNto) + a(" >= ") + a(1-M));
					constraint.push_back(edgeAroudNToUsed + a(" + ") + a(M) + a(" ") + a(n1UseNto) + a(" <= ") + a(1+M));

				}


				//must be a simple path
				for(Node_ptr nTo:getLegitNodes(path)){
					if(nTo == port0 || nTo == port1)
						continue;


						bool nToMayN1 = false;

						if(ifContainNode(n1LegitNodes,nTo)){
							nToMayN1 = true;
						}
					// if n1 may use nTo
					if(nToMayN1){
						string n1UseNto = nodeUseNode(n1,nTo);
						string eUseNode = edgeUseNode(path,nTo);
						string edgeAroudUsed = "";
						for(Edge_ptr eTo:nTo->adjEdgesList){
							//eTo must be a legit Edge
							if(!ifContain(pathLegitEdges,eTo))
								continue;
							string eBindE= edgeUseEdge(path,eTo);
							edgeAroudUsed += a(" + ") + eBindE;
						}

						//if not port0 or port1 and not n1UseThisNode, edge used = 2 or 0

						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" + ")  + a(M) + a(" ") + a(n1UseNto)+ a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" - ")+a(M) + a(" ") + a(n1UseNto)+ a(" <= ") + a(0));

					}
					//
					else{
						string eUseNode = edgeUseNode(path,nTo);
						string edgeAroudUsed = "";
						for(Edge_ptr eTo:nTo->adjEdgesList){
							//eTo must be a legit Edge
							if(!ifContain(pathLegitEdges,eTo))
								continue;
							string eBindE= edgeUseEdge(path,eTo);
							edgeAroudUsed += a(" + ") + eBindE;
						}

						//if not port0 or port1 and not n1UseThisNode, edge used = 2 or 0

						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" = ") + a(0));

					}


				}




			}
			else if (!n0->isDev && n1->isDev){
				vector<Node_ptr> n0LegitNodes = getLegitNodesForDev(n0);
				//path use port 0 or port 1
				Pd_ptr pd = nodesDev[n1];
				Node_ptr port0 = pd->port0Node;
				Node_ptr port1 = pd->port1Node;

				string pathEndPort0 = edgeEndNode(path,port0);
				varName.push_back(pathEndPort0);varType.push_back("1");
				string pathEndPort1 = edgeEndNode(path,port1);
				varName.push_back(pathEndPort1);varType.push_back("1");

				constraint.push_back(pathEndPort1 + a(" + ")+ pathEndPort0 + a(" = 1"));


				//n0 use one node
				string n0useOneNode ="";
				for(Node_ptr nTo:n0LegitNodes){
					string n0UseNto = nodeUseNode(n0,nTo);
					varName.push_back(n0UseNto);varType.push_back("1");
					n0useOneNode += a(" + ") + n0UseNto;
				}

				constraint.push_back(n0useOneNode  + a(" = 1"));

				//path must start n1 and end with n0

				//end with port0 or port1
				string edgeAroudPort0Used = "";
				for(Edge_ptr eTo:port0->adjEdgesList){
					if(!ifContain(pathLegitEdges,eTo))
						continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudPort0Used += a(" + ") + eBindE;

				}

				constraint.push_back(edgeAroudPort0Used + a(" - ") + a(M) + a(" ") + a(pathEndPort0) + a(" >= ") + a(1-M));
				constraint.push_back(edgeAroudPort0Used + a(" + ") + a(M) + a(" ") + a(pathEndPort0) + a(" <= ") + a(1+M));
				//if use port1, edge around Port0 cannot be used
				constraint.push_back(edgeAroudPort0Used + a(" - ") + a(M) + a(" ") + a(pathEndPort1) + a(" >= ") + a(-M));
				constraint.push_back(edgeAroudPort0Used + a(" + ") + a(M) + a(" ") + a(pathEndPort1) + a(" <= ") + a(+M));



				string edgeAroudPort1Used = "";
				for(Edge_ptr eTo:port1->adjEdgesList){
					if(!ifContain(pathLegitEdges,eTo))
						continue;
					string eBindE= edgeUseEdge(path,eTo);
					edgeAroudPort1Used += a(" + ") + eBindE;

				}

				constraint.push_back(edgeAroudPort1Used + a(" - ") + a(M) + a(" ") + a(pathEndPort1) + a(" >= ") + a(1-M));
				constraint.push_back(edgeAroudPort1Used + a(" + ") + a(M) + a(" ") + a(pathEndPort1) + a(" <= ") + a(1+M));
				//if use port0, edge around Port1 cannot be used
				constraint.push_back(edgeAroudPort1Used + a(" - ") + a(M) + a(" ") + a(pathEndPort0) + a(" >= ") + a(-M));
				constraint.push_back(edgeAroudPort1Used + a(" + ") + a(M) + a(" ") + a(pathEndPort0) + a(" <= ") + a(+M));

				//if use nTo
				for(Node_ptr nTo:n0LegitNodes){
					string n0UseNto = nodeUseNode(n0,nTo);
					string edgeAroudNToUsed = "";
					for(Edge_ptr eTo:nTo->adjEdgesList){
						if(eTo->x == 1 && eTo->y == 2 && eTo->s == 1 && eTo->t == 3){
							cout << "got ya" << endl;
						}
						if(!ifContain(pathLegitEdges,eTo))
							continue;
						string eBindE= edgeUseEdge(path,eTo);
						edgeAroudNToUsed += a(" + ") + eBindE;
					}
					constraint.push_back(edgeAroudNToUsed+ a(" - ") + a(M) + a(" ") + a(n0UseNto) + a(" >= ") + a(1-M));
					constraint.push_back(edgeAroudNToUsed + a(" + ") + a(M) + a(" ") + a(n0UseNto) + a(" <= ") + a(1+M));

				}


				//must be a simple path
				for(Node_ptr nTo:getLegitNodes(path)){
					if(nTo == port0 || nTo == port1)
						continue;


						bool nToMayN1 = false;

						if(ifContainNode(n0LegitNodes,nTo)){
							nToMayN1 = true;
						}
					// if n0 may use nTo
					if(nToMayN1){
						string n0UseNto = nodeUseNode(n0,nTo);
						string eUseNode = edgeUseNode(path,nTo);
						string edgeAroudUsed = "";
						for(Edge_ptr eTo:nTo->adjEdgesList){
							//eTo must be a legit Edge
							if(!ifContain(pathLegitEdges,eTo))
								continue;
							string eBindE= edgeUseEdge(path,eTo);
							edgeAroudUsed += a(" + ") + eBindE;
						}

						//if not port0 or port1 and not n0UseThisNode, edge used = 2 or 0

						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" + ")  + a(M) + a(" ") + a(n0UseNto)+ a(" >= ") + a(0));
						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" - ")+a(M) + a(" ") + a(n0UseNto)+ a(" <= ") + a(0));

					}
					//
					else{
						string eUseNode = edgeUseNode(path,nTo);
						string edgeAroudUsed = "";
						for(Edge_ptr eTo:nTo->adjEdgesList){
							//eTo must be a legit Edge
							if(!ifContain(pathLegitEdges,eTo))
								continue;
							string eBindE= edgeUseEdge(path,eTo);
							edgeAroudUsed += a(" + ") + eBindE;
						}

						//if not port0 or port1 and not n0UseThisNode, edge used = 2 or 0

						constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)  + a(" = ") + a(0));

					}


				}
			}



	}// for path must start n0 and end with n1z

	//one node can only be used in one path
	for(Node_ptr nTo:outputGrid.nodes){


		bool isDevNode = false;
		for(Pd_ptr pd:phyDevs){
			Node_ptr port0 = pd->port0Node;
			Node_ptr port1 = pd->port1Node;
			if(port0 == nTo){
				isDevNode = true;
				break;
			}
			if(port1 == nTo){
				isDevNode = true;
				break;
			}

		}

		if(isDevNode)
			continue;

		string nodeUsedInAllE = "";
		for(Edge_ptr path:inputGrid.edges){
			vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
			vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
			vector<Node_ptr> legitNodes = availebleNodes(sqrsContainE);
			//if path's legit nodes doesnt contain nTo; continue
			if(find(legitNodes.begin(),legitNodes.end(),nTo) == legitNodes.end())
				continue;





			string pathUseNode = edgeUseNode(path,nTo);
			nodeUsedInAllE += a(" + ") +pathUseNode;
		}
		constraint.push_back(nodeUsedInAllE + a(" <= 1"));
	}


	for(int i = 0; i<= outputGrid.sizeX-2; i++){
		for(int j = 0; j<=outputGrid.sizeY-2;j++){
			Node_ptr n0 = outputGrid.getNode(i,j);
			Node_ptr n1 = outputGrid.getNode(i,j+1);
			Node_ptr n2 = outputGrid.getNode(i+1,j+1);
			Node_ptr n3 = outputGrid.getNode(i+1,j);

			Edge_ptr e0 = outputGrid.getEdge(i,j,i,j+1);
			Edge_ptr e1 = outputGrid.getEdge(i,j+1,i+1,j+1);
			Edge_ptr e2 = outputGrid.getEdge(i+1,j,i+1,j+1);
			Edge_ptr e3 = outputGrid.getEdge(i,j,i+1,j);

			for(Edge_ptr path:inputGrid.edges){
				vector<Node_ptr> pathLNodes = getLegitNodes(path);
				vector<Edge_ptr> pathLEdges = getLegitEdges(path);
				if(!ifContainNode(pathLNodes,n0))
					continue;
				if(!ifContainNode(pathLNodes,n1))
									continue;
				if(!ifContainNode(pathLNodes,n2))
									continue;
				if(!ifContainNode(pathLNodes,n3))
									continue;

				if(!ifContain(pathLEdges,e0))
					continue;
				if(!ifContain(pathLEdges,e1))
					continue;

				if(!ifContain(pathLEdges,e2))
					continue;
				if(!ifContain(pathLEdges,e3))
					continue;

				string pathUe0 = edgeUseEdge(path,e0);
				string pathUe1 = edgeUseEdge(path,e1);
				string pathUe2 = edgeUseEdge(path,e2);
				string pathUe3 = edgeUseEdge(path,e2);

				constraint.push_back(pathUe0 + a(" + ") +pathUe1 + a(" + ") +pathUe2 + a(" + ") +pathUe3 + a(" <= 3 "));
			}


		}
	}

	/*//one Edge can only be used in one path
	for(Edge_ptr eTo:outputGrid.edges){

		bool legitEdge = false;

		for(Edge_ptr path:inputGrid.edges){
			vector<Edge_ptr> pathLegitEdges = getLegitEdges(path);
			if(ifContain(pathLegitEdges,eTo)){
				legitEdge = true;
				break;
			}
		}

		if(!legitEdge)
			continue;

		string pathsUseEdge= "";
		for(Edge_ptr path:inputGrid.edges){
			vector<Edge_ptr> pathLegitEdges = getLegitEdges(path);
			if(!ifContain(pathLegitEdges,eTo))
				continue;
			string pathUseEdge= edgeUseEdge(path,eTo);
			pathsUseEdge += a(" + ") + pathUseEdge;
		}
		constraint.push_back(pathsUseEdge + a(" <= 1"));
	}*/


	//path is longer than storage
	for(Edge_ptr path:inputGrid.edges){
		if(!path->isStorage)
			continue;
		string str = "";
		vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
		vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
		for(Edge_ptr eTo:legitEdges){
			string eBindE= edgeUseEdge(path,eTo);
			str+= a(" + ") + a(eBindE);
		}
		str += a(" >= ") + a(STORAGESIZE);
		constraint.push_back(str);
	}

	//OBJ
	OBJ.push_back("Minimize");
	string str = "";
	for(Edge_ptr path:inputGrid.edges){

			vector<Sqr_ptr> sqrsContainE = getLegitSquareInOutputGrid(path);
			vector<Edge_ptr> legitEdges = availebleEdges(sqrsContainE);
			for(Edge_ptr eTo:legitEdges){
				string eBindE= edgeUseEdge(path,eTo);
				str+= a(" + ") + a(eBindE);
			}
	}
	OBJ.push_back(str);

}


void PhysicalDesign::nodeBind(){
	for(Node_ptr nFrom:inputGrid.nodes){
		for(Node_ptr nTo:outputGrid.nodes){
			string nodeBindNode = nodeBNode(nFrom,nTo);
			varName.push_back(nodeBindNode);varType.push_back("1");
		}
	}

	//one device binds to one node
	for(Node_ptr nFrom:inputGrid.nodes){
		string str = "";

		for(Node_ptr nTo:outputGrid.nodes){
			string nodeBindNode = nodeBNode(nFrom,nTo);
			str+= a(" + ") + a(nodeBindNode);

		}
		str += a(" = 1");
		constraint.push_back(str);
	}

	//one node bind at most one dev
	for(Node_ptr nTo:outputGrid.nodes){
		string str = "";
		for(Node_ptr nFrom:inputGrid.nodes){
			string nodeBindNode = nodeBNode(nFrom,nTo);


			str+= a(" + ") + a(nodeBindNode);

		}
		str += a(" <= 1");
		constraint.push_back(str);
	}
}

void PhysicalDesign::paths(){
	for(Edge_ptr eFrom:inputGrid.edges){
		for(Edge_ptr eTo:outputGrid.edges){
			string eBindE = edgeUseEdge(eFrom,eTo);
			varName.push_back(eBindE); varType.push_back("1");
		}


		for(Node_ptr nTo:outputGrid.nodes){
			string eUseNode = edgeUseNode(eFrom,nTo);
			varName.push_back(eUseNode); varType.push_back("1");
		}
	}




	//path must start n0 and end with n1z
	for(Edge_ptr eFrom:inputGrid.edges){
		Node_ptr n0 = inputGrid.hashNodes.at(Node::hash2Int(eFrom->x,eFrom->y));
		Node_ptr n1 = inputGrid.hashNodes.at(Node::hash2Int(eFrom->s,eFrom->t));

		//if n0 or n1 is bind to a node, edge aroud it must be used
		for(Node_ptr nTo:outputGrid.nodes){
			string n0BindN = nodeBNode(n0,nTo);
			string n1BindN =  nodeBNode(n1,nTo);


			//if n0 bind to N, edge0 + edge1 + edge2 + edge 3 = 1
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudFUsed = "";
			for(Edge_ptr eTo:nTo->adjEdgesList){
				string eBindE= edgeUseEdge(eFrom,eTo);
				edgeAroudFUsed += a(" + ") + eBindE;
			}

			constraint.push_back(edgeAroudFUsed + a(" - ") + a(M) + a(" ") + a(n0BindN) + a(" >= ") + a(1-M));
			constraint.push_back(edgeAroudFUsed + a(" + ") + a(M) + a(" ") + a(n0BindN) + a(" <= ") + a(1+M));
			//if n1 bind To
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudaUsed = "";
			for(Edge_ptr eTo:nTo->adjEdgesList){
				string eBindE= edgeUseEdge(eFrom,eTo);
				edgeAroudaUsed += a(" + ") + eBindE;
			}

			constraint.push_back(edgeAroudaUsed + a(" - ") + a(M) + a(" ") + a(n1BindN) + a(" >= ") + a(1-M));
			constraint.push_back(edgeAroudaUsed + a(" + ") + a(M) + a(" ") + a(n1BindN) + a(" <= ") + a(1+M));

			//for device other father and son, if this device bind to node, edge around it cannot be used

			for(Node_ptr otherN:inputGrid.nodes){
				if(otherN == n0 || otherN == n1)
					continue;

				string  otherNBindN = nodeBNode(otherN,nTo);

				string edgeAroudDUsed = "";
				for(Edge_ptr eTo:nTo->adjEdgesList){
					string eBindE= edgeUseEdge(eFrom,eTo);
					edgeAroudDUsed += a(" + ") + eBindE;
				}

				//if dbindN = 1 then edge = 0
				constraint.push_back(edgeAroudDUsed + a(" - ") + a(M) + a(" ") + a(otherNBindN) + a(" >= ") + a(-M));
				constraint.push_back(edgeAroudDUsed + a(" + ") + a(M) + a(" ") + a(otherNBindN) + a(" <= ") + a(+M));

			}


		}


	}// for path must start n0 and end with n1z


	// must be a simple path
	for(Edge_ptr eFrom:inputGrid.edges){

		Node_ptr n0 = inputGrid.hashNodes.at(Node::hash2Int(eFrom->x,eFrom->y));
		Node_ptr n1 = inputGrid.hashNodes.at(Node::hash2Int(eFrom->s,eFrom->t));


		for(Node_ptr nTo:outputGrid.nodes){
			string eUseNode = edgeUseNode(eFrom,nTo);


			string n0BindN = nodeBNode(n0,nTo);
			string n1BindN =  nodeBNode(n1,nTo);

			string edgeAroudUsed = "";
			for(Edge_ptr eTo:nTo->adjEdgesList){
				string eBindE= edgeUseEdge(eFrom,eTo);

				edgeAroudUsed += a(" + ") + eBindE;
			}

			//if n0BindN = 0 && n1Bind = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * father >= 0
			//edgeUsde - 2 * nodeUsedInC - M * father <= 0
			constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode)+ a(" + ") + a(M) + a(" ") + a(n0BindN) +a(" + ")+a(M) + a(" ") + a(n1BindN) + a(" >= ") + a(0));
			constraint.push_back(edgeAroudUsed + a(" - ") + a(2) +a(" ") +a(eUseNode) + a(" - ") + a(M) + a(" ") + a(n0BindN)+a(" - ")+a(M) + a(" ") + a(n1BindN) + a(" <= ") + a(0));




		}




	} //  must be a simple path


	//one node can only be used in one path
	for(Node_ptr nTo:outputGrid.nodes){
		string nodeUsedInAllE = "";
		for(Edge_ptr eFrom:inputGrid.edges){
			string eUseNode = edgeUseNode(eFrom,nTo);
			nodeUsedInAllE += a(" + ") +eUseNode;
		}
		constraint.push_back(nodeUsedInAllE + a(" <= 1"));
	}

	//path is longer than storage
	for(Edge_ptr eFrom:inputGrid.edges){
		if(!eFrom->isStorage)
			continue;
		string str = "";
		for(Edge_ptr eTo:outputGrid.edges){
			string eBindE= edgeUseEdge(eFrom,eTo);
			str+= a(" + ") + a(eBindE);
		}
		str += a(" >= ") + a(STORAGESIZE);
		constraint.push_back(str);
	}



}



void PhysicalDesign::setDevPos(Node_ptr inputDevNode){
	vector<int> outputNodePos = nodeLocInOutputgrid(inputDevNode);
	int outX = outputNodePos.at(0);
	int outY = outputNodePos.at(1);

	boost::shared_ptr<phyDev> pDVer(new phyDev());
	pDVer->vertical = true;
	pDVer->horizontal = false;
	verPhyDevs.push_back(pDVer);
	nodesVerDev[inputDevNode] = pDVer;
	pDVer->setGrid(outputGrid);

	boost::shared_ptr<phyDev> pDHor(new phyDev());
	pDHor->vertical = false;
	pDHor->horizontal = true;
	pDHor->setGrid(outputGrid);
	horPhyDevs.push_back(pDHor);
	nodesHorDev[inputDevNode] = pDHor;

	vector<Sqr_ptr> sqrContainV = getSquareInputGridContainNode(inputDevNode);
	//if dev is in the corner, shared by 1 square
	if(sqrContainV.size() == 1){
		Sqr_ptr sqr = sqrContainV.at(0);
		sqr->getCornerPos();
		//left down
		if(inputDevNode->x == sqr->left && inputDevNode->y == sqr->down){
			//ver
			pDVer->setDevCenterofGrid(outX + 1,outY  + 2);
			//hor
			pDHor->setDevCenterofGrid(outX + 2,outY  + 1);
		}
		//left up
		else if(inputDevNode->x == sqr->left && inputDevNode->y == sqr->up){
			//ver
			pDVer->setDevCenterofGrid(outX + 1,outY  - 2);
			//hor
			pDHor->setDevCenterofGrid(outX + 2,outY  - 1);
		}
		//right down
		else if(inputDevNode->x == sqr->right && inputDevNode->y == sqr->down){
			//ver
			pDVer->setDevCenterofGrid(outX - 1,outY  + 2);
			//hor
			pDHor->setDevCenterofGrid(outX - 2,outY  + 1);

		}
		//right up
		else if(inputDevNode->x == sqr->right && inputDevNode->y == sqr->up){
			//ver
			pDVer->setDevCenterofGrid(outX - 1,outY - 2);
			//hor
			pDHor->setDevCenterofGrid(outX - 2,outY - 1);

		}


	}
	//if dev is on the edge, shared by two squares
	else if(sqrContainV.size() == 2){
		int xMoveR = inputDevNode->x + 1;
		int xMoveL = inputDevNode->x - 1;
		int yMoveU = inputDevNode->y + 1;
		int yMoveD = inputDevNode->y - 1;

		Sqr_ptr sqr0 = sqrContainV.at(0);
		Sqr_ptr sqr1 = sqrContainV.at(1);

		sqr0->getCornerPos();
		sqr1->getCornerPos();


		//when node move 1 unit right, if it is out of both square, means node is
		if(xMoveR > sqr0->right && xMoveR > sqr1->right){
			//ver
			pDVer->setDevCenterofGrid(outX - 1,outY);
			//hor
			pDHor->setDevCenterofGrid(outX - 2,outY);
		}
		//move left
		if(xMoveL < sqr0->left && xMoveL < sqr1->left){
			//ver
			pDVer->setDevCenterofGrid(outX + 1,outY);
			//hor
			pDHor->setDevCenterofGrid(outX + 2,outY);
		}
		// move up
		if(yMoveU > sqr0->up && yMoveU > sqr1->up){
			//ver
			pDVer->setDevCenterofGrid(outX,outY - 2);
			//hor
			pDHor->setDevCenterofGrid(outX,outY - 1);
		}

		//move down
		if(yMoveD < sqr0->down && yMoveD < sqr1->down){
			//ver
			pDVer->setDevCenterofGrid(outX,outY + 2);
			//hor
			pDHor->setDevCenterofGrid(outX,outY + 1);
		}




	}
	//if dev is is shared by 3 or more squares
	else if(sqrContainV.size() == 3 || sqrContainV.size() == 4){
		//ver
		pDVer->setDevCenterofGrid(outX,outY);
		//hor
		pDHor->setDevCenterofGrid(outX,outY);
	}






	//set pD nodes and edges
	pDVer->setNodesOffsetFromCenter();
	pDVer->setNodesInGrid();
	pDHor->setNodesOffsetFromCenter();
	pDHor->setNodesInGrid();

}

void PhysicalDesign::genILP(){

	//set rank of each square


#if 0

	squaresInput[0]->minX = 5;
	squaresInput[0]->minY = 5;
	inputGrid.getNode(0,0)->isDev = true;
	Grid g(6,6);
	outputGrid = g;
	Grid squareG = getGridFromSquare(squaresInput[0]);
	boost::shared_ptr<phyDev> pD(new phyDev());
	pD->vertical = false;
	pD->horizontal = true;
	pD->setGrid(squareG);
	pD->setDevCenterofGrid(2,1);
	pD->setNodesOffsetFromCenter();
	pD->setNodesInGrid();


	phyDevs.push_back(pD);
	nodesDev[inputGrid.getNode(0,0)] = pD;



	setTime(60);
	setGap(0.1);
	pathSquareWithDev();
	writeToFile("squareILP.lp");
	ILPresults = ILP("squareILP.lp");
	writeGraphFile();
	return;
#endif

// 3*3 input grid, each grid has each individual
#if 1
	hashInputSquare[hash2Int(0,0)]->minY = 5;
	hashInputSquare[hash2Int(0,0)]->minX = 6;
/*	hashInputSquare[hash2Int(0,0)]->minX = 6;
	hashInputSquare[hash2Int(0,1)]->minY = 6;
	hashInputSquare[hash2Int(1,0)]->minX = 6;
	hashInputSquare[hash2Int(1,0)]->minY = 6;
	hashInputSquare[hash2Int(1,1)]->minX = 6;
	hashInputSquare[hash2Int(1,1)]->minY = 6;*/

	int outputGridX = 0;
	cout << " inputGrid size X "<<inputGrid.sizeX << endl;
	int index = 0;
	for(int i = 0; i <= inputGrid.sizeX -2 ;i++){
		//chose a square on row 0
		//cout <<"i is "<< index << endl;
		int temp = hash2Int(index,0);
		cout <<"hash is "<< hash2Int(index,0) <<  endl;
		cout << "hashInputSquare minx is "<<hashInputSquare[temp]->minX <<endl;
		Sqr_ptr sqr = hashInputSquare[hash2Int(index,0)];
		outputGridX += sqr->minX;
	}
	int outputGridY = 0;
	for(int j = 0; j <= inputGrid.sizeY-2;j++){
		//chose a square on row 0
		Sqr_ptr sqr = hashInputSquare[hash2Int(0,j)];
		outputGridY += sqr->minY;
	}



	Grid g(outputGridX+1,outputGridY+1);
	outputGrid = g;
	cout << "im here" << endl;

	//set device position in output grid;
	for(Node_ptr n:(inputGrid.nodes)){
		if(n->isDev){
			setDevPos(n);
		}
	}

	setTime(60);
	setGap(0.1);
	pathSquareFixCrossDev();
	writeToFile("squareILP.lp");
	ILPresults = ILP("squareILP.lp");
	writeGraphFile();
	return;
#endif


#if 1
	for(Sqr_ptr sqr:squaresInput){
		if(sqr->rowNum == 0){
			sqr->minX = STORAGESIZE-1;
			sqr->minY = STORAGESIZE-2;

		}else{
			sqr->minX = STORAGESIZE-1;
			sqr->minY = STORAGESIZE-1;
		}
	}


	//Grid g(9,8);
	outputGrid = g;

	setTime(60);
	setGap(0.1);
	pathSquare();
	writeToFile("squareILP.lp");
	ILPresults = ILP("squareILP.lp");
	writeGraphFile();
	return;
#endif



}

void PhysicalDesign::writeToFile(string fileName){
	writeILP write;
	const char* f = fileName.c_str();

	for(int i = 0; i <= varName.size() -1 ;i++){
		string name = varName.at(i);
		string type = varType.at(i);

		if(type == "0")
			bounds.push_back(a(-M) + a(" <= ") + name + a(" <= ") + a(M));
	}

	write.writeOBJ(OBJ,f);
	write.writeConstraint(constraint,f);
	write.writeBounds(bounds,f);
	write.writeVarNames(varName,varType,f);

}

void PhysicalDesign::writeGraphFile(){
	ofstream file;
	file.open("edgesPhyDesign.txt");
	ofstream edgeInfo;
	int cCount = 0;
	for(Edge_ptr path:inputGrid.edges){
			for(Edge_ptr e:outputGrid.edges){
				string pathUseEdge = edgeUseEdge(path,e);
				int edgeUsedValue = ILPresults[pathUseEdge];
				if(edgeUsedValue == 0)
					continue;
				//cout << edgeUsedInC << " is 1" << endl;


				file << e->x << endl;
				file << e->y << endl;
				file << e->s << endl;
				file << e->t << endl;
				//cout << " color is" << color << endl;
			}

	}
	for(Pd_ptr pd:phyDevs){

		for(Edge_ptr e:pd->edges){
			file << e->x << endl;
			file << e->y << endl;
			file << e->s << endl;
			file << e->t << endl;
		}

	}

	for(Node_ptr devNode:inputGrid.nodes){
		if(!devNode->isDev)
			continue;

		Pd_ptr horDev = nodesHorDev[devNode];
		Pd_ptr verDev = nodesVerDev[devNode];

		string devIsHor = devHor(devNode);

		int devHorValue = ILPresults[devIsHor];

		if(devHorValue == 1){
			for(Edge_ptr e:horDev->edges){
				file << e->x << endl;
				file << e->y << endl;
				file << e->s << endl;
				file << e->t << endl;
			}
		}
		else{
			for(Edge_ptr e:verDev->edges){
				file << e->x << endl;
				file << e->y << endl;
				file << e->s << endl;
				file << e->t << endl;
			}
		}

	}


	file.close();


	file.open("nodePhyDesign.txt");


	for(Node_ptr n:inputGrid.nodes){
		if(n->isDev)
				continue;
		for(Node_ptr nTo:outputGrid.nodes){
			string nodeUNode = nodeUseNode(n,nTo);
			int edgeUsedValue = ILPresults[nodeUNode];
			if(edgeUsedValue == 0)
				continue;
			//cout << edgeUsedInC << " is 1" << endl;


			file << nTo->x << endl;
			file << nTo->y << endl;
			//cout << " color is" << color << endl;
		}

	}
	for(Pd_ptr pd:phyDevs){
		Node_ptr n0 = pd->port0Node;
		Node_ptr n1 = pd->port1Node;
		file<<n0->x << endl;
		file << n0 ->y << endl;
		file<< n1->x << endl;
		file << n1->y<<endl;

	}


	file.close();

}


void PhysicalDesign::fromGridToSqaures(){



	for(int i = 0; i <= inputGrid.sizeX -2; i++ ){
		for(int j = 0; j <= inputGrid.sizeY -2; j++){
			Sqr_ptr sqr(new Square());
			squaresInput.push_back(sqr);
			hashInputSquare[hash2Int(i,j)] = sqr;
			sqr->rowNum = j;
			sqr->columnNum = i;

			Node_ptr n0 = inputGrid.getNode(i,j);
			Node_ptr n1 = inputGrid.getNode(i+1,j);
			Node_ptr n2 = inputGrid.getNode(i+1,j+1);
			Node_ptr n3 = inputGrid.getNode(i,j+1);

			sqr->nodes.push_back(n0);
			sqr->nodes.push_back(n1);
			sqr->nodes.push_back(n2);
			sqr->nodes.push_back(n3);

			Edge_ptr e0 = inputGrid.getEdge(i,j,i+1,j);
			Edge_ptr e1 = inputGrid.getEdge(i+1,j,i+1,j+1);
			Edge_ptr e2 = inputGrid.getEdge(i,j+1,i+1,j+1);
			Edge_ptr e3 = inputGrid.getEdge(i,j,i,j+1);

			sqr->edges.push_back(e0);
			sqr->edges.push_back(e1);
			sqr->edges.push_back(e2);
			sqr->edges.push_back(e3);

			sqr->setMinXY(STORAGESIZE,STORAGESIZE);
			inputGrid.sqaureRankX[hash2Int(i,j)] = STORAGESIZE;
			cout << inputGrid.sqaureRankX[hash2Int(i,j)] << endl;
			inputGrid.sqaureRankY[hash2Int(i,j)] = STORAGESIZE;

		}
	}

	for(int i = 0; i <= inputGrid.sizeX -2; i++ ){
			for(int j = 0; j <= inputGrid.sizeY -2; j++){

				Sqr_ptr sqr = hashInputSquare[hash2Int(i,j)];
				cout << "sqr " << i << j << " size x is " << sqr->minX;
				cout << "sqr " << i << j << " size y is " << sqr->minY;

			}
		}


}










