#ifndef RANDOMSEQ_H
#define RANDOMSEQ_H

#include "../header/device.h"
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;

using namespace std;

class RandomSeq{

	const int childSize = 1;
	const int parentSize = 1;
	const int maxDuration = 30;
	const int maxDevSize = 1;
    int opCount = 0;
    int devCount = 0;

private:
	vector<Op_ptr> priorityList;
	vector<Dev_ptr> availableDevices;
public:
	vector<Op_ptr> ops;
	vector<int> opsLayer;
	vector<int> opsIdInThisLayer;
	vector<Dev_ptr> devices;



private:

	void addOneOp();


	Op_ptr genRandomOp();
	Dev_ptr genRandomDev();
	Dev_ptr genDev(operationType type);



public:
	void genSeqByLayer(const vector<int>& opNumEachLayer);
	void drawOps();
	void genDevs(int num);


};







#endif
