#ifndef LISTALGORITHM_H
#define LISTALGORITHM_H

#include "../header/device.h"
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



private:
	void setPriorityList();
	void addToAvailableDevice(Device& d);
	void removeFromAvaailableDevice(Device& d);
	void ilpConstraint();
	void ilpObj();
	void writeToFile();




public:
    void readFromXml(const char* xmlFilename);
    void readFromSolver(map<string,int> const & input);

    void listAlgorithm();
    void genILP();



};







#endif
