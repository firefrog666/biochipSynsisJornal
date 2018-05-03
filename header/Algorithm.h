#ifndef ALGORITHM_H
#define ALGORITHM_H


#include "assert.h"
using namespace std;
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

string S(int i);
string S(const char* s);
string S(string s);
#define EDGE_FILE "drawedges.txt"
#define EDGE_NAME_FILE "edgesNames.txt"
#define NODE_NAME_FILE "nodeNames.txt"
#define NODE_FILE "drawnodes.txt"
#define DRAW_SCRIPT "./drawGraph.sh "
#define LOG "log_file.txt"
#define V vector
typedef enum {
	RED = 0,
	BLUE = 1,
	WHITE = 2,
	BLACK = 3,
	GRAY = 4
} Color;


extern ofstream lg;





/*
namespace Algorithm{

	template <typename T>
	void remove(std::vector<T>& v, T e)
	{
		auto it = std::find(v.begin(), v.end(), e);
		if(it != v.end())
			v.erase(it);
	}

	template <class T,class T2>
	void remove(std::map<T,T2>& v, T e)
	{
		auto it = v.find(e);
		if(it != v.end())
			v.erase(it);
	}



	template<class T>
	void exchange(vector<T>& input, int i,int j){
	    T tmp = input.at(j);
	    input.at(j) = input.at(i);
	    input.at(i) = tmp;

	}

	template<class T>
	int partition(vector<T>& input,int p,int r){
	       int index = p - 1;
	       T x = input.at(r);
	       for(int j = p; j<=r-1; j++){
	           if(input.at(j) <= x){
	               index++;
	               exchange(input,index,j);
	           }
	       }

	       exchange(input, index+1,r);
	       return index+1;

	}



	template<class T>
	void quickSort(std::vector<T>& input,int p,int r){
		if (p < r){
			int q = partition(input,p,r);
			quickSort(input,p,q-1);
			quickSort(input,q+1,r);

		}
	}

	template<class T>
	T* previousElement(std::vector<T> const & vec, T element){
		T* pre = nullptr;
		///typename std::vector<T>::iterator it;
		auto it = find(vec.begin(),vec.end(),element);
		if(it != vec.begin() && it != vec.end()){
			it--;
			*pre = *it;
		}


		return pre;
	}
}
*/


class  algo final{



public:

	template<typename T>
	static T stringToNumber(string& s){
		T r;
		istringstream abuffer(s);
		abuffer>>r;
		return r;
	}



	template<typename T>
	static bool vecContains(const  std::vector<T>& vec, T& element)
	{
		if(find(vec.begin(),vec.end(),element) == vec.end())
			return false;
		else
			return true;
	}

	template<typename T>
	static bool vecsContains(const  std::vector<std::vector<T>>& vecs, T& element)
	{
		for(vector<T> vec:vecs){
			if(vecContains(vec,element))
				return true;
		}

		return false;
	}

	template<typename key, typename T>
	static bool mapContains(std::map<key,T>& m, key& k)
	{
		if(m.find(k)==m.end())
			return false;
		else
			return true;
	}

	template<typename key, typename T>
	static T mapElemntKey(std::map<key,T>& m, key& k)
	{
		if(mapContains(m,k))
			return m.at(k);
		else
			return NULL;
	}
	template<typename T>
	static void remove(std::vector<T>& vec, T& element)
	{
		auto it = find(vec.begin(),vec.end(),element);

		if(it == vec.end())
			return;

		vec.erase(it);

	}
	template<typename T>
	static void remove(std::vector<T>& vec, std::vector<T>& elements)
	{
		for(T e:elements){
			remove(vec,e);
		}
	}

	template<typename T>
	static void join2Vec(std::vector<T>& vec0, std::vector<T>& vec1)
	{
		vec0.insert(vec0.end(),vec1.begin(),vec1.end());
	}


