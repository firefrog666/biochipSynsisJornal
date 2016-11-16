#ifndef LISTALGORITHM_H
#define LISTALGORITHM_H

#include "../header/device.h"
#include "../header/channel.h"
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


typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;
typedef boost::shared_ptr<Channel> Ch_ptr;
using namespace std;

class ListAlgorithm{



private:
	vector<Op_ptr> priorityList;
	vector<Dev_ptr> availableDevices;
	vector<string> ILP;
	vector<string> OBJ;
	vector<string> varName;
	vector<string> varType;

	int opCount = 0;
public:
	vector<Op_ptr> ops;
	vector<Dev_ptr> devices;
	vector<Ch_ptr> channels;

	vector<Op_ptr> concise_ops;
	vector<Dev_ptr> concise_devs;
	vector<Ch_ptr> concise_channels;
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

	void getConciseSeq();
    void listAlgorithm();
    void genILP();



};







#endif
