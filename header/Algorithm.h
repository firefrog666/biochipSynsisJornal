#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <vector>
#include <algorithm>

namespace Algorithm{

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





#endif
