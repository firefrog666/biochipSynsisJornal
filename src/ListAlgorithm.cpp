/*
 * ListAlgorithm.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: ga63quk
 */


#include "../header/ListAlgorithm.h"
#include<vector>
#include <sstream>
#include "../header/device.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <cstring>

#define TRANSTIME 10
using namespace std;
typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;

void ListAlgorithm::listAlgorithm(){

	for(Op_ptr op:ops){
		op->running = false;
		op->done = false;
	}

	for(Dev_ptr dev:devices){
		dev->availeble = true;
	}



	availableDevices = devices;
	int finishedTask = 0;

	for(int t = 0; ; t++){

		//if one task is done, free its device and make his descendant operation available
		for(Op_ptr task : ops){

			if(task->done == true)
  				continue;
			if(task->running == false)
				continue;

			if(t - task->startTime == task->duration + TRANSTIME){

				//availableDevices.push_back(task->bindDevice);
				task->endTime = task->startTime + task->duration;
				task->done = true;
				task->running = false;
				task->bindDevice->availeble = true;
				finishedTask++;

			}
		}

		if(finishedTask == ops.size())
			break;

		for(int i = 0; i <= ops.size()-1;i++){
			Op_ptr task = ops.at(i);
			if(task->running == true)
				continue;
			if(task->done == true)
				continue;
			bool allParentsDone = true;
			for(Op_ptr parent: task->parents){
				if(parent->done == false)
 					allParentsDone = false;
			}

			if(allParentsDone == false)
				continue;

			for(int j = 0; j <= devices.size()-1; j++){
				Dev_ptr d = devices.at(j);

				if(d->availeble == false)
					continue;

				if(task->type == d->type){
					task->bindDevice = d;
					task->startTime = t;
					task->running = true;
					d->availeble = false;
					break;
				}
			}
		}
	}


}

void ListAlgorithm::readFromXml(const char* xmlFilename){
	rapidxml::xml_document<> doc;    // character type defaults to char
	rapidxml::xml_node<> * root_node;
	ifstream theFile (xmlFilename);
	vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
	buffer.push_back('\0');
	// Parse the buffer using the xml file parsing library into doc
	doc.parse<0>(&buffer[0]);
	root_node = doc.first_node("sequenceGraph");




	//initialize all operations
	for (rapidxml::xml_node<> * operation_node = root_node->first_node("operation"); operation_node; operation_node = operation_node->next_sibling())
	{
		if( strcmp(operation_node->name(), "operation") != 0)
			continue;
		Op_ptr operation(new Op);
		operation->name = operation_node->first_attribute("name")->value();
		string sduration = operation_node->first_attribute("duration")->value();

		istringstream abuffer(sduration);
		abuffer>>operation->duration;

		string type = operation_node->first_attribute("type")->value();
		if(type == "mix"){
			operation->type = operationType::mix;
		}
		else if(type == "heat"){
			operation->type = operationType::heat;
		}
		else if(type == "detect"){
			operation->type = operationType::detect;
		}


		ops.push_back(operation);



	}

	//initialize all devs
	for (rapidxml::xml_node<> * device_node = root_node->first_node("device"); device_node; device_node = device_node->next_sibling())
	{

		if( strcmp(device_node->name(), "device") != 0)
					continue;
		Dev_ptr device(new Device);
		device->name = device_node->first_attribute("name")->value();
		string sx = device_node->first_attribute("x")->value();
		string sy = device_node->first_attribute("y")->value();
		string type = device_node->first_attribute("type")->value();
		istringstream abuffer(sx);
		istringstream bbuffer(sy);

		if(type == "mix"){
			device->type = operationType::mix;
		}
		else if(type == "heat"){
			device->type = operationType::heat;
		}
		else if(type == "detect"){
			device->type = operationType::detect;
		}

		abuffer>>device->sizeX;
		bbuffer>>device->sizeY;
		devices.push_back(device);



	}


	//assign attribute to each operation

	for (rapidxml::xml_node<> * operation_node = root_node->first_node("operation"); operation_node; operation_node = operation_node->next_sibling())
	{
		if( strcmp(operation_node->name(), "operation") != 0)
					continue;
		vector<Op_ptr>::iterator it;
		string name = operation_node->first_attribute("name")->value();
		it = find_if(ops.begin(),ops.end(), [&name](const Op_ptr obj) {return obj->name == name;});

		Op_ptr operation = *it;


		for(rapidxml::xml_node<>* childNode = operation_node->first_node();childNode;childNode = childNode->next_sibling()){
			string childNodeName = childNode->name();
			if(childNodeName == "child"){
				name = childNode->first_attribute("name")->value();
				it = find_if(ops.begin(),ops.end(), [&name](const Op_ptr& obj) {return obj->name == name;});
				Op_ptr childOperation = *it;
				operation->children.push_back(childOperation);
			}
			if(childNodeName == "parent"){
				name = childNode->first_attribute("name")->value();
				it = find_if(ops.begin(),ops.end(), [&name](const Op_ptr& obj) {return obj->name == name;});
				Op_ptr parentOperation = *it;
				operation->parents.push_back(parentOperation);
			}

		}
	}
}








