#ifndef INT4_H
#define INT4_H

using namespace std;


class Int4{
public:
	Int4(int a, int b, int c, int d){
		x = a;
		y = b;
		s = c;
		t = d;
	}

	Int4(){
		x = 0;
		y = 0;
		s = 0;
		t = 0;
	}


public:
	int x,y,s,t;

public:
	int hash(){
		return 1000000*x +10000 * y + 100 * s + t;
	}
};
#endif
