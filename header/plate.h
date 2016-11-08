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
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;
typedef boost::shared_ptr<Channel> Channel_ptr;

using namespace std;


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
		Op_ptr op1(new Op());
		Op_ptr op2(new Op());

	}


private:
	int x,y,s,t;
	int CHIPSIZE  = 5;
	const double valveLenth = 0.5;
	const double valveWidth = 0.2;
	vector<Dev_ptr> devices;
	vector<Op_ptr> operations;
	vector<Channel_ptr> channels;
	vector<Channel_ptr> Lchannels;

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
	map<Dev_ptr,Node_ptr> devBindNode;

	Grid g;
	vector<string> resultsFromLastItr; //results from last time

	//for concise seq;
	vector<Op_ptr> concise_ops;
	vector<Dev_ptr> concise_devs;
	vector<Ch_ptr> concise_channels;
	vector<int> channels_count;

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


	void textReplaceILP();

	string textReplacement(const string& target, const string& source,const  string& replace);
	vector<string> textReplacement(const vector<string>& target, const vector<string>& source, const vector<string>& replace);


	void setSequenceGraph(const SequenceGraph& thatSeq);
	void getBindingFromList(const ListAlgorithm& L);
	void getPartInfoFromList(const ListAlgorithm& L, int numberOfOps);
	void getPartInfoFromListByTime(const ListAlgorithm& L, int numberOfOps);


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

	void writeDeviceLoc(map<string,int> const & input);
	void readDeviceLoc();
	void switchDeviceLoc();
	void moveDeviceLoc();
	void writeDevLocToILP();
	void genRandomDevLoc();
	//void writeDeviceLoc();
	int calEdgeUseNum();

	vector<string> getILP();
	vector<string> getVarName();
	vector<string> getVarType();
	void setChipSize(int size){CHIPSIZE = size;}
	void setChannelsTime(); //according to sequenceGraph, set channel time
	void setConciseChannelTime();

private:
	void assignChannels(); // assign channels to each operation, and assign operations to channels

	map<string,vector<Op>> devicesOperations(); // decide all operations on one device.  sort them by time
	Dev_ptr getDeviceFromOp(const Op_ptr& op);

};


#endif
