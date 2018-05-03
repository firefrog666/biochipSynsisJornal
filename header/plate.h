#ifndef PLATE_H
#define PLATE_H
#include <vector>
#include <string>
#include <map>
#include "../header/device.h"
#include "../header/channel.h"
#include "../header/FlowPath.h"
#include "../header/sequenceGraph.h"
#include "../header/Algorithm.h"
#include "../header/ListAlgorithm.h"
#include "../header/grid.h"
#include "../header/Dna.h"
#include <boost/shared_ptr.hpp>



using namespace std;


class FlowChannel{
public:
	FlowChannel(){
		startTime = 0;
		endTime = 0;
	}

	void printSelf(){
		cout<<"flow start at "<<startTime<<" end at "<<endTime<<endl;
		for(N n:nodesToCover){
			cout<<n->name<<" ";
		}
		cout<<" to cover "<<endl;
	}



	bool isStore = false;
	V<N> nodesToCover;
	int startTime;
	int endTime;
};

class Plate{
public:
	Plate(SequenceGraph &s){
		seq = s;
	}

	Plate(){
		x = 0;
		y = 0;
		s = 0;
		t = 0;
		Op* op1 = new Op();
		Op* op2 = new Op();

	}


private:
	int x,y,s,t;
	int CHIPSIZE  = 5;
	const double valveLenth = 0.5;
	const double valveWidth = 0.2;
	Edge* emptE = new Edge(-1);
	vector<Device*> devices;
	vector<Op*> operations;
	vector<Channel*> channels;
	vector<Channel*> Lchannels;
	SequenceGraph seq;
	vector<string> OBJ;
	vector<string> ILP;
	vector<string> bounds;
	vector<string> varName;
	vector<string> varType;
	vector<string> varNameObj;
	vector<string> shortILP;
	vector<string> shortOBJ;
	vector<string> shortVarNames;

	vector<int> conflictMoment;


	int itrTimes = 0;
	map<string,int> ILPResults;
	map<Device*,Node*> devBindNode;

	vector<string> resultsFromLastItr; //results from last time

	//for concise seq;
	vector<Op*> concise_ops;
	vector<Device*> concise_devs;
	vector<Channel*> concise_channels;
	vector<int> channels_count;

	//for building flow channels.
	V<FlowChannel*> flowChannels;
	vector<Node*> pumps;
	vector<Node*> wastes;
	map<Channel*,Channel*> firstLastChannelPair;
public:
	Grid g;
	Grid phyGrid;

public:
	void clearLastResult(){resultsFromLastItr.clear();}
	void setGrid(Grid& grid){g = grid;}


	void devicePlacement();
	void channelStartEnd();
	void channelSimplePath();
	void channelFirstStoreLast();
	void channelTimeConfict();
	void objective();


	void channelStartEndFloorPlan();
	void channelSimplePathFloorPlan();
	void channelFirstStoreLastFloorPlan();
	void channelTimeConfictFloorPlan();


	void momentUsedEdge(int moment);


	void textReplaceILP();

	string textReplacement(const string& target, const string& source,const  string& replace);
	vector<string> textReplacement(const vector<string>& target, const vector<string>& source, const vector<string>& replace);


	void setSequenceGraph(const SequenceGraph& thatSeq);
	void getBindingFromList(const ListAlgorithm& L);
	void getPartInfoFromList(const ListAlgorithm& L, int numberOfOps);
	void getPartInfoFromListByTime(const ListAlgorithm& L, int numberOfOps);
	void clearInforFromL();
	void genPhyGrid();
	bool ifEdgeUsed(Edge* e);
	bool ifEdgeUseAsStore(Edge* e);
	bool ifNodeDev(Node* n);

	void writeToFile(string fileName);
	void writeToFileShort(string fileName);
	void writeRealGraphFile(int time);

	void writeValves();
	void writeValve(ofstream& file, int x, int y, int type);
	void writeTimeLine();

	void readFromSolver( map<string,int> const  & results);
	void readFromSolverDevice( map<string,int> const  & results);

	void writeGraphFile(int moment);
	void writeGraphFileByMoments();
	void writeGraphFileByChannels();
	void writeGraphFile();
	void writeDeviceCoord(string fileName);
	void constraintClear();

	void writeDeviceLoc();

	int countValves();
	void readILPResultsFromFile();
	void setILPResults(map<string,int> const  & results){ILPResults = results;};
	void readDeviceLoc();
	void switchDeviceLoc();
	void moveDeviceLoc();
	void writeDevLocToILP();
	void genRandomDevLoc();
	V<N> busyDevices(int start, int end);
	V<Edge*> busyEdges(int start, int end);


	//void writeDeviceLoc();

	int calEdgeUseNum();

	vector<string> getILP();
	vector<string> getVarName();
	vector<string> getVarType();
	void setChipSize(int size){CHIPSIZE = size;}
	void setChannelsTime(); //according to sequenceGraph, set channel time
	void setConciseChannelTime();

	void assignChannels(); // assign channels to each operation, and assign operations to channels

	map<string,vector<Op>> devicesOperations(); // decide all operations on one device.  sort them by time
	Device* getDeviceFromOp(const Op& op);


	//to get flow channel for every move
	void setPumps();
	void setWastes();
	void getSynthesiResultGraph();
	//void creatFlowChannelsSetUp();
	void createFlowChannels();
	//bool findPath(const FlowChannel* f, V<E>& path, const V<N>& forbidNodes,const V<E>& forbidEdges,const V<V<E>>& existingPath);
	bool findPath(const Channel* c, V<E>& path, const V<N>& forbidNodes,const V<E>& forbidEdges,const V<V<E>>& existingPath);
	void drawPlate(const char* fileName);
	V<V<FlowChannel*>> findConcurrentPaths();
	void elimateCrtChannelSet(V<V<Channel*>>& crtChannelSet);
	void channelsToFlowChannels();
	//bool creatConcurrentPaths(const V<FlowChannel*>& conCurrentFlowChannel);
	bool creatConcurrentPaths(const V<Channel*>& conCurrentChannel);
	V<E> updateForbidEdges(const V<E>& forbidEdges, const V<V<E>>& existingPaths);
	V<N> updateForbidNodes(const V<N>& forbidNodes, const V<V<E>>& existingPaths);
	void drawPath(const V<E>& path, const char* pathName);


	//postpone channels in order to eliminate conflicts

    V<Channel*> channelsOutOp(Op* o);
    V<Channel*> channelsInToOp(Op* o);

    void postponeChannel(Channel* c,V<Channel*> concurruntChannels,int time);
    void changeOpTime(Op* o);
    void elimateConcrtChannels(V<Channel*>& channels);

    void splitChannels();
    V<V<Channel*>> findConcrtChannels();
    Channel* creatFoSChannel(int start,int end, Op* fOp, Edge* store);
    Channel* creatFfromSChannel(int start,int end, Op* sonOp, Edge* store);
    void setGridDeviceNode();
    Dna* createPlateDna();
    void analysisDna(const Dna& d);
    bool setChannelStoreByDna(const Dna& d);


};


#endif
