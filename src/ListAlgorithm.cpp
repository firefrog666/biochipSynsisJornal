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
#include "../header/channel.h"
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
typedef boost::shared_ptr<Channel> Ch_ptr;

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
		string opInj = opName + s("Inj");
		string opEj = opName + s("Ej");
		op->startTime = input.at(opStart);
		op->endTime = input.at(opFinish);
		op->injecTime = input.at(opInj);
		op->ejectTime = input.at(opEj);
		for(Dev_ptr dev:devices){
			string opBindDev = op->name + s("Bind") + dev->name;
			int bind = input.at(opBindDev);
			if(bind == 0){
				op->bindDevice = dev;
				break;
			}
		}
	}

	for(Ch_ptr c:channels){
		string cName = c->name;
		string cStart = c->name + s("Start");
		string cFinish = c->name + s("Finish");

		c->startTime = input.at(cStart);
		c->endTime = input.at(cFinish);
	}

	writeTimeline();





}

void ListAlgorithm::writeTimeline(){
	ofstream file;
		file.open("timeline.txt");

		for(Ch_ptr c:channels){
			Op_ptr f = c->fatherOp;
			Op_ptr son = c->childOp;

			file<< c->name << " "  << c->startTime << " " << c->endTime << " " << c->fatherOp->name << " " << c->childOp->name << endl;

		}
		for(Op_ptr op:ops){
			file << op->name << " " << op->injecTime << " " << op->startTime << " " << op->endTime << " " << op->ejectTime << " " << op->bindDevice->name << endl;
		}
		file.close();
}

