#ifndef PLATE_CPP
#define PLATE_CPP
#include <iostream>
#include "../header/plate.h"
#include "../header/device.h"
#include "../header/FlowPath.h"
#include "../header/writeILP.h"
#include "../header/Node.h"
#include "../header/edge.h"

#include <stdlib.h>
#include <time.h>
#include <boost/shared_ptr.hpp>
#include <math.h>       /* sin */

#define PI 3.14159265


#include <string>
#include <sstream>
#include <functional>
#include <fstream>
#include <algorithm>

using namespace std;

#define jointStr(s1...)
#define M 10000
#define TRANSTIME 10

#define LIQUIDESIZE 1
#define DEVICESTEP 3
#define SOURCEX 0
#define SOURCEY 0

#define FLOWSOURCEX 5
#define FLOWSOURCEY 10
#define FLOWWASTEX  5
#define FLOWWASTEY  0


typedef boost::shared_ptr<Op> Op*;
typedef boost::shared_ptr<Device> Device*;
typedef boost::shared_ptr<Channel> Channel*;
typedef boost::shared_ptr<FlowPath> FlowPath_ptr;
typedef boost::shared_ptr<Node> Node*;
typedef boost::shared_ptr<Edge> Edeg_ptr;

#ifndef SSTRING
#define SSTRING




#endif


string S(int i){
	stringstream ss;
	ss<<i;
	return ss.str();
}
string S(const char* s){
	stringstream ss;
	ss<<s;
	return ss.str();
}
string S(string s){
	stringstream ss;
	ss<<s;
	return ss.str();
}

__inline__ string getNodeName(Node* n){
	return S("n") + S("x") +S(n->x)+ S("y") + S(n->y);
}
__inline__ string getEdgeName(Edge* e){
	return S("e") + S("x") +S(e->x)+ S("y") + S(e->y)+ S("s") +S(e->s)+ S("t") + S(e->t);
}

