#ifndef RANDOMSEQ_H
#define RANDOMSEQ_H

#include "../header/device.h"
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>


using namespace std;

class RandomSeq{

	const int childSize = 1;
	const int parentSize = 1;
	const int maxDuration = 30;
	const int maxDevSize = 1;
    int opCount = 0;
    int devCount = 0;

private:
	vector<Op*> priorityList;
	vector<Device*> availableDevices;
public:
	vector<Op*> ops;
	vector<int> opsLayer;
	vector<int> opsIdInThisLayer;
	vector<Device*> devices;



private:

	void addOneOp();


	Op* genRandomOp();
	Device* genRandomDev();
	Device* genDev(operationType type);



public:
	void genSeqByLayer(const vector<int>& opNumEachLayer);
	void drawOps();
	void genDevs(int num);


};







#endif
