//============================================================================
// Name        : goodLuck.cpp
// Author      : cheffer
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include "../header/Int4.h"
#include "../header/Node.h"
#include "..//header/plate.h"
#include <iostream>

#include "../header/ILP.h"
#include "../header/writeILP.h"
#include "../header/sequenceGraph.h"
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
#if 1
	SequenceGraph seq("data20.xml");
	//SequenceGraph seq(argv[1]);
	Plate plate;
	plate.setSequenceGraph(seq);
	plate.devicePlacementConstraint();
	plate.channelPlaceConstraint();
	plate.channeTimeConstraint();
	//plate.ValveObject();
	plate.writeToFile();
	map<string,int> results = ILP("ilp.lp");
	plate.readFromSolver(results);
	plate.writeGraphFile(-1);
#endif

#if 0
	Plate plate;
	map<string,int> results = ILP("temp.lp");
	plate.readFromSolver(results);
	plate.writeGraphFile(-1);
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