void ListAlgorithm::outerMemilpConstraint(){
	//create var
		for(Op_ptr op:ops){
			string opName = op->name;
			string opStart = opName + s("Start");
			string opFinish = opName + s("Finish");
			string opInj = opName + s("Inj");
			string opEj = opName + s("Ej");
			varName.push_back(opStart);varType.push_back("2");
			varName.push_back(opFinish);varType.push_back("2");
			varName.push_back(opInj);varType.push_back("2");
			varName.push_back(opEj);varType.push_back("2");
			//if op bind to dev
			for(Dev_ptr dev:devices){
				string devName = dev->name;
				string opBindDev = opName + s("Bind") + devName;
				varName.push_back(opBindDev);varType.push_back("1");

			}

		}

		//create channels
		for(Op_ptr child:ops){
			for(Op_ptr parent:child->parents){
				Ch_ptr c(new Channel);
				channels.push_back(c);
				c->name = s("c") + parent->name + child->name;
				string cStart = c->name + s("Start");
				string cFinish = c->name + s("Finish");
				c->fatherOp = parent;
				c->childOp = child;
				varName.push_back(cStart);varType.push_back("2");
				varName.push_back(cFinish);varType.push_back("2");
			}
		}

		//ops finsh -begin >= duration
		//ops after his parent
		for(Op_ptr op:ops){
			string opStart = op->name + s("Start");
			string opFinish = op->name + s("Finish");

			ILP.push_back(opFinish + s(" - ") + opStart + s(" >= ") +s(op->duration));
		}

		for(Op_ptr op:ops){
			string opName = op->name;
			string opStart = opName + s("Start");
			string opFinish = opName + s("Finish");
			string opInj = opName + s("Inj");
			string opEj = opName + s("Ej");
			ILP.push_back(opInj + s(" - ") + opStart + s(" <= 0"));
			ILP.push_back(opEj + s(" - ") + opFinish + s(" >= 0"));

		}

		//ops after his parent
		for(Op_ptr child:ops){
			string childStart = child->name + s("Start");
			string childFinish = child->name + s("Finish");
			string childInj = child->name + s("Inj");
			string childEj = child->name + s("Ej");
			for(Op_ptr parent:child->parents){
				string parentStart = parent->name +s("Start");
				string parentFinish = parent->name + s("Finish");
				string parentInj = parent->name + s("Inj");
				string parentEj = parent->name + s("Ej");
				string cName = s("c") + parent->name + child->name;
				string cStart = cName + s("Start");
				string cFinish = cName+ s("Finish");
				//channel start after parent end and channel before
				ILP.push_back(cStart + s(" - ") + parentFinish + s(" >= 0"));
				ILP.push_back(childStart + s(" - ") + cFinish + s(" >= 0"));
				//child op inject before each channel finish
				ILP.push_back(childInj + s(" - ") + cFinish + s(" <= ") +s(-TRANSTIME));
				//father op eject after each channel start
				ILP.push_back(parentEj + s(" - ") + cStart + s(" >= ") + s(TRANSTIME));
			}
		}


		//if several channel meets on the same operation, they must queue
		for(Op_ptr child:ops){
			for(Op_ptr father0:child->parents){
				for(Op_ptr father1:child->parents){


					if(father0 == father1)
						continue;

					string c0Name = s("c") + father0->name + child->name;
					string c0Start = c0Name + s("Start");
					string c0Finish = c0Name+ s("Finish");

					string c1Name = s("c") + father1->name + child->name;
					string c1Start = c1Name + s("Start");
					string c1Finish = c1Name+ s("Finish");

					string c0Beforec1 = c0Name + s("BF") + c1Name;
					varName.push_back(c0Beforec1); varType.push_back("1");
					//if c0bc1 = 0 then c0f - c1f <= -trantime
					ILP.push_back(c0Finish + s(" - ") + c1Finish + s(" - ") + s(M) + s(" ") + c0Beforec1 +s(" <= ") + s(-TRANSTIME));
					//if c0bc1 = 1 then c0f-c1f >= transtime
					//c0f - c1f + (1-c0b1f)M >= transtime
					ILP.push_back(c0Finish + s(" - ") + c1Finish + s(" - ") + s(M) + s(" ") + c0Beforec1 +s(" >= ") + s(TRANSTIME-M));


				}
			}
		}

		//if  channels stores or from on the same operation, they must queue
		for(Ch_ptr c0:channels){
			string c0Name = s("c") + c0->fatherOp->name + c0->childOp->name;
			string c0Start = c0Name + s("Start");
			string c0Finish = c0Name+ s("Finish");
			//if c0Finish - c1Start > Trans


			for(Ch_ptr c1:channels){
				if (c0 == c1)
					continue;



					string c1Name = s("c") + c1->fatherOp->name + c1->childOp->name;
					string c1Start = c1Name + s("Start");
					string c1Finish = c1Name+ s("Finish");

					string c0Beforec1 = c0Name + s("BF") + c1Name;
					varName.push_back(c0Beforec1); varType.push_back("1");
					//if c0bc1 = 0 then c0f - c1f <= trantime
					ILP.push_back(c0Finish + s(" - ") + c1Finish + s(" - ") + s(M) + s(" ") + c0Beforec1 +s(" <= ") + s(-TRANSTIME));
					//if c0bc1 = 1 then c0f-c1f >= transtime
					//c0f - c1f + (1-c0b1f)M >= transtime
					ILP.push_back(c0Finish + s(" - ") + c1Finish + s(" - ") + s(M) + s(" ") + c0Beforec1 +s(" >= ") + s(TRANSTIME-M));


				}
			}



		//if operation runs on the same device, channel start time = channel end time
		// or channel time > transtime
		for(Ch_ptr c:channels){
			string channelStartEndSame  = c->name + s("SES");
			varName.push_back(channelStartEndSame);varType.push_back("1");

			Op_ptr father = c->fatherOp;
			Op_ptr son = c->childOp;
			string cStart = c->name + s("Start");
			string cFinish = c->name + s("Finish");

			for(Dev_ptr dev:devices){

				string channelStartEndSameDev = c->name +s("SES") + dev->name;
				varName.push_back(channelStartEndSameDev);varType.push_back("1");

				string childBindDev = father->name + s("Bind") + dev->name;
				string parentBindDev = son->name + s("Bind") + dev->name;


				//if child = 0 and parent = 0 then sameDev = 0
				//if child = 1 or parent = 1 then sameDev = 1
				ILP.push_back( channelStartEndSameDev+ s(" - ")+ s(M) + s(" ") + childBindDev+ s(" - ") + s(M) + s(" ") + parentBindDev + s(" <= 0"));
				ILP.push_back( channelStartEndSameDev+ s(" + ") + s(M) + s(" ") + childBindDev+ s(" + ") + s(M) + s(" ") + parentBindDev + s(" >= 0"));
				ILP.push_back(channelStartEndSameDev + s(" - ") + childBindDev + s(" >= 0"));
				ILP.push_back(channelStartEndSameDev + s(" - ") + parentBindDev + s(" >= 0"));

			}
			//if dev1 = 0 or dev2 = 0 then same = 0
			//if dev1 =1 and dev2 =1 then same = 1
			string allDevSamePlus = "";
			string allDevSameMinus = "";
			for(Dev_ptr dev:devices){
				string channelStartEndSameDev = c->name +s("SES") + dev->name;
				ILP.push_back(channelStartEndSame + s(" - ") + channelStartEndSameDev + s(" <= 0"));
				allDevSamePlus += s(" + ") + s(M) + s(" ") + s(channelStartEndSameDev);
				allDevSameMinus += s(" - ") + s(M) + s(" ") + s(channelStartEndSameDev);
			}
			ILP.push_back(channelStartEndSame + allDevSameMinus + s(" >= ") + s(1 - M * devices.size()));
			ILP.push_back(channelStartEndSame + allDevSamePlus + s(" <= ") + s(1+ M * devices.size()));

			// if channelStartEndSame = 0 then channel start = end

			ILP.push_back(cFinish + s(" - ") + cStart + s(" - ")+ s(M) + s(" ") + channelStartEndSame + s(" <= 0"));
			ILP.push_back(cFinish + s(" - ") + cStart + s(" + ") + s(M) + s(" ") + channelStartEndSame + s( " >= 0"));

			// if channelSatartEndSame = 1 then channel end - start > transtime
			// end - start + (1-s) M  >= trasTime ----> end - start -Ms >= trasTime-M


			ILP.push_back(cFinish + s(" - ") + cStart + s(" - ")+ s(M) + s(" ") + channelStartEndSame + s(" >= ")+ s(TRANSTIME - M));
			//ILP.push_back(cFinish + s(" - ") + cStart + s(" + ") + s(M) + s(" ") + channelStartEndSame + s( " <= ") + s(TRANSTIME + M));



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

				string op0Inj = op0->name + s("Inj");
				string op0Ej = op0->name + s("Ej");
				for(int j = 0; j < i; j++){

					Op_ptr op1 = ops.at(j);



					if(op0->type != op1->type){
						continue;
					}

					string op1Inj = op1->name + s("Inj");
					string op1Ej = op1->name + s("Ej");

					string op0BeforeOp1 = op0->name +s("Before") + op1->name;
					string op1BeforeOp0 = op1->name + s("Before") + op0->name;
					varName.push_back(op0BeforeOp1); varType.push_back("1");
					varName.push_back(op1BeforeOp0); varType.push_back("1");
					string op0BindDev = op0->name + s("Bind") + devName;
					string op1BindDev = op1->name + s("Bind") + devName;

					//if op0bind == 0 and op1bind == 0 then op1before = 0 or op1befor 0

					//if op0before = 0 then op1start - op1finish >= trans
					ILP.push_back(op1Inj + s(" - ") + op0Ej + s(" + ") +s(M) + s(" ") + op0BeforeOp1 + s(" >= ") + s(0));


					//if op1before = 0 then op0start - op10Finish >= trans
					ILP.push_back(op0Inj + s(" - ") + op1Ej + s(" + ") + s(M) + s(" ") + op1BeforeOp0 + s(" >= ") + s(0)) ;

					// op0Bind = 1 or op1Bind = 1 or op0b = 0 or op1b = 0
					//(1-op0) + (1-op1) + op0b + op1b <=3; -op0 - op1 + op0b + op1b <= 1
					ILP.push_back(s(" - ") + op0BindDev + s(" - ") + op1BindDev + s(" + ") + op0BeforeOp1 + s(" + ") + op1BeforeOp0+ s(" <= 1"));

				}
			}
		}

		/*//for a parent and a child, they must use different devices
		for(Op_ptr child:ops){
			for(Op_ptr parent:child->parents){
				for(Dev_ptr dev:devices){
					string childBindDev = child->name + s("Bind") + dev->name;
					string parentBindDev = parent->name + s("Bind") + dev->name;

					//only one operation can bind to here
					ILP.push_back(childBindDev + " + " + parentBindDev + " >= 1");
				}
			}
		}*/
}

