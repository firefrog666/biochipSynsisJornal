#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <functional>
#include <fstream>
#include <algorithm>

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
