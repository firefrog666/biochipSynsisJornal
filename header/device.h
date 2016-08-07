#ifndef DEVICE_H
#define DEVICE_H

using namespace std;




class Device{
public:
	Device(int a, int b, int c, int d){
		x = a;
		y = b;
		s = c;
		t = d;
		startTime = 0;
		endTime	= 0;
	}

	Device(){
		x = 0;
		y = 0;
		s = 0;
		t = 0;
		startTime = 0;
		endTime	= 0;
		portXOffset = -1;
		portYOffset = -1;
	}
private:
	int x,y,s,t;

public:
	string name;
	int id;
	int startTime;
	int endTime;
	int sizeX,sizeY;
	int portXOffset;
	int portYOffset;

public:
	inline bool operator== (const Device& rhs) const{
				if(		this->name == rhs.name &&
						this->id == rhs.id &&
						this->sizeX == rhs.sizeX &&
						this->sizeY == rhs.sizeY &&
						this->startTime == rhs.startTime &&
						this->endTime == rhs.endTime
						)
					return true;
				else
					return false;

			}


};


//Operation in a sequence graph
class Op {
public:
	Op(){
		startTime = 0;
		endTime = 0;

	}

	//compare each operation by startTime
		inline bool operator< ( const Op& rhs) const{
			if(this->startTime < rhs.startTime)
				return true;
			else
				return false;
		}
		inline bool operator> (const Op& rhs) const{ return rhs < *this; }
		inline bool operator<=(const Op& rhs) const{ return !(*this > rhs); }
		inline bool operator>=(const Op& rhs) const{ return !(*this < rhs); }
		inline bool operator== (const Op& rhs) const{
			if(		this->name == rhs.name &&
					this->bindDevice == rhs.bindDevice &&
					this->parents == rhs.parents &&
					this->children == rhs.children &&
					this->startTime == rhs.startTime &&
					this->endTime == rhs.endTime
					)
				return true;
			else
				return false;

		}
public:
	string name;
	Device bindDevice;
	vector<Op> parents;
	vector<Op> children;
	int startTime;
	int endTime;
};

#endif
