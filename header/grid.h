#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>
#include <map>
#include "../header/Node.h"
#include "../header/edge.h"
#include "../header/Algorithm.h"
#include "../header/Dna.h"
#include <boost/shared_ptr.hpp>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */




using namespace std;

typedef   Node* N;
typedef  Edge* E ;


class Grid{
public:
Grid(){

}



Grid(int i, int j){
	sizeX = i;
	sizeY = j;
	formGrid(i,j);
	for(Edge* e:edges){
		e->isStorage = true;
	}
}


/*
void drawPath(const V<E>& path, const V<N> criticalNodes, const char* pathName){
	lg<<"drawing plate"<<endl;
	drawNodes(nodes,"drawnodes.txt");
	drawEdges(path,"drawedges.txt");

	string command = S("./drawGraph.sh ")+ pathName;
	system(command.c_str());
	algo::pause();
	lg<<"test log in grid.h"<<endl;
}*/


public:
Node* nullNode;
vector<Edge*> edges;
vector<Node*> nodes;

map<int,int> sqaureRankX;
map<int,int> sqaureRankY;

map<float,Node*> hashNodes;
map<float,Edge*> hashEdges;

V<float> brinkNodeHash;

V<E> possibleEdgesSlot;
//V<N> possiblePortsSlot;

V<N> pumps;
V<N> wastes;
V<N> deviceNodes;

private:


public:
int sizeX;
int sizeY;
int left,down,up,right; //bounding box



public:

/*void drawNodes(const vector<Node*> nodes, const char* fileName){

	ofstream file;
	file.open(fileName,fstream::in | fstream::out | fstream::app);
	//cout<< "drawing Nodes" << endl;
	for(Node* n: nodes){
		file<<n->x<<endl;
		file<<n->y<<endl;
		file<<RED<<endl;
		//color
	}
	file.close();
}*/
void drawNodes(const vector<Node*> nodes, const char* fileName,Color color = GRAY,bool writeName = false,const char* nameFileName = NODE_NAME_FILE){

	assert(color == RED || color == WHITE || color == BLUE || color == BLACK || color == GRAY);
	ofstream file;
	ofstream nameFile;
	file.open(fileName,fstream::in | fstream::out | fstream::app);
	nameFile.open(nameFileName,fstream::in | fstream::out | fstream::app);
	for(Node* n: nodes){
		file<<n->x<<endl;
		file<<n->y<<endl;
		file<<color<<endl;
		if(writeName)
			nameFile<<n->name<<endl;
		else
			nameFile<<" "<<endl;
	}
	file.close();
	nameFile.close();
}
void drawEdges(const vector<Edge*>& edges, const char* fileName, Color color = GRAY,bool writeName = false,const char* nameFileName = EDGE_NAME_FILE){
	ofstream file;
	ofstream nameFile;
	file.open(fileName,fstream::in | fstream::out | fstream::app);
	nameFile.open(nameFileName,fstream::in | fstream::out | fstream::app);

	for(Edge* e: edges){
		file<<e->x<<endl;
		file<<e->y<<endl;
		file<<e->s<<endl;
		file<<e->t<<endl;
		file<<color<<endl;
		if(writeName)
			nameFile<<e->name<<endl;
		else
			nameFile<<" "<<endl;
	}
	file.close();
	nameFile.close();
}


void drawPath(const V<E>& path, const char* pathName,const V<N>& criticalNodes = {}, const V<N>& crticalNodes2 = {},const V<N>& critN3 = {},
					const V<E>& critialEdges = {}
					){
	drawEdges(edges,EDGE_FILE,GRAY);
	drawEdges(path,EDGE_FILE,BLUE);
	drawEdges(critialEdges,EDGE_FILE,RED);
	drawNodes(nodes,NODE_FILE,WHITE,true);
	drawNodes(criticalNodes,NODE_FILE,BLACK,true);
	drawNodes(crticalNodes2,NODE_FILE,GRAY,true);
	drawNodes(critN3,NODE_FILE,RED,true);
	string command = S(DRAW_SCRIPT)+ pathName;
	system(command.c_str());
	algo::pause();

}



Node* getNode(int i,int j){

	float key = algo::hash2Int(i,j);
	if(algo::mapContains(hashNodes,key))
		return hashNodes[key];
	else
		return NULL;
}



Edge* getEdge(int x,int y,int s,int t){


	float key0 = algo::hash4Int(x,y,s,t);
	float key1 = algo::hash4Int(s,t,x,y);
	if(algo::mapContains(hashEdges,key0)){
		return hashEdges[key0];
	}
	else if(algo::mapContains(hashEdges,key1)){
		return hashEdges[key1];
	}
	else
		return NULL;

}

void shiftToLeftDownCorner(){
	int xShift = left;
	int yShift = down;

	hashNodes.clear();
	for(Node* n:nodes){
		n->x = n->x - xShift;
		n->y = n->y - yShift;
		hashNodes[n->hashValue()] = n;
	}

	hashEdges.clear();
	for(Edge* e:edges){
		e->x = e->x - xShift;
		e->y = e->y - yShift;
		e->s = e->s - xShift;
		e->t = e->t - yShift;
		hashEdges[e->hashValue()] = e;
	}


	right = right -left;
	up = up - down;
	left = 0;
	down = 0;

}



void removeEdge(Edge* e){

	cout<< "removing edge ";
	e->printMyself();
	Node* n0 = getNode(e->x,e->y);
	Node* n1 = getNode(e->s,e->t);
	assert(n0 != NULL);
	assert(n1 != NULL);
	algo::remove(n0->adjNodesList,n1);

	algo::remove(n1->adjNodesList,n0);



	algo::remove(n0->adjEdgesList,e);

	algo::remove(n1->adjEdgesList,e);

	if(n0->adjEdgesList.size() == 0)
		removeNode(n0);
	if(n1->adjEdgesList.size() == 0)
		removeNode(n1);
	algo::remove(edges,e);
	hashEdges.erase(e->hashValue());

}






void removeNode(Node* n){
	assert(n->adjEdgesList.size() == 0);
	algo::remove(nodes,n);
	int i = n->hashValue();
	//Algorithm::remove(hashNodes,i);
	hashNodes.erase(i);
}
//calculate new x and y for the grid
void reshape(){
	int l = 10000;
	int d = 10000;
	int u = 0;
	int r = 0;

	for(Node* n:nodes){
		if(n->x <= l)
			l = n->x;

		if(n->y <= d)
			d = n->y;

		if(n->x >= r)
			r = n->x;
		if(n->y >= u)
			u = n->y;

	}

	left = l;
	right = r;
	up = u;
	down = d;
	sizeX = right - left + 1;
	sizeY = up - down + 1;
}



Edge* getEdgebyOffsite(int x, int y, int s , int t){
	//get left down corner
	int cornerX = 10000;
	int cornerY = 10000;
	for(Node* n:nodes){
		if(n->x <= cornerY && n->y <= cornerY){
			cornerX = n->x;
			cornerY = n->y;
		}
	}

	for(Edge* e:edges){
		if( x + cornerX == e->x
				&& y + cornerY  == e->y
				&& s + cornerX == e->s
				&& t + cornerY == e->t)
			return e;

	}
}

vector<Node*> getNodesByOffsite(vector<int> offsites ){
	vector<Node*> r;
	for(int i = 0; i <=offsites.size()-1;i+=2 ){
		int x = offsites.at(i);
		int y = offsites.at(i+1);
		r.push_back(getNodeByOffsite(x,y));
	}

	return r;
}

vector<Edge*> getEdgesByNodes(vector<Node*> inputNodes){

	vector<Edge*> r;


	for(int i = 0; i <= inputNodes.size()-2;i++){
		Node* n0 = inputNodes.at(i);
		for(int j = i+1; j <= inputNodes.size()-1;j++ ){
			Node* n1 = inputNodes.at(j);
			bool isNeigbour = false;

			//see if neighbour
			for(Node* adjNode : n0->adjNodesList){
				if(n1 == adjNode){
					isNeigbour = true;
					break;
				}
			}

			if(isNeigbour){
				Edge* e = getEdge(n0->x,n0->y,n1->x,n1->y);
				r.push_back(e);
				continue;
			}


		}

	}

	return r;
}

Node* getNodeByOffsite(int x, int y){
	int cornerX = 10000;
	int cornerY = 10000;
	for(Node* n:nodes){
		if(n->x <= cornerY && n->y <= cornerY){
			cornerX = n->x;
			cornerY = n->y;
		}
	}

	for(Node* n:nodes){
		if( x + cornerX == n->x
				&& y + cornerY  == n->y)
			return n;
	}
}
void reportSize(){
	cout << "sizeX = " << sizeX << endl;
	cout << "sizeY = " << sizeY << endl;
}


void formGrid(int x, int y){
	//Nodes
	for(int i = 0; i < x; i ++){
		for( int j = 0 ; j < y ; j++){
			Node* n(new Node(i,j));
			hashNodes[n->hashValue()] = n;
			nodes.push_back(n);
		}
	}

	//set neigbous
	for(int i = 0; i < x; i++){
		for(int j =0; j < y; j++){
			Node* n = hashNodes[algo::hash2Int(i,j)];
			int l = i - 1;
			int r = i + 1;
			int u = j + 1;
			int d = j - 1;
			if(l >= 0 ){
				n->setAdjNodes(hashNodes[algo::hash2Int(l,j)]);
			}

			if(r <= x-1 ){
				n->setAdjNodes(hashNodes[algo::hash2Int(r,j)]);
			}

			if(u <= y-1 ){
				n->setAdjNodes(hashNodes[algo::hash2Int(i,u)]);
			}

			if( d >= 0 ){
				n->setAdjNodes(hashNodes[algo::hash2Int(i,d)]);
			}

		}
	}

	//Edges
	for(Node* n:nodes){
		for(Node* neigbour:n->adjNodesList){
			if(Node::aLeftOrUnderb(n,neigbour)){
				Edge* e(new Edge(n->x,n->y,neigbour->x,neigbour->y));

				hashEdges[e->hashValue()] = e;
				edges.push_back(e);
				n->adjEdgesList.push_back(e);
				neigbour->adjEdgesList.push_back(e);
			}
		}
	}

	reshape();
}

float hash2Nodes(Node* a, Node* b){
	 float x = a->x;
	 float y = a->y;
	 float s = b->x;
	 float t = b->y;

	 float c = s-x;
	 float d = t-y;

	 if(d <= 0){
		 if(!(c > 0 && d == 0)){
			Node* temp;
			temp = a;
			a = b;
			b = temp;

		 }
	 }




	return algo::hash4Int(a->x,a->y,b->x,b->y);


}

Edge* getEdge(Node* start, Node* end){
	//cout << "find Edge"<<" " << start->x<<" " << start->y<<" "<< end->x<<" "<<end->y<<endl;

/*	int index = hash2Nodes(start,end);
	//cout<< "finding " <<index <<endl;
	auto it = hashEdges.find(index);


	if(it != hashEdges.end())
		return it->second;
	else
	{
		for( auto it = hashEdges.begin(); it !=hashEdges.end(); ++it ){
				cout<<it->first<<" ";
				cout<<it->second->name<<endl;
			}
		cout << "can't find the Edge with "<<start->name<<" "<<end->name <<endl;
		return NULL;
	}*/
	return getEdge(start->x,start->y,end->x,end->y);
}

vector<Edge*> pathNodesToEdges(vector<Node*> sortedNodes){
	vector<Edge*> r;
	for(auto it = sortedNodes.begin();it != sortedNodes.end()-1; it++){
		Node* fNode = *it;
		Node* lNode = *(it+1);

		Edge* e = getEdge(fNode,lNode);
		cout<<"adding e"<<e->name <<endl;
		//cin.get();
		//assert(e != NULL);
		if(e != NULL)
			r.push_back(e);
	}
	return r;
}

/*
 * find all paths originate from one of the starts to one of the ends, cover all nodes in nodesToCover in order
 * randomly return one path
 */
V<E> pathSoFar(V<V<E>>& pathSegments){
	V<E> path;

	for(V<E> segment: pathSegments){
		algo::join2Vec(path,segment);
	}
	return path;
}


/*
 * from one start to multiple destination, randomly randomly return one segment
 */
bool dfs(V<E>& segment,N start,const V<N>& ends = {},const  V<E>& exisitingPath = {}, const V<E>& forbidEdges = {},const V<N>& forbidNodes = {}){
	cout<<"searching path from ";
	cout<<start->name<<"to ";
	for(N n:ends){
		cout<<n->name<<", ";
	}
	cout<<endl;
	algo::pause();
	if(algo::vecContains(ends,start))
		return true;
	vector<Node*> searchPath;
	vector<Node*> stack;
	V<N> exsitingPathNodes = fromEdgesToNodes(exisitingPath);
	V<N> joints;
	stack.push_back(start);
	joints.push_back(start);

	cout<<" rand number " <<rand()%10<<endl;

	bool findT = false;
	while(stack.size()>0){
		Node* seed = stack.back();
		N joint = joints.back();
		stack.pop_back();
		joints.pop_back();
		algo::pop_To_Element(searchPath,joint);
		searchPath.push_back(seed);
		if(seed == getNode(4,3))
			cout<<"find node4,3"<<endl;
	/*	if(searchPath.size() > 1)
			drawPath(pathNodesToEdges(searchPath),"searchPath");*/
		//cout<<"searching Node "<<seed->name<<endl;
		if(algo::vecContains(ends,seed)){
			findT = true;
			break;
		}
		//cout<<"visiting seed"<< seed->name<<endl;
		//find a random adjNode
		V<int> visitedAdjId;
		int randAdjNodeId = -1;
		while(visitedAdjId.size()<seed->getAdjEdges()->size()){
			randAdjNodeId = rand()%seed->getAdjEdges()->size();
			//cout<<"neighbor size is "<<seed->adjEdgesList.size();
			//cout<<" randAdjId is "<<randAdjNodeId<<endl;
			if(algo::vecContains(visitedAdjId,randAdjNodeId))
				continue;
			else
				visitedAdjId.push_back(randAdjNodeId);

			Node* adjNode = (*seed->getAdjNodes()).at(randAdjNodeId);
			//cout<<"adjNode "<<adjNode->name<<endl;
/*			if(algo::vecContains(ends,seed)){
				findT = true;
				break;
			}*/

			if(algo::vecContains(exsitingPathNodes,adjNode) &&!algo::vecContains(ends,adjNode))
				continue;

			if(algo::vecContains(forbidNodes,adjNode) && !algo::vecContains(ends,adjNode))
				continue;

			if(algo::vecContains(searchPath,adjNode))
				continue;

			Edge* e = getEdge(seed,adjNode);
			//cout<<e->name <<endl;

			if(algo::vecContains(forbidEdges,e))
				continue;

			stack.push_back(adjNode);
			joints.push_back(seed);

		}
	}


	if(findT){
		segment = pathNodesToEdges(searchPath);
		cout<<"segment contains: ";
		for(E e:segment){
			cout<< e->name<<", ";
		}
		cout<<endl;
		return true;
	}
	else{
		return false;
	}

}


V<N> fromEdgesToNodes(const V<E>& pathEdges){
	V<N> r;
	for(E e:pathEdges){
		N n0 = getNode(e->x,e->y);
		N n1 = getNode(e->s,e->t);
		algo::distincAddVec(r,n0);
		algo::distincAddVec(r,n1);
	}
	return r;
}

/*
 * from one start to one destination, randomly randomly return one segment
 */

bool dfs(V<E>& segment, N s, N t, const V<E>& exsitingPath, const V<E>& forbidEdges, const V<N>& forbidNodes){
	cout<<"searching path from "<<s->name << " to "<<t->name << endl;
	if(s == t)
		return true;
	vector<Node*> searchPath;
	vector<Node*> stack;
	V<N> exsitingPathNodes = fromEdgesToNodes(exsitingPath);
	V<N> joints;
	stack.push_back(s);
	joints.push_back(s);

	bool findT = false;
	while(stack.size()>0){
		Node* seed = stack.back();
		N joint = joints.back();
		stack.pop_back();
		joints.pop_back();
		algo::pop_To_Element(searchPath,joint);
		searchPath.push_back(seed);

		if(seed == t){
			findT = true;
			break;
		}
		//find a random adjNode
		V<int> visitedAdjId;
		int randAdjNodeId = -1;
		while(visitedAdjId.size()<seed->getAdjEdges()->size()){
			randAdjNodeId = rand()%seed->getAdjEdges()->size();
			//cout<<"neighbor size is "<<seed->adjEdgesList.size();
			//cout<<" randAdjId is "<<randAdjNodeId<<endl;
			if(algo::vecContains(visitedAdjId,randAdjNodeId))
				continue;
			else
				visitedAdjId.push_back(randAdjNodeId);

			Node* adjNode = (*seed->getAdjNodes()).at(randAdjNodeId);
			//cout<<"adjNode "<<adjNode->name<<endl;
			if(algo::vecContains(exsitingPathNodes,adjNode))
				continue;

			if(algo::vecContains(forbidNodes,adjNode) && adjNode != t)
				continue;

			if(algo::vecContains(searchPath,adjNode))
				continue;

			Edge* e = getEdge(seed,adjNode);
			//cout<<e->name <<endl;

			if(algo::vecContains(forbidEdges,e))
				continue;

			stack.push_back(adjNode);
			joints.push_back(seed);

		}
	}


	if(findT){
		segment = pathNodesToEdges(searchPath);
		cout<<"segment contains: ";
		for(E e:segment){
			cout<< e->name<<", ";
		}
		cout<<endl;
		return true;
	}
	else{
		return false;
	}


}

bool dfs(const V<N>& starts, const V<N>& ends ,const V<N>& nodesToCover, int pathNumber,V<V<E>>& possiblePaths, const V<E>& forbidEdges,const V<N>& forbidNodes){
	for(int i = 0; i < pathNumber; i++){
		V<E> possiblePath;

		if(findPath(starts,ends,nodesToCover,possiblePath,forbidEdges,forbidNodes)){
			possiblePaths.push_back(possiblePath);
		}

	}

	if(possiblePaths.size() == 0){
		cout<<"no paths found"<<endl;
		return false;
	}
	else
		return true;

}
bool findPath(const V<N>& starts, const V<N>& ends ,const V<N>& nodesToCover, V<E>& possiblePath, const V<E>& forbidEdges,const V<N>& forbidNodes){
	lg<<"finding path in grih.h"<<endl;
	V<E> path;
	int nextNodeIndex = -1; //-1 means find starts to first node, BIGNUMBER means find last  node to destination
	//find starts to first node to cover
	V<V<E>> pathSegments;
	map<int,int> nodeIdTryTimes; //each node0 to node 1 try certain times //try certain times and quit;
	for(int startNodeIndex = -1; startNodeIndex <=nodesToCover.size()-1; startNodeIndex++){
		nodeIdTryTimes[startNodeIndex] = 0;
	}
	int maxTry = 10;

	do{
		V<E> segment;
		V<N> startLine;
		N destination;

		if(nextNodeIndex  == -1){
			startLine = starts;
			destination = nodesToCover.front();
		}
		else if(nextNodeIndex> -1 &&  nextNodeIndex < nodesToCover.size()-1){
			startLine.push_back(nodesToCover[nextNodeIndex]);
			destination = nodesToCover[nextNodeIndex+1];
		}
		else if(nextNodeIndex >= nodesToCover.size()-1){
			startLine = ends;
			destination = nodesToCover.back();
		}

		if(dfs(segment,destination,startLine,pathSoFar(pathSegments),forbidEdges,forbidNodes)){
			pathSegments.push_back(segment);
			nodeIdTryTimes[nextNodeIndex]++;
			cout<<"starts "<<" has tried " <<nodeIdTryTimes[nextNodeIndex]<<endl;
			if(nodeIdTryTimes[nextNodeIndex] >= maxTry)
				return false;
			nextNodeIndex++;
		}
		else{
			nextNodeIndex--;
			if(nextNodeIndex < -1)
				return false;
			pathSegments.pop_back();
			nodeIdTryTimes[nextNodeIndex] = 0;

		}
		possiblePath = pathSoFar(pathSegments);
		drawPath(possiblePath,"pathSoFar",forbidNodes);
		if(nextNodeIndex  == nodesToCover.size()){
			cout<<"now nextNodeIndex is "<< nextNodeIndex <<" and nodesToCover size is "<<nodesToCover.size()<<endl;
			break;
		}

	}while(true);


	return true;
}







