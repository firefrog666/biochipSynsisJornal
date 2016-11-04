#ifndef CHANNEL_H
#define CHANNEL_H

using namespace std;
#include "../header/Node.h"
#include "../header/device.h"
#include <boost/shared_ptr.hpp>


typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;




class Channel {

public:



public:
	int const static vertexNum = 4;
	int startTime;
	int endTime;
	int injectTime;
	int ejectTime;
	int  storageStart = 1;
	int  storageEnd = 2;
	bool isStore = false;
	bool isFirst = false;
	bool isLast = false;
	bool isNormal = false;

	string name;
	Dev_ptr ends[2];
	Dev_ptr first;
	Dev_ptr second;
	Dev_ptr storage;
	string belongTo = "myself";
	Op_ptr fatherOp;
	Op_ptr childOp;


public:

};


/*class storage : public Channel{

};

class tmpChannel : public Channel{

};*/
#endif
