#if 0
#ifndef PLATE_CPP
#define PLATE_CPP
#include <iostream>
#include "../header/plate.h"
#include "../header/device.h"
#include "../header/FlowPath.h"
#include "../header/writeILP.h"
#include "../header/Node.h"
#include "../header/edge.h"
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


typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;
typedef boost::shared_ptr<Channel> Channel_ptr;
typedef boost::shared_ptr<FlowPath> FlowPath_ptr;
typedef boost::shared_ptr<Node> Node_ptr;
typedef boost::shared_ptr<Edge> Edeg_ptr;

#ifndef SSTRING
#define SSTRING

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


#endif

__inline__ string getNodeName(Node_ptr n){
	return S("n") + S("x") +S(n->x)+ S("y") + S(n->y);
}
__inline__ string getEdgeName(Edge_ptr e){
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
}

void Plate::getPartInfoFromListByTime(const ListAlgorithm& L, int numberOfOps){
	string fileNameOps = "newOps" + S(itrTimes) + ".txt";
	ofstream fileOps;
	fileOps.open(fileNameOps.c_str());



	int newOpNumber = 0;
	int channelCount = 0;
	int opCount = 0;
	for(int time = 0; ;time++){
		for(Op_ptr op:L.ops){
			auto it = find(operations.begin(),operations.end(),op);
			//op is already in operations
			if(it != operations.end())
				continue;

			if(op->endTime == time){
				operations.push_back(op);
				fileOps << "new Op " << op->name << "  bind to " << op->bindDevice->name << " type "<<op->type <<endl;
				opCount++;
				for(Op_ptr parent:op->parents){

					fileOps << "parent " << parent->name<< " type "<<parent->type << endl;
					fileOps << "new Channel from " << parent->name <<" to " <<op->name << " from " << parent->bindDevice->name << " " << parent->bindDevice->type
							<< " to " << op->bindDevice->name << " " << op->bindDevice->type << endl;
					channelCount++;
				}
				fileOps << "--------------------" << endl;



				Dev_ptr bindDev = op->bindDevice;
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

		for(Op_ptr op:L.ops){

			auto it = find(operations.begin(),operations.end(),op);
			//op is already in operations
			if(it != operations.end())
				continue;

			bool allFatherInOperations = true;
			for(Op_ptr father:op->parents){
				auto fatherIt = find(operations.begin(),operations.end(),father);
				//op father not already in operations
				if(fatherIt == operations.end())
					allFatherInOperations = false;
			}

			if(allFatherInOperations == true){
				operations.push_back(op);
				Dev_ptr bindDev = op->bindDevice;
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





string getVertexNameX(Channel_ptr const &c, int number){

	return c->name + S("x") + S(number);


}

string getVertexNameY(Channel_ptr const & c, int number){
	return c->name + S("y") + S(number);
}
string  getSegName(Channel_ptr const &c, int number){

	return c->name + S("Seg") + S(number - 1);

}


//x y s t ilp name
vector<string> getDeviceCoordName(Dev_ptr const & d){
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
	for(Op_ptr op:operations){
		file << op->name<<" start at" << op->startTime << " end at" << op->endTime << " bind to " << op->bindDevice->name <<endl;
	}

	for(Channel_ptr c:channels){


		file << c->name <<" start at" << c->fatherOp->endTime << " end at" << c->childOp->startTime
				<< "start from  "<< c->fatherOp->bindDevice->name << " to " << c->childOp->bindDevice->name<<endl;
		if(c->childOp->startTime- c->fatherOp->endTime > TRANSTIME )
			file << c->name << " contains a storage" << endl;
	}
	file.close();
}






void Plate::writeGraphFile(int pathNumber){
	ofstream file;
	file.open("edges.txt");
	int flag = 0;
	for(Edge_ptr e:g.edges){
		string edgeUsed = getEdgeName(e) + S("U");
		int edgeUsedValue = ILPResults[edgeUsed];
		if(edgeUsedValue == 0)
			continue;
		file << e->x << endl;
		file << e->y << endl;
		file << e->s << endl;
		file << e->t << endl;

	}


	file.close();

	file.open("devices.txt");
	double deviceR = 0.2;
		for(Dev_ptr d:devices){
			for(Node_ptr n:g.nodes){
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

		file.close();
}


void Plate::writeDeviceCoord(string fileName){
	ofstream file;
	file.open("deviceCoord.txt");
	for(Dev_ptr d:devices){
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


	for(Dev_ptr d:devices){
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

void Plate::writeToFile(){
	writeILP write;

	write.writeOBJ(OBJ,"ilp.lp");
	write.writeConstraint(ILP,"ilp.lp");
	resultsFromLastItr.push_back(" ");
	write.writeResult(resultsFromLastItr,"ilp.lp");
	//write.writeBounds(bounds,"ilp.lp");

	write.writeVarNames(varName,varType,"ilp.lp");




}
void Plate::writeToFileShort(){
	writeILP write;

	write.writeOBJ(shortOBJ,"ilp.lp");
	write.writeConstraint(shortILP,"ilp.lp");
	resultsFromLastItr.push_back(" ");
	write.writeResult(resultsFromLastItr,"ilp.lp");
	//write.writeBounds(bounds,"ilp.lp");

	write.writeVarNames(shortVarNames,varType,"ilp.lp");




}
// decide all operations on one device.  sort them by time

map<string,vector<Op>> Plate::devicesOperations(){
	 map<string,vector<Op>> results;
	 for(Dev_ptr d:devices){
		 vector<Op_ptr> sortedOperations;
		 for(Op_ptr op:operations){
			if(op->bindDevice->name == d->name){
				sortedOperations.push_back(op);
			}
		 }

		 //Algorithm::quickSort(sortedOperations,0,sortedOperations.size()-1);

		//results[d->name] = sortedOperations;
	 }

	 return results;


}

Dev_ptr Plate::getDeviceFromOp(const Op_ptr& op){
	Dev_ptr o;
	for(int i = 0; i < devices.size();i++){
		Dev_ptr d = devices.at(i);
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
	for(Op_ptr child:operations){



		Dev_ptr childDevice = child->bindDevice;
		for(Op_ptr parent:child->parents){


			Channel_ptr c(new Channel);
			c->name = S("c") + S(parent->name) + S(child->name);
			FlowPath_ptr flowPSource(new FlowPath),flowPWaste(new FlowPath);

			if(parent->name == "source"){
				c->fatherOp = parent;
				c->childOp = child;



				channels.push_back(c);
			}
			else{
				Dev_ptr fatherDevice = child->bindDevice;
				//tmpChannel leftEnd,rightEnd;

				c->startTime = parent->endTime;
				c->endTime = child->startTime;

				c->fatherOp = parent;
				c->childOp = child;

				c->name = S("c") + S(parent->name) + S(child->name);

				channels.push_back(c);
				//channels.push_back(flowPSource);
				//channels.push_back(flowPWaste);

				//storage store;
				if(parent->endTime + 10 < child->startTime){
					c->isStore = true;
					c->storageStart = c->startTime + TRANSTIME;
					c->storageEnd = c->endTime-TRANSTIME;
				}

			}

		}


	}

}


void Plate::devicePlacement(){
	for(Dev_ptr d:devices){
		for(Node_ptr n:g.nodes){
			string nName = getNodeName(n);
			string dBindN = S(d->name) + S("Bind") + S(nName);
			varName.push_back(dBindN);varType.push_back("1"); // 1 means true, 0 means false

		}
	}
	//one device binds to one node
	for(Dev_ptr d:devices){
		string str = "";

		for(Node_ptr n:g.nodes){
			string nName = getNodeName(n);
			string dBindN = S(d->name) + S("Bind") + S(nName);


			str+= S(" + ") + S(dBindN);

		}
		str += S(" = 1");
		ILP.push_back(str);
	}

	//one node bind at most one dev
	for(Node_ptr n:g.nodes){
		string str = "";
		for(Dev_ptr d:devices){
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
	for(Ch_ptr c:channels){
		if(c->isStore)
			continue;
		string str = "";
		for(Edge_ptr e:g.edges){
			string eName = getEdgeName(e);
			string cUsedEdge = S(c->name) +S("U")+S(eName);
			varName.push_back(cUsedEdge);varType.push_back("1");
			str += S(" + ") + cUsedEdge;
		}
		ILP.push_back(str + S(" >= 1"));
	}



	//channel start with father end with child
	for(Ch_ptr c:channels){
		if(c->isStore)
			continue;
		Dev_ptr father = c->fatherOp->bindDevice;
		Dev_ptr son = c->childOp->bindDevice;

		//if device is bind to a node, edge aroud it must be used
		for(Node_ptr n:g.nodes){
			string nName = getNodeName(n);
			string fatherBindN = S(father->name) + S("Bind") + S(nName);
			string sonBindN = S(son->name) + S("Bind") + S(nName);


			//if father bind to N, edge0 + edge1 + edge2 + edge 3 = 1
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudFUsed = "";
			for(Edge_ptr e:n->adjEdgesList){
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
			for(Edge_ptr e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cUsedEdge = S(c->name) +S("U")+S(eName);
				edgeAroudSUsed += S(" + ") + cUsedEdge;
			}

			ILP.push_back(edgeAroudSUsed + S(" - ") + S(M) + S(" ") + S(sonBindN) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudSUsed + S(" + ") + S(M) + S(" ") + S(sonBindN) + S(" <= ") + S(1+M));

			//for device other father and son, if this device bind to node, edge around it cannot be used

			for(Dev_ptr d:devices){
				if(d == father || d == son )
					continue;

				string dBindN = S(d->name) + S("Bind") + S(nName);

				string edgeAroudDUsed = "";
				for(Edge_ptr e:n->adjEdgesList){
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

void Plate::channelSimplePath(){
	for(Channel_ptr c:channels){
		if(c->isStore)
			continue;
		for(Node_ptr n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInC = c->name + S("U") + nName;
			varName.push_back(nodeUsedInC); varType.push_back("1");
		}
	}

	for(Channel_ptr c:channels){
		if(c->isStore)
			continue;
		Dev_ptr father = c->fatherOp->bindDevice;
		Dev_ptr son = c->childOp->bindDevice;


		for(Node_ptr n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInC =  c->name + S("U") +nName;

			string fatherBindN = S(father->name) + S("Bind") + S(nName);
			string sonBindN = S(son->name) + S("Bind") + S(nName);

			string edgeAroudUsed = "";
			for(Edge_ptr e:n->adjEdgesList){
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

void Plate::channelFirstStoreLast(){

	for(Ch_ptr c:channels){
		if(!c->isStore)
			continue;
		string storedEdge = "";
		for(Edge_ptr e:g.edges){
			string eName = getEdgeName(e);
			string cFirstEdge = S(c->name) + S("F") +(eName);
			string cLastEdge = S(c->name) + S("L") + S(eName);
			varName.push_back(cFirstEdge);varType.push_back("1");
			varName.push_back(cLastEdge);varType.push_back("1");

			string cStoredEdge = S(c->name) +S("S")+S(eName);
			varName.push_back(cStoredEdge);varType.push_back("1");
			storedEdge += S(" + ") + cStoredEdge;

		}
		ILP.push_back(storedEdge + S(" = 1"));

		string oneStartNode = "";
		string oneEndNode = "";
		for(Node_ptr n:g.nodes){
			string storeStartNode = S(c->name) + S("SS") + getNodeName(n);
			varName.push_back(storeStartNode);varType.push_back("1");
			string storeEndNode = S(c->name) + S("SE") + getNodeName(n);
			varName.push_back(storeEndNode);varType.push_back("1");

			string nodeUsedInFirst = S(c->name) + S("F") + getNodeName(n);
			varName.push_back(nodeUsedInFirst);varType.push_back("1");
			string nodeUsedInLast = S(c->name) + S("L") + getNodeName(n);
			varName.push_back(nodeUsedInLast);varType.push_back("1");

			oneStartNode += S(" + ") + storeStartNode;
			oneEndNode += S(" + ") + storeEndNode;
		}

		//there is only one store end node and one store start node
		ILP.push_back(oneStartNode + S(" = 1"));
		ILP.push_back(oneEndNode + S(" = 1"));


	}

	//first
	for(Ch_ptr c:channels){
		if(!c->isStore)
			continue;
		Dev_ptr father = c->fatherOp->bindDevice;
		Dev_ptr son = c->childOp->bindDevice;




		for(Node_ptr n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInFirst = S(c->name) + S("F") + getNodeName(n);
			string storeStartNode = S(c->name) + S("SS") + getNodeName(n);
			string fatherBindN = S(father->name) + S("Bind") + S(nName);

			string edgeAroudUsedF = "";
			for(Edge_ptr e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cFirstEdge = S(c->name) +S("F")+S(eName);
				edgeAroudUsedF += S(" + ") + cFirstEdge;
			}
			//if fatherBindN = 0 && storeStart = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * father >= 0
			//edgeUsde - 2 * nodeUsedInC - M * father <= 0
			ILP.push_back(edgeAroudUsedF + S(" - ") + S(2) +S(" ") +S(nodeUsedInFirst)+ S(" + ") + S(M) + S(" ") + S(fatherBindN)+ S(" + ") + S(M) + S(" ") + S(storeStartNode) + S(" >= ") + S(0));
			ILP.push_back(edgeAroudUsedF + S(" - ") + S(2) +S(" ") +S(nodeUsedInFirst) + S(" - ") + S(M) + S(" ") + S(fatherBindN) + S(" - ") + S(M) + S(" ") + S(storeStartNode) + S(" <= ") + S(0));


			//first must start with father and end with store start

			//if father bind to N, edge0 + edge1 + edge2 + edge 3 = 1
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudFUsed = "";
			for(Edge_ptr e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cFirstEdge = S(c->name) +S("F")+S(eName);
				edgeAroudFUsed += S(" + ") + cFirstEdge;
			}

			ILP.push_back(edgeAroudFUsed + S(" - ") + S(M) + S(" ") + S(fatherBindN) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudFUsed + S(" + ") + S(M) + S(" ") + S(fatherBindN) + S(" <= ") + S(1+M));
			//if store start bind To node
			// edge0 + edge1 + edge2 + edge3 + M(1-storeStart) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-storeStart) <= 1
			string edgeAroudSUsed = "";
			for(Edge_ptr e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cFirstEdge = S(c->name) +S("F")+S(eName);
				edgeAroudSUsed += S(" + ") + cFirstEdge;
			}

			ILP.push_back(edgeAroudSUsed + S(" - ") + S(M) + S(" ") + S(storeStartNode) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudSUsed + S(" + ") + S(M) + S(" ") + S(storeStartNode) + S(" <= ") + S(1+M));

			//for device other father, if this device bind to node, edge around it cannot be used

			for(Dev_ptr d:devices){
				if(d == father)
					continue;

				string dBindN = S(d->name) + S("Bind") + S(nName);

				string edgeAroudDUsedF = "";
				for(Edge_ptr e:n->adjEdgesList){
					string eName = getEdgeName(e);
					string cFirstEdge = S(c->name) +S("F")+S(eName);
					edgeAroudDUsedF += S(" + ") + cFirstEdge;
				}

				//if dbindN = 1 then edge = 0
				ILP.push_back(edgeAroudDUsedF + S(" - ") + S(M) + S(" ") + S(dBindN) + S(" >= ") + S(-M));
				ILP.push_back(edgeAroudDUsedF + S(" + ") + S(M) + S(" ") + S(dBindN) + S(" <= ") + S(+M));

			}

		}


	}
	//last
	for(Ch_ptr c:channels){
		if(!c->isStore)
			continue;
		Dev_ptr father = c->fatherOp->bindDevice;
		Dev_ptr son = c->childOp->bindDevice;


		for(Node_ptr n:g.nodes){
			string nName = getNodeName(n);
			string nodeUsedInLast = S(c->name) + S("L") + getNodeName(n);
			string storeEndNode = S(c->name) + S("SE") + getNodeName(n);
			string sonBindN = S(son->name) + S("Bind") + S(nName);

			string edgeAroudUsedSon = "";
			for(Edge_ptr e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cLastEdge = S(c->name) +S("L")+S(eName);
				edgeAroudUsedSon += S(" + ") + cLastEdge;
			}
			//if sonBindNode = 0 and storeEnd = 0, edge used = 2 or 0
			//edgeUsed - 2 * nodeUsedInC + M * son >= 0
			//edgeUsde - 2 * nodeUsedInC - M * son <= 0
			ILP.push_back(edgeAroudUsedSon + S(" - ") + S(2) +S(" ") +S(nodeUsedInLast)+ S(" + ") + S(M) + S(" ") + S(sonBindN) + S(" + ") + S(M) + S(" ") + S(storeEndNode) + S(" >= ") + S(0));
			ILP.push_back(edgeAroudUsedSon + S(" - ") + S(2) +S(" ") +S(nodeUsedInLast) + S(" - ") + S(M) + S(" ") + S(sonBindN) + S(" - ") + S(M) + S(" ") + S(storeEndNode)  + S(" <= ") + S(0));


			//first must start with father and end with store start

			//if father bind to N, edge0 + edge1 + edge2 + edge 3 = 1
			// edge0 + edge1 + edge2 + edge3 + M(1-fatherB) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-fatherB) <= 1
			string edgeAroudSonDevUsed = "";
			for(Edge_ptr e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cLastEdge = S(c->name) +S("L")+S(eName);
				edgeAroudSonDevUsed += S(" + ") + cLastEdge;
			}

			ILP.push_back(edgeAroudSonDevUsed + S(" - ") + S(M) + S(" ") + S(sonBindN) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudSonDevUsed + S(" + ") + S(M) + S(" ") + S(sonBindN) + S(" <= ") + S(1+M));

			//if storeEnd bind To node
			// edge0 + edge1 + edge2 + edge3 + M(1-storeEnd) >= 1
			//edge0 + edge1 + edge2 + edge 3 - M(1-storeEnd) <= 1
			string edgeAroudStoreEndUsed = "";
			for(Edge_ptr e:n->adjEdgesList){
				string eName = getEdgeName(e);
				string cLastEdge = S(c->name) +S("L")+S(eName);
				edgeAroudStoreEndUsed += S(" + ") + cLastEdge;
			}

			ILP.push_back(edgeAroudStoreEndUsed + S(" - ") + S(M) + S(" ") + S(storeEndNode) + S(" >= ") + S(1-M));
			ILP.push_back(edgeAroudStoreEndUsed + S(" + ") + S(M) + S(" ") + S(storeEndNode) + S(" <= ") + S(1+M));

			//for device other son, if this device bind to node, edge around it cannot be used

			for(Dev_ptr d:devices){
				if( d == son )
					continue;

				string dBindN = S(d->name) + S("Bind") + S(nName);

				string edgeAroudDUsed = "";
				for(Edge_ptr e:n->adjEdgesList){
					string eName = getEdgeName(e);
					string cLastEdge = S(c->name) +S("L")+S(eName);
					edgeAroudDUsed += S(" + ") + cLastEdge;
				}

				//if dbindN = 1 then edge = 0
				ILP.push_back(edgeAroudDUsed + S(" - ") + S(M) + S(" ") + S(dBindN) + S(" >= ") + S(-M));
				ILP.push_back(edgeAroudDUsed + S(" + ") + S(M) + S(" ") + S(dBindN) + S(" <= ") + S(+M));

			}

		}


	}

	//store
	for(Channel_ptr c:channels){
		if(!c->isStore)
			continue;

		for(Edge_ptr e:g.edges){
			string cStoredEdge = S(c->name) + S("S") + getEdgeName(e);
			Node_ptr n0 = g.hashNodes[Node::hash2Int(e->x,e->y)];
			Node_ptr n1 = g.hashNodes[Node::hash2Int(e->s,e->t)];

			string storeEndN0 = S(c->name) + S("SE") + getNodeName(n0);
			string storeStartN0 = S(c->name) + S("SS") + getNodeName(n0);
			string storeEndN1 = S(c->name) + S("SE") + getNodeName(n1);
			string storeStartN1 = S(c->name) + S("SS") + getNodeName(n1);
			//if cStoredEdge = 1 then storeStartN0 = 1 and storeEndN1 = 1 or storeStartN1 = 1 and storeEndN0 = 1
			//sN0 + sN1 - (1-sE)M <= 1 sN0+sN1 + (1-sE)M >= 1
			ILP.push_back(storeStartN0 + S(" + ") + storeStartN1  + S(" + ") + S(M) + S(" ") + cStoredEdge  + S(" <= ") + S(1+M));
			ILP.push_back(storeStartN0 + S(" + ") + storeStartN1  + S(" - ") + S(M) + S(" ") + cStoredEdge  + S(" >= ") + S(1-M));
			ILP.push_back(storeEndN0 + S(" + ") + storeEndN1  + S(" + ") + S(M) + S(" ") + cStoredEdge  + S(" <= ") + S(1+M));
			ILP.push_back(storeEndN0 + S(" + ") + storeEndN1  + S(" - ") + S(M) + S(" ") + cStoredEdge  + S(" >= ") + S(1-M));
			ILP.push_back(storeStartN0 + S(" + ") + storeEndN0 + S(" <= 1"));
			ILP.push_back( storeStartN1+S(" + ") + storeEndN1 + S(" <= 1"));
		}


	}

}
void Plate::channelTimeConfict(){
	//2 conflict channels
	for(Channel_ptr c1:channels){
		for(Channel_ptr c2:channels){
			if(c1 == c2)
				continue;

			if((c1->startTime >= c2->endTime || c1->endTime <= c2->startTime))
				continue;
			//c1 not store and c2 not store dont share same node
			if(!c1->isStore && !c2->isStore){

				for(int time = 0; time < M; time++){
					if(c1->startTime < time && time < c1->endTime && c2->startTime < time && time < c2->endTime){
						conflictMoment.push_back(time);
						break;
					}
				}

				for(Node_ptr n:g.nodes){

					string nodeUsedInc1 = S(c1->name)+S("U")+getNodeName(n);
					string nodeUsedInc2 = S(c2->name)+S("U")+getNodeName(n);
					ILP.push_back(nodeUsedInc1 + S(" + ") + nodeUsedInc2 + S(" <= 1 "));

				}

				//and they dont share edge
				for(Edge_ptr e:g.edges){
					string c1UsedEdge = c1->name + S("U") + getEdgeName(e);
					string c2UsedEdge = c2->name + S("U") + getEdgeName(e);
					ILP.push_back(c1UsedEdge + S(" + ") + c2UsedEdge + S(" <= 1"));

				}
			}
			else if(c1->isStore && !c2->isStore){

					//c1 f conflict with c2
					if(!(c1->startTime >= c2->endTime || c1->storageStart <=c2->startTime )){

						for(int time = 0; time < M; time++){
							if(c1->startTime < time && time < c1->storageStart && c2->startTime < time && time < c2->endTime){
								conflictMoment.push_back(time);
								break;
							}
						}

						for(Node_ptr n:g.nodes){
							string nodeUsedInFirstc1 = S(c1->name) + S("F") + getNodeName(n);
							string nodeUsedInc2 = S(c2->name)+S("U")+getNodeName(n);
							ILP.push_back(nodeUsedInFirstc1+ S(" + ") + nodeUsedInc2 + S(" <= 1 "));
						}

						//and they dont share edge
						for(Edge_ptr e:g.edges){
							string c1FUsedEdge = c1->name + S("F") + getEdgeName(e);
							string c2UsedEdge = c2->name + S("U") + getEdgeName(e);
							ILP.push_back(c1FUsedEdge + S(" + ") + c2UsedEdge + S(" <= 1"));

						}
					}
					//c1 store conflict with c2
					if(!(c1->storageStart >= c2->endTime || c1->storageEnd <= c2->startTime)){
						for(int time = 0; time < M; time++){
							if(c1->storageStart< time && time < c1->storageEnd && c2->startTime < time && time < c2->endTime){
								conflictMoment.push_back(time);
								break;
							}
						}
						for(Edge_ptr e:g.edges){
							string c1StoredEdge = S(c1->name) + S("S") + getEdgeName(e);
							string c2UsedEdge = S(c2->name) + S("U") + getEdgeName(e);
							ILP.push_back(c1StoredEdge + S(" + ") + c2UsedEdge + S(" <= 1"));
						}
					}


					//c1 L conflict with c2
					if(!(c1->storageEnd >= c2->endTime || c1->endTime <= c2->startTime )){
						for(Node_ptr n:g.nodes){
							for(int time = 0; time < M; time++){
								if(c1->storageEnd < time && time < c1->endTime && c2->startTime < time && time < c2->endTime){
									conflictMoment.push_back(time);
									break;
								}
							}
							string nodeUsedInLastc1 = S(c1->name) + S("L") + getNodeName(n);
							string nodeUsedInc2 = S(c2->name)+S("U")+getNodeName(n);
							ILP.push_back(nodeUsedInLastc1+ S(" + ") + nodeUsedInc2 + S(" <= 1 "));
						}

						//and they dont share edge
						for(Edge_ptr e:g.edges){
							string c1LUsedEdge = c1->name + S("L") + getEdgeName(e);
							string c2UsedEdge = c2->name + S("U") + getEdgeName(e);
							ILP.push_back(c1LUsedEdge + S(" + ") + c2UsedEdge + S(" <= 1"));

						}
					}


			}
			else if(c2->isStore && !c1->isStore){

					//c2 f conflict with c1
					if(!(c2->startTime >= c1->endTime || c2->startTime + TRANSTIME <=c1->startTime )){

						for(int time = 0; time < M; time++){
							if(c2->startTime < time && time < c2->storageStart && c1->startTime < time && time < c1->endTime){
								conflictMoment.push_back(time);
								break;
							}
						}

						for(Node_ptr n:g.nodes){
							string nodeUsedInFirstc2 = S(c2->name) + S("F") + getNodeName(n);
							string nodeUsedInc1 = S(c1->name)+S("U")+getNodeName(n);
							ILP.push_back(nodeUsedInFirstc2+ S(" + ") + nodeUsedInc1 + S(" <= 1 "));
						}
						//and they dont share edge
						for(Edge_ptr e:g.edges){
							string c1UsedEdge = c1->name + S("U") + getEdgeName(e);
							string c2FUsedEdge = c2->name + S("F") + getEdgeName(e);
							ILP.push_back(c1UsedEdge + S(" + ") + c2FUsedEdge + S(" <= 1"));

						}
					}
					//c2 store conflict with c1
					if(!(c2->storageStart >= c1->endTime || c2->storageEnd <= c1->startTime)){
						for(Edge_ptr e:g.edges){
							string c2StoredEdge = S(c2->name) + S("S") + getEdgeName(e);
							string c1UsedEdge = S(c1->name) + S("U") + getEdgeName(e);
							ILP.push_back(c2StoredEdge + S(" + ") + c1UsedEdge + S(" <= 1"));
						}
					}


					//c2 L conflict with c1
					if(!(c2->storageEnd >= c1->endTime || c2->endTime <= c1->startTime )){
						for(Node_ptr n:g.nodes){
							string nodeUsedInLastc2 = S(c2->name) + S("L") + getNodeName(n);
							string nodeUsedInc1 = S(c1->name)+S("U")+getNodeName(n);
							ILP.push_back(nodeUsedInLastc2+ S(" + ") + nodeUsedInc1 + S(" <= 1 "));
						}
						//and they dont share edge
						for(Edge_ptr e:g.edges){
							string c1UsedEdge = c1->name + S("U") + getEdgeName(e);
							string c2LsedEdge = c2->name + S("L") + getEdgeName(e);
							ILP.push_back(c1UsedEdge + S(" + ") + c2LsedEdge + S(" <= 1"));

						}
					}

			}
			else if(c1->isStore && c2->isStore){
				//c1 f conflict with c2 f
				if(!(c1->startTime >= c2->storageStart|| c1->storageStart <= c2->startTime )){
					for(Node_ptr n:g.nodes){
						string nodeUsedInFirstc1 = S(c1->name)+S("F")+getNodeName(n);
						string nodeUsedInFirstc2 = S(c2->name) + S("F") + getNodeName(n);
						ILP.push_back(nodeUsedInFirstc2+ S(" + ") + nodeUsedInFirstc1 + S(" <= 1 "));
					}

					//and they dont share edge
					for(Edge_ptr e:g.edges){
						string c1FUsedEdge = c1->name + S("F") + getEdgeName(e);
						string c2FUsedEdge = c2->name + S("F") + getEdgeName(e);
						ILP.push_back(c1FUsedEdge + S(" + ") + c2FUsedEdge + S(" <= 1"));

					}
				}
				//c1 f conflict with c2 storage
				if(!(c1->startTime >= c2->storageEnd|| c1->storageStart <= c2->storageStart )){
					for(Edge_ptr e:g.edges){
						string c1FirstEdge = S(c1->name) + S("F") + getEdgeName(e);
						string c2StorageEdge = S(c2->name) + S("S") + getEdgeName(e);
						ILP.push_back(c1FirstEdge + S(" + ") + c2StorageEdge + S(" <= 1"));
					}
				}
				//c1 f conflict with c2 L
				if(!(c1->startTime >= c2->endTime || c1->storageStart <= c2->storageEnd)){
					for(Node_ptr n:g.nodes){
						string nodeUsedInFirstc1 = S(c1->name)+S("F")+getNodeName(n);
						string nodeUsedInLastc2 = S(c2->name) + S("L") + getNodeName(n);
						ILP.push_back(nodeUsedInLastc2+ S(" + ") + nodeUsedInFirstc1 + S(" <= 1 "));
					}
					//and they dont share edge
					for(Edge_ptr e:g.edges){
						string c1FUsedEdge = c1->name + S("F") + getEdgeName(e);
						string c2LUsedEdge = c2->name + S("L") + getEdgeName(e);
						ILP.push_back(c1FUsedEdge + S(" + ") + c2LUsedEdge + S(" <= 1"));

					}
				}

				//c1 storage conflict with c2 f
				if(!(c1->storageStart >= c2->storageStart|| c1->storageEnd <= c2->startTime)){
					for(Edge_ptr e:g.edges){
						string c1StorageEdge = S(c1->name) + S("S") + getEdgeName(e);
						string c2FirstEdge = S(c2->name) + S("F") + getEdgeName(e);
						ILP.push_back(c2FirstEdge + S(" + ") + c1StorageEdge + S(" <= 1"));
					}
				}
				//c1 storage conflict with c2 storage
				if(!(c1->storageStart >= c2->storageEnd|| c1->storageEnd <= c2->storageStart)){
					for(Edge_ptr e:g.edges){
						string c1StorageEdge = S(c1->name) + S("S") + getEdgeName(e);
						string c2StorageEdge = S(c2->name) + S("S") + getEdgeName(e);
						ILP.push_back(c2StorageEdge+ S(" + ") + c1StorageEdge + S(" <= 1"));
					}
				}
				//c1 storage conflict with c2 L
				if(!(c1->storageStart >= c2->endTime|| c1->storageEnd <= c2->storageEnd)){
					for(Edge_ptr e:g.edges){
						string c1StorageEdge = S(c1->name) + S("S") + getEdgeName(e);
						string c2LastEdge = S(c2->name) + S("L") + getEdgeName(e);
						ILP.push_back(c2LastEdge+ S(" + ") + c1StorageEdge + S(" <= 1"));
					}
				}


				//c1 L conflict with c2 f
				if(!(c1->storageEnd >= c2->storageStart|| c1->endTime<= c2->startTime )){
					for(Node_ptr n:g.nodes){
						string nodeUsedInLastc1 = S(c1->name)+S("L")+getNodeName(n);
						string nodeUsedInFirstc2 = S(c2->name) + S("F") + getNodeName(n);
						ILP.push_back(nodeUsedInFirstc2+ S(" + ") + nodeUsedInLastc1 + S(" <= 1 "));
					}
					//and they dont share edge
					for(Edge_ptr e:g.edges){
						string c1LUsedEdge = c1->name + S("L") + getEdgeName(e);
						string c2FUsedEdge = c2->name + S("F") + getEdgeName(e);
						ILP.push_back(c1LUsedEdge + S(" + ") + c2FUsedEdge + S(" <= 1"));

					}
				}
				//c1 L conflict with c2 storage
				if(!(c1->storageEnd >= c2->storageEnd|| c1->endTime <= c2->storageStart )){
					for(Edge_ptr e:g.edges){
						string c1LastEdge = S(c1->name) + S("L") + getEdgeName(e);
						string c2StorageEdge = S(c2->name) + S("S") + getEdgeName(e);
						ILP.push_back(c1LastEdge + S(" + ") + c2StorageEdge + S(" <= 1"));
					}
				}
				//c1 L conflict with c2 L
				if(!(c1->storageEnd >= c2->endTime || c1->endTime <= c2->storageEnd)){
					for(Node_ptr n:g.nodes){
						string nodeUsedInLastc1 = S(c1->name)+S("L")+getNodeName(n);
						string nodeUsedInLastc2 = S(c2->name) + S("L") + getNodeName(n);
						ILP.push_back(nodeUsedInLastc2+ S(" + ") + nodeUsedInLastc1 + S(" <= 1 "));
					}
					//and they dont share edge
					for(Edge_ptr e:g.edges){
						string c1LUsedEdge = c1->name + S("L") + getEdgeName(e);
						string c2LsedEdge = c2->name + S("L") + getEdgeName(e);
						ILP.push_back(c1LUsedEdge + S(" + ") + c2LsedEdge + S(" <= 1"));

					}
				}

			}

		}
	}

}

void Plate::objective(){
	string objective = "";

	for(Edge_ptr e:g.edges){
		string eName = getEdgeName(e);
		string eUsed = getEdgeName(e) + S("U");
		varName.push_back(eUsed);varType.push_back("1");

		string allCUsedEdge = "";
		for(Channel_ptr c:channels){
			if(c->isStore)
				continue;
			string cUsedEdge = S(c->name) + S("U") + S(eName);

			allCUsedEdge += S(" + ") + cUsedEdge;
		}

		for(Channel_ptr c:channels){
			if(!c->isStore)
				continue;
			string cFirstEdge = S(c->name) + S("F") + S(eName);
			string cLastEdge = S(c->name) + S("L") + S(eName);
			string cStoreEdge = S(c->name) + S("S") + S(eName);

			allCUsedEdge += S(" + ") + cFirstEdge + S(" + ") + cLastEdge + S(" + ") + cStoreEdge;
		}

		ILP.push_back(allCUsedEdge + S(" - ") + S(M) + S(" ") + eUsed + S(" <= 0"));

		objective += S(" + ") + eUsed;
	}
	OBJ.push_back("Minimize");
	OBJ.push_back(objective);
}




#endif


#endif