	template<typename pair_first,typename pair_second,typename T>
	static T map_select_pair(map<pair<pair_first,pair_second>,T>& amap, pair<pair_first,pair_second>& apair)
	{
		if(mapContains(amap,apair))
			return amap[apair];

		pair<pair_first,pair_second> reverser_pair = make_pair(apair.second,apair.first);

		if(mapContains(amap,reverser_pair))
			return amap[reverser_pair];

		T* r = NULL;

		return *r;

	}


	template<typename T>
	static void distincAddVec(std::vector<T>& vec,  T& element){
		if(!vecContains(vec,element))
			vec.push_back(element);
	}


	static int countDigital(int a){
		//assert(a > 0);
		int dig = 1;
		while( a > 10){
			a += 1;
			a = a / 10;
		}
		return dig;
	}

	template<typename T>
	static void pop_front(std::vector<T>& vec)
	{
	    assert(!vec.empty());
	    vec.erase(vec.begin());
	}

	template<typename T>
	static void pop_To_Element(std::vector<T>& vec, T& element)
	{
		if(!vecContains(vec,element))
			return;
		while(element != vec.back()){
			vec.pop_back();
		}
	}

	static float hash2Int(float a, float b){

		float r = a*100+b;

		return r;

	}
	static float hash4Int(float a,float b, float c, float d){


		float dig_1 = d;
		float  dig_10 =  c * 100;
		float  dig_100 = b * 10000;
		float dig_1000 = a * 1000000;
		return dig_1 + dig_10 + dig_100 + dig_1000;

	}

	template<typename T>
	static void writeNumbersInFile(const char* fileName, const vector<T>& numbers){
		ofstream file;
 		//ofstream file;
 		if(!file.is_open())
 			file.open(fileName);


 		for(int i = 0; i<= numbers.size()-1; i++)
 		{
 			file<<numbers.at(i)<<endl;
 		}

 		file.close();

	}
	template<typename T>
	static void readNumbersInFile(const char* fileName,  vector<T>& numbers){
		  string line;
		  ifstream file (fileName);
		  if (file.is_open())
		  {
		    while ( getline (file,line) )
		    {
		      T number;
				istringstream abuffer(line);
				abuffer>>number;
		    	numbers.push_back(number);
		    }
		    file.close();
		  }


		  return;

	}


	template<typename T>
	static void swap(vector<T>& list, int i, int j){
		//std::cout<<"switching"<<std::endl;
		T r = list[i];
		list[i] = list[j];
		list[j] = r;
	}

	template<typename T>
	static int partition(vector<T>& list, int left, int right, int pivotIndex, int (*eva)(T t)){
		 int pivotValue = eva(list[pivotIndex]);
		 swap(list,pivotIndex, right); // 把pivot移到結尾
		 int storeIndex = left;
		 for(int i = left; i< right;i++){
			 if (eva(list[i]) <= pivotValue){
				 swap(list,i,storeIndex);
				 storeIndex = storeIndex + 1;
			 }
		 }
		 swap(list,right, storeIndex); // move pivot back
		 return storeIndex;
	 }
	template<typename T>
	 static int quicksort(vector<T>& list, int left, int right, int(*eva)(T t)){
	     if (right > left){
	         //select a pivot value a[pivotIndex]
	    	 int pivotIndex = (left+right)/2;
	         int pivotNewIndex = partition(list, left, right, pivotIndex,eva);
	         quicksort(list, left, pivotNewIndex-1,eva);
	         quicksort(list, pivotNewIndex+1, right,eva);
	     }
	}

	template<typename T>
	static T popElemnt_i(vector<T>& list,int index){
		int end = list.size()-1;
		swap(list,index,end);
		T result = list.back();
		list.pop_back();
		return result;
	}
	template<typename T>
	static vector<T> slice(const vector<T> &v, int m, int n)
	{
	    vector<T> vec(n - m + 1);
	    copy(v.begin() + m, v.begin() + n + 1, vec.begin());
	    return vec;
	}
	static void pause(){
		cout<<"press any key to continue"<<endl;
		system("read");
	}

};



#endif
