#ifndef PLATE_CPP
#define PLATE_CPP
#include <iostream>
#include "../header/plate.h"
#include "../header/device.h"
#include "../header/writeILP.h"
#include <boost/shared_ptr.hpp>


#include <string>
#include <sstream>
#include <functional>
#include <fstream>
#include <algorithm>

using namespace std;

#define jointStr(s1...)
#define M 10000
#define TRANSTIME 1
#define CHIPSIZE 10
#define LIQUIDESIZE 1
#define DEVICESTEP 3

typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;

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



string getFirstVertexNameX(Channel const& c, int number){
	return S(c.name) + S("first") + S("x") + S(number);
}

string getStorageVertexNameX(Channel const&  c, int number){
	return S(c.name) + S("storage") + S("x") + S(number);
}

string getEndVertexNameX(Channel const&  c, int number){
	return S(c.name) + S("end") + S("x") + S(number);
}

string getFirstVertexNameY(Channel const&  c, int number){
	return S(c.name) + S("first") + S("y") + S(number);
}

string getStorageVertexNameY(Channel const&  c, int number){
	return S(c.name) + S("storage") + S("y") + S(number);
}

string getEndVertexNameY(Channel const&  c, int number){
	return S(c.name) + S("end") + S("y") + S(number);
}

string getVertexNameX(Channel const &c, int number){

	//first
	if( number >= 0 && number <= c.vertexNum -1)
		return getFirstVertexNameX(c,number);
	//storage
	else if( number >= c.vertexNum && number <= 2*(c.vertexNum)-2)
		return getStorageVertexNameX(c,number - c.vertexNum+1);
	//end
	else
		return getEndVertexNameX(c,number - 2*(c.vertexNum)+2);
}

string getVertexNameY(Channel const & c, int number){
	//first
		if( number >= 0 && number <= c.vertexNum -1)
			return getFirstVertexNameY(c,number);
		//storage
		else if( number >= c.vertexNum && number <= 2*(c.vertexNum)-2)
			return getStorageVertexNameY(c,number - c.vertexNum+1);
		//end
		else
			return getEndVertexNameY(c,number - 2*(c.vertexNum)+2);
}
string  getSegName(Channel const &c, int vertexEndNumber){
	//first
		if( vertexEndNumber >= 1 && vertexEndNumber <= c.vertexNum-1)
			return c.name + S("FirstSeg") + S(vertexEndNumber-1);
		//storage
		else if( vertexEndNumber >= c.vertexNum && vertexEndNumber <= 2*(c.vertexNum)-2)
			return c.name + S("StorageSeg") + S(vertexEndNumber- c.vertexNum);
		//end
		else
			return  c.name + S("EndSeg") + S(vertexEndNumber- 2*c.vertexNum+1);
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


void Plate::writeGraphFile(int pathNumber){
	ofstream file;
	file.open("paths.txt");
	int flag = 0;
	for(int j = 0; j<channels.size();j++){
		Channel c = channels.at(j);

	//for(Channel c:channels){
	if(pathNumber != -1){
		if(j != pathNumber ){
				continue;
		}
	}
		for(int i =1; i <= 3*(c.vertexNum -1);i++){
			string x0 = getVertexNameX(c,i-1);
			string y0 = getVertexNameY(c,i-1);
			string x1 = getVertexNameX(c,i);
			string y1 = getVertexNameY(c,i);

			if(y0 == "co2o3storagey3" ){
				cout << "gotte ya" <<endl;
			}

			int x0Value = ILPResults[x0];
			int y0Value = ILPResults[y0];
			int x1Value = ILPResults[x1];
			int y1Value = ILPResults[y1];

			file << x0Value <<endl;
			file << y0Value <<endl;
			file << x1Value <<endl;
			file << y1Value <<endl;
		}

		/*for(int i = 1; i<c.vertexNum;i++){
			string preX = getFirstVertexNameX(c,i-1);
			string preY = getFirstVertexNameY(c,i-1);
			string x = getFirstVertexNameX(c,i);
			string y = getFirstVertexNameY(c,i);
			int preXValue = ILPResults[preX];
			int preYValue = ILPResults[preY];
			int XValue = ILPResults[x];
			int YValue = ILPResults[y];
			file << preXValue <<endl;
			file << preYValue<<endl;
			file << XValue << endl;
			file << YValue << endl;
		}



			for(int i = 1; i<c.vertexNum;i++){
				string preX = getStorageVertexNameX(c,i-1);
				string preY = getStorageVertexNameY(c,i-1);
				string x = getStorageVertexNameX(c,i);
				string y = getStorageVertexNameY(c,i);
				int preXValue = ILPResults[preX];
				int preYValue = ILPResults[preY];
				int XValue = ILPResults[x];
				int YValue = ILPResults[y];
				file << preXValue <<endl;
				file << preYValue<<endl;
				file << XValue << endl;
				file << YValue << endl;
			}



			for(int i = 1; i<c.vertexNum;i++){
				string preX = getEndVertexNameX(c,i-1);
				string preY = getEndVertexNameY(c,i-1);
				string x = getEndVertexNameX(c,i);
				string y = getEndVertexNameY(c,i);
				int preXValue = ILPResults[preX];
				int preYValue = ILPResults[preY];
				int XValue = ILPResults[x];
				int YValue = ILPResults[y];
				file << preXValue <<endl;
				file << preYValue<<endl;
				file << XValue << endl;
				file << YValue << endl;
			}*/




		}


	file.close();

	file.open("devices.txt");
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
				file << xValue <<endl;
				file << yValue <<endl;
				file << sValue << endl;
				file << tValue << endl;

		}

		file.close();
}

void Plate::readFromSolver(map<string,int> const & input){
	ILPResults = input;
	resultsFromLastItr.clear();
	for(auto const &iter : ILPResults){
		string varname = iter.first;
		int result = iter.second;
		resultsFromLastItr.push_back(varname + " = " + S(result));
	}
}