// one step
bool replace(std::string& str, const std::string& from, const std::string& to) {
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

string Plate::textReplacement(const string& str,const  string& from,const string& to){
	string result = str;
	bool textExist = replace(result,from,to);
	while(textExist){
		textExist = replace(result,from,to);
	}
	return result;

}


vector<string> Plate::textReplacement(const vector<string>& target,const vector<string>& source, const vector<string>& replacetext){
	vector<string> result;
	for(int i =0; i < target.size();i++){
		string str = target.at(i);

		for(int j =0 ; j < source.size();j++){
			string from = source.at(j);
			string to = replacetext.at(j);
			str = textReplacement(str,from,to);
		}
		result.push_back(str);
	}
	return result;
}

void Plate::textReplaceILP(){
	for(int i = 0; i < varName.size();i++){
		string shortVarName = S("x") + S(i);
		shortVarNames.push_back(shortVarName);
	}

	shortILP = textReplacement(ILP,varName,shortVarNames);
	shortOBJ = textReplacement(OBJ,varName,shortVarNames);

}


void Plate::setSequenceGraph(const SequenceGraph& thatSeq)
{
	/*seq = thatSeq;
	devices = seq.devs;
	operations = seq.ops;*/

}

void Plate::getBindingFromList(const ListAlgorithm& L){
	operations = L.ops;
	devices = L.devices;
	Lchannels = L.channels;
}

void Plate::getPartInfoFromListByTime(const ListAlgorithm& L, int numberOfOps){
	string fileNameOps = "newOps" + S(itrTimes) + ".txt";
	ofstream fileOps;
	fileOps.open(fileNameOps.c_str());



	int newOpNumber = 0;
	int channelCount = 0;
	int opCount = 0;
	for(int time = 0; ;time++){
		for(Op* op:L.ops){
			auto it = find(operations.begin(),operations.end(),op);
			//op is already in operations
			if(it != operations.end())
				continue;

			if(op->endTime == time){
				operations.push_back(op);
				fileOps << "new Op " << op->name << "  bind to " << op->bindDevice->name << " type "<<op->type <<endl;
				opCount++;
				for(Op* parent:op->parents){

					fileOps << "parent " << parent->name<< " type "<<parent->type << endl;
					fileOps << "new Channel from " << parent->name <<" to " <<op->name << " from " << parent->bindDevice->name << " " << parent->bindDevice->type
							<< " to " << op->bindDevice->name << " " << op->bindDevice->type << endl;
					channelCount++;
				}
				fileOps << "--------------------" << endl;



				Device* bindDev = op->bindDevice;
				auto bindItr = find(devices.begin(),devices.end(),bindDev);
				if(bindItr == devices.end()){
					devices.push_back(bindDev);
				}

				newOpNumber++;
			}
		}

		if(newOpNumber >= numberOfOps)
			break;

		if(operations.size() >= L.ops.size())
			break;
	}

	fileOps << "channelCount " << channelCount <<endl;
	fileOps << "OpsCount" << opCount <<endl;
	fileOps.close();

	itrTimes++;
}
void Plate::getPartInfoFromList(const ListAlgorithm& L, int numberOfOps){
	int i = 0;


	while(i < numberOfOps){
		if(i >= L.ops.size())
			break;

		for(Op* op:L.ops){

			auto it = find(operations.begin(),operations.end(),op);
			//op is already in operations
			if(it != operations.end())
				continue;

			bool allFatherInOperations = true;
			for(Op* father:op->parents){
				auto fatherIt = find(operations.begin(),operations.end(),father);
				//op father not already in operations
				if(fatherIt == operations.end())
					allFatherInOperations = false;
			}

			if(allFatherInOperations == true){
				operations.push_back(op);
				//also push back the channel
				for(Op* father:op->parents){
					string cName = S("c") + father->name + op->name;
					for(Channel* c:L.channels){
						if(c->name == cName){
							auto cItr = find(Lchannels.begin(),Lchannels.end(),c);
							if(cItr == Lchannels.end()){
								Lchannels.push_back(c);
							}
						}
					}
				}
				// push bind channel
				Device* bindDev = op->bindDevice;
				auto bindItr = find(devices.begin(),devices.end(),bindDev);
				if(bindItr == devices.end()){
					devices.push_back(bindDev);
				}
				break;


			}

		}

		i++;
	}
}





string getVertexNameX(Channel* const &c, int number){

	return c->name + S("x") + S(number);


}

string getVertexNameY(Channel* const & c, int number){
	return c->name + S("y") + S(number);
}
string  getSegName(Channel* const &c, int number){

	return c->name + S("Seg") + S(number - 1);

}


//x y s t ilp name
vector<string> getDeviceCoordName(Device* const & d){
	vector<string> results;
	string x = S(d->name) + S("x");
	string y = S(d->name) + S("y");
	string s = S(d->name) + S("s");
	string t = S(d->name) + S("t");

	results.push_back(x);
	results.push_back(y);
	results.push_back(s);
	results.push_back(t);
	return results;


}

void Plate::writeTimeLine(){

	ofstream file;
	file.open("timeline.txt");
	for(Op* op:operations){
		file << op->name<<" start at" << op->startTime << " end at" << op->endTime << " bind to " << op->bindDevice->name <<endl;
	}

	for(Channel* c:channels){


		file << c->name <<" start at" << c->fatherOp->endTime << " end at" << c->childOp->startTime
				<< "start from  "<< c->fatherOp->bindDevice->name << " to " << c->childOp->bindDevice->name<<endl;
		if(c->childOp->startTime- c->fatherOp->endTime > TRANSTIME )
			file << c->name << " contains a storage" << endl;
	}
	file.close();
}



void Plate::writeGraphFileByMoments(){
	if(ILPResults.size() == 0)
		return;
	for(int moment:conflictMoment){
		writeGraphFile(moment);
	}
}

void Plate::writeGraphFileByChannels(){
	ofstream file;

	int flag = 0;
	int channelcount = 0;
	for(Channel* c:channels){

		string fileName = S("edgesC") + S(channelcount) + S(".txt");
		file.open(fileName.c_str());


		for(Edge* e:g.edges){
			string edgeUsedInC = c->name + S("U") +getEdgeName(e);
			int edgeUsedValue = ILPResults[edgeUsedInC];
			if(edgeUsedValue == 0)
				continue;
			file << e->x << endl;
			file << e->y << endl;
			file << e->s << endl;
			file << e->t << endl;
			if(c->isStore)
				file << 0 << endl;
			else if(c->isFirst)
				file << 1 << endl;
			else if(c->isLast)
				file << 2 << endl;
			else if(c->isNormal)
				file << 3 << endl;
			else
				file << 3 << endl;
		}
		file.close();
		channelcount++;
	}


	string fileName = S("devices") +S(".txt");
	string deviceName = S("deviceName") + S(".txt");
	ofstream deviceNameFile;
	deviceNameFile.open(deviceName.c_str());

	file.open(fileName.c_str());
	double deviceR = 0.2;
		for(Device* d:devices){
			deviceNameFile << d->name << endl;
			for(Node* n:g.nodes){
				string dbindN = d->name + S("Bind") + getNodeName(n);
				int dBindNValue = ILPResults[dbindN];

				if(dBindNValue == 0)
					continue;
				//draw a circle
				int devX = n->x;
				int devY = n->y;

				file << devX<< endl;
				file << devY << endl;
				file << deviceR << endl;
			}

		}

		deviceNameFile.close();
		file.close();
}

void Plate::writeGraphFile(int moment){
	ofstream file;
	string fileName = S("edges") + S(moment) + S(".txt");
	ofstream edgeInfo;
	string edgeInfoName = S("edgesInfo") + S(moment) + S(".txt");
	file.open(fileName.c_str());
	edgeInfo.open(edgeInfoName.c_str());
	int flag = 0;
	int cCount = 0;
	for(Channel* c:channels){

		if(!(c->startTime <= moment && c->endTime >= moment))
			continue;

		int color = cCount%4;
		cCount++;
		//cout << " at moment " << moment << " "<< c->name << " used " << "start from " << c->startTime << " to " << c->endTime << endl;
		for(Edge* e:g.edges){
			string edgeUsedInC = c->name + S("U") +getEdgeName(e);
			int edgeUsedValue = ILPResults[edgeUsedInC];
			if(edgeUsedValue == 0)
				continue;
			//cout << edgeUsedInC << " is 1" << endl;
			edgeInfo << c->name + S("U") + getEdgeName(e) << "S" << c->startTime << "E" << c->endTime << endl;


			file << e->x << endl;
			file << e->y << endl;
			file << e->s << endl;
			file << e->t << endl;
			//cout << " color is" << color << endl;
			file << color << endl;
		}


	}
	edgeInfo.close();
	file.close();
	fileName = S("devices") + S(moment)+S(".txt");

	file.open(fileName.c_str());
	string deviceName = S("deviceName") + S(".txt");
		ofstream deviceNameFile;
		deviceNameFile.open(deviceName.c_str());
	double deviceR = 0.2;
		for(Device* d:devices){
			deviceNameFile << d->name << endl;
			for(Node* n:g.nodes){
				string dbindN = d->name + S("Bind") + getNodeName(n);
				int dBindNValue = ILPResults[dbindN];

				if(dBindNValue == 0)
					continue;
				//draw a circle
				int devX = n->x;
				int devY = n->y;

				file << devX<< endl;
				file << devY << endl;
				file << deviceR << endl;
			}

		}
		deviceNameFile.close();
		file.close();
}

void Plate::writeGraphFile(){
	ofstream file;
	file.open("edges.txt");
	ofstream edgeInfo;
	string edgeInfoName = S("edgesInfo")  + S(".txt");
	int flag = 0;
	edgeInfo.open(edgeInfoName.c_str());
	int cCount = 0;
	for(Channel* c:channels){


			int color = cCount%4;
			cCount++;

			for(Edge* e:g.edges){
				string edgeUsedInC = c->name + S("U") +getEdgeName(e);
				int edgeUsedValue = ILPResults[edgeUsedInC];
				if(edgeUsedValue == 0)
					continue;
				//cout << edgeUsedInC << " is 1" << endl;
				edgeInfo << c->name + S("U") + getEdgeName(e) << "S" << c->startTime << "E" << c->endTime << endl;


				file << e->x << endl;
				file << e->y << endl;
				file << e->s << endl;
				file << e->t << endl;
				//cout << " color is" << color << endl;
				file << color << endl;
			}


		}

	file.close();
	edgeInfo.close();

	file.open("devices.txt");
	string deviceName = S("deviceName") + S(".txt");
		ofstream deviceNameFile;
		deviceNameFile.open(deviceName.c_str());
	double deviceR = 0.2;
		for(Device* d:devices){
			deviceNameFile<<d->name<<endl;
			for(Node* n:g.nodes){
				string dbindN = d->name + S("Bind") + getNodeName(n);
				int dBindNValue = ILPResults[dbindN];

				if(dBindNValue == 0)
					continue;
				//draw a circle
				int devX = n->x;
				int devY = n->y;

				file << devX<< endl;
				file << devY << endl;
				file << deviceR << endl;
			}

		}
		deviceNameFile.close();
		file.close();
}


void Plate::writeDeviceCoord(string fileName){
	ofstream file;
	file.open("deviceCoord.txt");
	for(Device* d:devices){
		vector<string> coordNames = getDeviceCoordName(d);
		string x = coordNames.at(0);
		string y = coordNames.at(1);
		string s = coordNames.at(2);
		string t = coordNames.at(3);

		int xValue = ILPResults[x];
		int yValue = ILPResults[y];
		int sValue = ILPResults[s];
		int tValue = ILPResults[t];
		file << x << " " <<xValue <<endl;
		file << y << " " <<yValue <<endl;
		file << s << " " <<sValue << endl;
		file << t << " " <<tValue << endl;
	}
	file.close();
}
void Plate::readFromSolver(map<string,int> const & input){
	ILPResults = input;
	resultsFromLastItr.clear();
	for(auto const &iter : ILPResults){
		string varname = iter.first;
		int result = iter.second;
		int isObjName = false;
		for(string objname:varNameObj){
			if(varname == objname){
				isObjName = true;
				break;
			}
		}
		if(!isObjName){
			resultsFromLastItr.push_back(varname + " = " + S(result));
		}
	}


}



void Plate::readFromSolverDevice(map<string,int> const & input){
	ILPResults = input;
	resultsFromLastItr.clear();


	for(Device* d:devices){
		string x = S(d->name) + S("x");
		string y = S(d->name) + S("y");
		string s = S(d->name) + S("s");
		string t = S(d->name) + S("t");

		int xV = ILPResults.at(x);
		int yV = ILPResults.at(y);
		int sV = ILPResults.at(s);
		int tV = ILPResults.at(t);
		resultsFromLastItr.push_back(x + " = " + S(xV));
		resultsFromLastItr.push_back(y + " = " + S(yV));
		resultsFromLastItr.push_back(s + " = " + S(sV));
		resultsFromLastItr.push_back(t + " = " + S(tV));

	}


}

void Plate::writeDeviceLoc(map<string,int> const & inputResult){

	if(inputResult.size() == 0)
		return;

	ofstream file1;
	ofstream file2;
	file1.open("deviceLocVarName.txt");
	file2.open("deviceLocValue.txt");
	for(Device* d:devices){
		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string dBindN = S(d->name) + S("Bind") + S(nName);



			int result = inputResult.at(dBindN);
			if(result== 1){
				devBindNode[d] = n;
			}

			file1 << dBindN << endl;
			file2<<result<<endl;
		}
	}
	file1.close();
	file2.close();
}

