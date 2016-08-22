#ifndef CHANNEL_H
#define CHANNEL_H

using namespace std;
#include "../header/Node.h"
#include "../header/device.h"
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;

class Channel : public Device{

public:



public:
	int const static vertexNum = 2;
	vector<Vertex> vertexs;
	Dev_ptr ends[2];
	Dev_ptr first;
	Dev_ptr second;
	Dev_ptr storage;

	Op_ptr fatherOp;
	Op_ptr childOp;


public:

};

/*class storage : public Channel{

};

class tmpChannel : public Channel{

};*/
#endif
