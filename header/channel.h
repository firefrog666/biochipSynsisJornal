#ifndef CHANNEL_H
#define CHANNEL_H

using namespace std;
#include "../header/Node.h"
#include "../header/device.h"

class Channel : public Device{

public:



public:
	int const static vertexNum = 3;
	vector<Vertex> vertexs;
	Device ends[2];
	Device first;
	Device second;
	Device storage;

	Op fatherOp;
	Op childOp;


public:

};

/*class storage : public Channel{

};

class tmpChannel : public Channel{

};*/
#endif