void Plate::genRandomDevLoc(){

	vector<int> existedNodesPos;

	for(Device* d:devices){
		int randNodePos = rand()%g.nodes.size();
		while(find(existedNodesPos.begin(),existedNodesPos.end(),randNodePos) != existedNodesPos.end()){
			randNodePos = rand()%g.nodes.size();
		}

		existedNodesPos.push_back(randNodePos);
		Node* n  = g.nodes.at(randNodePos);
		devBindNode[d] = n;
		cout << d->name << "is bind to " << getNodeName(n) << endl;
	}


}

void Plate::readDeviceLoc(){
	string name;
		int value;
		std::ifstream file1("deviceLocVarName.txt");
		std::ifstream file2("deviceLocValue.txt");
		string str1,str2;
		map<string,int> results;

		while (getline(file1, str1) && getline(file2,str2))
		{
			name = str1;
			istringstream abuffer(str2);
			abuffer >> value;
			results[name] = value;

		}

		for(Device* d:devices){
			for(Node* n:g.nodes){
				string nName = getNodeName(n);
				string dBindN = S(d->name) + S("Bind") + S(nName);

				int result = results[dBindN];
				if(result == 1){
					devBindNode[d] = n;
				}

			}
		}
}

void Plate::switchDeviceLoc(){
	srand (time(NULL));
	int randDev0Pos = rand()%(devices.size());
	int randDev1Pos = rand()%(devices.size());
	Device* randD0 = devices[randDev0Pos];
	Device* randD1 = devices[randDev1Pos];

	Node* temp = devBindNode[randD0];
	devBindNode[randD0] = devBindNode[randD1];
	devBindNode[randD1] = temp;
}

void Plate::moveDeviceLoc(){

	bool haveMove1Node = false;
	while(!haveMove1Node){
		int randDev0Pos = rand()%(devices.size());

		Device* randD0 = devices[randDev0Pos];
		Node* bindNode = devBindNode[randD0];
		for(Node* neigbour : bindNode->adjNodesList){
			bool neigbourOcupied = false;
			for(Device* d:devices){
				if(neigbour == devBindNode[d]){
					neigbourOcupied = true;
					break;
				}
			}

			if(!neigbourOcupied){
				devBindNode[randD0] = neigbour;
				haveMove1Node = true;
				break;
			}

		}
	}


}

void Plate::writeDevLocToILP(){
	if(devBindNode.size() == 0)
		return;

	for(Device* d:devices){
		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string dBindN = S(d->name) + S("Bind") + S(nName);

			if(devBindNode[d] == n){
				ILP.push_back(dBindN + S(" = 1"));
			}
			else{
				ILP.push_back(dBindN + S(" = 0"));
			}
		}
	}
}

void Plate::writeToFile(string fileName){
	writeILP write;
	const char* f = fileName.c_str();
	write.writeOBJ(OBJ,f);
	write.writeConstraint(ILP,f);
	resultsFromLastItr.push_back(" ");
	write.writeResult(resultsFromLastItr,f);
	//write.writeBounds(bounds,"ilp.lp");

	write.writeVarNames(varName,varType,f);




}
void Plate::writeToFileShort(string fileName){
	writeILP write;
	const char* f = fileName.c_str();
	write.writeOBJ(shortOBJ,f);
	write.writeConstraint(shortILP,f);
	resultsFromLastItr.push_back(" ");
	write.writeResult(resultsFromLastItr,f);
	//write.writeBounds(bounds,"ilp.lp");

	write.writeVarNames(shortVarNames,varType,f);




}
// decide all operations on one device.  sort them by time

map<string,vector<Op>> Plate::devicesOperations(){
	 map<string,vector<Op>> results;
	 for(Device* d:devices){
		 vector<Op*> sortedOperations;
		 for(Op* op:operations){
			if(op->bindDevice->name == d->name){
				sortedOperations.push_back(op);
			}
		 }

		 //Algorithm::quickSort(sortedOperations,0,sortedOperations.size()-1);

		//results[d->name] = sortedOperations;
	 }

	 return results;


}

Device* Plate::getDeviceFromOp(const Op*& op){
	Device* o;
	for(int i = 0; i < devices.size();i++){
		Device* d = devices.at(i);
		if(op->bindDevice->name == d->name)
			return d;
	}
	return o;
}






string inline valveNameStr(int x0,int y0,int x1,int y1){
	return   S("V") + S("x")+S(x0)+S("y")+S(y0) +S("s")+S(x1)+S("t")+S(y1);
}

string inline valveAlongChannelStr(const string& valveName){
	return valveName+S("Along");
}

string inline valveInChannelStr(const string& valveName){
	return valveName + S("in");
}

string inline valveUsedStr(string valveName){
	return valveName + S("used");
}

string inline pointNameStr(int i,int j){
	return S("point")+S(i)+S(j);
}


//to see if 2 channels cross at all




void Plate::constraintClear(){
	OBJ.clear();
	varName.clear();
	varType.clear();
	ILP.clear();
	varNameObj.clear();
	//resultsFromLastItr.clear();
	bounds.clear();
}






void Plate::setConciseChannelTime(){

}


