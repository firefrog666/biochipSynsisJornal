#ifndef LISTALGORITHM_H
#define LISTALGORITHM_H

#include "../header/device.h"
#include "../header/channel.h"
#include "../header/Algorithm.h"
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <string>

#include <string>
#include <sstream>
#include <functional>
#include <fstream>
#include <algorithm>
#include <map>





using namespace std;


class ListAlgorithm{



private:
	vector<Op*> priorityList;
	vector<Device*> availableDevices;
	vector<string> constraints;
	vector<string> OBJ;
	vector<string> varName;
	vector<string> varType;

	int opCount = 0;
public:
	vector<Op*> ops;
	vector<Device*> devices;
	vector<Channel*> channels;

	vector<Op*> concise_ops;
	vector<Device*> concise_devs;
	vector<Channel*> concise_channels;
	vector<int> channels_count;


private:
	void setPriorityList();
	void addToAvailableDevice(Device& d);
	void removeFromAvaailableDevice(Device& d);
	void outerMemilpConstraint();
	void ilpConstraint();
	void ilpObj();
	void writeToFile();




public:
	void readResultFromFile();
	void writeResultToFile(map<string,int>results);
    void readFromXml(const char* xmlFilename);
    void readFromSolver(map<string,int> const & input);
    void writeTimeline();
    void howManyStore();

	void getConciseSeq();
    void listAlgorithm();
    void genILP();

    void oldVersion();





};







#endif
