#ifndef WRITEILP_H
#define WRITEILP_H


#include <fstream>
#include <vector>



class writeILP{
public:
	~writeILP(){
		if(file.is_open())
			file.close();
	}

private:
	ofstream file;



public:
	 void closeFile(){
		 if(file.is_open())
		 		file.close();
	 }

	 void writeOBJ(const vector<string>& OBJ, const char* fileName){
		 //ofstream file;
		 if(!file.is_open())
			 file.open(fileName);
		 file<<"Maximize"<<endl;

		 for(int i = 0; i<= int(OBJ.size()-1); i++)
		 {
			 file<<OBJ.at(i)<<endl;
		 }
	 }

	 void writeBounds(const vector<string> & bounds, const char* fileName){
		 //ofstream file;
		 if(!file.is_open())
			 file.open(fileName);
		 file<<"Bounds"<<endl;

		 for(int i = 0; i<= bounds.size()-1; i++)
		 {
			 file<<bounds.at(i)<<endl;
		 }

	 }
	 void writeVarNames(vector<string> varNames,vector<string> varTypes,const char* fileName){
		if(!file.is_open())
			file.open(fileName);
		bool firstIntegerFlag, firstBinaryFlag, firstSemiFlag;
		firstIntegerFlag = false;
		firstBinaryFlag = false;
		firstSemiFlag = false;
		for(int i = 0; i<= varNames.size()-1; i++)
		{
			//binary
			if(varTypes.at(i) == "1"){
				if(firstBinaryFlag == false){
					firstBinaryFlag = true;
					file<<"Binaries"<<endl;
					file<<varNames.at(i)<<endl;
				}
				else
				{
					file<<varNames.at(i)<<endl;
				}
			}

		}

		for(int i = 0; i<= varNames.size()-1; i++)
		{
			//integer
			if(varTypes.at(i) == "0"){
				if(firstIntegerFlag == false){
					firstIntegerFlag = true;
					file<<"Generals"<<endl;
					file<<varNames.at(i)<<endl;
				}
				else
				{
					file<<varNames.at(i)<<endl;
				}
			}
		}

		for(int i = 0; i<= varNames.size()-1; i++)
		{
			//Semi
			if(varTypes.at(i) == "2"){
				if(firstSemiFlag == false){
					firstSemiFlag = true;
					file<<"Semi"<<endl;
					file<<varNames.at(i)<<endl;
				}
				else
				{
					file<<varNames.at(i)<<endl;
				}
			}
		}


	}

	 void writeConstraint(vector<string> ILP,const char* fileName){
		//ofstream file;
		if(!file.is_open())
			file.open(fileName);
		file<<"SUBJECT TO"<<endl;

		for(int i = 0; i<= ILP.size()-1; i++)
		{
			file<<ILP.at(i)<<endl;
		}

	}
};

#endif