void Plate::setChannelsTime()
{
	channels.clear();
	//for each parent of each Operation, generate 3 Channel, in/out/storage

	for(Channel* motherC:Lchannels){
		Op* parent = motherC->fatherOp;
		Op* child = motherC->childOp;

		if(motherC->startTime == motherC->endTime)
			continue;
		//storage store;
		if(motherC->startTime + TRANSTIME < motherC->endTime){
			Channel* first(new Channel);
			Channel* last(new Channel);
			Channel* storage(new Channel);

			first->startTime = motherC->startTime;
			first->endTime = motherC->startTime + TRANSTIME;
			first->name = S("f") + parent->name + child->name;
			first->belongTo = S("c") + S(parent->name) + S(child->name);
			first->isFirst = true;
			first->fatherOp = parent;
			channels.push_back(first);

			last->startTime = motherC->endTime- TRANSTIME;
			last->endTime = motherC->endTime;
			last->name = S("l") + parent->name + child->name;
			last->belongTo = S("c") + S(parent->name) + S(child->name);
			last->isLast= true;
			last->childOp = child;
			channels.push_back(last);

			storage->startTime = motherC->startTime;
			storage->endTime = motherC->endTime;
			storage->name = S("s") + parent->name + child->name;
			storage->belongTo = S("c") + S(parent->name) + S(child->name);
			storage->isStore= true;
			channels.push_back(storage);

		}
		else{
			Channel* c(new Channel);


			//tmpChannel leftEnd,rightEnd;
			c->isNormal = true;
			c->startTime = motherC->startTime;
			c->endTime = motherC->endTime;

			c->fatherOp = parent;
			c->childOp = child;

			c->name = S("c") + S(parent->name) + S(child->name);
			c->belongTo = c->name;

			channels.push_back(c);
			//channels.push_back(flowPSource);
			//channels.push_back(flowPWaste);
		}



	}




}


void Plate::devicePlacement(){
	for(Device* d:devices){
		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string dBindN = S(d->name) + S("Bind") + S(nName);
			varName.push_back(dBindN);varType.push_back("1"); // 1 means true, 0 means false

		}
	}
	//one device binds to one node
	for(Device* d:devices){
		string str = "";

		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string dBindN = S(d->name) + S("Bind") + S(nName);


			str+= S(" + ") + S(dBindN);

		}
		str += S(" = 1");
		ILP.push_back(str);
	}

	//one node bind at most one dev
	for(Node* n:g.nodes){
		string str = "";
		for(Device* d:devices){
			string nName = getNodeName(n);
			string dBindN = S(d->name) + S("Bind") + S(nName);


			str+= S(" + ") + S(dBindN);

		}
		str += S(" <= 1");
		ILP.push_back(str);
	}


}

void Plate::channelStartEnd(){
	//channel are formed by edges, there is at least one edge
	for(Channel* c:channels){
		if(!c->isNormal)
			continue;
		string str = "";
		for(Edge* e:g.edges){
			string eName = getEdgeName(e);
			string cUsedEdge = S(c->name) +S("U")+S(eName);
			varName.push_back(cUsedEdge);varType.push_back("1");
			str += S(" + ") + cUsedEdge;
		}
		ILP.push_back(str + S(" >= 1"));
	}



	//channel start with father end with child
	for(Channel* c:channels){
		if(!c->isNormal)
			continue;
		Device* father = c->fatherOp->bindDevice;
		Device* son = c->childOp->bindDevice;

		//if device is bind to a node, edge aroud it must be used
		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string fatherBindN = S(father->name) + S("Bind") + S(nName);
			string sonBindN = S(son->name) + S("Bind") + S(nName);


			//if father bind to N, edge0 + edge1 + edge2 + edge 3 = 1
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudFUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cUsedEdge = S(c->name) +S("U")+S(eName);
				edgeAroudFUsed += S(" + ") + cUsedEdge;
			}

			ILP.push_back(edgeAroudFUsed + S(" - ") + S(M) + S(" ") + S(fatherBindN) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudFUsed + S(" + ") + S(M) + S(" ") + S(fatherBindN) + S(" <= ") + S(1+M));
			//if son bind To
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudSUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cUsedEdge = S(c->name) +S("U")+S(eName);
				edgeAroudSUsed += S(" + ") + cUsedEdge;
			}

			ILP.push_back(edgeAroudSUsed + S(" - ") + S(M) + S(" ") + S(sonBindN) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudSUsed + S(" + ") + S(M) + S(" ") + S(sonBindN) + S(" <= ") + S(1+M));

			//for device other father and son, if this device bind to node, edge around it cannot be used

			for(Device* d:devices){
				if(d == father || d == son )
					continue;

				string dBindN = S(d->name) + S("Bind") + S(nName);

				string edgeAroudDUsed = "";
				for(Edge* e:n->adjEdgesList){
					string eName = getEdgeName(e);
					string cUsedEdge = S(c->name) +S("U")+S(eName);
					edgeAroudDUsed += S(" + ") + cUsedEdge;
				}

				//if dbindN = 1 then edge = 0
				ILP.push_back(edgeAroudDUsed + S(" - ") + S(M) + S(" ") + S(dBindN) + S(" >= ") + S(-M));
				ILP.push_back(edgeAroudDUsed + S(" + ") + S(M) + S(" ") + S(dBindN) + S(" <= ") + S(+M));

			}


		}
	}
}

void Plate::channelStartEndFloorPlan(){
	//channel are formed by edges, there is at least one edge
	for(Channel* c:channels){
		if(!c->isNormal)
			continue;
		string str = "";
		for(Edge* e:g.edges){
			string eName = getEdgeName(e);
			string cUsedEdge = S(c->name) +S("U")+S(eName);
			varName.push_back(cUsedEdge);varType.push_back("1");
			str += S(" + ") + cUsedEdge;
		}
		ILP.push_back(str + S(" >= 1"));
	}



	//channel start with father end with child
	for(Channel* c:channels){
		if(!c->isNormal)
			continue;
		Device* father = c->fatherOp->bindDevice;
		Node* fatherNode = devBindNode[father];

		Device* son = c->childOp->bindDevice;
		Node* sonNode = devBindNode[son];

		//if device is bind to a node, edge aroud it must be used
			Node* n;
			n = fatherNode;


			//if father bind to N, edge0 + edge1 + edge2 + edge 3 = 1
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudFUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cUsedEdge = S(c->name) +S("U")+S(eName);
				edgeAroudFUsed += S(" + ") + cUsedEdge;
			}

			ILP.push_back(edgeAroudFUsed + S(" = 1"));

			n = sonNode;
			//if son bind To
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudSUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cUsedEdge = S(c->name) +S("U")+S(eName);
				edgeAroudSUsed += S(" + ") + cUsedEdge;
			}

			ILP.push_back(edgeAroudSUsed + S(" = 1"));

			//for device other father and son, if this device bind to node, edge around it cannot be used
			for(Node* n:g.nodes){
				for(Device* d:devices){
					if(d == father || d == son )
						continue;

					Node* dNode = devBindNode[d];

					if(n != dNode)
						continue;

					string edgeAroudDUsed = "";
					for(Edge* e:n->adjEdgesList){
						string eName = getEdgeName(e);
						string cUsedEdge = S(c->name) +S("U")+S(eName);
						edgeAroudDUsed += S(" + ") + cUsedEdge;
					}

					//if dbindN = 1 then edge = 0
					ILP.push_back(edgeAroudDUsed +  S(" = 0") );

				}
			}
	}
}

