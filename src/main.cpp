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
#include "../header/grid.h"
#include "..//header/plate.h"
#include "../header/edge.h"
#include "../header/ListAlgorithm.h"
#include "../header/randomSeq.h"
#include "../header/physicalDesign.h"
#include <iostream>

#include "../header/ILP.h"
#include "../header/Node.h"
#include "../header/draw.h"
//#include "../header/writeILP.h"
//#include "../header/sequenceGraph.h"
#include "../rapidxml-1.13/rapidxml.hpp"
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "../header/Dna.h"

using namespace std;
ofstream lg(LOG, std::ios_base::out | std::ios_base::app );


int generalTest(){
	V<int> v = {1,2,3,4,5,6,7,8};
	V<int> v2 = algo::slice(v,0,7);
	for(auto i:v2)
		cout<<i<<endl;
	return 0;
}


int evalueDna(Dna dna){
	int eva = 0;
	for(int i : dna.chromes){
		eva += i;
	}
	return eva;
}

void dnaTest(){
	float probality  = rand()%100;
	probality = float(probality/100);
	cout<<"probality is "<< probality<<endl;
	Dna d0;
	Dna d1;
	Dna d2;
	Dna d3;
	Dna d4,d5,d6,d7;
	Dna d8,d9,d10,d11,d12,d13,d14,d15;
	d3.chromes = {0,0,0,0,0,1};
	d2.chromes = {0,0,0,0,1,1};
	d1.chromes = {0,0,0,1,1,1};
	d0.chromes = {0,0,0,1,1,1};
	d4.chromes = {0,0,0,0,0,1};
	d5.chromes = {0,0,0,0,1,1};
	d6.chromes = {0,0,0,1,1,1};
	d7.chromes = {0,0,0,1,1,1};
	d8.chromes = {0,0,0,0,0,1};
	d9.chromes = {0,0,0,0,1,1};
	d10.chromes = {0,0,0,1,1,1};
	d11.chromes = {0,0,0,1,1,1};
	d12.chromes = {0,0,0,0,0,1};
	d13.chromes = {0,0,0,0,1,1};
	d14.chromes = {0,0,0,1,1,1};
	d15.chromes = {0,0,0,1,1,1};


	V<Dna> dnas;
	dnas = {d0,d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12,d13,d14,d15};
/*	dnas.push_back(d0);
	dnas.push_back(d1);
	dnas.push_back(d2);
	dnas.push_back(d3);
	dnas.push_back(d4);dnas.push_back(d5);dnas.push_back(d6);dnas.push_back(d7);*/
	const float exchangeRate = 0.5;
	const float muteRate = 0.1;
	char ctnu = 'N';
	int count = 0;
	do{
		dnas = Enviroment::getNextGeneration(dnas,muteRate,exchangeRate,evalueDna);
		//cout<<"continue? Y/n";
		//cin>>ctnu;
		ctnu = 'y';
		count++;
		cout<<"counting...."<<count<<endl;
		if(count > 1000)
			break;
	}while(ctnu == 'Y' || ctnu == 'y');


}

void continued(){


	//get scedule

	lg.clear();
	ListAlgorithm L;
	L.readFromXml("ivd.xml");
	L.genILP();
	setGap(0.9);
	setTime(10.0);
	map<string,int> results;
	results = ILP("seq.lp" );
	L.writeResultToFile(results);
	L.readFromSolver(results);

	lg<<"finish schedule. press enter to continue;"<<endl;
	//cin.get();
	//get synthesis result

	Plate plate = Plate();

	Grid g(4,4);
	plate.setGrid(g);
	int step = 12;

	plate.getPartInfoFromList(L,step);
	plate.setChannelsTime();
	plate.devicePlacement();

	plate.channelStartEnd();
	plate.channelSimplePath();
	plate.channelFirstStoreLast();
	plate.channelTimeConfict();
	//plate.objective();
	setGap(0.9);
	setTime(10);
	plate.writeToFile("ilp.lp");
	results = ILP("ilp.lp");
	lg<<"result size is "<<results.size()<<endl;
	plate.setILPResults(results);
	plate.writeDeviceLoc(); //write device location
	//
	plate.writeGraphFile();
	lg<<"finish synthesis. press enter to continue;"<<endl;
	//cin.get();
	plate.getSynthesiResultGraph();
	//plate.drawPlate("sythesisResult");

	plate.g.reshapeGridGrowRight();


	plate.g.reshapeGridGrowLeft();
	cout<<"after moving grid left"<<endl;

	plate.g.reshapeGridGrowUp();
	cout<<"after moving grid up"<<endl;

	plate.g.reshapeGridGrowDown();


	plate.g.possibleEdgeToAdd();
	plate.g.getBrinkNodeHash();
	plate.splitChannels();
	V<V<Channel*>> crtChSet = plate.findConcrtChannels();
	//plate.elimateCrtChannelSet(crtChSet);

	Dna* d = plate.createPlateDna();
	plate.analysisDna(*d);
	plate.g.addNewEdgesByDna(*d);
	plate.setGridDeviceNode();
	plate.g.addPortByDna(*d,2,2);
	plate.setChannelStoreByDna(*d);
	plate.creatConcurrentPaths(crtChSet.at(0));
	//plate.channelsToFlowChannels();
	return;
	return;

	//v[1] = 0;
	//v[10] = 0;
	//v[25] = 0;
	//d.chromes = v;
	d->printSelf();
	//algo::pause();
	return;


	plate.drawPlate("dnaAdding");
	plate.createFlowChannels();

	lg.close();
	return;




}