	//srand(time(NULL));
bool dfs(Node* s, Node* t, V<E>& path ,const V<E>& forbidEdges = {}, const V<N>& forbidNodes = {}){
	cout<<"begin dfs"<<endl;
	cout<<"start is "<<s->name<<endl;
	cout<<"end is "<<t->name <<endl;

	vector<Node*> searchPath;
	vector<Node*> stack;
	V<N> joints;
	stack.push_back(s);
	joints.push_back(s);

	bool findT = false;
	while(stack.size()>0){
		Node* seed = stack.back();
		N joint = joints.back();

		stack.pop_back();
		joints.pop_back();

		algo::pop_To_Element(searchPath,joint);
		searchPath.push_back(seed);

		if(seed == t){
			findT = true;
			break;
		}

		cout<<"visiting seed"<< seed->name<<endl;

		//find a random adjNode
		V<int> visitedAdjId;
		int randAdjNodeId = -1;
		while(visitedAdjId.size()<seed->getAdjEdges()->size()){
			randAdjNodeId = rand()%seed->getAdjEdges()->size();
			//randAdjNodeId++;
			//cout<<"neighbor size is "<<seed->adjEdgesList.size();
			//cout<<" randAdjId is "<<randAdjNodeId<<endl;
			if(algo::vecContains(visitedAdjId,randAdjNodeId))
				continue;
			else
				visitedAdjId.push_back(randAdjNodeId);

			Node* adjNode = (*seed->getAdjNodes()).at(randAdjNodeId);
			//cout<<"adjNode "<<adjNode->name<<endl;

			if(algo::vecContains(forbidNodes,adjNode) && adjNode != t)
				continue;

			if(algo::vecContains(searchPath,adjNode))
				continue;

			Edge* e = getEdge(seed,adjNode);
			//cout<<e->name <<endl;

			if(algo::vecContains(forbidEdges,e))
				continue;

			stack.push_back(adjNode);
			joints.push_back(seed);

		}
	}

	//return true;
	if(findT){
		V<E> searchPathE = pathNodesToEdges(searchPath);


		path = searchPathE;
		return true;
	}
	else{
		return false;
	}

}


void calBondingBox(){
	left = 10000;
	down = 10000;
	right = 0;
	up = 0;
	for(N n:nodes){
		if(n->x <= left)
			left = n->x;
		if(n->x >= right)
			right = n->x;
		if(n->y <= down)
			down= n->y;
		if(n->y >= up)
			up = n->y;
	}
	cout<<"left "<<left<<" right "<<right<<" up "<< up << " down " << down<<endl;
}

void moveNodeRight(N n){

	n->x = n->x+1;
	n->setName();

}

void moveNodeUp(N n){
	n->y = n->y+1;
	n->setName();

}
void moveEdgeRight(E e){
	e->x = e->x+1;
	e->s = e->s + 1;
	e->setName();
}
void moveEdgeUp(E e){
	e->y = e->y+1;
	e->t = e->t + 1;
	e->setName();
}

void expandBondingbox(int newLeft,int newRigth, int newUp, int newDown){
	left = newLeft;
	right = newRigth;
	up = newUp;
	down = newDown;
}
void hashAllEdges(){
	hashEdges.clear();
	for(E e:edges){
		hashEdges[e->hashValue()] = e;
	}
}

void hashAllNodes(){
	hashNodes.clear();
	for(N n:nodes){
		hashNodes[n->hashValue()] = n;
	}
}
void reshapeGridGrowLeft(){
	for(N n:nodes){
		moveNodeRight(n);
	}
	for(E e:edges){
		moveEdgeRight(e);
	}
	hashAllNodes();
	hashAllEdges();

	expandBondingbox(left,right+1,up,down);

}
void reshapeGridGrowRight(){
	expandBondingbox(left,right+1,up,down);

}

void reshapeGridGrowUp(){
	expandBondingbox(left,right,up+1,down);
}

void reshapeGridGrowDown(){
	for(N n:nodes){
		moveNodeUp(n);
	}
	for(E e:edges){
		moveEdgeUp(e);
	}

	hashAllNodes();
	hashAllEdges();
	expandBondingbox(left,right,up+1,down);
}

//when adding new edges,see where to add new edges
void possibleEdgeToAdd(){

	for(int i = left; i < right;i++){
		for(int j = down; j<=up;j++){
			int e_x = i;
			int e_s = i+1;
			int e_y = j;
			int e_t = j;
			if(getEdge(e_x,e_y,e_s,e_t) == NULL){
				E e = new Edge(e_x,e_y,e_s,e_t);
				possibleEdgesSlot.push_back(e);

			}
		}
	}
	for(int j = down; j<up;j++){
		for(int i = left; i <= right;i++){
			int e_x = i;
			int e_s = i;
			int e_y = j;
			int e_t = j+1;
			if(getEdge(e_x,e_y,e_s,e_t) == NULL){
				E e = new Edge(e_x,e_y,e_s,e_t);
				possibleEdgesSlot.push_back(e);
			}

		}
	}

}

void addNode(N n ){
	if(n->x == 4 && n->y == 3)
		cout<<"adding node 4,3"<<endl;
	if(getNode(n->x,n->y) != NULL){
		cout<<n->name<<"exsit "<<endl;
		return;
	}
	nodes.push_back(n);
	hashNodes[n->hashValue()] = n;
}
void addEdge(E e){
	if(getEdge(e->x,e->y,e->s,e->t) != NULL){
		cout<<e->name<<" exists"<<endl;
		return;
	}
	edges.push_back(e);
	hashEdges[e->hashValue()] = e;
	N lNode = NULL;
	N rNode = NULL;
	if(getNode(e->x,e->y) == NULL){
		lNode = new Node(e->x,e->y);
		addNode(lNode);
	}
	else{
		lNode = getNode(e->x,e->y);
	}
	if(getNode(e->s,e->t) == NULL){
		rNode = new Node(e->s,e->t);
		addNode(rNode);
	}
	else{
		rNode = getNode(e->s,e->t);
	}
	assert(lNode != NULL);
	assert(rNode != NULL);
	lNode->adjNodesList.push_back(rNode);
	rNode->adjNodesList.push_back(lNode);
	lNode->adjEdgesList.push_back(e);
	rNode->adjEdgesList.push_back(e);
	//drawPath(edges,"addingEdges");

}


/*
 * first m chrome says who are edges (size of possible edges to add), after n chrome says who are pumbs (size of possible ports),
 *  n chrome after says who are wastes (size of possible ports)
 */

bool addNewEdgesByDna(Dna dna){
	for(int i = 0; i < possibleEdgesSlot.size();i++){
		int r = rand()%2;
		//if(dna.chromes[i] == 1 r == 1)
		if(dna.chromes.at(i) == 1)
			addEdge(possibleEdgesSlot[i]);
	}
	drawPath(edges,"afterAdding");
	return true;
}


void getBrinkNodeHash(){
	for(int i = left; i <= right; i++){
		brinkNodeHash.push_back(algo::hash2Int(i,up));
		brinkNodeHash.push_back(algo::hash2Int(i,down));
	}
	for(int j = down+1; j <= up-1 ; j++){
		brinkNodeHash.push_back(algo::hash2Int(left,j));
		brinkNodeHash.push_back(algo::hash2Int(right,j));
	}
}



void addPortByDna(Dna dna, int pumNumr,int wasteNum){
	addPumpByDna(dna,pumNumr);
	addWasteByDna(dna,wasteNum);
	drawPath(edges,"ports",pumps,wastes,deviceNodes);
}


bool validPort(N n){
	if(n == NULL)
		return false;
	//assert(algo::vecContains(possiblePortsSlot,n));
	assert(deviceNodes.size()>0);
	N deviceNode = deviceNodes.front();
	if(algo::vecContains(pumps,n)||algo::vecContains(wastes,n))
		return false;

	V<E> path;
	if(!dfs(n,deviceNode,path))
		return false;
	return true;
}

N findAPossilbePort(int indexLowBound, int indexUpperBound, int index){
	 N vPort = NULL;
	 int offset = 0;
	 bool findAPort = false;
	 do{
		 N port = algo::mapElemntKey(hashNodes,brinkNodeHash.at(index+offset));
		 if(validPort(port)){
			 vPort = port;
			 findAPort = true;
			 index++;
			 break;
		 }
		 offset--;
	 }while(index + offset >= indexLowBound);
	 if(findAPort)
		 return vPort;

	 offset = 1;
	 while(index + offset < indexUpperBound){
		 N port = algo::mapElemntKey(hashNodes,brinkNodeHash.at(index+offset));
		 if(validPort(port)){
			 vPort = port;
			 findAPort = true;
			 index++;
			 break;
		 }
		 offset++;
	 }
	 if(!findAPort){ //means after thorough search, there is not enough
		 return NULL;
	 }
	 else{
		 return vPort;
	 }
}

bool addPumpByDna(Dna dna, int pumNum){
	int pumpFound = 0;
	int pumIndexBegin = possibleEdgesSlot.size();
	int pumIndexEnd = possibleEdgesSlot.size()  + brinkNodeHash.size();
	int index = pumIndexBegin;
	while(pumpFound < pumNum){
		 while(dna.chromes.at(index) != 1){
			 index++;
			 if(index == pumIndexEnd){
				 cout<<"this is an invalid dna for adding pump"<<endl;
				 return false;
			 }
		 }
		 N port = findAPossilbePort(0,brinkNodeHash.size(),index-pumIndexBegin);
		 if(port == NULL){
			 cout<<"this is an invalid dna for adding pump"<<endl;
			 return false;
		 }
		 else{
			 algo::distincAddVec(pumps,port);
			 pumpFound++;
			 index++;
		 }
	}
	drawPath(edges,"pumps",pumps);
	return true;
}



bool addWasteByDna(Dna dna, int wasteNum){
	int wasteFound = 0;
	int wasteIndexBegin = possibleEdgesSlot.size() + brinkNodeHash.size();
	int wasteIndexEnd = possibleEdgesSlot.size() + brinkNodeHash.size()* 2;
	int index = wasteIndexBegin;
	while(wasteFound < wasteNum){
		 while(dna.chromes.at(index) != 1){
			 index++;
			 if(index == wasteIndexEnd){
				 cout<<"this is an invalid dna for adding waste"<<endl;
				 return false;
			 }
		 }
		 N port = findAPossilbePort(0,brinkNodeHash.size(),index-wasteIndexBegin);
		 if(port == NULL){
			 cout<<"this is an invalid dna for adding waste"<<endl;
			 return false;
		 }
		 else{
			 algo::distincAddVec(wastes,port);
			 wasteFound++;
			 index++;
		 }
	}
	return true;
}

};




#endif