void Plate::channelSimplePath(){
	for(Channel* c:channels){
		if(!c->isNormal)
			continue;
		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInC = c->name + S("U") + nName;
			varName.push_back(nodeUsedInC); varType.push_back("1");
		}
	}

	for(Channel* c:channels){
		if(!c->isNormal)
			continue;
		Device* father = c->fatherOp->bindDevice;
		Device* son = c->childOp->bindDevice;


		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInC =  c->name + S("U") +nName;

			string fatherBindN = S(father->name) + S("Bind") + S(nName);
			string sonBindN = S(son->name) + S("Bind") + S(nName);

			string edgeAroudUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cUsedEdge = S(c->name) +S("U")+S(eName);
				edgeAroudUsed += S(" + ") + cUsedEdge;
			}
			//if fatherBindN = 0 && sonBind = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * father >= 0
			//edgeUsde - 2 * nodeUsedInC - M * father <= 0
			ILP.push_back(edgeAroudUsed + S(" - ") + S(2) +S(" ") +S(nodeUsedInC)+ S(" + ") + S(M) + S(" ") + S(fatherBindN) +S(" + ")+S(M) + S(" ") + S(sonBindN) + S(" >= ") + S(0));
			ILP.push_back(edgeAroudUsed + S(" - ") + S(2) +S(" ") +S(nodeUsedInC) + S(" - ") + S(M) + S(" ") + S(fatherBindN)+S(" - ")+S(M) + S(" ") + S(sonBindN) + S(" <= ") + S(0));

		}
	}


}

void Plate::channelSimplePathFloorPlan(){
	for(Channel* c:channels){
		if(!c->isNormal)
			continue;
		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInC = c->name + S("U") + nName;
			varName.push_back(nodeUsedInC); varType.push_back("1");
		}
	}

	for(Channel* c:channels){
		if(!c->isNormal)
			continue;
		Device* father = c->fatherOp->bindDevice;
		Node* fatherNode = devBindNode[father];
		Device* son = c->childOp->bindDevice;
		Node* sonNode = devBindNode[son];


		for(Node* n:g.nodes){

			if(n == fatherNode || n == sonNode )
				continue;
			string nName = getNodeName(n);
			string nodeUsedInC =  c->name + S("U") +nName;



			string edgeAroudUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cUsedEdge = S(c->name) +S("U")+S(eName);
				edgeAroudUsed += S(" + ") + cUsedEdge;
			}
			//if fatherBindN = 0 && sonBind = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * father >= 0
			//edgeUsde - 2 * nodeUsedInC - M * father <= 0
			ILP.push_back(edgeAroudUsed + S(" - ") + S(2) +S(" ") +S(nodeUsedInC)+   S(" = 0"));

		}
	}


}

