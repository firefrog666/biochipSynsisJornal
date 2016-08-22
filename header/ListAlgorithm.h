#ifndef LISTALGORITHM_H
#define LISTALGORITHM_H

#include "../header/device.h"
#include <vector>
#include <algorithm>
#include <boost/shared_ptr.hpp>

typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;

using namespace std;

class ListAlgorithm{



private:
	vector<Op_ptr> priorityList;
	vector<Dev_ptr> availableDevices;
public:
	vector<Op_ptr> ops;
	vector<Dev_ptr> devices;


private:
	void setPriorityList();
	void addToAvailableDevice(Device& d);
	void removeFromAvaailableDevice(Device& d);





public:
    void readFromXml(const char* xmlFilename);
    void listAlgorithm();



};







#endif
