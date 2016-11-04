/*
 * ListAlgorithm.cpp
 *
 *  Created on: Aug 14, 2016
 *      Author: ga63quk
 */


#include "../header/randomSeq.h"
#include<vector>
#include <sstream>
#include "../header/device.h"

#include <stdlib.h>
#include <time.h>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <cstring>


#include <string>
#include <sstream>






#define TRANSTIME 10
using namespace std;
typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;

string toS(int i){
	stringstream ss;
	ss<<i;
	return ss.str();
}
string toS(const char* s){
	stringstream ss;
	ss<<s;
	return ss.str();
}
string toS(string s){
	stringstream ss;
	ss<<s;
	return ss.str();
}

Op_ptr RandomSeq::genRandomOp(){
	Op_ptr op(new Op);
	op->name = "o" + toS(opCount);
	opCount++;
	op->duration = 40;
	//op->duration = rand() % (maxDuration) + 10;
	op->type =static_cast<operationType>( rand()%(operationType::last-1));
	if(op->type == operationType::mix){
		op->parentSize = 2;
	}
	else{
		op->parentSize = 1;
	}

	op->childSize = rand() % 3 +1;
	return op;


}

Dev_ptr RandomSeq::genDev(operationType type){
	Dev_ptr dev(new Device);
	dev->name = "d" + toS(devCount);
	devCount++;


	dev->sizeX = rand() % maxDevSize +1;
	dev->sizeY = rand()% maxDevSize +1;
	dev->type = type;

	return dev;

}

Dev_ptr RandomSeq::genRandomDev(){
	Dev_ptr dev(new Device);
	dev->name = "d" + toS(devCount);
	devCount++;


	dev->sizeX = rand() % maxDevSize +1;
	dev->sizeY = rand()% maxDevSize +1;
	dev->type =static_cast<operationType>( rand()%operationType::last-1);

	return dev;
}

void RandomSeq::genDevs(int num){
	for(int i = 0; i < num;i++){

		operationType type = static_cast<operationType>(i%(operationType::last-1));

		Dev_ptr dev = genDev(type);
		devices.push_back(dev);

		/*Dev_ptr dev = genRandomDev();
		devices.push_back(dev);*/
	}
}
void RandomSeq::addOneOp(){
	Op_ptr op = genRandomOp();
	if(ops.size() == 0){
		ops.push_back(op);
		return;
	}

	//for each anchor of son position, choose a son

	for(int i = 0; i < parentSize; i++){
		//always choose a father
		if(i == 0){
			for(Op_ptr child:ops){
				if(child->parents.size() < parentSize){
					child->parents.push_back(op);
					op->children.push_back(child);
				}
			}
			continue;
		}



		int decide = rand()%2;
		// find a father, always find your previous father's sibling
		if(decide == 1){
			for(Op_ptr child:ops){
				if(child->parents.size() < parentSize){
					child->parents.push_back(op);
					op->children.push_back(child);
				}
			}

		}


	}


}


void RandomSeq::genSeqByLayer(const vector<int>& opNumEachLayer){

	vector<Op_ptr> opsTemp;
	vector<int> opsLayerTemp;
	vector<int> opsIdInThisLayerTemp;
	vector<Op_ptr> lastLayer;
	vector<Op_ptr> thisLayer;
	int idOFOneLayer = 0;
	for(int layer = 0; layer < opNumEachLayer.size();layer++){
		idOFOneLayer = 0;
		int opNum = opNumEachLayer.at(layer);
		if(layer == 0){
			for(int opId = 0; opId < opNum; opId++){
				Op_ptr op = genRandomOp();
				opsTemp.push_back(op);
				opsLayerTemp.push_back(layer);
				opsIdInThisLayerTemp.push_back(idOFOneLayer);idOFOneLayer++;

				thisLayer.push_back(op);
			}
			continue;
		}

		lastLayer = thisLayer;
		thisLayer.clear();

		for(int opId = 0; opId < opNum; opId++){
			Op_ptr op = genRandomOp();

			//for each anchor
			int randomParentSize;
			int random = (rand()%100+1);
			if(random > 1){
				randomParentSize = 2;
			}
			else
				randomParentSize = 1;


			int initFatherId = 0;
			for(int parentAnchor = 0; parentAnchor </*randomParentSize*/op->parentSize; parentAnchor++){

				//random decide if find a father
				/*if(parentAnchor > 0){
					int decide = rand()%2;
					if(decide == 0)
							continue;
				}*/



				for(int fatherId = initFatherId; fatherId < lastLayer.size();fatherId++){
					Op_ptr father = lastLayer.at(fatherId);

					//match
					if(father->children.size() < (rand()%2+1)/*father->childSize*/){
						op->parents.push_back(father);
						father->children.push_back(op);
						initFatherId = fatherId+1;
						break;
					}

				}

			}

			//if one op does not find father, discard this op
			if(op->parents.size() == 0)
				continue;

			opsTemp.push_back(op);
			opsLayerTemp.push_back(layer);
			opsIdInThisLayerTemp.push_back(idOFOneLayer);idOFOneLayer++;
			thisLayer.push_back(op);
		}
	}

	//discard alone ops
	for(int i = 0; i < opsTemp.size(); i++){
		Op_ptr op = opsTemp.at(i);
		int opLayer = opsLayerTemp.at(i);
		int opIdThisLayer = opsIdInThisLayerTemp.at(i);

		if(op->children.size() == 0 && op->parents.size() == 0){
			continue;
		}

		ops.push_back(op);
		opsLayer.push_back(opLayer);
		opsIdInThisLayer.push_back(opIdThisLayer);

	}

	cout<<"ops number is  " << ops.size()<<endl;

}

void RandomSeq::drawOps(){
	const int radius = 3;
	const int layerSpace = 15;
	const int opsSpace = 9;
	const int paperWidth  = 100;

	int verOffset = 0;
	int horOffset = 0;
	ofstream file;

	file.open("operations.txt");

	for(int i = 0; i < ops.size(); i++){
		Op_ptr op = ops.at(i);
		int opLayer = opsLayer.at(i);
		int opIdThisLayer = opsIdInThisLayer.at(i);

		verOffset = radius + opLayer*(radius + layerSpace);
		horOffset = radius + opIdThisLayer * (radius + opsSpace);
		int opType =static_cast<int>(op->type);

		file << opType <<endl;
		file << horOffset <<endl;
		file << verOffset<<endl;
		file << radius <<endl;



	}

	file.close();

	file.open("arrows.txt");
	for(int i = 0; i < ops.size(); i++){
		Op_ptr op = ops.at(i);
		int opLayer = opsLayer.at(i);
		int opIdThisLayer = opsIdInThisLayer.at(i);

		int arrowStartVer = radius + opLayer*(radius + layerSpace) + radius;
		int arrowStartHor =  radius + opIdThisLayer * (radius + opsSpace);

		for(int j = 0; j < op->children.size();j++){
			Op_ptr child = op->children.at(j);
			int childId;

			//find child
			for(int index = 0; index < ops.size(); index++){
				if(child == ops.at(index)){
					childId = index;
					break;
				}
			}

			int childLayer = opsLayer.at(childId);
			int childIdInThisLayer = opsIdInThisLayer.at(childId);


			int arrowEndVer =childLayer*(radius + layerSpace);
			int arrowEndHor =  radius + childIdInThisLayer * (radius + opsSpace);

			file << arrowStartHor <<endl;
			file << arrowStartVer <<endl;
			file << arrowEndHor<<endl;
			file << arrowEndVer <<endl;

		}


	}

	file.close();










}







