//============================================================================
// Name        : goodLuck.cpp
// Author      : cheffer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "../header/ListAlgorithm.h"
#include "../header/Int4.h"
#include "../header/Node.h"
#include "..//header/plate.h"
#include "../header/ListAlgorithm.h"
#include "../header/randomSeq.h"
#include <iostream>

#include "../header/ILP.h"
//#include "../header/writeILP.h"
//#include "../header/sequenceGraph.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <vector>
#include <fstream>
using namespace std;



int main(int   argc,
	     char *argv[]) {




/*
	if (argc < 2) {
			cout << "Usage: lp_c++ filename" << endl;
			return 1;
		}*/
#if 0
	ListAlgorithm L;
	//L.readFromXml("cpa20opsnosource.xml");
	//L.readFromXml("pcr.xml");
	//L.readFromXml("ivd.xml");
	L.readFromXml("random30ops.xml");
	L.genILP();
	map<string,int> results = ILP("seq.lp" );
	L.readFromSolver(results);
	Plate plate;
	//plate.setSequenceGraph(seq);

	//plate.getBindingFromList(L);
	int step =41;
	for(int i = 0; i<L.ops.size(); i += step){
		if(i > 0)
			step = 30;

		plate.constraintClear();

		plate.getPartInfoFromList(L,step);
		plate.devicePlacementConstraint();
		plate.channelPlaceConstraint();
		plate.channeTimeConstraint();

		plate.ValveObject();
		plate.writeToFile();
		map<string,int> results = ILP("ilp.lp");
		plate.readFromSolver(results);
		plate.writeGraphFile(-1);
	}

#endif



#if 1
	 //vector<int> v {10,5,15,5,15,10,15,5,15,10,15,10,15,10,10,5,15,5,15,10,15,5,15,10,15,10,15,10}; //100 ops, with parent maxmum 3
	vector<int> v {10,5,15,5,15,10,15,5,15,10,15,10};
	//vector<int> v {10,5,15,5,15,10,15,5,15,10,15,10,15,10,10,5,15,5,15,10,15,5,15,10,15}; //200ops with maxParent 2
	//vector<int> v {20,20,30,10,30,20,15,10,30,20,20,20}; //200ops with maxParent 2, fat version

	//vector<int> v {10,5,15,5,15,10,15,5,15,10,15,10,15,10,10,5,15,5,15,10,15,5,15,10,15,
	//				10,5,15,5,15,10,15,5,15,10,15}; //300 ops with maxParent 2

	//vector<int> v {10,5,15,5,15,10,15,5,15,10,15,10,15,10,10,5,15,5,15,10,15,5,15,10,15,
	//					10,5,15,5,15,10,15,5,15,10,15,10,5,15,5,15,10,15,5,15,10,15}; //400 ops with maxParent 2

	//vector<int> v {15,15,45,35,25,30,45,20,45,30,20,30};//200 fat, 2 parent most likely
	//vector<int> v {30,30,50,50,45,30,50,60,45,30,20,30,20,45,30};//400 fat, 2 parent most likely
	//vector<int> v {3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6,3,6}; //200 ops
	//vector<int> v {10,5,15,5,15,10,15,5,15,10,10,5,15,5,15,10,15,5,15,10,10,5,15,5,15,10,15,5,15,10}; // 300 ops
	//vector<int> v {10,5,15,5,15,10,15,5,15,10,10,5,15,5,15,10,15,5,15,10,10,5,15,5,15,10,15,5,15,10,10,5,15,5,15,10,15,5,15,10};//400ops
	RandomSeq seq;
	seq.genSeqByLayer(v);
	seq.genDevs(6);
	seq.drawOps();
	ListAlgorithm L;
	L.devices = seq.devices;
	L.ops = seq.ops;
	L.genILP();
	setGap(0.0);
	setTime(60);
	map<string,int> results = ILP("seq.lp" );
	L.readFromSolver(results);
	Plate plate;
	//plate.setSequenceGraph(seq);

		//plate.getBindingFromList(L);
		int step = 20;
		for(int i = 0; i<L.ops.size(); i += step){
			if(i > 0)
				step = 81;

			plate.constraintClear();

			plate.getPartInfoFromListByTime(L,step);
			plate.devicePlacementConstraint();
			plate.channelPlaceConstraint();
			plate.channeTimeConstraint();

			plate.ValveObject();
			plate.writeToFile();
			setGap(5.0);
			setTime(7200.0);
			map<string,int> results = ILP("ilp.lp");
			plate.readFromSolverDevice(results);
			plate.writeGraphFile(-1);
		}

	return 0 ;


#endif
#define switch 0
#if switch
	//SequenceGraph seq("data3ops_3devs_2concurrentchannel.xml");
	//SequenceGraph seq(argv[1]);
	ListAlgorithm L;
	//L.readFromXml("sequenceGraph16ops6devs.xml");
	//L.readFromXml("sequenceGraph.xml");
	//L.readFromXml("lostsops.xml");
	L.readFromXml("cpa20opsnosource.xml");
	//L.readFromXml("cpa5opswithsource.xml");
	L.listAlgorithm();
	Plate plate;
	//plate.setSequenceGraph(seq);

	//plate.getBindingFromList(L);
	int step =41;
	for(int i = 0; i<L.ops.size(); i += step){
		if(i > 0)
			step = 30;

		plate.constraintClear();

		plate.getPartInfoFromList(L,step);
		plate.devicePlacementConstraint();
		plate.channelPlaceConstraint();
		plate.channeTimeConstraint();

		plate.ValveObject();
		plate.writeToFile();
		map<string,int> results = ILP("ilp.lp");
		plate.readFromSolver(results);
		plate.writeGraphFile(-1);
	}
#endif
#if switch
	//SequenceGraph seq("data3ops_3devs_2concurrentchannel.xml");
		//SequenceGraph seq(argv[1]);
		ListAlgorithm L;
		//L.readFromXml("sequenceGraph16ops6devs.xml");
		L.readFromXml("sequenceGraph.xml");
		//L.readFromXml("lostsops.xml");
		//L.readFromXml("cpa5opsnosource.xml");
		L.listAlgorithm();
		Plate plate;
		//plate.setSequenceGraph(seq);

		//plate.getBindingFromList(L);
		int step = 16;
		for(int i = 0; i<L.ops.size(); i += step){

			plate.constraintClear();

			plate.getPartInfoFromList(L,step);
			plate.devicePlacementConstraint();
			plate.channelPlaceConstraint();
			plate.channeTimeConstraint();

			//plate.ValveObject();
			//plate.writeToFile();
			map<string,int> results = ILP("ilp.lp" );
			plate.readFromSolver(results);
			plate.writeGraphFile(-1);
		}
#endif

#if 0
	Plate plate;
	map<string,int> results = ILP("temp.lp");
	plate.readFromSolver(results);
#endif
	//ILP("temp.lp");


	/*plate p;
	p.placementConstraint();
	string *tmp = &(p.ILP.back());*/
	//cout<< *tmp << endl;

//	ofstream myfile;<fstream>
//	myfile.open ("example.txt");
//	myfile << "Writing this to a file.\n";
//	myfile.close();
//	//Foo f = Foo();
//	Int4 a = Int4(1,2,3,4);

	/*vector<string> varNames;
	vector<string> varTypes;
	varNames.push_back("AA");
	varNames.push_back("BB");
	varTypes.push_back("1");
	varTypes.push_back("0");
	writeILP write;
	write.writeVarNames(varNames,varTypes,"example.txt");*/

	//ILP(argv[1]);
//	Graph g = Graph(3,3);
//	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
//	cout << a.hash() << endl;

	return 0;
}

