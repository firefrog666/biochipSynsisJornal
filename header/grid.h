#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <map>
#include "../header/Node.h"
#include "../header/edge.h"
#include "../header/Algorithm.h"
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Node> Node_ptr;
typedef boost::shared_ptr<Edge> Edge_ptr;

using namespace std;



class Grid{
public:
	Grid(){

	}



	Grid(int i, int j){
		sizeX = i;
		sizeY = j;
		formGrid(i,j);
		for(Edge_ptr e:edges){
			e->isStorage = true;
		}
	}



public:
	Node_ptr nullNode;
	vector<Edge_ptr> edges;
	vector<Node_ptr> nodes;

	map<int,int> sqaureRankX;
	map<int,int> sqaureRankY;

	map<int,Node_ptr> hashNodes;
	map<int,Edge_ptr> hashEdges;

private:


public:
	int sizeX;
	int sizeY;


public:
	Node_ptr getNode(int i,int j){

		for(Node_ptr n:nodes){
			if(i == n->x
					&& j == n->y)
				return n;
		}

	}

	Edge_ptr getEdge(int x,int y,int s,int t){

		for(Edge_ptr e:edges){
					if( x == e->x
							&& y  == e->y
							&& s== e->s
							&& t== e->t)
						return e;
					else if( x == e->s
							&& y  == e->t
							&& s== e->x
							&& t== e->y)
						return e;
			}

	}


	Edge_ptr getEdgebyOffsite(int x, int y, int s , int t){
		//get left down corner
		int cornerX = 10000;
		int cornerY = 10000;
		for(Node_ptr n:nodes){
			if(n->x <= cornerY && n->y <= cornerY){
				cornerX = n->x;
				cornerY = n->y;
			}
		}

		for(Edge_ptr e:edges){
			if( x + cornerX == e->x
					&& y + cornerY  == e->y
					&& s + cornerX == e->s
					&& t + cornerY == e->t)
				return e;

		}
	}

	vector<Node_ptr> getNodesByOffsite(vector<int> offsites ){
		vector<Node_ptr> r;
		for(int i = 0; i <=offsites.size()-1;i+=2 ){
			int x = offsites.at(i);
			int y = offsites.at(i+1);
			r.push_back(getNodeByOffsite(x,y));
		}

		return r;
	}

	vector<Edge_ptr> getEdgesByNodes(vector<Node_ptr> inputNodes){

		vector<Edge_ptr> r;


		for(int i = 0; i <= inputNodes.size()-2;i++){
			Node_ptr n0 = inputNodes.at(i);
			for(int j = i+1; j <= inputNodes.size()-1;j++ ){
				Node_ptr n1 = inputNodes.at(j);
				bool isNeigbour = false;

				//see if neighbour
				for(Node_ptr adjNode : n0->adjNodesList){
					if(n1 == adjNode){
						isNeigbour = true;
						break;
					}
				}

				if(isNeigbour){
					Edge_ptr e = getEdge(n0->x,n0->y,n1->x,n1->y);
					r.push_back(e);
					continue;
				}


			}

		}

		return r;
	}

	Node_ptr getNodeByOffsite(int x, int y){
		int cornerX = 10000;
		int cornerY = 10000;
		for(Node_ptr n:nodes){
			if(n->x <= cornerY && n->y <= cornerY){
				cornerX = n->x;
				cornerY = n->y;
			}
		}

		for(Node_ptr n:nodes){
			if( x + cornerX == n->x
					&& y + cornerY  == n->y)
				return n;
		}
	}


	void formGrid(int x, int y){
		//Nodes
		for(int i = 0; i < x; i ++){
			for( int j = 0 ; j < y ; j++){
				Node_ptr n(new Node(i,j));
				hashNodes[n->hashValue()] = n;
				nodes.push_back(n);
			}
		}

		//set neigbous
		for(int i = 0; i < x; i++){
			for(int j =0; j < y; j++){
				Node_ptr n = hashNodes[Node::hash2Int(i,j)];
				int left = i - 1;
				int right = i + 1;
				int up = j + 1;
				int down = j - 1;
				if(left >= 0 ){
					n->setAdjNodes(hashNodes[Node::hash2Int(left,j)]);
				}

				if(right <= x-1 ){
					n->setAdjNodes(hashNodes[Node::hash2Int(right,j)]);
				}

				if(up <= y-1 ){
					n->setAdjNodes(hashNodes[Node::hash2Int(i,up)]);
				}

				if( down >= 0 ){
					n->setAdjNodes(hashNodes[Node::hash2Int(i,down)]);
				}

			}
		}

		//Edges
		for(Node_ptr n:nodes){
			for(Node_ptr neigbour:n->adjNodesList){
				if(Node::aLeftOrUnderb(n,neigbour)){
					Edge_ptr e(new Edge(n->x,n->y,neigbour->x,neigbour->y));

					hashEdges[e->hashValue()] = e;
					edges.push_back(e);
					n->adjEdgesList.push_back(e);
					neigbour->adjEdgesList.push_back(e);
				}
			}
		}
	}

};




#endif
