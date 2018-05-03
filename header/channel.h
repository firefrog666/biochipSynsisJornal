#ifndef CHANNEL_H
#define CHANNEL_H

using namespace std;
#include "../header/Node.h"
#include "../header/edge.h"
#include "../header/device.h"
#include <boost/shared_ptr.hpp>







class Channel {

public:





	Edge* storeE = NULL;
public:
	int const static vertexNum = 4;
	int startTime;
	int endTime;
	int injectTime;
	int ejectTime;
	int  storageStart = 1;
	int  storageEnd = 2;
	bool isStore = false;
	bool isFirst = false;
	bool isLast = false;
	bool isNormal = false;

	string name;
	//Device* ends[2];
	//Device* first;
	//Device* second;
	//Device* storage;
	string belongTo = "myself";
	Op* fatherOp;
	Op* childOp;


public:
	bool endsBeforeC(Channel* c){
		if(endTime < c->endTime)
			return true;
		return false;
	}
	bool conlictWith(Channel* c){
		if(c->startTime >= this->endTime || c->endTime <= this->startTime)
			return false;
		else
			return true;
	}

	void delay(int time){
		startTime = startTime+time;
		endTime = endTime+time;
		injectTime = injectTime+time;
		ejectTime = ejectTime+time;
	}

	void printSelf(){
		cout<<name<<endl;
		cout<<"start at "<<startTime << " end at "<<endTime<<endl;
	}
	void setName(){
		if(isFirst){
			assert(fatherOp !=NULL);
			if(storeE == NULL)
				name = S("fToS") + fatherOp->name + S("NULL");
			else
				name = S("fToS") + fatherOp->name + storeE->name;

		}
		else if(isLast){
			assert(childOp != NULL);
			if(storeE == NULL)
				name = S("fFromS") + childOp->name + S("NULL");
			else
				name = S("fFromS") + childOp->name + storeE->name;

		}
		else{
			assert(fatherOp !=NULL);
			assert(childOp != NULL);
			name = S("normal") + fatherOp->name + S(" to ") + childOp->name;
		}
	}
	void setStore(Edge* e){
		storeE = e;
		setName();
	}
};


/*class storage : public Channel{

};

class tmpChannel : public Channel{

};*/
#endif