void ListAlgorithm::ilpConstraint(){
	//create var
	for(Op_ptr op:ops){
		string opName = op->name;
		string opStart = opName + s("Start");
		string opFinish = opName + s("Finish");
		string opInj = opName + s("Inj");
		string opEj = opName + s("Ej");
		varName.push_back(opStart);varType.push_back("2");
		varName.push_back(opFinish);varType.push_back("2");
		varName.push_back(opInj);varType.push_back("2");
		varName.push_back(opEj);varType.push_back("2");
		//if op bind to dev
		for(Dev_ptr dev:devices){
			string devName = dev->name;
			string opBindDev = opName + s("Bind") + devName;
			varName.push_back(opBindDev);varType.push_back("1");

		}

	}

	//create channels
	for(Op_ptr child:ops){
		for(Op_ptr parent:child->parents){
			Ch_ptr c(new Channel);
			channels.push_back(c);
			c->name = s("c") + parent->name + child->name;
			string cStart = c->name + s("Start");
			string cFinish = c->name + s("Finish");
			c->fatherOp = parent;
			c->childOp = child;
			varName.push_back(cStart);varType.push_back("2");
			varName.push_back(cFinish);varType.push_back("2");
		}
	}

	//ops finsh -begin >= duration
	//ops after his parent
	for(Op_ptr op:ops){
		string opStart = op->name + s("Start");
		string opFinish = op->name + s("Finish");

		ILP.push_back(opFinish + s(" - ") + opStart + s(" >= ") +s(op->duration));
	}

	for(Op_ptr op:ops){
		string opName = op->name;
		string opStart = opName + s("Start");
		string opFinish = opName + s("Finish");
		string opInj = opName + s("Inj");
		string opEj = opName + s("Ej");
		ILP.push_back(opInj + s(" - ") + opStart + s(" <= 0"));
		ILP.push_back(opEj + s(" - ") + opFinish + s(" >= 0"));

	}

	//ops after his parent
	for(Op_ptr child:ops){
		string childStart = child->name + s("Start");
		string childFinish = child->name + s("Finish");
		string childInj = child->name + s("Inj");
		string childEj = child->name + s("Ej");
		for(Op_ptr parent:child->parents){
			string parentStart = parent->name +s("Start");
			string parentFinish = parent->name + s("Finish");
			string parentInj = parent->name + s("Inj");
			string parentEj = parent->name + s("Ej");
			string cName = s("c") + parent->name + child->name;
			string cStart = cName + s("Start");
			string cFinish = cName+ s("Finish");
			//channel start after parent end and channel before
			ILP.push_back(cStart + s(" - ") + parentFinish + s(" >= 0"));
			ILP.push_back(childStart + s(" - ") + cFinish + s(" >= 0"));
			//child op inject before each channel finish
			ILP.push_back(childInj + s(" - ") + cFinish + s(" <= ") +s(-TRANSTIME));
			//father op eject after each channel start
			ILP.push_back(parentEj + s(" - ") + cStart + s(" >= ") + s(TRANSTIME));
		}
	}


	//if several channel meets on the same operation, they must queue
	for(Op_ptr child:ops){
		for(Op_ptr father0:child->parents){
			for(Op_ptr father1:child->parents){


				if(father0 == father1)
					continue;

				string c0Name = s("c") + father0->name + child->name;
				string c0Start = c0Name + s("Start");
				string c0Finish = c0Name+ s("Finish");

				string c1Name = s("c") + father1->name + child->name;
				string c1Start = c1Name + s("Start");
				string c1Finish = c1Name+ s("Finish");

				string c0Beforec1 = c0Name + s("BF") + c1Name;
				varName.push_back(c0Beforec1); varType.push_back("1");
				//if c0bc1 = 0 then c0f - c1f <= trantime
				ILP.push_back(c0Finish + s(" - ") + c1Finish + s(" - ") + s(M) + s(" ") + c0Beforec1 +s(" <= ") + s(-TRANSTIME));
				//if c0bc1 = 1 then c0f-c1f >= transtime
				//c0f - c1f + (1-c0b1f)M >= transtime
				ILP.push_back(c0Finish + s(" - ") + c1Finish + s(" - ") + s(M) + s(" ") + c0Beforec1 +s(" >= ") + s(TRANSTIME-M));


			}
		}
	}


	//if operation runs on the same device, channel start time = channel end time
	// or channel time > transtime
	for(Ch_ptr c:channels){
		string channelStartEndSame  = c->name + s("SES");
		varName.push_back(channelStartEndSame);varType.push_back("1");

		Op_ptr father = c->fatherOp;
		Op_ptr son = c->childOp;
		string cStart = c->name + s("Start");
		string cFinish = c->name + s("Finish");

		for(Dev_ptr dev:devices){

			string channelStartEndSameDev = c->name +s("SES") + dev->name;
			varName.push_back(channelStartEndSameDev);varType.push_back("1");

			string childBindDev = father->name + s("Bind") + dev->name;
			string parentBindDev = son->name + s("Bind") + dev->name;


			//if child = 0 and parent = 0 then sameDev = 0
			//if child = 1 or parent = 1 then sameDev = 1
			ILP.push_back( channelStartEndSameDev+ s(" - ")+ s(M) + s(" ") + childBindDev+ s(" - ") + s(M) + s(" ") + parentBindDev + s(" <= 0"));
			ILP.push_back( channelStartEndSameDev+ s(" + ") + s(M) + s(" ") + childBindDev+ s(" + ") + s(M) + s(" ") + parentBindDev + s(" >= 0"));
			ILP.push_back(channelStartEndSameDev + s(" - ") + childBindDev + s(" >= 0"));
			ILP.push_back(channelStartEndSameDev + s(" - ") + parentBindDev + s(" >= 0"));

		}
		//if dev1 = 0 or dev2 = 0 then same = 0
		//if dev1 =1 and dev2 =1 then same = 1
		string allDevSamePlus = "";
		string allDevSameMinus = "";
		for(Dev_ptr dev:devices){
			string channelStartEndSameDev = c->name +s("SES") + dev->name;
			ILP.push_back(channelStartEndSame + s(" - ") + channelStartEndSameDev + s(" <= 0"));
			allDevSamePlus += s(" + ") + s(M) + s(" ") + s(channelStartEndSameDev);
			allDevSameMinus += s(" - ") + s(M) + s(" ") + s(channelStartEndSameDev);
		}
		ILP.push_back(channelStartEndSame + allDevSameMinus + s(" >= ") + s(1 - M * devices.size()));
		ILP.push_back(channelStartEndSame + allDevSamePlus + s(" <= ") + s(1+ M * devices.size()));

		// if channelStartEndSame = 0 then channel start = end

		ILP.push_back(cFinish + s(" - ") + cStart + s(" - ")+ s(M) + s(" ") + channelStartEndSame + s(" <= 0"));
		ILP.push_back(cFinish + s(" - ") + cStart + s(" + ") + s(M) + s(" ") + channelStartEndSame + s( " >= 0"));

		// if channelSatartEndSame = 1 then channel end - start > transtime
		// end - start + (1-s) M  >= trasTime ----> end - start -Ms >= trasTime-M


		ILP.push_back(cFinish + s(" - ") + cStart + s(" - ")+ s(M) + s(" ") + channelStartEndSame + s(" >= ")+ s(TRANSTIME - M));
		//ILP.push_back(cFinish + s(" - ") + cStart + s(" + ") + s(M) + s(" ") + channelStartEndSame + s( " <= ") + s(TRANSTIME + M));



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

			string op0Inj = op0->name + s("Inj");
			string op0Ej = op0->name + s("Ej");
			for(int j = 0; j < i; j++){

				Op_ptr op1 = ops.at(j);



				if(op0->type != op1->type){
					continue;
				}

				string op1Inj = op1->name + s("Inj");
				string op1Ej = op1->name + s("Ej");

				string op0BeforeOp1 = op0->name +s("Before") + op1->name;
				string op1BeforeOp0 = op1->name + s("Before") + op0->name;
				varName.push_back(op0BeforeOp1); varType.push_back("1");
				varName.push_back(op1BeforeOp0); varType.push_back("1");
				string op0BindDev = op0->name + s("Bind") + devName;
				string op1BindDev = op1->name + s("Bind") + devName;

				//if op0bind == 0 and op1bind == 0 then op1before = 0 or op1befor 0

				//if op0before = 0 then op1start - op1finish >= trans
				ILP.push_back(op1Inj + s(" - ") + op0Ej + s(" + ") +s(M) + s(" ") + op0BeforeOp1 + s(" >= ") + s(0));


				//if op1before = 0 then op0start - op10Finish >= trans
				ILP.push_back(op0Inj + s(" - ") + op1Ej + s(" + ") + s(M) + s(" ") + op1BeforeOp0 + s(" >= ") + s(0)) ;

				// op0Bind = 1 or op1Bind = 1 or op0b = 0 or op1b = 0
				//(1-op0) + (1-op1) + op0b + op1b <=3; -op0 - op1 + op0b + op1b <= 1
				ILP.push_back(s(" - ") + op0BindDev + s(" - ") + op1BindDev + s(" + ") + op0BeforeOp1 + s(" + ") + op1BeforeOp0+ s(" <= 1"));

			}
		}
	}

	/*//for a parent and a child, they must use different devices
	for(Op_ptr child:ops){
		for(Op_ptr parent:child->parents){
			for(Dev_ptr dev:devices){
				string childBindDev = child->name + s("Bind") + dev->name;
				string parentBindDev = parent->name + s("Bind") + dev->name;

				//only one operation can bind to here
				ILP.push_back(childBindDev + " + " + parentBindDev + " >= 1");
			}
		}
	}*/

}

