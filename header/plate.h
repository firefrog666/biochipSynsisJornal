#ifndef PLATE_H
#define PLATE_H
#include <vector>
#include <string>
#include <map>
#include "../header/device.h"
#include "../header/channel.h"
#include "../header/sequenceGraph.h"
#include "../header/Algorithm.h"
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
	}


private:
	int x,y,s,t;

	vector<Device> devices;
	vector<Op> operations;
	vector<Channel> channels;

	SequenceGraph seq;
	vector<string> OBJ;
	vector<string> ILP;
	vector<string> bounds;
	vector<string> varName;
	vector<string> varType;
	map<string,int> ILPResults;

public:
	void devicePlacementConstraint();
	void channelPlaceConstraint();
	void channeTimeConstraint();
	void ValveObject();
	void setSequenceGraph(const SequenceGraph& thatSeq);

	void writeToFile();
	void readFromSolver( map<string,int> const  & results);
	void writeGraphFile(int pathNumber);
	vector<string> getILP();
	vector<string> getVarName();
	vector<string> getVarType();

private:
	void assignChannels(); // assign channels to each operation, and assign operations to channels
	void setChannelsTime(); //according to sequenceGraph, set channel time
	map<string,vector<Op>> devicesOperations(); // decide all operations on one device.  sort them by time
	Device getDeviceFromOp(const Op& op);

};


#endif