int main(int   argc,
	     char *argv[]) {
	//system("read");
	srand(3);
	//generalTest();
	//return 0;
	//dnaTest();
	continued();
	return 0;

#if 0
	setGap(0.1);
	setTime(120.0);
	map<string,int> results = ILP("temp.lp" );

#endif


/*
	if (argc < 2) {
			cout << "Usage: lp_c++ filename" << endl;
			return 1;
		}*/

#define physicalDesgin 0

#if physicalDesgin
	Grid inputGrid(2,2);
	for(Edge* e:inputGrid.edges){
		if(e->x == 0 && e->y == 0 && e->s == 0 && e->t == 1)
			continue;
		e->isStorage = false;
	}

	//inputGrid.edges[5]->isStorage =false;
	//inputGrid.edges[2]->isStorage = false;
	inputGrid.nodes[0]->isDev = true;
	for(Node* n:inputGrid.nodes){
		//if(n->x == 0 && n->y == 1)
			n->isDev = true;
	}
	//inputGrid.nodes[4]->isDev = true;
	//inputGrid.nodes[7]->isDev = true;

	PhysicalDesign p;

	p.inputGrid = inputGrid;
	p.fromGridToSqaures();
	p.genILP();

	return 0;
#endif



#if 1

	ListAlgorithm L;
#if 1
	//L.readFromXml("simpleStore.xml");
	//L.readFromXml("simple.xml");
	//L.readFromXml("cpa20opsnosource.xml");
	//L.readFromXml("pcr.xml");
	L.readFromXml("ivd.xml");
	//L.readFromXml("random30ops.xml");
	//L.readFromXml("150ops.xml");
	//L.readFromXml("70ops.xml");
#else
	RandomSeq seq;
	//vector<int> v {10,5,15,5,15,10,15,5,15,10,15,10}; //100 ops
	vector<int> v {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6}; //narrow 100 ops
	//seq.genDevs(5);
	//vector<int> v {3,6,6};
	seq.genSeqByLayer(v);
	seq.genDevs(5);
	seq.drawOps();

	L.devices = seq.devices;
	L.ops = seq.ops;
#endif
	L.genILP();

	//return 0;
	//L.listAlgorithm();
	//L.writeTimeline();
	cout << "emmm" << endl;
	//return 0;
	setGap(0.1);
	setTime(3600.0);
	map<string,int> results;

#if 1
	L.readResultFromFile();
	L.howManyStore();
	//L.writeTimeline();
	//return 0;
#else
	cout<< "hahahahahha "<<endl;
	results = ILP("seq.lp" );
	L.writeResultToFile(results);
	L.readFromSolver(results);
	return 0;
#endif


	Plate plate = Plate();

	Grid g(4,4);
	plate.setGrid(g);

#define valveCount 0
#if valveCount
	int appsize = 55;

			//plate.genRandomDevLoc();

				plate.getPartInfoFromList(L,appsize);
				plate.setChannelsTime();
				plate.readILPResultsFromFile();
				plate.countValves();

	return 0;
#endif
#define notarchitecutal 1
#if notarchitecutal
	//gen flow plan
	int step = 30;


	plate.getPartInfoFromList(L,step);
	plate.setChannelsTime();
	plate.devicePlacement();

	plate.channelStartEnd();
	plate.channelSimplePath();
	plate.channelFirstStoreLast();
	plate.channelTimeConfict();
	plate.objective();
	setGap(0.1);
	setTime(1800);
	plate.writeToFile("ilp.lp");
	results = ILP("ilp.lp");
	plate.writeDeviceLoc();
	plate.readFromSolver(results);
	plate.readILPResultsFromFile();
	plate.momentUsedEdge(35);
	plate.genPhyGrid();
	PhysicalDesign p;
	plate.phyGrid.shiftToLeftDownCorner();
	p.inputGrid = plate.phyGrid;
	for(Edge* e:p.inputGrid.edges){
		e->printMyself();
		cout << "used at now ? "<<e->isUsedAtMoment << endl;
	}


	p.fromGridToSqaures();
	p.genILP();
	return 0;
	//plate.writeGraphFileByMoments();
	for(int i = 5; i <= 660; i += 10){
		plate.writeGraphFile(i);
	}
	plate.writeGraphFile();


	return 0;

	return 0;
	vector<int> howManyEdges;
	//simulation anealing
#else
	vector<int> howManyEdges;
	srand (time(NULL));
	int step = 20;
	/*for(int i = 0; i <= 10 ; i++){
		if( i > 0)
			step = 35;
			plate.constraintClear();
			plate.getPartInfoFromList(L,step);
			//plate.
			plate.setChannelsTime();
			plate.devicePlacement();

			plate.channelStartEnd();
			plate.channelSimplePath();
			plate.channelFirstStoreLast();
			plate.channelTimeConfict();
			plate.objective();
			plate.readDeviceLoc();
			if(i%2 == 0)
				plate.moveDeviceLoc();
			else
				plate.switchDeviceLoc();

			//plate.writeDevLocToILP();
			plate.writeToFile("arc.lp");
			setGap(0.1);
			if(i == 0)
			setTime(900);
			else
				setTime(1800);
			results = ILP("arc.lp");
			if(results.size()>0){
				plate.writeDeviceLoc(results);
				plate.readFromSolver(results);
				plate.writeGraphFile();
				int edgeUseNum = plate.calEdgeUseNum();
				howManyEdges.push_back(edgeUseNum);
			}
			else{
				plate.clearLastResult();
			}

		}*/
#endif
#define twostep 1
#if twostep

		/*	if(i > 0)
				step = 35;*/
			//step 1 gen
			step = 50;

			//plate.genRandomDevLoc();
		bool readDevLoc = true;
		for(int i = 0; i <= 1000; i++){
			int haha = 0;
			while(results.size() <= 0){
				cout << "on step 1 iteration " << haha <<endl;
				plate.getPartInfoFromList(L,step);
				/*if(readDevLoc)
					plate.readDeviceLoc();*/
				plate.genRandomDevLoc();
				plate.constraintClear();
				plate.setChannelsTime();
				plate.devicePlacement();
				plate.channelStartEnd();
				plate.channelSimplePath();
				plate.channelFirstStoreLast();
				plate.channelTimeConfict();
				plate.objective();

				plate.writeDevLocToILP();
				plate.writeToFile("sastep1.lp");
				setTime(60);
				results = ILP("sastep1.lp");
				if(results.size()>0){
					plate.writeDeviceLoc();
					plate.readFromSolver(results);
					//int edgeUseNum = plate.calEdgeUseNum();
					//howManyEdges.push_back(edgeUseNum);
					//return 0;
				}

				else{
					readDevLoc= false;
					if(haha%2 == 0)
						plate.moveDeviceLoc();
					else
						plate.switchDeviceLoc();
				}
				haha++;
			}

			//step 2
			int step2 = 55;
			plate.getPartInfoFromList(L,step2);
			plate.constraintClear();
			plate.setChannelsTime();
			plate.devicePlacement();
			plate.channelStartEnd();
			plate.channelSimplePath();
			plate.channelFirstStoreLast();
			plate.channelTimeConfict();
			plate.objective();
			plate.writeToFile("sastep2.lp");
			setTime(600);
			results = ILP("sastep2.lp");

			if(results.size()>0){


				plate.readFromSolver(results);
				plate.writeGraphFile();
				int edgeUseNum = plate.calEdgeUseNum();
				howManyEdges.push_back(edgeUseNum);
				if(haha%2 == 0)
					plate.moveDeviceLoc();
				else
					plate.switchDeviceLoc();
				readDevLoc = false;
				plate.clearLastResult();
				plate.clearInforFromL();
				break;
			}
			else{
				/*if(haha%2 == 0)
					plate.moveDeviceLoc();
				else
					plate.switchDeviceLoc();*/
				readDevLoc = false;
				plate.clearInforFromL();
				plate.clearLastResult();

			}
			cout << "now have " << howManyEdges.size() << " result"<<endl;
		}

		for(int num:howManyEdges){
			cout << "use " << num << " edges" << endl;
		}

		return 0;
#endif


/*	step = 20;
	plate.constraintClear();
	plate.getPartInfoFromList(L,step);
				//plate.
	plate.setChannelsTime();
	plate.devicePlacement();

	plate.channelStartEnd();
	plate.channelSimplePath();
	plate.channelFirstStoreLast();
	plate.channelTimeConfict();
	plate.objective();
	//plate.readDeviceLoc();
	plate.writeToFile("arc.lp");
		setGap(0.1);

		setTime(1800);
		results = ILP("arc.lp");
		if(results.size()>0){
			plate.writeDeviceLoc(results);
			plate.readFromSolver(results);
			plate.writeGraphFile();
			int edgeUseNum = plate.calEdgeUseNum();
			howManyEdges.push_back(edgeUseNum);
		}
		else{
			plate.clearLastResult();
		}
		return 0 ;*/
	step = 50;
	bool needMoreOps = true;
	bool needReadDevLoc = true;
	for(int i = 0; i <= 1000; i++){
	/*	if(i > 0)
			step = 35;*/
		plate.constraintClear();
		if(needMoreOps){
			plate.getPartInfoFromList(L,step);
		}
		//plate.genRandomDevLoc();
		plate.setChannelsTime();
		plate.devicePlacement();

		plate.channelStartEnd();
		plate.channelSimplePath();
		plate.channelFirstStoreLast();
		plate.channelTimeConfict();
		plate.objective();
		if(needReadDevLoc){
			plate.readDeviceLoc();
		}
		plate.writeDevLocToILP();
		plate.writeToFile("sa.lp");
		setGap(0.1);
		if(i == 0)
		setTime(1800);
		else
			setTime(3600);
		results = ILP("sa.lp");
		if(results.size()>0){
			needReadDevLoc = false;
			plate.writeDeviceLoc();
			plate.readFromSolver(results);
			int edgeUseNum = plate.calEdgeUseNum();
			howManyEdges.push_back(edgeUseNum);
			needReadDevLoc = false;
		}
		else{
			if(i%2 == 0)
				plate.moveDeviceLoc();
			else
				plate.switchDeviceLoc();

			plate.clearLastResult();
			plate.clearInforFromL();

			needReadDevLoc = false;
			//ops clear read new ops
			needMoreOps = true;

		}

	}

	for(int num:howManyEdges){
		cout << "use " << num << " edges" << endl;
	}

	plate.writeGraphFile();



#endif



#if 0
	 //vector<int> v {10,5,15,5,15,10,15,5,15,10,15,10,15,10,10,5,15,5,15,10,15,5,15,10,15,10,15,10}; //100 ops, with parent maxmum 3
	vector<int> v {10,5,15,5,15,10,15,5,15,10,15,10};

	//vector<int> v {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
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
	seq.genDevs(5);
	seq.drawOps();
	ListAlgorithm L;
	L.devices = seq.devices;
	L.ops = seq.ops;
	L.genILP();
	setGap(0.0);
	setTime(400);
	map<string,int> results = ILP("seq.lp" );
	L.readFromSolver(results);
	Plate plate;
	//plate.setSequenceGraph(seq);
	for(int size = 5;; size++){

		//plate.getBindingFromList(L);
		int step = 20;
		bool finished = false;
		for(int i = 0; i<L.ops.size(); i += step){
			finished = false;
			if(i > 0)
				step = 130;

			plate.constraintClear();
			plate.setChipSize(size);
			plate.getPartInfoFromListByTime(L,step);
			plate.devicePlacementConstraint();
			plate.channelPlaceConstraint();
			plate.channeTimeConstraint();

			plate.ValveObject();
			plate.writeToFile();
			setGap(5.0);
			setTime(7200.0);
			map<string,int> results = ILP("ilp.lp");
			if(results.size() == 0){
				cout << "unfinished" <<endl;
				break;
			}
			plate.readFromSolverDevice(results);
			plate.writeGraphFile(-1);
			finished = true;
		}
		if(finished)
			break;
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
	L.readFromXml("pcr.xml");
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
#if 0
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