void Plate::writeToFile(){
	writeILP write;
	write.writeOBJ(OBJ,"ilp.lp");
	write.writeConstraint(ILP,"ilp.lp");
	resultsFromLastItr.push_back(" ");
	write.writeResult(resultsFromLastItr,"ilp.lp");
	write.writeBounds(bounds,"ilp.lp");

	write.writeVarNames(varName,varType,"ilp.lp");




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

void Plate::channeTimeConstraint(){
	//map<string,vector<Op>> deviceOpsSorted =  devicesOperations();


	//cout << channels.at(0).name << endl;

	//time constraint for a single channel
	//c0 start d0 end with d1, c1 start with c0end , end with c2start, c2  start with c1end, start with c1;

	for(Channel c:channels){
		string firststart = c.name + S("first") + S("start");varName.push_back(firststart);varType.push_back("2");
		string firstend = c.name + S("first") + S("end");varName.push_back(firstend);varType.push_back("2");
		string storagestart = c.name + S("storage") + S("start");varName.push_back(storagestart);varType.push_back("2");
		string storageend = c.name + S("storage") + S("end");varName.push_back(storageend);varType.push_back("2");
		string endstart = c.name + S("end") + S("start");varName.push_back(endstart);varType.push_back("2");
		string endend = c.name + S("end") + S("end");varName.push_back(endend);varType.push_back("2");

		Dev_ptr childDevice = c.childOp->bindDevice;
		Op_ptr& father = c.fatherOp;
		Op_ptr& child = c.childOp;
		//vector<Op> sortedOps = deviceOpsSorted.at(childDevice.name);
		//Op* childDevicePreviousOp = Algorithm::previousElement(sortedOps,c.childOp);

		//first.start >= father.end
		//first.end  <= storage.end
		//first.end >= first.start + TRANSTIME
		ILP.push_back(firststart + S(" >= ") + S(father->endTime));
		ILP.push_back(firstend + S(" - ") + storageend+ S(" <= 0"));
		ILP.push_back(firstend + S(" - ") + firststart + S(" >= ") + S(TRANSTIME));
		//storage.start = first.start
		//storage.end = end.end
		//storage.end >= storage.start;
		ILP.push_back(storagestart + S(" - ") + firststart + S(" = 0"));
		ILP.push_back(storagestart + S(" - ") + storageend+ S(" <= 0"));
		ILP.push_back(storageend + S(" - ") + endend + S(" = 0"));

		//end.start >= storage.start
		//end.end <= child.start
		//end.end >= end.start + TRANSTIME
		ILP.push_back(endstart + S(" - ") + storagestart + S(" >= 0"));
		ILP.push_back(endend + S(" <= ") + S(child->startTime));
		ILP.push_back(endend+ S(" - ") + endstart+ S(" >= ") + S(TRANSTIME));


		//end.end >= child.device.previousOp.first.end
		/*if(childDevicePreviousOp != nullptr){
			//string childDevicePreviousOpFirst
			ILP.push_back(endstart + S(" - ") + )
		}*/



	}



	//if two channels may concurrent with each other, set constraint
	for(int i = 0; i < channels.size();i++){

		Channel c0 = channels[i];
		for(int j = i+1; j < channels.size();j++){
			Channel c1 = channels[j];

			if(c0.startTime > c1.endTime || c0.endTime < c1.startTime)
				break;

			//c1's storage compare to all parts of c2
			for(int m = c0.vertexNum;m<=2*(c0.vertexNum-1);m++ ){
				//vertex from the seg before
				string x0 = getVertexNameX(c0,m-1);
				string y0 = getVertexNameY(c0,m-1);
				string x1 = getVertexNameX(c0,m);
				string y1 = getVertexNameY(c0,m);
				string seg0Name = getSegName(c0,m);

				for(int n = 1; n <= 3*(c0.vertexNum-1);n++){
				//vertex from this seg
					string x2 = getVertexNameX(c1,n-1);
					string y2 = getVertexNameY(c1,n-1);
					string x3 = getVertexNameX(c1,n);
					string y3 = getVertexNameY(c1,n);


					string seg1Name = getSegName(c1,n);


					//two segs do not cross at all

					string up = seg1Name +  S("Up") +  seg0Name;
					varName.push_back(up); varType.push_back("1");
					string down = seg1Name +  S("Down") + seg0Name;
					varName.push_back(down); varType.push_back("1");
					string left = seg1Name +  S("Left") + seg0Name;
					varName.push_back(left); varType.push_back("1");
					string right = seg1Name +  S("Right") + seg0Name;
					varName.push_back(right); varType.push_back("1");

					//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
					ILP.push_back(y0 + S(" - ") + y2 +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
					ILP.push_back(y0 + S(" - ") + y3 +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
					ILP.push_back(y1 + S(" - ") + y2 +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));
					ILP.push_back(y1 + S(" - ") + y3 +S(" + ") + S(M) + S(" ") + up +  S(" >= 1"));

					//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
					ILP.push_back(y0 + S(" - ") + y2 +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
					ILP.push_back(y0 + S(" - ") + y3 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
					ILP.push_back(y1 + S(" - ") + y2 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
					ILP.push_back(y1 + S(" - ") + y3 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

					//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
					ILP.push_back(x0 + S(" - ") + x2 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
					ILP.push_back(x0 + S(" - ") + x3 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
					ILP.push_back(x1 + S(" - ") + x2 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
					ILP.push_back(x1 + S(" - ") + x3 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));

					//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
					ILP.push_back(x0 + S(" - ") + x2 +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
					ILP.push_back(x0 + S(" - ") + x3 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
					ILP.push_back(x1 + S(" - ") + x2 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
					ILP.push_back(x1 + S(" - ") + x3 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));

					ILP.push_back(up + S(" + ") + down + S(" + ") + left+ S(" + ") + right + S(" <= 3"));
					}
				}


			//c2's storage compare to all parts of c1
			for(int m = 1;m<=3*(c0.vertexNum-1);m++ ){
				if( m >= c0.vertexNum && m<= 2*(c0.vertexNum-1))
						continue;
				//vertex from the seg before
				string x0 = getVertexNameX(c0,m-1);
				string y0 = getVertexNameY(c0,m-1);
				string x1 = getVertexNameX(c0,m);
				string y1 = getVertexNameY(c0,m);
				string seg0Name = getSegName(c0,m);

				for(int n = c0.vertexNum; n <= 2*(c0.vertexNum-1);n++){
				//vertex from this seg
					string x2 = getVertexNameX(c1,n-1);
					string y2 = getVertexNameY(c1,n-1);
					string x3 = getVertexNameX(c1,n);
					string y3 = getVertexNameY(c1,n);


					string seg1Name = getSegName(c1,n);


					//two segs do not cross at all

					string up = seg1Name +  S("Up") +  seg0Name;
					varName.push_back(up); varType.push_back("1");
					string down = seg1Name +  S("Down") + seg0Name;
					varName.push_back(down); varType.push_back("1");
					string left = seg1Name +  S("Left") + seg0Name;
					varName.push_back(left); varType.push_back("1");
					string right = seg1Name +  S("Right") + seg0Name;
					varName.push_back(right); varType.push_back("1");

					//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
					ILP.push_back(y0 + S(" - ") + y2 +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
					ILP.push_back(y0 + S(" - ") + y3 +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
					ILP.push_back(y1 + S(" - ") + y2 +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));
					ILP.push_back(y1 + S(" - ") + y3 +S(" + ") + S(M) + S(" ") + up +  S(" >= 1"));

					//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
					ILP.push_back(y0 + S(" - ") + y2 +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
					ILP.push_back(y0 + S(" - ") + y3 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
					ILP.push_back(y1 + S(" - ") + y2 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
					ILP.push_back(y1 + S(" - ") + y3 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

					//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
					ILP.push_back(x0 + S(" - ") + x2 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
					ILP.push_back(x0 + S(" - ") + x3 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
					ILP.push_back(x1 + S(" - ") + x2 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
					ILP.push_back(x1 + S(" - ") + x3 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));

					//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
					ILP.push_back(x0 + S(" - ") + x2 +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
					ILP.push_back(x0 + S(" - ") + x3 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
					ILP.push_back(x1 + S(" - ") + x2 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
					ILP.push_back(x1 + S(" - ") + x3 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
					ILP.push_back(up + S(" + ") + down + S(" + ") + left+ S(" + ") + right + S(" <= 3"));
					}
				}

			}
		}
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

void Plate::ValveObject(){
	//minimize intersections
	string obj;
	for(int i = 0; i <= CHIPSIZE-1;i++){
		for(int j = 0; j<= CHIPSIZE-1;j++){

			string pointName = pointNameStr(i,j);
			string pointOnVerticalSeg = pointName + S("VerticalSeg"); varName.push_back(pointOnVerticalSeg); varType.push_back("1");
			string pointOnHorSeg = pointName + S("HorSeg"); varName.push_back(pointOnHorSeg); varType.push_back("1");
			string pointUsed = pointName +S("Used");  varName.push_back(pointUsed); varType.push_back("1");
			ILP.push_back(pointOnVerticalSeg + S(" + ") + pointOnHorSeg + S(" - ") + pointUsed + S(" >= 0"));
			 obj += S(" + ") + pointUsed;

			for(int cnum = 0; cnum < channels.size(); cnum++ ){
				Channel c = channels.at(cnum);
				for(int k = 1 ; k<= 3*(c.vertexNum-1);k++){
					string x0 = getVertexNameX(c,k-1);
					string y0 = getVertexNameY(c,k-1);
					string x1 = getVertexNameX(c,k);
					string y1 = getVertexNameY(c,k);

					//if x0 = x1 && y0 <= j && y1 >= j then pointOnVertical = 0
					//x0 < x1 or x0 > x1 or y0 > j or y1 <j or pointOnVertical
					string x0Lessx1 = x0 + S("Less") +x1; // already exist
					string x0Biggerx1 = x0+ S("Bigger") + x1; // already exist
					string y0BiggerJ = y0+S("Bigger") + S(j); varName.push_back(y0BiggerJ);varType.push_back("1");
					string y1LessJ =  y1+S("Less")+S(j); varName.push_back(y1LessJ); varType.push_back("1");

					ILP.push_back(y0 + S(" + ") + S(M) +S(" ") + y0BiggerJ +S(" >= ") + S(j+1));
					ILP.push_back(y1 + S(" - ") + S(M) +S(" ") + y1LessJ +S(" <= ") + S(j-1));
					//at least one of them is true
					ILP.push_back((x0Lessx1+ S(" + ") + x0Biggerx1+ S(" + ") + y0BiggerJ+ S(" + ") + y1LessJ+ S(" + ") + pointOnVerticalSeg + S(" <= 4")));




					//if x0 = x1 && y0 >= j && y1 <=j then pointOnVertical = 0
					// x0 < x1 or x0 > x1 or y0<j or y1>j or poitnV
					string y1BiggerJ = y1+S("Bigger") + S(j); varName.push_back(y0BiggerJ);varType.push_back("1");
					string y0LessJ =  y0+S("Less")+S(j); varName.push_back(y1LessJ); varType.push_back("1");

					ILP.push_back(y1 + S(" + ") + S(M) +S(" ") + y1BiggerJ +S(" >= ") + S(j+1));
					ILP.push_back(y0 + S(" - ") + S(M) +S(" ") + y0LessJ +S(" <= ") + S(j-1));
					//at least one of them is true
					ILP.push_back((x0Lessx1+ S(" + ") + x0Biggerx1+ S(" + ") + y1BiggerJ+ S(" + ") + y0LessJ+ S(" + ") + pointOnVerticalSeg + S(" <= 4")));


					//if y0 = y1 && x0 <= i && x1 >= i then pointHor = 0
					// y0 < y1 or y0 > y1 or y0 >  i or y1 < i or pointHor
					string y0Lessy1 = y0 + S("Less") +y1; // already exist
					string y0Biggery1 = y0+ S("Bigger") + y1; // already exist
					string x0BiggerI = x0+S("Bigger") + S(i); varName.push_back(x0BiggerI);varType.push_back("1");
					string x1LessI =  x1+S("Less")+S(i); varName.push_back(x1LessI); varType.push_back("1");

					ILP.push_back(x0 + S(" + ") + S(M) +S(" ") + x0BiggerI +S(" >= ") + S(i+1));
					ILP.push_back(x1 + S(" - ") + S(M) +S(" ") + x1LessI +S(" <= ") + S(i-1));
					//at least one of them is true
					ILP.push_back((y0Lessy1+ S(" + ") + y0Biggery1+ S(" + ") + x0BiggerI+ S(" + ") + x1LessI+ S(" + ") + pointOnHorSeg + S(" <= 4")));



					//if y0 = y1 && x0 >= x && x1 <= x then pointHor = 0
					string x0LessI = x0+S("Less") + S(i); varName.push_back(x0LessI);varType.push_back("1");
					string x1BiggerI =  x1+S("Bigger")+S(i); varName.push_back(x1BiggerI); varType.push_back("1");

					ILP.push_back(x1 + S(" + ") + S(M) +S(" ") + x1BiggerI +S(" >= ") + S(i+1));
					ILP.push_back(x0 + S(" - ") + S(M) +S(" ") + x0LessI +S(" <= ") + S(i-1));
					//at least one of them is true
					ILP.push_back((y0Lessy1+ S(" + ") + y0Biggery1+ S(" + ") + x0LessI+ S(" + ") + x1BiggerI+ S(" + ") + pointOnHorSeg + S(" <= 4")));


				}
			}



		}
	}

	OBJ.push_back(obj);



}

void Plate::constraintClear(){
	OBJ.clear();
	varName.clear();
	varType.clear();
	ILP.clear();
	//resultsFromLastItr.clear();
	bounds.clear();
}

void Plate::channelPlaceConstraint(){
	setChannelsTime();

	const string plus = " + ";
	const string minus = " - ";

	//create variables
	for(Channel c:channels){
		for(int i = 0; i < c.vertexNum; i++){

			string fvx,fvy,svx,svy,evx,evy;
			fvx = S(c.name) + S("first") + S("x") + S(i);
			fvy = S(c.name) + S("first") + S("y") + S(i);
			svx = S(c.name) + S("storage") + S("x") + S(i);
			svy = S(c.name) + S("storage") + S("y") + S(i);
			evx = S(c.name) + S("end") + S("x") + S(i);
			evy = S(c.name) + S("end") + S("y") + S(i);

			varName.push_back(fvx); varType.push_back("0");
			varName.push_back(fvy); varType.push_back("0");
			varName.push_back(svx); varType.push_back("0");
			varName.push_back(svy); varType.push_back("0");
			varName.push_back(evx); varType.push_back("0");
			varName.push_back(evy); varType.push_back("0");

			bounds.push_back(S("0 <= ") + fvx + S(" <= ") + S(CHIPSIZE));
			bounds.push_back(S("0 <= ") + fvy + S(" <= ") + S(CHIPSIZE));
			bounds.push_back(S("0 <= ") + svx + S(" <= ") + S(CHIPSIZE));
			bounds.push_back(S("0 <= ") + svy + S(" <= ") + S(CHIPSIZE));
			bounds.push_back(S("0 <= ") + evx + S(" <= ") + S(CHIPSIZE));
			bounds.push_back(S("0 <= ") + evy + S(" <= ") + S(CHIPSIZE));


		}

	}

	//channels start with xx, end with xx
	for(Channel c:channels){

		Dev_ptr d0 = getDeviceFromOp(c.fatherOp);
		Dev_ptr d1 = getDeviceFromOp(c.childOp);

		//if d0 != d1
		//x0 = xx y0 = xx, xn = xx yn = xx
		string fx0 =  S(c.name) + S("first") + S("x") + S(0);
		string fxn =  S(c.name) + S("first") + S("x") + S(c.vertexNum-1);
		string fy0 =  S(c.name) + S("first") + S("y") + S(0);
		string fyn =  S(c.name) + S("first") + S("y") + S(c.vertexNum-1);

		string sx0 =  S(c.name) + S("storage") + S("x") + S(0);
		string sxn =  S(c.name) + S("storage") + S("x") + S(c.vertexNum-1);
		string sy0 =  S(c.name) + S("storage") + S("y") + S(0);
		string syn =  S(c.name) + S("storage") + S("y") + S(c.vertexNum-1);

		string ex0 =  S(c.name) + S("end") + S("x") + S(0);
		string exn =  S(c.name) + S("end") + S("x") + S(c.vertexNum-1);
		string ey0 =  S(c.name) + S("end") + S("y") + S(0);
		string eyn =  S(c.name) + S("end") + S("y") + S(c.vertexNum-1);

		string d0x = S(d0->name) + S("x");
		string d0y = S(d0->name) + S("y");
		string d1x = S(d1->name) + S("x");
		string d1y = S(d1->name) + S("y");

		string d0Port0X = S(d0->name)+S("Port0X");
		string d0Port0Y = S(d0->name)+S("Port0Y");
		string d0Port1X = S(d0->name)+S("Port1X");
		string d0Port1Y = S(d0->name)+S("Port1Y");

		string d1Port0X = S(d1->name)+S("Port0X");
		string d1Port0Y = S(d1->name)+S("Port0Y");
		string d1Port1X = S(d1->name)+S("Port1X");
		string d1Port1Y = S(d1->name)+S("Port1Y");


		string channelStartDevicePort0 = c.name + S("Start") + d0->name + S("Port0");
		varName.push_back(channelStartDevicePort0);varType.push_back("1");
		string channelStartDevicePort1 = c.name + S("Start") + d0->name + S("Port1");
		varName.push_back(channelStartDevicePort1);varType.push_back("1");
		string channelEndDevicePort0 = c.name + S("End") + d1->name + S("Port0");
		varName.push_back(channelEndDevicePort0);varType.push_back("1");
		string channelEndDevicePort1 = c.name + S("End") + d1->name + S("Port1");
		varName.push_back(channelEndDevicePort1);varType.push_back("1");

		//if d0 != d1 then start with d0 end with d1
		if(d0->name != d1->name){

			ILP.push_back(S(fx0) + S(" - ") + S(d0Port0X) + S(" + ") + S(M) +S(" ") + channelStartDevicePort0 +S(" >= 0"));
			ILP.push_back(S(fx0) + S(" - ") + S(d0Port0X) + S(" - ") + S(M) +S(" ") + channelStartDevicePort0 +S(" <= 0"));

			ILP.push_back(S(fy0) + S(" - ") + S(d0Port0Y) + S(" + ") + S(M) +S(" ") + channelStartDevicePort0 +S(" >= 0"));
			ILP.push_back(S(fy0) + S(" - ") + S(d0Port0Y) + S(" - ") + S(M) +S(" ") + channelStartDevicePort0 +S(" <= 0"));

			ILP.push_back(S(fx0) + S(" - ") + S(d0Port1X) + S(" + ") + S(M) +S(" ") + channelStartDevicePort1 +S(" >= 0"));
			ILP.push_back(S(fx0) + S(" - ") + S(d0Port1X) + S(" - ") + S(M) +S(" ") + channelStartDevicePort1 +S(" <= 0"));

			ILP.push_back(S(fy0) + S(" - ") + S(d0Port1Y) + S(" + ") + S(M) +S(" ") + channelStartDevicePort1 +S(" >= 0"));
			ILP.push_back(S(fy0) + S(" - ") + S(d0Port1Y) + S(" - ") + S(M) +S(" ") + channelStartDevicePort1 +S(" <= 0"));
			ILP.push_back(channelStartDevicePort0 +S(" + ") + channelStartDevicePort1 + S(" = 1"));


			ILP.push_back(S(exn) + S(" - ") + S(d1Port0X) + S(" + ") + S(M) +S(" ") + channelEndDevicePort0 +S(" >= 0"));
			ILP.push_back(S(exn) + S(" - ") + S(d1Port0X) + S(" - ") + S(M) +S(" ") + channelEndDevicePort0 +S(" <= 0"));

			ILP.push_back(S(eyn) + S(" - ") + S(d1Port0Y) + S(" + ") + S(M) +S(" ") + channelEndDevicePort0 +S(" >= 0"));
			ILP.push_back(S(eyn) + S(" - ") + S(d1Port0Y) + S(" - ") + S(M) +S(" ") + channelEndDevicePort0 +S(" <= 0"));

			ILP.push_back(S(exn) + S(" - ") + S(d1Port1X) + S(" + ") + S(M) +S(" ") + channelEndDevicePort1 +S(" >= 0"));
			ILP.push_back(S(exn) + S(" - ") + S(d1Port1X) + S(" - ") + S(M) +S(" ") + channelEndDevicePort1 +S(" <= 0"));

			ILP.push_back(S(eyn) + S(" - ") + S(d1Port1Y) + S(" + ") + S(M) +S(" ") + channelEndDevicePort1 +S(" >= 0"));
			ILP.push_back(S(eyn) + S(" - ") + S(d1Port1Y) + S(" - ") + S(M) +S(" ") + channelEndDevicePort1 +S(" <= 0"));
			ILP.push_back(channelEndDevicePort0 +S(" + ") + channelEndDevicePort1 + S(" = 1"));
		}
		//else d0 == d1 then only start from d0
		{
			ILP.push_back(S(fx0) + S(" - ") + S(d0Port0X) + S(" + ") + S(M) +S(" ") + channelStartDevicePort0 +S(" >= 0"));
			ILP.push_back(S(fx0) + S(" - ") + S(d0Port0X) + S(" - ") + S(M) +S(" ") + channelStartDevicePort0 +S(" <= 0"));

			ILP.push_back(S(fy0) + S(" - ") + S(d0Port0Y) + S(" + ") + S(M) +S(" ") + channelStartDevicePort0 +S(" >= 0"));
			ILP.push_back(S(fy0) + S(" - ") + S(d0Port0Y) + S(" - ") + S(M) +S(" ") + channelStartDevicePort0 +S(" <= 0"));

			ILP.push_back(S(fx0) + S(" - ") + S(d0Port1X) + S(" + ") + S(M) +S(" ") + channelStartDevicePort1 +S(" >= 0"));
			ILP.push_back(S(fx0) + S(" - ") + S(d0Port1X) + S(" - ") + S(M) +S(" ") + channelStartDevicePort1 +S(" <= 0"));

			ILP.push_back(S(fy0) + S(" - ") + S(d0Port1Y) + S(" + ") + S(M) +S(" ") + channelStartDevicePort1 +S(" >= 0"));
			ILP.push_back(S(fy0) + S(" - ") + S(d0Port1Y) + S(" - ") + S(M) +S(" ") + channelStartDevicePort1 +S(" <= 0"));
			ILP.push_back(channelStartDevicePort0 +S(" + ") + channelStartDevicePort1 + S(" = 1"));

		}





		ILP.push_back(S(fxn) + S(" - ") + S(sx0) + S(" = 0"));
		ILP.push_back(S(fyn) + S(" - ") + S(sy0) + S(" = 0"));

		ILP.push_back(S(sxn) + S(" - ") + S(ex0) + S(" = 0"));
		ILP.push_back(S(syn) + S(" - ") + S(ey0) + S(" = 0"));



		// x1 = x0 or y1 = y0
		//first
		for(int i = 1; i<c.vertexNum; i++){
			string xPre =  S(c.name) + S("first") + S("x") + S(i-1);
			string yPre =  S(c.name) + S("first") + S("y") + S(i-1);
			string xCur =  S(c.name) + S("first") + S("x") + S(i);
			string yCur =  S(c.name) + S("first") + S("y") + S(i);

			string xEqual = S(xPre) + S("Equals") + S(xCur);varName.push_back(xEqual); varType.push_back("1");
			string yEqual = S(yPre) + S("Equals") + S(yCur);varName.push_back(yEqual); varType.push_back("1");
			// x0 - x1 - M * b <= 0 x0 - x1 + M * b >= 0
			ILP.push_back(S(xPre) + S(" - ") + xCur + S(" - ") + S(M) + S(" ")+ xEqual + S(" <= 0"));
			ILP.push_back(S(xPre) + S(" - ") + xCur + S(" + ") + S(M) + S(" ")+ xEqual + S(" >= 0"));
			ILP.push_back(S(yPre) + S(" - ") + yCur + S(" - ") + S(M) + S(" ")+ yEqual + S(" <= 0"));
			ILP.push_back(S(yPre) + S(" - ") + yCur + S(" + ") + S(M) + S(" ")+ yEqual + S(" >= 0"));
			ILP.push_back(xEqual + S(" + ") + yEqual + S(" <= 1"));
		}

		//storage
		for(int i = 1; i<c.vertexNum; i++){
			string xPre =  S(c.name) + S("storage") + S("x") + S(i-1);
			string yPre =  S(c.name) + S("storage") + S("y") + S(i-1);
			string xCur =  S(c.name) + S("storage") + S("x") + S(i);
			string yCur =  S(c.name) + S("storage") + S("y") + S(i);

			string xEqual = S(xPre) + S("Equals") + S(xCur);varName.push_back(xEqual); varType.push_back("1");
			string yEqual = S(yPre) + S("Equals") + S(yCur);varName.push_back(yEqual); varType.push_back("1");
			// x0 - x1 - M * b <= 0 x0 - x1 + M * b >= 0
			ILP.push_back(S(xPre) + S(" - ") + xCur + S(" - ") + S(M) + S(" ")+ xEqual + S(" <= 0"));
			ILP.push_back(S(xPre) + S(" - ") + xCur + S(" + ") + S(M) + S(" ")+ xEqual + S(" >= 0"));
			ILP.push_back(S(yPre) + S(" - ") + yCur + S(" - ") + S(M) + S(" ")+ yEqual + S(" <= 0"));
			ILP.push_back(S(yPre) + S(" - ") + yCur + S(" + ") + S(M) + S(" ")+ yEqual + S(" >= 0"));
			ILP.push_back(xEqual + S(" + ") + yEqual + S(" <= 1"));
		}

		//end
		for(int i = 1; i<c.vertexNum; i++){
			string xPre =  S(c.name) + S("end") + S("x") + S(i-1);
			string yPre =  S(c.name) + S("end") + S("y") + S(i-1);
			string xCur =  S(c.name) + S("end") + S("x") + S(i);
			string yCur =  S(c.name) + S("end") + S("y") + S(i);

			string xEqual = S(xPre) + S("Equals") + S(xCur);varName.push_back(xEqual); varType.push_back("1");
			string yEqual = S(yPre) + S("Equals") + S(yCur);varName.push_back(yEqual); varType.push_back("1");
			// x0 - x1 - M * b <= 0 x0 - x1 + M * b >= 0
			ILP.push_back(S(xPre) + S(" - ") + xCur + S(" - ") + S(M) + S(" ")+ xEqual + S(" <= 0"));
			ILP.push_back(S(xPre) + S(" - ") + xCur + S(" + ") + S(M) + S(" ")+ xEqual + S(" >= 0"));
			ILP.push_back(S(yPre) + S(" - ") + yCur + S(" - ") + S(M) + S(" ")+ yEqual + S(" <= 0"));
			ILP.push_back(S(yPre) + S(" - ") + yCur + S(" + ") + S(M) + S(" ")+ yEqual + S(" >= 0"));
			ILP.push_back(xEqual + S(" + ") + yEqual + S(" <= 1"));
		}

	}

	//channels cannot cross with itself

	for(Channel c:channels){

		//for a new vertex, it will grow a new edge
		//the new edge cannot cross any old edge
		for(int i = 2; i<=3*(c.vertexNum -1) ; i++){

			for(int j = 1; j <= i-1;j++){

				//vertex from the seg before
				string x0 = getVertexNameX(c,j-1);
				string y0 = getVertexNameY(c,j-1);
				string x1 = getVertexNameX(c,j);
				string y1 = getVertexNameY(c,j);

				//vertex from this seg
				string x2 = getVertexNameX(c,i-1);
				string y2 = getVertexNameY(c,i-1);
				string x3 = getVertexNameX(c,i);
				string y3 = getVertexNameY(c,i);


				string seg1Name = getSegName(c,i);
				string seg0Name = getSegName(c,j);

				//binary

				string seg0ConnectSeg1 = seg0Name+S("Connect")+seg1Name;
				varName.push_back(seg0ConnectSeg1); varType.push_back("1");


				//the first node of seg1 is the second node of seg0
				// the second node of seg0 is not on the  seg0
				/*
				 * x0y0 x1y1 x2y2 x3y3
				 * if x1 == x2 and y1 == y2
				 * 		if y0 == y1
				 * 			if x0 < x1
				 * 			then x3 == x2
				 * 				or y3 == y2 && x3 > x2
				 * translated
				 * !(x1 == x2 && y1 == y2 && y0 == y1 && x0 < x1 ) or x3 == x2 or (y3 == y2 && x2 >x1)
				 * => x1 < x2 or x1 > x2 or y1 < y2 or y1>y2 or y0 > y1 or y0< y1 or x0 >= x1 or x3 == x2 or (y3 == y2 && x2 > x1)
				 */

				//x1 < x2 or x1 >x2
				string x1Lessx2 = x1 + S("Less") + x2; varName.push_back(x1Lessx2); varType.push_back("1");
				string x1Biggerx2 = x1 + S("Bigger") + x2;varName.push_back(x1Biggerx2); varType.push_back("1");


				//if b = 0 then x1 < x2
				//if b = 1 then x1 >= x2
				//x1 - x2 + M(1-b) > =0
				// x1 - x2 - M *b >= -M
				ILP.push_back(x1 + S(" - ") + x2 + S(" - ")+ S(M) + S(" ") + x1Lessx2 + S(" <= -1"));
				ILP.push_back(x1 + S(" - ") + x2 + S(" - ") + S(M) + S(" ") + x1Lessx2 + S(" >= ") + S(-M));
				//ILP.push_back()

				//if b = 0 then x1 > x2
				//if b = 1 then x1 <= x2
				//x1 - x2 + M(1-b) <= 0
				// x1 - x2 - M *b <= -M
				ILP.push_back(x1 + S(" - ") + x2 + S(" + ")+ S(M) + S(" ") + x1Biggerx2 + S(" >= 1"));
				ILP.push_back(x1 + S(" - ") + x2 + S(" - ") + S(M) + S(" ") + x1Biggerx2 + S(" <= ") + S(-M));
				// y1 < y2 or y1 > y2
				string y1Lessy2 = y1 + S("Less") + y2; varName.push_back(y1Lessy2); varType.push_back("1");
				string y1Biggery2 = y1 + S("Bigger") + y2;varName.push_back(y1Biggery2); varType.push_back("1");
				ILP.push_back(y1 + S(" - ") + y2 + S(" - ")+ S(M) + S(" ") + y1Lessy2 + S(" <= -1"));
				ILP.push_back(y1 + S(" - ") + y2 + S(" - ") + S(M) + S(" ") + y1Lessy2 + S(" >= ") + S(-M));
				ILP.push_back(y1 + S(" - ") + y2 + S(" + ")+ S(M) + S(" ") + y1Biggery2 + S(" >= 1"));
				ILP.push_back(y1 + S(" - ") + y2 + S(" - ") + S(M) + S(" ") + y1Biggery2 + S(" <= ") + S(-M));

				// y0 < y1 or y0>y1
				string y0Lessy1 = y0 + S("Less") + y1; varName.push_back(y0Lessy1); varType.push_back("1");
				string y0Biggery1 = y0 + S("Bigger") + y1;varName.push_back(y0Biggery1); varType.push_back("1");
				ILP.push_back(y0 + S(" - ") + y1 + S(" - ")+ S(M) + S(" ") + y0Lessy1 + S(" <= -1"));
				ILP.push_back(y0 + S(" - ") + y1+ S(" + ") + S(M) + S(" ") + y0Biggery1 + S(" >= 1"));
				// x0 <= x1
				string x0BiggerEqualx1 = x0 + S("BiggerEqual") + x1;varName.push_back(x0BiggerEqualx1); varType.push_back("1");
				ILP.push_back(x0 + S(" - ") + x1 + S(" + ") +  S(M) + S(" ")+ x0BiggerEqualx1 + S(" >= 0"));

				// x3 == x2
				string x2Equalx3 = x2 + S("Equal") + x3; varName.push_back(x2Equalx3); varType.push_back("1");
				ILP.push_back(x2 + S(" - ") + x3 + S(" - ") + S(M) + S(" ") + x2Equalx3 + S(" <= 0"));
				ILP.push_back(x2 + S(" - ") + x3 + S(" + ") + S(M) + S(" ") + x2Equalx3 + S(" >= 0"));
				//y2 == y3 && x2 < x3
				string y2Equaly3 = y2 + S("Equal") + y3;
				varName.push_back(y2Equaly3); varType.push_back("1");
				string x2Lessx3 = x2 + S("Less") + x3;
				varName.push_back(x2Lessx3); varType.push_back("1");

				ILP.push_back(y2 + S(" - ") + y3 + S(" - ") + S(M) + S(" ") + y2Equaly3 + S(" <= 0"));
				ILP.push_back(y2 + S(" - ") + y3 + S(" + ") + S(M) + S(" ") + y2Equaly3 + S(" >= 0"));
				ILP.push_back(x2 + S(" - ") + x3 + S(" - ") + S(M) + S(" ") + x2Lessx3 +S(" <= -1"));
				// at least one of them is true y2==y3
				ILP.push_back(x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" + ")
						+ y0Lessy1 + S(" + ")+ y0Biggery1+ S(" + ") + x0BiggerEqualx1 + S(" + ") + x2Equalx3+ S(" + ") + y2Equaly3+ S(" <= 8"));
				// && x2<x3
				ILP.push_back(x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" + ")
										+ y0Lessy1 + S(" + ")+ y0Biggery1+ S(" + ") + x0BiggerEqualx1 + S(" + ") + x2Equalx3+ S(" + ") + x2Lessx3+ S(" <= 8"));

				//decide if seg0 and seg1 are connected
				// seg0Connectedseg1 =1 means disconnect = (!x1lessx2 or !x1Biggerx2 or !y1Lessy2 or !y1Biggery2)
				// seg0Connectedseg1 <=(1-a) + (1-b) + (1-c) + (1-d) =  aka a+b+c+d + seg0Connectedseg1 <= 4
				//seg0 >= (1-a) seg0 >= (1-b) ...
				ILP.push_back(seg0ConnectSeg1 + S(" + ") + x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" <= 4"));
				ILP.push_back(seg0ConnectSeg1 + S(" + ") + x1Lessx2 + S(" >= 1"));
				ILP.push_back(seg0ConnectSeg1 + S(" + ") + x1Biggerx2 + S(" >= 1"));
				ILP.push_back(seg0ConnectSeg1 + S(" + ") + y1Lessy2 + S(" >= 1"));
				ILP.push_back(seg0ConnectSeg1 + S(" + ") + y1Biggery2+ S(" >= 1"));


				/*
				 * x0y0 x1y1 x2y2 x3y3
				 * if x1 == x2 and y1 == y2
				 * 		if y0 == y1
				 * 			if x0 > x1
				 * 			then x3 == x2
				 * 				or y3 == y2 && x3 < x2
				 * translated
				 * !(x1 == x2 && y1 == y2 && y0 == y1 && x0 > x1) or x3 == x2 or (y3 == y2 && x3 <x2)
				 * => x1 < x2 or x1 > x2 or y1 < y2 or y1>y2 or y0 > y1 or y0< y1 or  x0 <= x1 or  x3 == x2 or (y3 == y2 && x3 < x2)
				 */

				// x0 <= x1
				string x0LessEqualx1 = x0 + S("LessEqual") + x1;varName.push_back(x0LessEqualx1); varType.push_back("1");
				ILP.push_back(x0 + S(" - ") + x1 + S(" - ") +  S(M) + S(" ") + x0LessEqualx1 + S(" <= 0"));
				//y2 == y3 && x2 > x3

				string x2Biggerx3 = x2 + S("Bigger") + x3;
				varName.push_back(x2Biggerx3); varType.push_back("1");


				ILP.push_back(x2 + S(" - ") + x3 + S(" + ") + S(M) + S(" ") + x2Biggerx3 +S(" >= 1"));
				// at least one of them is true
				ILP.push_back(x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" + ")
									+ y0Lessy1 + S(" + ")+ y0Biggery1+ S(" + ") + x0LessEqualx1 + S(" + ") + x2Equalx3+ S(" + ") + y2Equaly3+ S(" <= 8"));
				ILP.push_back(x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" + ")
						+ y0Lessy1 + S(" + ")+ y0Biggery1+ S(" + ") + x0LessEqualx1 + S(" + ") + x2Equalx3+ S(" + ") + x2Biggerx3+ S(" <= 8"));

				/*
				 * x0y0 x1y1 x2y2 x3y3
				 * if x1 == x2 and y1 == y2
				 * 		if x0 == x1
				 * 			if y0 < y1
				 * 			then y2 == y3
				 * 				or x2 == x3 && y2 < y3
				 * translated
				 * !(x1 == x2 && y1 == y2 && x0 == x1 && y0 < y1) or y2 == y3 or (x2 == x3 && y2 < y3)
				 * => x1 < x2 or x1 > x2 or y1 < y2 or y1>y2 or x0 > x1 or x0< x1 or  y0 >= y1 or  y2 == y3 or (x2 == x3 && y2 < y3)
				 */
				// x0 > x1 or x0 < x1
				string x0Biggerx1 = x0 + S("Bigger") + x1;varName.push_back(x0Biggerx1); varType.push_back("1");
				string x0Lessx1= x0 + S("Less") + x1;varName.push_back(x0Lessx1); varType.push_back("1");
				ILP.push_back(x0 + S(" - ") + x1 + S(" + ") + S(M) + S(" ") + x0Biggerx1 + S(" >= 1"));
				ILP.push_back(x0 + S(" - ") + x1 + S(" - ") + S(M) + S(" ") + x0Lessx1 + S(" <= -1"));

				// y0 >= y1
				string y0BiggerEqualy1 = y0 + S("BiggerEqual") + y1; varName.push_back(y0BiggerEqualy1); varType.push_back("1");
				ILP.push_back(y0 + S(" - ") + y1 + S(" + ") + S(M) + S(" ") + y0BiggerEqualy1 + S(" >= 0"));



				// y2 < y3
				string y2Lessy3 = y2 + S("Less") + y3; varName.push_back(y2Lessy3); varType.push_back("1");
				ILP.push_back(y2 + S(" - ") + y3 + S(" - ") + S(M) + S(" ") + y2Lessy3 + S(" <= -1"));
				// at least one of them is true
				ILP.push_back(x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" + ")
									+ x0Biggerx1 + S(" + ")+ x0Lessx1+ S(" + ") + y0BiggerEqualy1 + S(" + ") + y2Equaly3+ S(" + ") + x2Equalx3+ S(" <= 8"));
				ILP.push_back(x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" + ")
									+ x0Biggerx1 + S(" + ")+ x0Lessx1+ S(" + ") + y0BiggerEqualy1 + S(" + ") + y2Equaly3+ S(" + ") + y2Lessy3+ S(" <= 8"));


				/*
				 * x0y0 x1y1 x2y2 x3y3
				 * if x1 == x2 and y1 == y2
				 * 		if x0 == x1
				 * 			if y0 > y1
				 * 			then y2 == y3
				 * 				or x2 == x3 && y2 > y3
				 * translated
				 * !(x1 == x2 && y1 == y2 && x0 == x1 && y0 > y1) or y2 == y3 or (x2 == x3 && y2 > y3)
				 * => x1 < x2 or x1 > x2 or y1 < y2 or y1>y2 or x0 > x1 or x0< x1 or  y0 <= y1 or  y2 == y3 or (x2 == x3 && y2 > y3)
				 */
				// y0 >= y1
				string y0LessEqualy1 = y0 + S("LessEqual") + y1; varName.push_back(y0LessEqualy1); varType.push_back("1");
				ILP.push_back(y0 + S(" - ") + y1 + S(" - ") + S(M) + S(" ") + y0LessEqualy1 + S(" <= 0"));
				// y2 > y3
				string y2Biggery3= y2 + S("Bigger") + y3; varName.push_back(y2Biggery3); varType.push_back("1");
				ILP.push_back(y2 + S(" - ") + y3 + S(" + ") + S(M) + S(" ") + y2Lessy3 + S(" >= 1"));

				ILP.push_back(x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" + ")
							+ x0Biggerx1 + S(" + ")+ x0Lessx1+ S(" + ") + y0LessEqualy1 + S(" + ") + y2Equaly3+ S(" + ") + x2Equalx3+ S(" <= 8"));
				ILP.push_back(x1Lessx2 + S(" + ") + x1Biggerx2 + S(" + ") + y1Lessy2 + S(" + ") + y1Biggery2 + S(" + ")
							+ x0Biggerx1 + S(" + ")+ x0Lessx1+ S(" + ") + y0LessEqualy1 + S(" + ") + y2Equaly3+ S(" + ") + y2Biggery3+ S(" <= 8"));



				//two segs do not cross at all

				string up = seg1Name +  S("Up")  + seg0Name;
				varName.push_back(up); varType.push_back("1");
				string down = seg1Name +  S("Down") + seg0Name;
				varName.push_back(down); varType.push_back("1");
				string left = seg1Name +  S("Left") + seg0Name;
				varName.push_back(left); varType.push_back("1");
				string right = seg1Name +  S("Right") + seg0Name;
				varName.push_back(right); varType.push_back("1");

				//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
				ILP.push_back(y0 + S(" - ") + y2 +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
				ILP.push_back(y0 + S(" - ") + y3 +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
				ILP.push_back(y1 + S(" - ") + y2 +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));
				ILP.push_back(y1 + S(" - ") + y3 +S(" + ") + S(M) + S(" ") + up +  S(" >= 1"));

				//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
				ILP.push_back(y0 + S(" - ") + y2 +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
				ILP.push_back(y0 + S(" - ") + y3 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
				ILP.push_back(y1 + S(" - ") + y2 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
				ILP.push_back(y1 + S(" - ") + y3 +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

				//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
				ILP.push_back(x0 + S(" - ") + x2 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
				ILP.push_back(x0 + S(" - ") + x3 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
				ILP.push_back(x1 + S(" - ") + x2 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
				ILP.push_back(x1 + S(" - ") + x3 +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));

				//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
				ILP.push_back(x0 + S(" - ") + x2 +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
				ILP.push_back(x0 + S(" - ") + x3 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
				ILP.push_back(x1 + S(" - ") + x2 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
				ILP.push_back(x1 + S(" - ") + x3 +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));

				//if not seg0Connectseg1 then up or down or left or right
				// seg0Connectseg1 or up or down or left or right

				ILP.push_back(seg0ConnectSeg1 + S(" + ") +  up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 4"));



			}
		}

	}



	//channels cannot cross any device
	for(Channel c:channels){
		//any vertex besides firstx0 firsty0 and endxn endyn must be outside any devices
		for(Dev_ptr d:devices){
				string dx = S(d->name) + S("x");
				string dy = S(d->name) + S("y");
				string ds = S(d->name) + S("s");
				string dt = S(d->name) + S("t");

			for(int i = 1; i<=3*(c.vertexNum -1) ; i++){
				string x0 = getVertexNameX(c,i-1);
				string y0 = getVertexNameY(c,i-1);
				string x1 = getVertexNameX(c,i);
				string y1 = getVertexNameY(c,i);

				string segName = getSegName(c,i);

				string up = segName + S("Up") + d->name;varName.push_back(up); varType.push_back("1");
				string down = segName + S("Down") + d->name;varName.push_back(down); varType.push_back("1");
				string left = segName + S("Left") + d->name;varName.push_back(left); varType.push_back("1");
				string right = segName + S("Right") + d->name;varName.push_back(right); varType.push_back("1");

				//up; y0 >= t, y1 >= t
				ILP.push_back(y0 + S(" - ") + dt + S(" + ") + S(M) + S(" ")+  up + S(" >= 1"));
				ILP.push_back(y1+ S(" - ") + dt + S(" + ") + S(M) + S(" ")+  up + S(" >= 1"));
				//down; y0 <= y, y1 <= t
				ILP.push_back(y0 + S(" - ") + dy + S(" - ") + S(M) + S(" ")+  down+ S(" <= -1"));
				ILP.push_back(y1+ S(" - ") + dy + S(" - ") + S(M) + S(" ")+  down + S(" <= -1"));
				//left; x0 <= x, x1 <= x
				ILP.push_back(x0 + S(" - ") + dx+ S(" - ") + S(M) + S(" ")+  left + S(" <= -1"));
				ILP.push_back(x1+ S(" - ") + dx + S(" - ") + S(M) + S(" ")+  left + S(" <= -1"));
				//right; x>= s, x1 >= s
				ILP.push_back(x0 + S(" - ") + ds + S(" + ") + S(M) + S(" ")+  right + S(" >= 1"));
				ILP.push_back(x1+ S(" - ") + ds + S(" + ") + S(M) + S(" ")+  right + S(" >= 1"));

				ILP.push_back(up + S(" + ") + down + S(" + ") + left+ S(" + ") + right + S(" <= 3"));

			}


		}

	}

	//channels storage >= liquidsize

	for(Channel c:channels){
		for(int i = c.vertexNum; i<=2*(c.vertexNum-1);i++){
			string x0 = getVertexNameX(c,i-1);
			string y0 = getVertexNameY(c,i-1);
			string x1 = getVertexNameX(c,i);
			string y1 = getVertexNameY(c,i);
			string v1RightUpx0 = c.name + S("Store")+S("v") + S(i-1) + S("RightUp") + S("v") + S(i);
			varName.push_back(v1RightUpx0); varType.push_back("1");

			//x1 + y1 - x0 - y0 >= liquidsize or x1+y1 - x0 -y <= -liquidSize
			ILP.push_back(x1 + S(" + ") + y1 + S(" - ") + x0 + S(" - ") + y0 +  S(" + ")+ S(M) + S(" ") + v1RightUpx0 +S( " >= ") + S(LIQUIDESIZE));
			// v -(1-b)M  <= -const v + Mb <= const +M
			ILP.push_back(x1 + S(" + ") + y1 + S(" - ") + x0 + S(" - ") + y0 +  S(" + ")+S(M) + S(" ") + v1RightUpx0 +S( " <= ") + S(-LIQUIDESIZE + M));
		}
	}



}



void Plate::devicePlacementConstraint()
{



	//Device cannot cross with each other

		string x0,y0,s0,t0;
		string x1,y1,s1,t1;
		string b0,b1,b2,b3;
		string port0X,port0Y,port1X,port1Y;
		stringstream ss;

		for(int i = 0; i < devices.size();i++){
			Dev_ptr d0 = devices.at(i);
			//push binaries name into vector
			x0 = S(d0->name) + S("x");
			y0 = S(d0->name) + S("y");
			s0 = S(d0->name) + S("s");
			t0 = S(d0->name) + S("t");



			varName.push_back(x0); varType.push_back("0");
			varName.push_back(y0); varType.push_back("0");
			varName.push_back(s0); varType.push_back("0");
			varName.push_back(t0); varType.push_back("0");

			port0X = S(d0->name)+S("Port0X");
			port0Y = S(d0->name)+S("Port0Y");
			port1X = S(d0->name)+S("Port1X");
			port1Y = S(d0->name)+S("Port1Y");
			varName.push_back(port0X); varType.push_back("0");
			varName.push_back(port0Y); varType.push_back("0");




			//set x y s t boundry
			bounds.push_back(S("0 <= ") + x0 + S(" <= ") + S(CHIPSIZE));
			bounds.push_back(S("0 <= ") + y0 + S(" <= ") + S(CHIPSIZE));
			bounds.push_back(S("0 <= ") + s0 + S(" <= ") + S(CHIPSIZE));
			bounds.push_back(S("0 <= ") + t0 + S(" <= ") + S(CHIPSIZE));



			for(int j = i+1; j<devices.size();j++){
				Dev_ptr d1 = devices.at(j);
				b0  = S(d0->name) + S("R") + S(d1->name);
				b1  = S(d0->name) + S("L") + S(d1->name);
				b2  = S(d0->name) + S("U" ) + S(d1->name);
				b3  = S(d0->name) + S("D") + S(d1->name);
				varName.push_back(b0); varType.push_back("1");
				varName.push_back(b1); varType.push_back("1");
				varName.push_back(b2); varType.push_back("1");
				varName.push_back(b3); varType.push_back("1");

			}
		}

		for(int i = 0; i < devices.size();i++){
			Dev_ptr d0 = devices.at(i);

			x0 = S(d0->name) + S("x");
			y0 = S(d0->name) + S("y");
			s0 = S(d0->name) + S("s");
			t0 = S(d0->name) + S("t");
			string seedX  = d0->name + S("seedX"); varName.push_back(seedX); varType.push_back("0");
			string seedY =  d0->name + S("seedY"); varName.push_back(seedY); varType.push_back("0");
			port0X = S(d0->name)+S("Port0X");
			port0Y = S(d0->name)+S("Port0Y");
			port1X = S(d0->name)+S("Port1X");
			port1Y = S(d0->name)+S("Port1Y");
			//x0 = 3*seedx
			//x1 = 3*seedy
			//x0 + size= s0, y0 + size = t0
			//x1 + size = s1, y0 + size = t1


			//ILP.push_back(x0 + S(" - ") + S(3) + S(" ") + seedX + S(" = 0"));
			//ILP.push_back(y0 + S(" - ") + S(3) + S(" ") + seedY + S(" = 0"));
			ILP.push_back(S(s0) + S(" - ") + S(x0) + S(" = ") +S(d0->sizeX) );
			ILP.push_back(S(t0) + S(" - ") + S(y0) + S(" = ") +S(d0->sizeY) );
			ILP.push_back(S(port0X) + S(" - ") + S(x0) + S(" = ") +S(d0->sizeX/2));
			ILP.push_back(S(port0Y) + S(" - ") + S(y0) + S(" = -1 "));
			ILP.push_back(S(port1X) + S(" - ") + S(s0) + S(" = ") +S(-d0->sizeX/2));
			ILP.push_back(S(port1Y) + S(" - ") + S(t0) + S(" = 1 "));


			for(int j = i+1; j<devices.size();j++){
				Dev_ptr d1 = devices.at(j);




				x1 = S(d1->name) + S("x");
				y1 = S(d1->name) + S("y");
				s1 = S(d1->name) + S("s");
				t1 = S(d1->name) + S("t");


				//4 binaries to depict the location of 2 devices
				b0  = S(d0->name) + S("R") + S(d1->name);
				b1  = S(d0->name) + S("L") + S(d1->name);
				b2  = S(d0->name) + S("U" ) + S(d1->name);
				b3  = S(d0->name) + S("D") + S(d1->name);







				//x1 >= s0 or y1 >= t0
				//or x0 >= s1 or y0> = t1;
				// x0 - s1 + M*B0 >= 0
				// y0 - t1 + M*B1 >= 0
				// x1 - s0 + M*B2 >= 0
				// y1 - t0 + M*B3 >= 0
				// B0 + B1 + B2 + B3 = 3

				ILP.push_back(S(x0) + S(" - ") + S(s1) + S(" + ")+ S(M) + S(" ") + S(b0) + S(" >= 1"));
				ILP.push_back(S(y0) + S(" - ") + S(t1) + S(" + ")+S(M) + S(" ") + S(b1) + S(" >= 1"));
				ILP.push_back(S(x1) + S(" - ") + S(s0) + S(" + ")+S(M) + S(" ") + S(b2) + S(" >= 1"));
				ILP.push_back(S(y1) + S(" - ") + S(t0) + S(" + ")+S(M) + S(" ") + S(b3) + S(" >= 1"));
				ILP.push_back(S(b0) + S(" + ") + S(b1) + S(" + ") + S(b2) + S(" + ") + S(b3) +  S(" = 3"));



			}
		}





		//Channels cannot cross with Devices


	//storage >= size of Operation


}

void Plate::setChannelsTime()
{
	channels.clear();
	//for each parent of each Operation, generate 3 Channel, in/out/storage
	for(Op_ptr childs:operations)
	{

		Dev_ptr childDevice = childs->bindDevice;
		for(Op_ptr parent:childs->parents){
			Channel c;
			Dev_ptr fatherDevice = childs->bindDevice;
			//tmpChannel leftEnd,rightEnd;
			//storage store;


			c.ends[0] = fatherDevice;
			c.ends[1] = childDevice;
			c.startTime = parent->endTime;
			c.endTime = childs->startTime;
			c.fatherOp = parent;
			c.childOp = childs;

			c.name = S("c") + S(parent->name) + S(childs->name);

			channels.push_back(c);

		}

	}
}


#endif


//dead code for calculating valves

//horizontal valves
	/*string obj;
	for(int i = 0; i <= CHIPSIZE-1;i++){
		int vx0 = i;
		int vx1 = i+1;
		for(int j = 0; j <= CHIPSIZE;j++){
			int vy0 = j;
			int vy1 = j;
			string valveName = valveNameStr(vx0,vy0,vx1,vy1);
			string valveUsed = valveUsedStr(valveName);
			string valveAlongChannel = valveAlongChannelStr(valveName);
			string valveInChannel = valveInChannelStr(valveName);
			varName.push_back(valveAlongChannel);varType.push_back("1");
			varName.push_back(valveInChannel);varType.push_back("1");
			varName.push_back(valveUsed);varType.push_back("1");
			//valveUsed = 0 when valveInChannel = 0 && valveAlongChannel = 0
			//valveUsed <= valveInChannel + vavleAlongChannel
			ILP.push_back(valveInChannel + S(" + ") + valveAlongChannel + S(" - ") + valveUsed + S(" >= 0"));
			 obj += S(" + ") + valveUsed;


			for(Channel c:channels){



				//valve along channel
				for(int i = 1; i <= 3*(c.vertexNum-1);i++){

					string segName = getSegName(c,i);
					string segx0 = getVertexNameX(c,i-1);
					string segy0 = getVertexNameY(c,i-1);
					string segx1 = getVertexNameX(c,i);
					string segy1 = getVertexNameY(c,i);
					//type1 when valve is under the channel
					//type1 seg.y0 = seg.y1 = v.y  and seg.x0 == v.x0
					//binary
					string segy0EqualsVy = segy0 + S("Equals") + valveName + S("y");
					string segy1EqualsVy = segy1 + S("Equals") + valveName + S("y");
					string segx0EqualsVx0 = segx0 + S("Equals") + valveName + S("x0");

					string segy0LessVy = segy0 + S("Less") + valveName + S("y");
					string segy1LessVy = segy1 + S("Less") + valveName + S("y");
					string segx0LessVx0 = segx0 + S("Less") + valveName + S("x0");
					string segy0BiggerVy = segy0 + S("Bigger") + valveName + S("y");
					string segy1BiggerVy = segy1 + S("Bigger") + valveName + S("y");
					string segx0BiggerVx0 = segx0 + S("Bigger") + valveName + S("x0");
					varName.push_back(segy0LessVy);varType.push_back("1");
					varName.push_back(segy1LessVy);varType.push_back("1");
					varName.push_back(segx0LessVx0);varType.push_back("1");
					varName.push_back(segy0BiggerVy);varType.push_back("1");
					varName.push_back(segy1BiggerVy);varType.push_back("1");
					varName.push_back(segx0BiggerVx0);varType.push_back("1");




					//if segy0 = v.y then b = 0
					// segy0 < v.y or segy0 > v.y or b = 0 one of them must hold true

					ILP.push_back(segy0 + S(" + ") + S(M) + S(" ") + segy0BiggerVy + S(" >= ") + S(vy0+1));
					ILP.push_back(segy0 + S(" - ") + S(M) + S(" ") + segy0LessVy + S(" <= ") + S(vy0-1));
					//one of them must hold true;
					ILP.push_back(segy0BiggerVy + S(" + ") + segy0LessVy + S(" + ") + segy0EqualsVy + S(" <= 2"));

					//if segy1 = v.y then b = 0
					// segy1 < v.y or segy1 > v.y or b = 0 one of them must hold true
					ILP.push_back(segy1 + S(" + ") + S(M) + S(" ") + segy1BiggerVy + S(" >= ") + S(vy0+1));
					ILP.push_back(segy1 + S(" - ") + S(M) + S(" ") + segy1LessVy + S(" <= ") + S(vy0-1));
					//one of them must hold true;
					ILP.push_back(segy1BiggerVy + S(" + ") + segy1LessVy + S(" + ") + segy1EqualsVy + S(" <= 2"));



					//if segx0 = v.y then b = 0
					// segx0 < v.y or segx0 > v.y or b = 0 one of them must hold true
					ILP.push_back(segx0 + S(" + ") + S(M) + S(" ") + segx0BiggerVx0 + S(" >= ") + S(vx0+1));
					ILP.push_back(segx0 + S(" - ") + S(M) + S(" ") + segx0LessVx0 + S(" <= ") + S(vx0-1));
					//one of them must hold true;
					ILP.push_back(segx0BiggerVx0 + S(" + ") + segx0LessVx0 + S(" + ") + segx0EqualsVx0 + S(" <= 2"));
					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVy + S(" + ") + segy1EqualsVy  + S(" + ") + segx0EqualsVx0 + S(" -  ")  + valveAlongChannel + S(" >= 0"));

					//-------  or seg.x1 == v.x0 ---------
					string segx1EqualsVx0 = segx1 + S("Equals") + valveName + S("x0");
					varName.push_back(segx1EqualsVx0);varType.push_back("1");
					string segx1LessVx0 = segx1 + S("Less") + valveName + S("x0");
					varName.push_back(segx1LessVx0);varType.push_back("1");
					string segx1BiggerVx0 = segx1 + S("Bigger") + valveName + S("x0");
					varName.push_back(segx1BiggerVx0);varType.push_back("1");

					//if segx1 = v.x0 then b = 0
					// segx1 < v.x0 or segx1 > v.x0 or b = 0 one of them must hold true
					ILP.push_back(segx1 + S(" + ") + S(M) + S(" ") + segx1BiggerVx0 + S(" >= ") + S(vx0+1));
					ILP.push_back(segx1 + S(" - ") + S(M) + S(" ") + segx1LessVx0 + S(" <= ") + S(vx0-1));
					//one of them must hold true;
					ILP.push_back(segx1BiggerVx0 + S(" + ") + segx1LessVx0 + S(" + ") + segx1EqualsVx0 + S(" <= 2"));
					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVy + S(" + ") + segy1EqualsVy  + S(" + ") + segx1EqualsVx0 + S(" -  ")  + valveAlongChannel + S(" >= 0"));

					//------- or seg.x0 < v.x0 seg.x1 > v.x1

					string segx1BiggerVx1 = segx1 + S("Bigger") + valveName + S("x1");

					varName.push_back(segx1BiggerVx1);varType.push_back("1");
					// if seg.x0 <= v.x0 then b = 0
					// => seg.x0 - v.x0 + M*(1-b) >= 0
					//=> seg.x0 - M*b >= v.x0 - M
					ILP.push_back(segx0 + S(" - ") + S(M) + S(" ") + segx0LessVx0 + S(" >= ") + S(vx0 - M));
					//if seg.x1 >= v.x1 then b = 0
					// => seg.x1 - v.x1 - M*(1-b) <= 0
					// => seg.x1 + M*b <= v.x1 + M
					ILP.push_back(segx1 + S(" + ") + S(M) + S(" ") + segx1BiggerVx1 + S(" <= ") + S(vx1 + M));

					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVy + S(" + ") + segy1EqualsVy  + S(" + ") + segx0LessVx0 + S(" + ") + segx1BiggerVx1 + S(" -  ")  + valveAlongChannel + S(" >= 0"));

					//------- or seg.x1 <= v.x0 seg.x0 >= v.x1

					string segx0BiggerVx1 = segx0 + S("Bigger") + valveName + S("x1");

					varName.push_back(segx0BiggerVx1);varType.push_back("1");
					// if seg.x1 <= v.x0 then b = 0
					// => seg.x1 - v.x0 + M*(1-b) >= 0
					//=> seg.x1 - M*b >= v.x0 - M
					ILP.push_back(segx1 + S(" - ") + S(M) + S(" ") + segx1LessVx0 + S(" >= ") + S(vx0 - M));
					//if seg.x0 >= v.x1 then b = 0
					// => seg.x0 - v.x1 - M*(1-b) <= 0
					// => seg.x0 + M*b <= v.x1 + M
					ILP.push_back(segx0 + S(" + ") + S(M) + S(" ") + segx0BiggerVx1 + S(" <= ") + S(vx1 + M));

					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVy + S(" + ") + segy1EqualsVy  + S(" + ") + segx1LessVx0 + S(" + ") + segx0BiggerVx1 + S(" -  ")  + valveAlongChannel + S(" >= 0"));




					// or valve is at end of a seg when seg is vertical
					// segx0 = segx1 = v.x and segy0 = v.y
					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVy + S(" + ") + segx0EqualsVx0 + S(" + ") + segx1EqualsVx0 + S(" -  ")  + valveAlongChannel + S(" >= 0"));
					//or segy1 = v.y
					ILP.push_back(segy1EqualsVy + S(" + ") + segx0EqualsVx0 + S(" + ") + segx1EqualsVx0 + S(" -  ")  + valveAlongChannel + S(" >= 0"));



					//type2 valve is up from channel
					//type1 seg.y0 = seg.y1 = v.y+1  and seg.x0 == v.x0
					string segy0EqualsVyPlus1 = segy0 + S("Equals") + valveName + S("yPlus1");
					string segy1EqualsVyPlus1 = segy1 + S("Equals") + valveName + S("yPlus1");


					string segy0LessVyPlus1 = segy0 + S("Less") + valveName + S("yPlus1");
					string segy1LessVyPlus1 = segy1 + S("Less") + valveName + S("yPlus1");

					string segy0BiggerVyPlus1 = segy0 + S("Bigger") + valveName + S("yPlus1");
					string segy1BiggerVyPlus1 = segy1 + S("Bigger") + valveName + S("yPlus1");

					varName.push_back(segy0EqualsVyPlus1);varType.push_back("1");
					varName.push_back(segy1EqualsVyPlus1);varType.push_back("1");
					varName.push_back(segy0LessVyPlus1);varType.push_back("1");
					varName.push_back(segy1LessVyPlus1);varType.push_back("1");
					varName.push_back(segy0BiggerVyPlus1);varType.push_back("1");
					varName.push_back(segy1BiggerVyPlus1);varType.push_back("1");





					//if segy0 = v.y then b = 0
					// segy0 < v.y or segy0 > v.y or b = 0 one of them must hold true

					ILP.push_back(segy0 + S(" + ") + S(M) + S(" ") + segy0BiggerVy + S(" >= ") + S(vy0+1));
					ILP.push_back(segy0 + S(" - ") + S(M) + S(" ") + segy0LessVy + S(" <= ") + S(vy0-1));
					//one of them must hold true;
					ILP.push_back(segy0BiggerVy + S(" + ") + segy0LessVy + S(" + ") + segy0EqualsVy + S(" <= 2"));

					//if segy1 = v.y then b = 0
					// segy1 < v.y or segy1 > v.y or b = 0 one of them must hold true
					ILP.push_back(segy1 + S(" + ") + S(M) + S(" ") + segy1BiggerVy + S(" >= ") + S(vy0+1));
					ILP.push_back(segy1 + S(" - ") + S(M) + S(" ") + segy1LessVy + S(" <= ") + S(vy0-1));
					//one of them must hold true;
					ILP.push_back(segy1BiggerVy + S(" + ") + segy1LessVy + S(" + ") + segy1EqualsVy + S(" <= 2"));


					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVyPlus1 + S(" + ") + segy1EqualsVyPlus1  + S(" + ") + segx0EqualsVx0 + S(" -  ")  + valveAlongChannel + S(" >= 0"));

					//-------  or seg.x1 == v.x0 ---------


					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVyPlus1 + S(" + ") + segy1EqualsVyPlus1  + S(" + ") + segx1EqualsVx0 + S(" -  ")  + valveAlongChannel + S(" >= 0"));

					//------- or seg.x0 <= v.x0 seg.x1 >= v.x1



					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVyPlus1 + S(" + ") + segy1EqualsVyPlus1  + S(" + ") + segx0LessVx0 + S(" + ") + segx1BiggerVx1 + S(" -  ")  + valveAlongChannel + S(" >= 0"));

					//------- or seg.x1 <= v.x0 seg.x0 >= v.x1


					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVyPlus1 + S(" + ") + segy1EqualsVyPlus1  + S(" + ") + segx1LessVx0 + S(" + ") + segx0BiggerVx1 + S(" -  ")  + valveAlongChannel + S(" >= 0"));




					// or valve is at end of a seg when seg is vertical
					// segx0 = segx1 = v.x and segy0 = v.y
					//if the conditions above are all true, valve is along the channel
					//blong <= b0 +b1 +b2
					ILP.push_back(segy0EqualsVyPlus1 + S(" + ") + segx0EqualsVx0 + S(" + ") + segx1EqualsVx0 + S(" -  ")  + valveAlongChannel + S(" >= 0"));
					//or segy1 = v.y
					ILP.push_back(segy1EqualsVyPlus1 + S(" + ") + segx0EqualsVx0 + S(" + ") + segx1EqualsVx0 + S(" -  ")  + valveAlongChannel + S(" >= 0"));


		//------------------ see if valveInChannel----------------------------//
					//if seg.x0 = seg.x1 = v.x
					//and seg.y0 <= v.y && seg.y1 >= v.y
					// if seg.y0 <= v.y then b = 0
					// => seg.y0 - v.y + M*(1-b) >= 0
					//=> seg.y0 - M*b >= v.x0 - M
					ILP.push_back(segy0 + S(" - ") + S(M) + S(" ") + segy0LessVy + S(" >= ") + S(vy0 - M));
					//if seg.y1 >= v.y then b = 0
					// => seg.y1 - v.y - M*(1-b) <= 0
					// => seg.y1 + M*b <= v.x1 + M
					ILP.push_back(segy1 + S(" + ") + S(M) + S(" ") + segy1BiggerVy + S(" <= ") + S(vy0 + M));
					ILP.push_back(segy0LessVy + S(" + ") + segy1BiggerVy + S(" + ") + segx0EqualsVx0 + S(" + ") + segx1EqualsVx0 + S(" - ") + valveInChannel + S(" >= 0"));

					//or seg.y0 >= v.y && seg.y1 <= v.y
					// if seg.y1 <= v.y then b = 0
					// => seg.y1 - v.y + M*(1-b) >= 0
					//=> seg.y1 - M*b >= v.x0 - M
					ILP.push_back(segy1 + S(" - ") + S(M) + S(" ") + segy1LessVy + S(" >= ") + S(vy0 - M));
					//if seg.y0 >= v.y then b = 0
					// => seg.y0 - v.y - M*(1-b) <= 0
					// => seg.y0 + M*b <= v.x1 + M
					ILP.push_back(segy0 + S(" + ") + S(M) + S(" ") + segy0BiggerVy + S(" <= ") + S(vy0 + M));
					ILP.push_back(segy1LessVy + S(" + ") + segy0BiggerVy + S(" + ") + segx0EqualsVx0 + S(" + ") + segx1EqualsVx0 + S(" - ") + valveInChannel + S(" >= 0"));



				}







			}



		}
	}*/




	//vertical valves
	/*for(int i = 0; i <= CHIPSIZE;i++){
		int vy0 = i;
		int vy1 = i+1;
		for(int j = 0; j <= CHIPSIZE+1;j++){
			int vx0 = j;
			int vx1 = j;
			string valveName = valveNameStr(vx0,vy0,vx1,vy1);
			string valveUsed = valveUsedStr(valveName);
			string valveAlongChannel = valveAlongChannelStr(valveName);
			string valveInChannel = valveInChannelStr(valveName);
			varName.push_back(valveAlongChannel);varType.push_back("1");
			varName.push_back(valveInChannel);varType.push_back("1");
			varName.push_back(valveUsed);varType.push_back("1");
			//valveUsed = 0 when valveInChannel = 0 && valveAlongChannel = 0
			//valveUsed <= valveInChannel + vavleAlongChannel
			ILP.push_back(valveInChannel + S(" + ") + valveAlongChannel + S(" - ") + valveUsed + S(" >= 0"));
			obj += S(" + ") + valveUsed;

			for(Channel c:channels){






			}



		}
	}*/

//c2's storage comapre to all parts of c1 but c1's storage




		/*string c0firststart = c0.name + S("first") + S("start");
		string c0firstend = c0.name + S("first") + S("end");
		string c0storagestart = c0.name + S("storage") + S("start");
		string c0storageend = c0.name + S("storage") + S("end");
		string c0endstart = c0.name + S("end") + S("start");
		string c0endend = c0.name + S("end") + S("end");



		string c1firststart = c1.name + S("first") + S("start");
		string c1firstend = c1.name + S("first") + S("end");
		string c1storagestart = c1.name + S("storage") + S("start");
		string c1storageend = c1.name + S("storage") + S("end");
		string c1endstart = c1.name + S("end") + S("start");
		string c1endend = c1.name + S("end") + S("end");







	----------------c0 f compare with c1 f------------------------------------------


		string fftimeNoOverlap = c0.name +S("F") + c1.name+S("F") + S("timeNoOverlap");
		varName.push_back(fftimeNoOverlap); varType.push_back("1");
		string ffspaceNoOverlap = c0.name+S("F") + c1.name+S("F") + S("spaceNoOverlap");
		varName.push_back(ffspaceNoOverlap); varType.push_back("1");

		//if timeNoOverLap
		string c0FStartAfterc1FEnd = c0.name + S("FStartAfter") +c1.name  + S("FEnd");
		varName.push_back(c0FStartAfterc1FEnd); varType.push_back("1");
		string c0FEndBeforec1fEnd = c0.name + S("FEndbefore") +c1.name  + S("FStart");
		varName.push_back(c0FEndBeforec1fEnd); varType.push_back("1");
		//c0 f start > c1 fend or c0 f end < c1 f start

		ILP.push_back(c0firststart + S(" - ") + c1firstend + S(" + ") + S(M) +S(" ") + c0FStartAfterc1FEnd +   S(" >= 0"));
		ILP.push_back(c0firstend + S(" - ") + c1firststart + S(" - ") + S(M) +S(" ") + c0FEndBeforec1fEnd + S(" <= 0"));
		ILP.push_back(c0FStartAfterc1FEnd + S(" + ") + c0FEndBeforec1fEnd +S(" - ") +  S(M) + S(" ") + fftimeNoOverlap   +S(" <= 1"));
		//ILP.push_back(ffspaceNoOverlap + " = 0");


		//if spaceNoOverLap
		//c0f c1f non cross
		for(int i = 1; i < c0.vertexNum; i++){
			for(int j =1; j< c1.vertexNum; j++){
				//vertex pos
				string c0PreFvx = S(c0.name) + S("first") + S("x") + S(i-1);
				string c0PreFvy = S(c0.name) + S("first") + S("y") + S(i-1);
				string c0CurFvx = S(c0.name) + S("first") + S("x") + S(i);
				string c0CurFvy = S(c0.name) + S("first") + S("y") + S(i);

				string c1PreFvx = S(c1.name) + S("first") + S("x") + S(j-1);
				string c1PreFvy = S(c1.name) + S("first") + S("y") + S(j-1);
				string c1CurFvx = S(c1.name) + S("first") + S("x") + S(j);
				string c1CurFvy = S(c1.name) + S("first") + S("y") + S(j);

				//binary
				string up = c0.name + S("FirstSeg")+ S(i-1)+ S("Up") + c1.name + S("FirstSeg") + S(j-1);
				varName.push_back(up); varType.push_back("1");
				string down = c0.name + S("FirstSeg")+ S(i-1)+ S("Down") + c1.name + S("FirstSeg") + S(j-1);
				varName.push_back(down); varType.push_back("1");
				string left = c0.name + S("FirstSeg")+ S(i-1)+ S("Left") + c1.name + S("FirstSeg") + S(j-1);
				varName.push_back(left); varType.push_back("1");
				string right = c0.name + S("FirstSeg")+ S(i-1)+ S("Right") + c1.name + S("FirstSeg") + S(j-1);
				varName.push_back(right); varType.push_back("1");

				//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
				ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" + ") +S(M) + S(" ") + ffspaceNoOverlap + S(" >= 1"));
				ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + ffspaceNoOverlap+ S(" >= 1"));
				ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + ffspaceNoOverlap+ S(" >= 1"));
				ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + ffspaceNoOverlap+ S(" >= 1"));

				//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
				ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + ffspaceNoOverlap+ S(" <= -1"));
				ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + ffspaceNoOverlap + S(" <= -1"));
				ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + ffspaceNoOverlap + S(" <= -1"));
				ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + ffspaceNoOverlap + S(" <= -1"));

				//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
				ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + ffspaceNoOverlap + S(" >= 1"));
				ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + ffspaceNoOverlap + S(" >= 1"));
				ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + ffspaceNoOverlap + S(" >= 1"));
				ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + ffspaceNoOverlap + S(" >= 1"));

				//left c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
				ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + ffspaceNoOverlap+ S(" <= -1"));
				ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + ffspaceNoOverlap + S(" <= -1"));
				ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + ffspaceNoOverlap + S(" <= -1"));
				ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + ffspaceNoOverlap + S(" <= -1"));

				ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



			}
		}

			ILP.push_back(fftimeNoOverlap + S(" + ") + ffspaceNoOverlap + S(" <= 1") );
			ILP.push_back(ffspaceNoOverlap + S(" = 0"));




	//-------------------c0 f compare with c1 e------------------

			string fetimeNoOverlap = c0.name +S("F") + c1.name+S("E") + S("timeNoOverlap");
			varName.push_back(fetimeNoOverlap); varType.push_back("1");
			string fespaceNoOverlap = c0.name+S("F") + c1.name+S("E") + S("spaceNoOverlap");
			varName.push_back(fespaceNoOverlap); varType.push_back("1");

			//if timeNoOverLap
			string c0FStartAfterc1EEnd = c0.name + S("FStartAfter") +c1.name  + S("EEnd");
			varName.push_back(c0FStartAfterc1EEnd); varType.push_back("1");
			string c0FEndBeforec1EStart = c0.name + S("FEndbefore") +c1.name  + S("EStart");
			varName.push_back(c0FEndBeforec1EStart); varType.push_back("1");

			//c0 f start > c1 e end or c0 f end < c1 e start
			ILP.push_back(c0firststart + S(" - ") + c1endend + S(" + ") + S(M) +S(" ") + c0FStartAfterc1EEnd +   S(" >= 0"));
			ILP.push_back(c0firstend + S(" - ") + c1endstart + S(" - ") + S(M) +S(" ") + c0FEndBeforec1EStart + S(" <= 0"));
			ILP.push_back(c0FStartAfterc1EEnd + S(" + ") + c0FEndBeforec1EStart +S(" - ") +  S(M) + S(" ") + fetimeNoOverlap   +S(" <= 1"));

			//if spaceNoOverLap
			//c0f c1e non cross
			for(int i = 1; i < c0.vertexNum; i++){
				for(int j =1; j< c1.vertexNum; j++){
					//vertex pos
					string c0PreFvx = S(c0.name) + S("first") + S("x") + S(i-1);
					string c0PreFvy = S(c0.name) + S("first") + S("y") + S(i-1);
					string c0CurFvx = S(c0.name) + S("first") + S("x") + S(i);
					string c0CurFvy = S(c0.name) + S("first") + S("y") + S(i);

					string c1PreFvx = S(c1.name) + S("end") + S("x") + S(j-1);
					string c1PreFvy = S(c1.name) + S("end") + S("y") + S(j-1);
					string c1CurFvx = S(c1.name) + S("end") + S("x") + S(j);
					string c1CurFvy = S(c1.name) + S("end") + S("y") + S(j);

					//binary
					string up = c0.name + S("FirstSeg")+ S(i-1)+ S("Up") + c1.name + S("EndSeg") + S(j-1);
					varName.push_back(up); varType.push_back("1");
					string down = c0.name + S("FirstSeg")+ S(i-1)+ S("Down") + c1.name + S("EndSeg") + S(j-1);
					varName.push_back(down); varType.push_back("1");
					string left = c0.name + S("FirstSeg")+ S(i-1)+ S("Left") + c1.name + S("EndSeg") + S(j-1);
					varName.push_back(left); varType.push_back("1");
					string right = c0.name + S("FirstSeg")+ S(i-1)+ S("Right") + c1.name + S("EndSeg") + S(j-1);
					varName.push_back(right); varType.push_back("1");

					//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
					ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" + ") +S(M) + S(" ") + fespaceNoOverlap + S(" >= 1"));
					ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + fespaceNoOverlap+ S(" >= 1"));
					ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + fespaceNoOverlap+ S(" >= 1"));
					ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + fespaceNoOverlap+ S(" >= 1"));

					//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
					ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + fespaceNoOverlap+ S(" <= -1"));
					ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + fespaceNoOverlap + S(" <= -1"));
					ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + fespaceNoOverlap + S(" <= -1"));
					ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + fespaceNoOverlap + S(" <= -1"));

					//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
					ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + fespaceNoOverlap + S(" >= 1"));
					ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + fespaceNoOverlap + S(" >= 1"));
					ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + fespaceNoOverlap + S(" >= 1"));
					ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + fespaceNoOverlap + S(" >= 1"));

					//left c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
					ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + fespaceNoOverlap+ S(" <= -1"));
					ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + fespaceNoOverlap + S(" <= -1"));
					ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + fespaceNoOverlap + S(" <= -1"));
					ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + fespaceNoOverlap + S(" <= -1"));

					ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



				}
			}

				ILP.push_back(fetimeNoOverlap + S(" + ") + fespaceNoOverlap + S(" <= 1") );
				ILP.push_back(fespaceNoOverlap + S(" = 0"));


	//-------------------c0 e compare with c1 f-----------------------

				string eftimeNoOverlap = c0.name +S("E") + c1.name+S("F") + S("timeNoOverlap");
				varName.push_back(eftimeNoOverlap); varType.push_back("1");
				string efspaceNoOverlap = c0.name+S("E") + c1.name+S("F") + S("spaceNoOverlap");
				varName.push_back(efspaceNoOverlap); varType.push_back("1");

				//if timeNoOverLap
				string c0EStartAfterc1FEnd = c0.name + S("EStartAfter") +c1.name  + S("FEnd");
				varName.push_back(c0EStartAfterc1FEnd); varType.push_back("1");
				string c0EEndBeforec1FSart= c0.name + S("EEndbefore") +c1.name  + S("FStart");
				varName.push_back(c0EEndBeforec1FSart); varType.push_back("1");

				//c0 e start > c1 f end or c0 e end < c1 e start
				ILP.push_back(c0endstart + S(" - ") + c1firstend + S(" + ") + S(M) +S(" ") + c0EStartAfterc1FEnd +   S(" >= 0"));
				ILP.push_back(c0endend + S(" - ") + c1firststart + S(" - ") + S(M) +S(" ") + c0EEndBeforec1FSart + S(" <= 0"));
				ILP.push_back(c0EStartAfterc1FEnd + S(" + ") + c0EEndBeforec1FSart +S(" - ") +  S(M) + S(" ") + eftimeNoOverlap   +S(" <= 1"));

				//if spaceNoOverlap
				//c0e c1f non cross
				for(int i = 1; i < c0.vertexNum; i++){
					for(int j =1; j< c1.vertexNum; j++){
						//vertex pos
						string c0PreFvx = S(c0.name) + S("end") + S("x") + S(i-1);
						string c0PreFvy = S(c0.name) + S("end") + S("y") + S(i-1);
						string c0CurFvx = S(c0.name) + S("end") + S("x") + S(i);
						string c0CurFvy = S(c0.name) + S("end") + S("y") + S(i);

						string c1PreFvx = S(c1.name) + S("first") + S("x") + S(j-1);
						string c1PreFvy = S(c1.name) + S("first") + S("y") + S(j-1);
						string c1CurFvx = S(c1.name) + S("first") + S("x") + S(j);
						string c1CurFvy = S(c1.name) + S("first") + S("y") + S(j);

						//binary
						string up = c0.name + S("EndSeg")+ S(i-1)+ S("Up") + c1.name + S("FirstSeg") + S(j-1);
						varName.push_back(up); varType.push_back("1");
						string down = c0.name + S("EndSeg")+ S(i-1)+ S("Down") + c1.name + S("FirstSeg") + S(j-1);
						varName.push_back(down); varType.push_back("1");
						string left = c0.name + S("EndSeg")+ S(i-1)+ S("Left") + c1.name + S("FirstSeg") + S(j-1);
						varName.push_back(left); varType.push_back("1");
						string right = c0.name + S("EndSeg")+ S(i-1)+ S("Right") + c1.name + S("FirstSeg") + S(j-1);
						varName.push_back(right); varType.push_back("1");

						//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
						ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" + ") +S(M) + S(" ") + efspaceNoOverlap + S(" >= 1"));
						ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + efspaceNoOverlap+ S(" >= 1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + efspaceNoOverlap+ S(" >= 1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + efspaceNoOverlap+ S(" >= 1"));

						//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
						ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + efspaceNoOverlap+ S(" <= -1"));
						ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + efspaceNoOverlap + S(" <= -1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + efspaceNoOverlap + S(" <= -1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down + S(" - ") +S(M) + S(" ") + efspaceNoOverlap + S(" <= -1"));

						//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
						ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + efspaceNoOverlap + S(" >= 1"));
						ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + efspaceNoOverlap + S(" >= 1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + efspaceNoOverlap + S(" >= 1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + efspaceNoOverlap + S(" >= 1"));

						//left c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
						ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + efspaceNoOverlap+ S(" <= -1"));
						ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + efspaceNoOverlap + S(" <= -1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + efspaceNoOverlap + S(" <= -1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left + S(" - ") +S(M) + S(" ") + efspaceNoOverlap + S(" <= -1"));

						ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



					}
				}

					ILP.push_back(eftimeNoOverlap + S(" + ") + efspaceNoOverlap + S(" <= 1") );
					ILP.push_back(efspaceNoOverlap + S(" = 0"));

	//c0 e compare with c1 e

			string eetimeNoOverlap = c0.name +S("E") + c1.name+S("E") + S("timeNoOverlap");
			varName.push_back(eetimeNoOverlap); varType.push_back("1");
			string eespaceNoOverlap = c0.name+S("E") + c1.name+S("E") + S("spaceNoOverlap");
			varName.push_back(eespaceNoOverlap); varType.push_back("1");


			string c0EStartAfterc1EEnd = c0.name + S("EStartAfter") +c1.name  + S("EEnd");
			varName.push_back(c0EStartAfterc1EEnd); varType.push_back("1");
			string c0EEndBeforec1EStart = c0.name + S("EEndbefore") +c1.name  + S("EStart");
			varName.push_back(c0EEndBeforec1EStart); varType.push_back("1");


			//c0 e start > c1 e end or c0 e end < c1 e start
			ILP.push_back(c0endstart + S(" - ") + c1endend + S(" + ") + S(M) +S(" ") + c0EStartAfterc1EEnd +   S(" >= 0"));
			ILP.push_back(c0endend + S(" - ") + c1endstart + S(" - ") + S(M) +S(" ") + c0EEndBeforec1EStart + S(" <= 0"));
			ILP.push_back(c0EStartAfterc1EEnd + S(" + ") + c0EEndBeforec1EStart +S(" - ") +  S(M) + S(" ") + eetimeNoOverlap   +S(" <= 1"));
			ILP.push_back(eespaceNoOverlap + S(" = 0"));

			//if spaceNoOverlap
			//c0e c1e non cross
			for(int i = 1; i < c0.vertexNum; i++){
				for(int j =1; j< c1.vertexNum; j++){
					//vertex pos
					string c0PreFvx = S(c0.name) + S("end") + S("x") + S(i-1);
					string c0PreFvy = S(c0.name) + S("end") + S("y") + S(i-1);
					string c0CurFvx = S(c0.name) + S("end") + S("x") + S(i);
					string c0CurFvy = S(c0.name) + S("end") + S("y") + S(i);

					string c1PreFvx = S(c1.name) + S("end") + S("x") + S(j-1);
					string c1PreFvy = S(c1.name) + S("end") + S("y") + S(j-1);
					string c1CurFvx = S(c1.name) + S("end") + S("x") + S(j);
					string c1CurFvy = S(c1.name) + S("end") + S("y") + S(j);

					//binary
					string up = c0.name + S("EndSeg")+ S(i-1)+ S("Up") + c1.name + S("EndSeg") + S(j-1);
					varName.push_back(up); varType.push_back("1");
					string down = c0.name + S("EndSeg")+ S(i-1)+ S("Down") + c1.name + S("EndSeg") + S(j-1);
					varName.push_back(down); varType.push_back("1");
					string left = c0.name + S("EndSeg")+ S(i-1)+ S("Left") + c1.name + S("EndSeg") + S(j-1);
					varName.push_back(left); varType.push_back("1");
					string right = c0.name + S("EndSeg")+ S(i-1)+ S("Right") + c1.name + S("EndSeg") + S(j-1);
					varName.push_back(right); varType.push_back("1");

					//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
					ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" + ") +S(M) + S(" ") + eespaceNoOverlap + S(" >= 1"));
					ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + eespaceNoOverlap+ S(" >= 1"));
					ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + eespaceNoOverlap+ S(" >= 1"));
					ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" + ")+ S(M) + S(" ") + eespaceNoOverlap+ S(" >= 1"));

					//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
					ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
					ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
					ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
					ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

					//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
					ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + eespaceNoOverlap + S(" >= 1"));
					ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + eespaceNoOverlap + S(" >= 1"));
					ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + eespaceNoOverlap + S(" >= 1"));
					ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" + ")+ S(M) + S(" ") + eespaceNoOverlap + S(" >= 1"));

					//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
					ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
					ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
					ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
					ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));

					ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



				}
			}

				ILP.push_back(eetimeNoOverlap + S(" + ") + eespaceNoOverlap + S(" <= 1") );
				ILP.push_back(eespaceNoOverlap + S(" = 0"));*/



			//c0 storage compare c1 f s e
				//c0s c1f non cross
				/*	for(int i = 1; i < c0.vertexNum; i++){
						for(int j =1; j< c1.vertexNum; j++){
							//vertex pos
							string c0PreFvx = S(c0.name) + S("storage") + S("x") + S(i-1);
							string c0PreFvy = S(c0.name) + S("storage") + S("y") + S(i-1);
							string c0CurFvx = S(c0.name) + S("storage") + S("x") + S(i);
							string c0CurFvy = S(c0.name) + S("storage") + S("y") + S(i);

							string c1PreFvx = S(c1.name) + S("first") + S("x") + S(j-1);
							string c1PreFvy = S(c1.name) + S("first") + S("y") + S(j-1);
							string c1CurFvx = S(c1.name) + S("first") + S("x") + S(j);
							string c1CurFvy = S(c1.name) + S("first") + S("y") + S(j);

							//binary
							string up = c0.name + S("StoreSeg")+ S(i-1)+ S("Up") + c1.name + S("FirstSeg") + S(j-1);
							varName.push_back(up); varType.push_back("1");
							string down = c0.name + S("StoreEndSeg")+ S(i-1)+ S("Down") + c1.name + S("FirstSeg") + S(j-1);
							varName.push_back(down); varType.push_back("1");
							string left = c0.name + S("StoreSeg")+ S(i-1)+ S("Left") + c1.name + S("FirstSeg") + S(j-1);
							varName.push_back(left); varType.push_back("1");
							string right = c0.name + S("StoreSeg")+ S(i-1)+ S("Right") + c1.name + S("FirstSeg") + S(j-1);
							varName.push_back(right); varType.push_back("1");

							//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
							ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
							ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));

							//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
							ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
							ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

							//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
							ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));

							//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
							ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
							ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));

							ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



						}
					}

					//c0s c1s non cross
					for(int i = 1; i < c0.vertexNum; i++){
						for(int j =1; j< c1.vertexNum; j++){
							//vertex pos
							string c0PreFvx = S(c0.name) + S("storage") + S("x") + S(i-1);
							string c0PreFvy = S(c0.name) + S("storage") + S("y") + S(i-1);
							string c0CurFvx = S(c0.name) + S("storage") + S("x") + S(i);
							string c0CurFvy = S(c0.name) + S("storage") + S("y") + S(i);

							string c1PreFvx = S(c1.name) + S("storage") + S("x") + S(j-1);
							string c1PreFvy = S(c1.name) + S("storage") + S("y") + S(j-1);
							string c1CurFvx = S(c1.name) + S("storage") + S("x") + S(j);
							string c1CurFvy = S(c1.name) + S("storage") + S("y") + S(j);

							//binary
							string up = c0.name + S("StoreSeg")+ S(i-1)+ S("Up") + c1.name + S("StoreSeg") + S(j-1);
							varName.push_back(up); varType.push_back("1");
							string down = c0.name + S("StoreEndSeg")+ S(i-1)+ S("Down") + c1.name + S("StoreSeg") + S(j-1);
							varName.push_back(down); varType.push_back("1");
							string left = c0.name + S("StoreSeg")+ S(i-1)+ S("Left") + c1.name + S("StoreSeg") + S(j-1);
							varName.push_back(left); varType.push_back("1");
							string right = c0.name + S("StoreSeg")+ S(i-1)+ S("Right") + c1.name + S("StoreSeg") + S(j-1);
							varName.push_back(right); varType.push_back("1");

							//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
							ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
							ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up +  S(" >= 1"));

							//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
							ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
							ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

							//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
							ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));

							//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
							ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
							ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));

							ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



						}
					}

					//c0s c1e non cross
					for(int i = 1; i < c0.vertexNum; i++){
						for(int j =1; j< c1.vertexNum; j++){
							//vertex pos
							string c0PreFvx = S(c0.name) + S("storage") + S("x") + S(i-1);
							string c0PreFvy = S(c0.name) + S("storage") + S("y") + S(i-1);
							string c0CurFvx = S(c0.name) + S("storage") + S("x") + S(i);
							string c0CurFvy = S(c0.name) + S("storage") + S("y") + S(i);

							string c1PreFvx = S(c1.name) + S("end") + S("x") + S(j-1);
							string c1PreFvy = S(c1.name) + S("end") + S("y") + S(j-1);
							string c1CurFvx = S(c1.name) + S("end") + S("x") + S(j);
							string c1CurFvy = S(c1.name) + S("end") + S("y") + S(j);

							//binary
							string up = c0.name + S("StoreSeg")+ S(i-1)+ S("Up") + c1.name + S("EndSeg") + S(j-1);
							varName.push_back(up); varType.push_back("1");
							string down = c0.name + S("StoreEndSeg")+ S(i-1)+ S("Down") + c1.name + S("EndSeg") + S(j-1);
							varName.push_back(down); varType.push_back("1");
							string left = c0.name + S("StoreSeg")+ S(i-1)+ S("Left") + c1.name + S("EndSeg") + S(j-1);
							varName.push_back(left); varType.push_back("1");
							string right = c0.name + S("StoreSeg")+ S(i-1)+ S("Right") + c1.name + S("EndSeg") + S(j-1);
							varName.push_back(right); varType.push_back("1");

							//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
							ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
							ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up +  S(" >= 1"));

							//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
							ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
							ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
							ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

							//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
							ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));

							//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
							ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
							ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
							ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));

							ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



						}
					}





			//c1 storage compare c0 f e
					//c0f c1s non cross
				for(int i = 1; i < c0.vertexNum; i++){
					for(int j =1; j< c1.vertexNum; j++){
						//vertex pos
						string c0PreFvx = S(c0.name) + S("first") + S("x") + S(i-1);
						string c0PreFvy = S(c0.name) + S("first") + S("y") + S(i-1);
						string c0CurFvx = S(c0.name) + S("first") + S("x") + S(i);
						string c0CurFvy = S(c0.name) + S("first") + S("y") + S(i);

						string c1PreFvx = S(c1.name) + S("storage") + S("x") + S(j-1);
						string c1PreFvy = S(c1.name) + S("storage") + S("y") + S(j-1);
						string c1CurFvx = S(c1.name) + S("storage") + S("x") + S(j);
						string c1CurFvy = S(c1.name) + S("storage") + S("y") + S(j);

						//binary
						string up = c0.name + S("FirstSeg")+ S(i-1)+ S("Up") + c1.name + S("StoreSeg") + S(j-1);
						varName.push_back(up); varType.push_back("1");
						string down = c0.name + S("FirstEndSeg")+ S(i-1)+ S("Down") + c1.name + S("StoreSeg") + S(j-1);
						varName.push_back(down); varType.push_back("1");
						string left = c0.name + S("FirstSeg")+ S(i-1)+ S("Left") + c1.name + S("StoreSeg") + S(j-1);
						varName.push_back(left); varType.push_back("1");
						string right = c0.name + S("FirstSeg")+ S(i-1)+ S("Right") + c1.name + S("StoreSeg") + S(j-1);
						varName.push_back(right); varType.push_back("1");

						//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
						ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
						ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up +  S(" >= 1"));

						//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
						ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
						ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

						//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
						ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
						ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));

						//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
						ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
						ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));

						ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



					}
				}


				//c0e c1s non cross
				for(int i = 1; i < c0.vertexNum; i++){
					for(int j =1; j< c1.vertexNum; j++){
						//vertex pos
						string c0PreFvx = S(c0.name) + S("end") + S("x") + S(i-1);
						string c0PreFvy = S(c0.name) + S("end") + S("y") + S(i-1);
						string c0CurFvx = S(c0.name) + S("end") + S("x") + S(i);
						string c0CurFvy = S(c0.name) + S("end") + S("y") + S(i);

						string c1PreFvx = S(c1.name) + S("storage") + S("x") + S(j-1);
						string c1PreFvy = S(c1.name) + S("storage") + S("y") + S(j-1);
						string c1CurFvx = S(c1.name) + S("storage") + S("x") + S(j);
						string c1CurFvy = S(c1.name) + S("storage") + S("y") + S(j);

						//binary
						string up = c0.name + S("EndSeg")+ S(i-1)+ S("Up") + c1.name + S("StoreSeg") + S(j-1);
						varName.push_back(up); varType.push_back("1");
						string down = c0.name + S("EndEndSeg")+ S(i-1)+ S("Down") + c1.name + S("StoreSeg") + S(j-1);
						varName.push_back(down); varType.push_back("1");
						string left = c0.name + S("EndSeg")+ S(i-1)+ S("Left") + c1.name + S("StoreSeg") + S(j-1);
						varName.push_back(left); varType.push_back("1");
						string right = c0.name + S("EndSeg")+ S(i-1)+ S("Right") + c1.name + S("StoreSeg") + S(j-1);
						varName.push_back(right); varType.push_back("1");

						//up c0y0 > c1y0 c0y0 > c1y1 c0y1 > c1y0 c0y1 > c1y1
						ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
						ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up  + S(" >= 1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" + ") + S(M) + S(" ") + up + S(" >= 1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" + ") + S(M) + S(" ") + up +  S(" >= 1"));

						//down c0y0 < c1y0 c0y0 < c1y1 c0y1 < c1y0 c0y1 < c1y1
						ILP.push_back(c0PreFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down + S(" <= -1"));
						ILP.push_back(c0PreFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1PreFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));
						ILP.push_back(c0CurFvy + S(" - ") + c1CurFvy +S(" - ") + S(M) + S(" ") + down  + S(" <= -1"));

						//right c0x0 > c1x0 c0x0 > c1x1 c0x1 > c1x0 c0x1 > c1x1
						ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
						ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" + ") + S(M) + S(" ") + right + S(" >= 1"));

						//leet c0x0 < c1x0 c0x0 < c1x1 c0x1 < c1x0 c0x1 < c1x1
						ILP.push_back(c0PreFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left + S(" <= -1"));
						ILP.push_back(c0PreFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1PreFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));
						ILP.push_back(c0CurFvx + S(" - ") + c1CurFvx +S(" - ") + S(M) + S(" ") + left  + S(" <= -1"));

						ILP.push_back(up + S(" + ") + down + S(" + ") + left + S(" + ") + right + S(" <= 3"));



					}
				}*/
