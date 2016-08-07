#ifndef OPERATION_H
#define OPERATION_H

using namespace std;


class Operation{
public:
	Operation(int a, int b, int c, int d){
		x = a;
		y = b;
		s = c;
		t = d;
		startTime = 0;
		endTime	= 0;
	}

	Operation(){
		x = 0;
		y = 0;
		s = 0;
		t = 0;
		startTime = 0;
		endTime	= 0;
	}


public:
	int name;
	int x,y,s,t;
	int startTime;
	int endTime;

public:

};
#endif