void ListAlgorithm::ilpObj(){
	string obj = "";
	string maxTime = "maxTime";
	varName.push_back(maxTime); varType.push_back("2");
	for(Op_ptr op:ops){
		string opFinish = op->name + s("Finish");
		ILP.push_back(maxTime + s(" - ")  + opFinish + s(" >= 0"));
	}
	obj +=  s(" ") + maxTime;
	//ILP.push_back(maxTime + s(" = 580")); //30
	//ILP.push_back(maxTime + s(" = 1090")); //50
	//ILP.push_back(maxTime + s(" = 1130")); //70
	//ILP.push_back(maxTime + s(" = 1340")); //100




	/*string maxChannelTime = s("maxChannelTime");
	varName.push_back(maxChannelTime); varType.push_back("0");
	for(Ch_ptr c:channels){
		string cStart = c->name + s("Start");
		string cFinish = c->name + s("Finish");
		ILP.push_back(maxChannelTime + s(" - ") + cFinish + s(" + ") + cStart + s(" >= 0"));
	}
	obj +=  s(" + ") + maxChannelTime;*/
#define optchannel 1
#if optchannel
	for(Ch_ptr c:channels){
		string cStart = c->name + s("Start");
		string cFinish = c->name + s("Finish");
		obj+= s(" + ") + cFinish + s(" - ")  + cStart;
	}
#endif
	OBJ.push_back("Minimize");
	OBJ.push_back(obj);

}

