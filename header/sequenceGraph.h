#ifndef SEQUENCEGRAPH_H
#define SEQUENCEGRAPH_H
#include "../header/Node.h"
#include <sstream>
#include "../header/device.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;


class SequenceGraph{
public:

	SequenceGraph(){

	}
	//read from xml file
	SequenceGraph(const char* xmlFilename){
		rapidxml::xml_document<> doc;    // character type defaults to char
		rapidxml::xml_node<> * root_node;
		ifstream theFile (xmlFilename);
		vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		buffer.push_back('\0');
		// Parse the buffer using the xml file parsing library into doc
		doc.parse<0>(&buffer[0]);
		root_node = doc.first_node("sequenceGraph");


		vector<Op>::iterator it;
		vector<Device>::iterator devIt;
		//initialize all operations
		for (rapidxml::xml_node<> * operation_node = root_node->first_node("operation"); operation_node; operation_node = operation_node->next_sibling())
		{
			Op operation = Op();
			operation.name = operation_node->first_attribute("name")->value();
			string sstartTime = operation_node->first_attribute("start")->value();
			string sendTime =operation_node->first_attribute("end")->value();
			istringstream abuffer(sstartTime);
			istringstream bbuffer(sendTime);
			abuffer>>operation.startTime;
			bbuffer>>operation.endTime;
			ops.push_back(operation);

			//record all devices in each operation
			rapidxml::xml_node<>* childNode = operation_node->first_node("device");

			string deviceName = childNode->first_attribute("name")->value();
			devIt = find_if(devs.begin(),devs.end(), [&deviceName](const Device& obj) {return obj.name == deviceName;});
			if(devIt == devs.end()){
				Device d = Device();
				d.name = deviceName;
				string ssizeX = childNode->first_attribute("x")->value();
				string ssizeY =childNode->first_attribute("y")->value();
				istringstream abuffer(ssizeX);
				istringstream bbuffer(ssizeY);
				abuffer>>d.sizeX;
				bbuffer>>d.sizeY;
				devs.push_back(d);
			}
		}


		//assign attribute to each operation

		for (rapidxml::xml_node<> * operation_node = root_node->first_node("operation"); operation_node; operation_node = operation_node->next_sibling())
		{
			string name = operation_node->first_attribute("name")->value();
			it = find_if(ops.begin(),ops.end(), [&name](const Op& obj) {return obj.name == name;});
			cout << "hello world" <<endl;


			cout << "+ops"<<endl;
			string t = it->name;
			cout << t<<endl;
			Op& operation = *it;


			for(rapidxml::xml_node<>* childNode = operation_node->first_node();childNode;childNode = childNode->next_sibling()){
				string childNodeName = childNode->name();
				if(childNodeName == "child"){
					name = childNode->first_attribute("name")->value();
					it = find_if(ops.begin(),ops.end(), [&name](const Op& obj) {return obj.name == name;});
					cout << it->name<<endl;
					Op childOperation = *it;
					//operation.children.push_back(childOperation);
				}
				if(childNodeName == "parent"){
					name = childNode->first_attribute("name")->value();
					it = find_if(ops.begin(),ops.end(), [&name](const Op& obj) {return obj.name == name;});
					cout << it->name<<endl;
					Op parentOperation = *it;
					//operation.parents.push_back(parentOperation);
				}

				if(childNodeName == "device"){
					name = childNode->first_attribute("name")->value();
					devIt = find_if(devs.begin(),devs.end(), [&name](const Device& obj) {return obj.name == name;});
					cout << it->name<<endl;
					Device bindDevice= *devIt;

					//operation.bindDevice = bindDevice;
				}





			}



		}

		/*for(int i = 0; i <= devs.size()-1; i++){
			cout<<"dev "<<i <<" name is "<<devs.at(i).name <<endl;
			cout<<"dev "<<i <<" sizeX is "<<devs.at(i).sizeX<<endl;
			cout<<"dev "<<i <<" sizeY is "<<devs.at(i).sizeY<<endl;
		}
		for(int i = 0; i <= ops.size()-1; i++){
			cout<<"ops "<<i <<" name is "<<ops.at(i).name <<endl;
			cout<<"ops "<<i <<" start is "<<ops.at(i).startTime<<endl;
			cout<<"ops "<<i <<" end is "<<ops.at(i).endTime <<endl;
		}*/

	}


private:
public:
	vector<Op> ops;
	vector<Device> devs;
	vector<Op> getOps(){ return ops; }

};
#endif