void Plate::channelFirstStoreLast(){

	for(Channel* c:channels){
		if(c->isNormal)
			continue;
		string storedEdge = "";
		for(Edge* e:g.edges){
			string eName = getEdgeName(e);
			string cUsedEdge = S(c->name) + S("U") +(eName);
			varName.push_back(cUsedEdge);varType.push_back("1");


		}

		string oneStartNode = "";
		string oneEndNode = "";
		for(Node* n:g.nodes){
			string storeStartNode = S(c->belongTo) + S("SS") + getNodeName(n);
			varName.push_back(storeStartNode);varType.push_back("1");
			string storeEndNode = S(c->belongTo) + S("SE") + getNodeName(n);
			varName.push_back(storeEndNode);varType.push_back("1");


			string nodeUsedInC= S(c->name) + S("U") + getNodeName(n);
			varName.push_back(nodeUsedInC);varType.push_back("1");

			oneStartNode += S(" + ") + storeStartNode;
			oneEndNode += S(" + ") + storeEndNode;
		}

		//there is only one store end node and one store start node
		ILP.push_back(oneStartNode + S(" = 1"));
		ILP.push_back(oneEndNode + S(" = 1"));


	}

	//first
	for(Channel* c:channels){
		if(!c->isFirst)
			continue;
		Device* father = c->fatherOp->bindDevice;


		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInC = S(c->name) + S("U") + getNodeName(n);
			string storeEndNode = S(c->belongTo) + S("SE") + getNodeName(n);
			string storeStartNode = S(c->belongTo) + S("SE") + getNodeName(n);
			string fatherBindN = S(father->name) + S("Bind") + S(nName);

			string edgeAroudUsedF = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cFirstEdge = S(c->name) +S("U")+S(eName);
				edgeAroudUsedF += S(" + ") + cFirstEdge;
			}
			//if fatherBindN = 0 && storeStart = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * father >= 0
			//edgeUsde - 2 * nodeUsedInC - M * father <= 0
			ILP.push_back(edgeAroudUsedF + S(" - ") + S(2) +S(" ") +S(nodeUsedInC)+ S(" + ") + S(M) + S(" ") + S(fatherBindN)+ S(" + ") + S(M) + S(" ") + S(storeEndNode) + S(" >= ") + S(0));
			ILP.push_back(edgeAroudUsedF + S(" - ") + S(2) +S(" ") +S(nodeUsedInC) + S(" - ") + S(M) + S(" ") + S(fatherBindN) + S(" - ") + S(M) + S(" ") + S(storeEndNode) + S(" <= ") + S(0));


			//first must start with father and end with store end

			//if father bind to N, edge0 + edge1 + edge2 + edge 3 = 1
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudFUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cFirstEdge = S(c->name) +S("U")+S(eName);
				edgeAroudFUsed += S(" + ") + cFirstEdge;
			}

			ILP.push_back(edgeAroudFUsed + S(" - ") + S(M) + S(" ") + S(fatherBindN) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudFUsed + S(" + ") + S(M) + S(" ") + S(fatherBindN) + S(" <= ") + S(1+M));
			//if store end bind To node
			// edge0 + edge1 + edge2 + edge3 + M(1-storeStart) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-storeStart) <= 1
			string edgeAroudSUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cFirstEdge = S(c->name) +S("U")+S(eName);
				edgeAroudSUsed += S(" + ") + cFirstEdge;
			}

			ILP.push_back(edgeAroudSUsed + S(" - ") + S(M) + S(" ") + S(storeEndNode) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudSUsed + S(" + ") + S(M) + S(" ") + S(storeEndNode) + S(" <= ") + S(1+M));




			//for device other father, if this device bind to node, edge around it cannot be used

			for(Device* d:devices){
				if(d == father)
					continue;

				string dBindN = S(d->name) + S("Bind") + S(nName);

				string edgeAroudDUsedF = "";
				for(Edge* e:n->adjEdgesList){
					string eName = getEdgeName(e);
					string cFirstEdge = S(c->name) +S("U")+S(eName);
					edgeAroudDUsedF += S(" + ") + cFirstEdge;
				}

				//if dbindN = 1 then edge = 0
				ILP.push_back(edgeAroudDUsedF + S(" - ") + S(M) + S(" ") + S(dBindN) + S(" >= ") + S(-M));
				ILP.push_back(edgeAroudDUsedF + S(" + ") + S(M) + S(" ") + S(dBindN) + S(" <= ") + S(+M));

			}

		}

		//store start must be bond to channel
		string ssandnodesharenode = "";
		for(Node* n:g.nodes){
			string nodeUsedInC = S(c->name) + S("U") + getNodeName(n);
			string storeStartNode = S(c->belongTo) + S("SS") + getNodeName(n);
			string nodeBothStoreStartN = S(c->belongTo) + S("SSN") +S(c->name) + ("U") + getNodeName(n);
			varName.push_back(nodeBothStoreStartN); varType.push_back("1");
			ILP.push_back(S(2) + S(" ") + nodeBothStoreStartN + S(" - ") + storeStartNode + S(" - ") + nodeUsedInC + S(" <= 0"));
			ssandnodesharenode += S(" + ")+ nodeBothStoreStartN;
		}
		ILP.push_back(ssandnodesharenode + S(" = 1"));


	}
	//last
	for(Channel* c:channels){
		if(!c->isLast)
			continue;

		Device* son = c->childOp->bindDevice;


		for(Node* n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInLast = S(c->name) + S("U") + getNodeName(n);
			string storeStartNode = S(c->belongTo) + S("SS") + getNodeName(n);
			string sonBindN = S(son->name) + S("Bind") + S(nName);

			string edgeAroudUsedSon = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cLastEdge = S(c->name) +S("U")+S(eName);
				edgeAroudUsedSon += S(" + ") + cLastEdge;
			}
			//if sonBindNode = 0 and storeEnd = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * son >= 0
			//edgeUsde - 2 * nodeUsedInC - M * son <= 0
			ILP.push_back(edgeAroudUsedSon + S(" - ") + S(2) +S(" ") +S(nodeUsedInLast)+ S(" + ") + S(M) + S(" ") + S(sonBindN) + S(" + ") + S(M) + S(" ") + S(storeStartNode) + S(" >= ") + S(0));
			ILP.push_back(edgeAroudUsedSon + S(" - ") + S(2) +S(" ") +S(nodeUsedInLast) + S(" - ") + S(M) + S(" ") + S(sonBindN) + S(" - ") + S(M) + S(" ") + S(storeStartNode)  + S(" <= ") + S(0));


			//first must start with father and end with store start

			//if father bind to N, edge0 + edge1 + edge2 + edge 3 = 1
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudSonDevUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cLastEdge = S(c->name) +S("U")+S(eName);
				edgeAroudSonDevUsed += S(" + ") + cLastEdge;
			}

			ILP.push_back(edgeAroudSonDevUsed + S(" - ") + S(M) + S(" ") + S(sonBindN) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudSonDevUsed + S(" + ") + S(M) + S(" ") + S(sonBindN) + S(" <= ") + S(1+M));

			//if storeEnd bind To node
			// edge0 + edge1 + edge2 + edge3 + M(1-storeEnd) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-storeEnd) <= 1
			string edgeAroudStoreEndUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cLastEdge = S(c->name) +S("U")+S(eName);
				edgeAroudStoreEndUsed += S(" + ") + cLastEdge;
			}

			ILP.push_back(edgeAroudStoreEndUsed + S(" - ") + S(M) + S(" ") + S(storeStartNode) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudStoreEndUsed + S(" + ") + S(M) + S(" ") + S(storeStartNode) + S(" <= ") + S(1+M));

			//for device other son, if this device bind to node, edge around it cannot be used

			for(Device* d:devices){
				if( d == son )
					continue;

				string dBindN = S(d->name) + S("Bind") + S(nName);

				string edgeAroudDUsed = "";
				for(Edge* e:n->adjEdgesList){
					string eName = getEdgeName(e);
					string cLastEdge = S(c->name) +S("U")+S(eName);
					edgeAroudDUsed += S(" + ") + cLastEdge;
				}

				//if dbindN = 1 then edge = 0
				ILP.push_back(edgeAroudDUsed + S(" - ") + S(M) + S(" ") + S(dBindN) + S(" >= ") + S(-M));
				ILP.push_back(edgeAroudDUsed + S(" + ") + S(M) + S(" ") + S(dBindN) + S(" <= ") + S(+M));

			}

		}
		//store start must be bond to channel
		string seandnodesharenode = "";
		for(Node* n:g.nodes){
			string nodeUsedInC = S(c->name) + S("U") + getNodeName(n);
			string storeEndNode = S(c->belongTo) + S("SE") + getNodeName(n);
			string nodeBothStoreEndN = S(c->belongTo) + S("SEN") +S(c->name) + ("U") + getNodeName(n);
			varName.push_back(nodeBothStoreEndN); varType.push_back("1");
			ILP.push_back(S(2) + S(" ") + nodeBothStoreEndN + S(" - ") + storeEndNode + S(" - ") + nodeUsedInC + S(" <= 0"));
			seandnodesharenode += S(" + ")+ nodeBothStoreEndN;
		}
		ILP.push_back(seandnodesharenode + S(" = 1"));


	}

	//store
	for(Channel* c:channels){
		if(!c->isStore)
			continue;
		string allEdge = "";
		for(Edge* e:g.edges){
			string cStoredEdge = S(c->name) + S("U") + getEdgeName(e);
			Node* n0 = g.hashNodes[Node::hash2Int(e->x,e->y)];
			Node* n1 = g.hashNodes[Node::hash2Int(e->s,e->t)];

			string storeEndN0 = S(c->belongTo) + S("SE") + getNodeName(n0);
			string storeStartN0 = S(c->belongTo) + S("SS") + getNodeName(n0);
			string storeEndN1 = S(c->belongTo) + S("SE") + getNodeName(n1);
			string storeStartN1 = S(c->belongTo) + S("SS") + getNodeName(n1);
			//if cStoredEdge = 1 then storeStartN0 = 1 and storeEndN1 = 1 or storeStartN1 = 1 and storeEndN0 = 1
			//sN0 + sN1 - (1-sE)M <= 1 sN0+sN1 + (1-sE)M >= 1
			ILP.push_back(storeStartN0 + S(" + ") + storeStartN1  + S(" + ") + S(M) + S(" ") + cStoredEdge  + S(" <= ") + S(1+M));
			ILP.push_back(storeStartN0 + S(" + ") + storeStartN1  + S(" - ") + S(M) + S(" ") + cStoredEdge  + S(" >= ") + S(1-M));
			ILP.push_back(storeEndN0 + S(" + ") + storeEndN1  + S(" + ") + S(M) + S(" ") + cStoredEdge  + S(" <= ") + S(1+M));
			ILP.push_back(storeEndN0 + S(" + ") + storeEndN1  + S(" - ") + S(M) + S(" ") + cStoredEdge  + S(" >= ") + S(1-M));
			ILP.push_back(storeStartN0 + S(" + ") + storeEndN0 + S(" <= 1"));
			ILP.push_back( storeStartN1+S(" + ") + storeEndN1 + S(" <= 1"));
			allEdge += S(" + ")+cStoredEdge;
		}
		//there must be an storage
		ILP.push_back(allEdge + S(" = 1"));

	}

	//



}