void ListAlgorithm::writeResultToFile(map<string,int> results){
	ofstream file1;
	ofstream file2;
	file1.open("listVarName.txt");
	file2.open("listVarResult.txt");
	for(string name:varName){
		int result = results[name];
		file1<<name<<endl;
		file2<<result<<endl;
	}
	file1.close();
	file2.close();
}

void ListAlgorithm::readResultFromFile(){
	string name;
	int value;
	std::ifstream file1("listVarName.txt");
	std::ifstream file2("listVarResult.txt");
	string str1,str2;
	map<string,int> results;

	while (getline(file1, str1) && getline(file2,str2))
	{
		name = str1;
		istringstream abuffer(str2);
		abuffer >> value;
		results[name] = value;

	}
	readFromSolver(results);
}
void ListAlgorithm::writeToFile(){
	writeILP write;
	write.writeOBJ(OBJ,"seq.lp");
	write.writeConstraint(ILP,"seq.lp");


	write.writeVarNames(varName,varType,"seq.lp");




}

void ListAlgorithm::getConciseSeq(){
	cout << "getConciseSeq" << endl;
	for(Op_ptr op:ops){
		for(Op_ptr father:op->parents){
			bool channelExsit = false;
			Dev_ptr father_dev = father->bindDevice;
			Dev_ptr child_dev = op->bindDevice;

			//find existed channel
			for(int i = 0; i< concise_channels.size();i++){
				if(concise_channels.size()==0)
					continue;
				Ch_ptr ch = concise_channels.at(i);
				if((ch->fatherOp->bindDevice == father_dev && ch->childOp->bindDevice == child_dev) ||
						(ch->fatherOp->bindDevice == child_dev && ch->childOp->bindDevice == father_dev)){

					//if is storage
					if(ch->fatherOp->endTime + 10 < ch->childOp->startTime){
						ch->isStore = true;
					}

					channels_count.at(i) = channels_count.at(i)+1;
					channelExsit = true;
					break;
				}
			}

			if(!channelExsit){
				Ch_ptr newCh(new Channel());
				newCh->fatherOp = father;
				newCh->childOp = op;
				newCh->name = s("c") + father_dev->name + child_dev->name;


				if(newCh->fatherOp->endTime + 10 < newCh->childOp->startTime){
					newCh->isStore = true;
				}
				concise_channels.push_back(newCh);
				channels_count.push_back(1);
			}

		}
	}

	for(int i  = 0; i < concise_channels.size();i++){
		Ch_ptr ch = concise_channels.at(i);
		Op_ptr father = ch->fatherOp;
		Op_ptr son = ch->childOp;
		Dev_ptr father_dev = father->bindDevice;
		Dev_ptr son_dev = son ->bindDevice;

		bool fatherOpExist = false;
		bool sonOpExist = false;
		bool fatherDevExist =false;
		bool sonDevExist =false;

		for(Op_ptr op:concise_ops){
			if(op->name == father->name){
				fatherOpExist = true;
				break;
			}
		}


		for(Op_ptr op:concise_ops){
			if(op->name == son->name){
				sonOpExist = true;
				break;
			}
		}


		for(Dev_ptr dev:concise_devs){
			if(dev->name == father_dev->name){
				fatherDevExist = true;
				break;
			}
		}


		for(Dev_ptr dev:concise_devs){
			if(dev->name == son_dev->name){
				sonDevExist = true;
				break;
			}
		}

		if(!fatherOpExist){
			concise_ops.push_back(father);
		}


		if(!sonOpExist){
			concise_ops.push_back(son);
		}


		if(!fatherDevExist){
			concise_devs.push_back(father_dev);
		}

		if(!sonDevExist){
			concise_devs.push_back(son_dev);
		}
	}
	cout << "concise channel size is " << concise_channels.size() << endl;
	cout <<"channel count is "<< channels_count.size() << endl;
	cout << "getConciseSeq done!" << endl;
}

