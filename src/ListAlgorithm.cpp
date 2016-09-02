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
#include "../header/writeILP.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <cstring>


#define TRANSTIME 10
#define M 10000
using namespace std;
typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;

#ifndef SSTRING
#define SSTRING
string s(int i){
	stringstream ss;
	ss<<i;
	return ss.str();
}
string s(const char* s){
	stringstream ss;
	ss<<s;
	return ss.str();
}
string s(string s){
	stringstream ss;
	ss<<s;
	return ss.str();
}
#endif
void ListAlgorithm::readFromSolver(map<string,int> const & input){


	for(Op_ptr op:ops){
		string opName = op->name;
		string opStart = opName + s("Start");
		string opFinish = opName + s("Finish");
		op->startTime = input.at(opStart);
		op->endTime = input.at(opFinish);
		for(Dev_ptr dev:devices){
			string opBindDev = op->name + s("Bind") + dev->name;
			int bind = input.at(opBindDev);
			if(bind == 0){
				op->bindDevice = dev;
				break;
			}
		}
	}





}

void ListAlgorithm::ilpConstraint(){
	//create var
	for(Op_ptr op:ops){
		string opName = op->name;
		string opStart = opName + s("Start");
		string opFinish = opName + s("Finish");
		varName.push_back(opStart);varType.push_back("0");
		varName.push_back(opFinish);varType.push_back("0");
		//if op bind to dev
		for(Dev_ptr dev:devices){
			string devName = dev->name;
			string opBindDev = opName + s("Bind") + devName;
			varName.push_back(opBindDev);varType.push_back("1");

		}

	}
	//ops finsh -begin >= duration
	//ops after his parent
	for(Op_ptr op:ops){
		string opStart = op->name + s("Start");
		string opFinish = op->name + s("Finish");

		ILP.push_back(opFinish + s(" - ") + opStart + s(" >= ") +s(op->duration));
	}



	//ops after his parent
	for(Op_ptr op:ops){
		string opStart = op->name + s("Start");
		string opFinish = op->name + s("Finish");

		for(Op_ptr parent:op->parents){
			string parentStart = parent->name +s("Start");
			string parentFinish = parent->name + s("Finish");
			ILP.push_back(opStart + s(" - ") + parentFinish + s(" >= ") + s(TRANSTIME));
		}
	}

	//dev op type match
	for(Op_ptr op:ops){
		string bindTo1Dev = "";
		int devCount = 0;
		for(Dev_ptr dev:devices){
			string opBindDev = op->name + s("Bind") + dev->name;
			bindTo1Dev += s(" + ") + opBindDev;
			devCount ++;

			if(op->type != dev->type){
				ILP.push_back(opBindDev + s(" = 1"));
			}
		}

		ILP.push_back(bindTo1Dev + s(" = ") + s(devCount-1));

	}

	//when 2 ops bind to 1 dev, they must seprate

	for(Dev_ptr dev:devices){
		string devName = dev->name;
		for(int i = 0; i < ops.size();i++){
			Op_ptr op0 = ops.at(i);

			string op0Start = op0->name + s("Start");
			string op0Finish = op0->name + s("Finish");
			for(int j = 0; j < i; j++){

				Op_ptr op1 = ops.at(j);



				if(op0->type != op1->type){
					continue;
				}

				string op1Start = op1->name + s("Start");
				string op1Finish = op1->name + s("Finish");

				string op0BeforeOp1 = op0->name +s("Before") + op1->name;
				string op1BeforeOp0 = op1->name + s("Before") + op0->name;
				varName.push_back(op0BeforeOp1); varType.push_back("1");
				varName.push_back(op1BeforeOp0); varType.push_back("1");
				string op0BindDev = op0->name + s("Bind") + devName;
				string op1BindDev = op1->name + s("Bind") + devName;

				//if op0bind == 0 and op1bind == 0 then op1before = 0 or op1befor 0

				//if op0before = 0 then op1start - op1finish >= trans
				ILP.push_back(op1Start + s(" - ") + op0Finish + s(" + ") +s(M) + s(" ") + op0BeforeOp1 + s(" >= ") + s(TRANSTIME));


				//if op1before = 0 then op0start - op10Finish >= trans
				ILP.push_back(op0Start + s(" - ") + op1Finish + s(" + ") + s(M) + s(" ") + op1BeforeOp0 + s(" >= ") + s(TRANSTIME)) ;

				// op0Bind = 1 or op1Bind = 1 or op0b = 0 or op1b = 0
				//(1-op0) + (1-op1) + op0b + op1b <=3; -op0 - op1 + op0b + op1b <= 1
				ILP.push_back(s(" - ") + op0BindDev + s(" - ") + op1BindDev + s(" + ") + op0BeforeOp1 + s(" + ") + op1BeforeOp0+ s(" <= 1"));

			}
		}
	}

}

void ListAlgorithm::ilpObj(){
	string obj = "";
	string maxTime = "maxTime";
	for(Op_ptr op:ops){
		string opFinish = op->name + s("Finish");
		ILP.push_back(maxTime + s(" - ")  + opFinish + s(" >= 0"));
	}
	//obj += s(M) + s(" ") + maxTime;

	for(Op_ptr op:ops){
		string opStart = op->name + s("Start");
		for(Op_ptr parent:op->parents){
			string parentFinish = parent->name + s("Finish");
			string channel = s("c") + s(parent->name) +s(op->name);
			string channelIsStore  = channel + s("IsStore");
			varName.push_back(channelIsStore); varType.push_back("1");
			//if  channelisStore = 1 then opStart > parentFinish + trans
			//opStart - parentFinish +(1-b)*M >= trans + 1
			//if channelIsStore = 0 then opStart <= parentFinish + trans;
			// opStart-parentFinsh - M*b <= trans;

			ILP.push_back(opStart + s(" - ") + parentFinish +s(" - ") + s(M) + s(" ") + channelIsStore + s(" >= " ) + s(TRANSTIME+1-M));
			ILP.push_back(opStart + s(" - ") + parentFinish +s(" - ")+ s(M) + s(" ") + channelIsStore + s(" <= ")  + s(TRANSTIME));
			obj+= s(" + ") + channelIsStore;
		}
	}
	OBJ.push_back("Minimize");
	OBJ.push_back(obj);

}

void ListAlgorithm::writeToFile(){
	writeILP write;
	write.writeOBJ(OBJ,"seq.lp");
	write.writeConstraint(ILP,"seq.lp");


	write.writeVarNames(varName,varType,"seq.lp");




}

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

void ListAlgorithm::genILP(){
	ilpConstraint();
	ilpObj();
	writeToFile();

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
		else if(type == "filter"){
			operation->type = operationType::filter;
		}
		else if(type == "source"){
			operation->type = operationType::source;
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
		else if(type == "filter"){
			device->type = operationType::filter;
				}
		else if(type == "source"){
			device->type = operationType::source;
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