void Plate::channelFirstStoreLastFloorPlan(){

	for(Channel* c:channels){
		if(c->isNormal)
			continue;
		string storedEdge = "";
		for(Edge* e:g.edges){
			string eName = getEdgeName(e);
			string cUsedEdge = S(c->name) + S("U") +(eName);
			varName.push_back(cUsedEdge);varType.push_back("1");


		}

		string oneStartNode = "";
		string oneEndNode = "";
		for(Node* n:g.nodes){
			string storeStartNode = S(c->belongTo) + S("SS") + getNodeName(n);
			varName.push_back(storeStartNode);varType.push_back("1");
			string storeEndNode = S(c->belongTo) + S("SE") + getNodeName(n);
			varName.push_back(storeEndNode);varType.push_back("1");


			string nodeUsedInC= S(c->name) + S("U") + getNodeName(n);
			varName.push_back(nodeUsedInC);varType.push_back("1");

			oneStartNode += S(" + ") + storeStartNode;
			oneEndNode += S(" + ") + storeEndNode;
		}

		//there is only one store end node and one store start node
		ILP.push_back(oneStartNode + S(" = 1"));
		ILP.push_back(oneEndNode + S(" = 1"));


	}

	//first
	for(Channel* c:channels){
		if(!c->isFirst)
			continue;
		Device* father = c->fatherOp->bindDevice;
		Node* fatherNode = devBindNode[father];

		string edgeAroudFUsed = "";
		for(Edge* e:fatherNode->adjEdgesList){
			string eName = getEdgeName(e);
			string cFirstEdge = S(c->name) +S("U")+S(eName);
			edgeAroudFUsed += S(" + ") + cFirstEdge;
		}

		ILP.push_back(edgeAroudFUsed +  S(" = 1"));

		for(Node* n:g.nodes){
			if(n == fatherNode)
				continue;

			string nName = getNodeName(n);
			string nodeUsedInC = S(c->name) + S("U") + getNodeName(n);
			string storeEndNode = S(c->belongTo) + S("SE") + getNodeName(n);
			string storeStartNode = S(c->belongTo) + S("SE") + getNodeName(n);

			string edgeAroudUsedF = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cFirstEdge = S(c->name) +S("U")+S(eName);
				edgeAroudUsedF += S(" + ") + cFirstEdge;
			}
			//if fatherBindN = 0 && storeStart = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * father >= 0
			//edgeUsde - 2 * nodeUsedInC - M * father <= 0
			ILP.push_back(edgeAroudUsedF + S(" - ") + S(2) +S(" ") +S(nodeUsedInC)+S(" + ") + S(M) + S(" ") + S(storeEndNode) + S(" >= ") + S(0));
			ILP.push_back(edgeAroudUsedF + S(" - ") + S(2) +S(" ") +S(nodeUsedInC) + S(" - ") + S(M) + S(" ") + S(storeEndNode) + S(" <= ") + S(0));




			//if store end bind To node
			// edge0 + edge1 + edge2 + edge3 + M(1-storeStart) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-storeStart) <= 1
			string edgeAroudSUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cFirstEdge = S(c->name) +S("U")+S(eName);
				edgeAroudSUsed += S(" + ") + cFirstEdge;
			}

			ILP.push_back(edgeAroudSUsed + S(" - ") + S(M) + S(" ") + S(storeEndNode) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudSUsed + S(" + ") + S(M) + S(" ") + S(storeEndNode) + S(" <= ") + S(1+M));




			//for device other father, if this device bind to node, edge around it cannot be used

			for(Device* d:devices){
				if(d == father)
					continue;

				Node* dNode = devBindNode[d];
				if(dNode != n)
					continue;

				string edgeAroudDUsedF = "";
				for(Edge* e:n->adjEdgesList){
					string eName = getEdgeName(e);
					string cFirstEdge = S(c->name) +S("U")+S(eName);
					edgeAroudDUsedF += S(" + ") + cFirstEdge;
				}

				//if dbindN = 1 then edge = 0
				ILP.push_back(edgeAroudDUsedF + S(" = 0"));

			}

		}

		//store start must be bond to channel
		string ssandnodesharenode = "";
		for(Node* n:g.nodes){
			string nodeUsedInC = S(c->name) + S("U") + getNodeName(n);
			string storeStartNode = S(c->belongTo) + S("SS") + getNodeName(n);
			string nodeBothStoreStartN = S(c->belongTo) + S("SSN") +S(c->name) + ("U") + getNodeName(n);
			varName.push_back(nodeBothStoreStartN); varType.push_back("1");
			ILP.push_back(S(2) + S(" ") + nodeBothStoreStartN + S(" - ") + storeStartNode + S(" - ") + nodeUsedInC + S(" <= 0"));
			ssandnodesharenode += S(" + ")+ nodeBothStoreStartN;
		}
		ILP.push_back(ssandnodesharenode + S(" = 1"));


	}
	//last
	for(Channel* c:channels){
		if(!c->isLast)
			continue;

		Device* son = c->childOp->bindDevice;
		Node* sonNode = devBindNode[son];
		//if son bind to N, edge0 + edge1 + edge2 + edge 3 = 1
		// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
		//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
		string edgeAroudSonDevUsed = "";
		for(Edge* e:sonNode->adjEdgesList){
			string eName = getEdgeName(e);
			string cLastEdge = S(c->name) +S("U")+S(eName);
			edgeAroudSonDevUsed += S(" + ") + cLastEdge;
		}

		ILP.push_back(edgeAroudSonDevUsed + S(" = 1"));

		for(Node* n:g.nodes){

			if(n == sonNode)
				continue;
			string nName = getNodeName(n);
			string nodeUsedInLast = S(c->name) + S("U") + getNodeName(n);
			string storeStartNode = S(c->belongTo) + S("SS") + getNodeName(n);

			string edgeAroudUsedSon = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cLastEdge = S(c->name) +S("U")+S(eName);
				edgeAroudUsedSon += S(" + ") + cLastEdge;
			}
			//if sonBindNode = 0 and storeEnd = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * son >= 0
			//edgeUsde - 2 * nodeUsedInC - M * son <= 0
			ILP.push_back(edgeAroudUsedSon + S(" - ") + S(2) +S(" ") +S(nodeUsedInLast) + S(" + ") + S(M) + S(" ") + S(storeStartNode) + S(" >= ") + S(0));
			ILP.push_back(edgeAroudUsedSon + S(" - ") + S(2) +S(" ") +S(nodeUsedInLast) + S(" - ") + S(M) + S(" ") + S(storeStartNode)  + S(" <= ") + S(0));


			//first must start with father and end with store start



			//if storeEnd bind To node
			// edge0 + edge1 + edge2 + edge3 + M(1-storeEnd) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-storeEnd) <= 1
			string edgeAroudStoreEndUsed = "";
			for(Edge* e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cLastEdge = S(c->name) +S("U")+S(eName);
				edgeAroudStoreEndUsed += S(" + ") + cLastEdge;
			}

			ILP.push_back(edgeAroudStoreEndUsed + S(" - ") + S(M) + S(" ") + S(storeStartNode) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudStoreEndUsed + S(" + ") + S(M) + S(" ") + S(storeStartNode) + S(" <= ") + S(1+M));

			//for device other son, if this device bind to node, edge around it cannot be used

			for(Device* d:devices){
				if( d == son )
					continue;

				Node* dNode = devBindNode[d];

				if(dNode != n)
					continue;

				//dnode == n
				string edgeAroudDUsed = "";
				for(Edge* e:n->adjEdgesList){
					string eName = getEdgeName(e);
					string cLastEdge = S(c->name) +S("U")+S(eName);
					edgeAroudDUsed += S(" + ") + cLastEdge;
				}

				//if dbindN = 1 then edge = 0
				ILP.push_back(edgeAroudDUsed + S(" = 0"));

			}

		}
		//store start must be bond to channel
		string seandnodesharenode = "";
		for(Node* n:g.nodes){
			string nodeUsedInC = S(c->name) + S("U") + getNodeName(n);
			string storeEndNode = S(c->belongTo) + S("SE") + getNodeName(n);
			string nodeBothStoreEndN = S(c->belongTo) + S("SEN") +S(c->name) + ("U") + getNodeName(n);
			varName.push_back(nodeBothStoreEndN); varType.push_back("1");
			ILP.push_back(S(2) + S(" ") + nodeBothStoreEndN + S(" - ") + storeEndNode + S(" - ") + nodeUsedInC + S(" <= 0"));
			seandnodesharenode += S(" + ")+ nodeBothStoreEndN;
		}
		ILP.push_back(seandnodesharenode + S(" = 1"));


	}

	//store
	for(Channel* c:channels){
		if(!c->isStore)
			continue;
		string allEdge = "";
		for(Edge* e:g.edges){
			string cStoredEdge = S(c->name) + S("U") + getEdgeName(e);
			Node* n0 = g.hashNodes[Node::hash2Int(e->x,e->y)];
			Node* n1 = g.hashNodes[Node::hash2Int(e->s,e->t)];

			string storeEndN0 = S(c->belongTo) + S("SE") + getNodeName(n0);
			string storeStartN0 = S(c->belongTo) + S("SS") + getNodeName(n0);
			string storeEndN1 = S(c->belongTo) + S("SE") + getNodeName(n1);
			string storeStartN1 = S(c->belongTo) + S("SS") + getNodeName(n1);
			//if cStoredEdge = 1 then storeStartN0 = 1 and storeEndN1 = 1 or storeStartN1 = 1 and storeEndN0 = 1
			//sN0 + sN1 - (1-sE)M <= 1 sN0+sN1 + (1-sE)M >= 1
			ILP.push_back(storeStartN0 + S(" + ") + storeStartN1  + S(" + ") + S(M) + S(" ") + cStoredEdge  + S(" <= ") + S(1+M));
			ILP.push_back(storeStartN0 + S(" + ") + storeStartN1  + S(" - ") + S(M) + S(" ") + cStoredEdge  + S(" >= ") + S(1-M));
			ILP.push_back(storeEndN0 + S(" + ") + storeEndN1  + S(" + ") + S(M) + S(" ") + cStoredEdge  + S(" <= ") + S(1+M));
			ILP.push_back(storeEndN0 + S(" + ") + storeEndN1  + S(" - ") + S(M) + S(" ") + cStoredEdge  + S(" >= ") + S(1-M));
			ILP.push_back(storeStartN0 + S(" + ") + storeEndN0 + S(" <= 1"));
			ILP.push_back( storeStartN1+S(" + ") + storeEndN1 + S(" <= 1"));
			allEdge += S(" + ")+cStoredEdge;
		}
		//there must be an storage
		ILP.push_back(allEdge + S(" = 1"));

	}

	//



}
void Plate::channelTimeConfict(){
	//2 conflict channels
	for(Channel* c1:channels){
		for(Channel* c2:channels){
			if(c1 == c2)
				continue;
			if(c1->belongTo == c2->belongTo)
				continue;

			if((c1->startTime >= c2->endTime || c1->endTime <= c2->startTime))
				continue;
			//c1 not store and c2 not store dont share same node


				for(int time = 0; time < M; time++){
					if(c1->startTime < time && time < c1->endTime && c2->startTime < time && time < c2->endTime){
						conflictMoment.push_back(time);
						break;
					}
				}

				for(Node* n:g.nodes){

					string nodeUsedInc1 = S(c1->name)+S("U")+getNodeName(n);
					string nodeUsedInc2 = S(c2->name)+S("U")+getNodeName(n);
					ILP.push_back(nodeUsedInc1 + S(" + ") + nodeUsedInc2 + S(" <= 1 "));

				}

				//and they dont share edge
				for(Edge* e:g.edges){
					string c1UsedEdge = c1->name + S("U") + getEdgeName(e);
					string c2UsedEdge = c2->name + S("U") + getEdgeName(e);
					ILP.push_back(c1UsedEdge + S(" + ") + c2UsedEdge + S(" <= 1"));

				}

		}
	}


}
int Plate::calEdgeUseNum(){
	int numUsedEdge = 0;
	for(Edge* e:g.edges){
			string eName = getEdgeName(e);
			string eUsed = getEdgeName(e) + S("U");
			int edgeUse = ILPResults[eUsed];
			numUsedEdge += edgeUse;
	}

	return numUsedEdge;
}

void Plate::objective(){
	string objective = "";

	for(Edge* e:g.edges){
		string eName = getEdgeName(e);
		string eUsed = getEdgeName(e) + S("U");
		varName.push_back(eUsed);varType.push_back("1");
		varNameObj.push_back(eUsed);

		string allCUsedEdge = "";
		for(Channel* c:channels){

			string cUsedEdge = S(c->name) + S("U") + S(eName);

			allCUsedEdge += S(" + ") + cUsedEdge;
		}

		ILP.push_back(allCUsedEdge + S(" - ") + S(M) + S(" ") + eUsed + S(" <= 0"));

		objective += S(" + ") + eUsed;
	}
	OBJ.push_back("Minimize");
	OBJ.push_back(objective);
}




#endif