void ListAlgorithm::listAlgorithm(){

	Op_ptr nullOp(new Op);
	Ch_ptr nullCh(new Channel);

	for(Op_ptr op:ops){
		op->running = false;
		op->done = false;
	}

	for(Dev_ptr dev:devices){
		dev->availeble = true;
		dev->injecting = false;
		dev->isRunning = false;
		dev->ejecting = false;
		dev->injectTime = M;
		dev->startTime = M;
		dev->endTime = M;
		dev->ejectTime = M;

	}

	map<string,Ch_ptr> channelByName;
	//create channels
	for(Op_ptr child:ops){
		for(Op_ptr parent:child->parents){
			Ch_ptr c(new Channel);
			channels.push_back(c);
			c->name = s("c") + parent->name + child->name;
			cout << c->name << endl;
			if(c->name == "co1o2")
				cout << "stop!" << endl;
			channelByName[c->name] = c;
			c->fatherOp = parent;
			c->childOp = child;
			c->startTime = M;
			c->endTime = M;
		}
	}


	map<Dev_ptr,Op_ptr> opOnDev;
	vector<Op_ptr> finishedOps;
	map<Dev_ptr,vector<Ch_ptr>> injectedC;
	map<Dev_ptr,vector<Ch_ptr>> ejectedC;




	for(int t = 0; ; t++){

		if(t == 40)
			cout << "time is 40" << endl;
		if(t == 465)
			cout  << "stop" << endl;
 		//if device's operation is end
		for(Dev_ptr d:devices){
			cout << "time is " << t << endl;
			if(d->availeble)
				cout << d->name << "  is availeble" << endl;
			if(d->injecting){
				cout <<d->name<< " is Occupied by" << opOnDev[d]->name << endl;
				cout << d->name << "  is injecting " << "start at" << d->injectTime<<endl;

			}
			if(d->isRunning){
				cout <<d->name << " is Occupied by " << opOnDev[d]->name << endl;
				cout << d->name << "  is running " << "start at"<<d->startTime<<endl;
			}
			if(d->ejecting){
				cout<<d->name<<" is Occupied by "  << opOnDev[d]->name << endl;
				cout << d->name << "  is ejecting " << "start at"<<d->endTime<<endl;
			}

			if(d->availeble){
				opOnDev[d] = nullOp;
				injectedC[d].clear();
				ejectedC[d].clear();
				Op_ptr chosenOp = nullOp;
				int longestStoreTime = 0;
				//choose an op to run
				for(Op_ptr op:ops){
					if(op->running)
						continue;
					if(op->done)
						continue;
					if(op->type != d->type)
						continue;

					bool allParentChannelReady = true;
					for(Op_ptr father:op->parents){
						string cName = s("c") + father->name + op->name;
						Ch_ptr c = channelByName[cName];
						if(c->startTime > t)
							allParentChannelReady = false;

						if(c->startTime <= t && c->startTime + TRANSTIME > t)
							allParentChannelReady = false;

					}

					if(!allParentChannelReady){
						continue;
					}

					//when op not running, not done and all father channel ready
					//choose the operation with longest storage
					for(Op_ptr father:op->parents){
						string cName = s("c") + father->name + op->name;
						Ch_ptr c = channelByName[cName];

						int storageTime = t - c->startTime;
						if(storageTime > longestStoreTime){
							longestStoreTime = storageTime;
							chosenOp = op;
						}

					}

					if(op->parents.size() == 0){
						if(chosenOp == nullOp)
							chosenOp = op;
					}

				}

				if(chosenOp != nullOp){
					if(chosenOp->name == "o4")
						cout << "stop" << endl;
					opOnDev[d] = chosenOp;
					chosenOp->bindDevice = d;
					chosenOp->running = true;
					chosenOp->injecTime = t;
					d->availeble = false;
					d->injecting = true;
					d->injectTime = t;
					d->injectingSth = false;

				}


			}

			if(d->injecting){
				Op_ptr op = opOnDev[d];

				if(d->injectingSth){
					if(t - d->injectingChannel->injectTime == TRANSTIME){
						injectedC[d].push_back(d->injectingChannel);
						d->injectingChannel->endTime = t;
						d->injectingSth = false;
					}
					else{
						continue;
					}
				}


				//if all cs have been injected, injecting phaze is over
				if(injectedC[d].size() == op->parents.size()){
					//injectedC[d].clear();
					d->injecting = false;
					d->isRunning = true;
					d->startTime = t;
					op->startTime = t;
				}
				//choose a c from all c's to come in
				Ch_ptr chosenC = nullCh;

				int longestStoreTime = 0;
				for(Op_ptr father:op->parents){
					string cName = s("c") + father->name + op->name;
					Ch_ptr c = channelByName[cName];
					//already injected
					if(find(injectedC[d].begin(),injectedC[d].end(),c) != injectedC[d].end())
						continue;

					int storageTime = t - c->startTime;
					if(storageTime > longestStoreTime){
						longestStoreTime = storageTime;
						chosenC = c;
					}

				}

				if(chosenC != nullCh){
					d->injectingChannel = chosenC;
					d->injectingSth = true;
					chosenC->injectTime = t;
				}
			}

			if(d->isRunning){
				Op_ptr op = opOnDev[d];
				if(t - d->startTime == op->duration){
					d->isRunning = false;
					d->ejecting = true;
					d->endTime = t;
					d->ejectingSth = false;
					op->endTime = t;
				}

			}

			if(d->ejecting){
				Op_ptr op = opOnDev[d];
				int longestStoreTime = 0;

				if(d->ejectingSth){
					if(t - d->ejectingChannel->startTime == TRANSTIME){
						ejectedC[d].push_back(d->ejectingChannel);

						d->ejectingSth = false;
					}
					else
						continue;
				}


				//if all cs have been ejected, ejecting phaze is over
				if(ejectedC[d].size() == op->children.size()){
					d->ejecting = false;
					d->availeble = true;
					d->endTime = t;
					//ejectedC[d].clear();
					//opOnDev[d] = nullOp;
					op->running = false;
					op->done = true;
					op->ejectTime = t;
					finishedOps.push_back(op);

				}




				//choose a c from all c's to go out
				Ch_ptr chosenC = nullCh;

				for(Op_ptr child:op->children){
					string cName = s("c") + op->name+ child->name;
					Ch_ptr c = channelByName[cName];
					//already injected
					if(find(ejectedC[d].begin(),ejectedC[d].end(),c) != ejectedC[d].end())
						continue;
					chosenC = c;
				}



				if(chosenC != nullCh){
					d->ejectingChannel = chosenC;

					d->ejectingSth = true;
					chosenC->startTime = t;
				}
			}
		}

		//if all ops are done
		cout << finishedOps.size() << " ops have finished" << endl;
		if(finishedOps.size() == ops.size())
			break;
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
		/*
		else if(type == "source"){
			operation->type = operationType::source;
		}
*/

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
		/*
		else if(type == "source"){
			device->type = operationType::source;
		}*/

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








