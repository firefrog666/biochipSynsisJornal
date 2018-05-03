#ifndef FLOWPATH_H
#define FLOWPATH_H

using namespace std;
#include "../header/Node.h"
#include "../header/device.h"
#include "../header/channel.h"
#include <boost/shared_ptr.hpp>

#ifndef SHAREDPTR
#define SHAREDPTR


#endif





class FlowPath : public Channel{
public:
	Channel* linkedChannel;
	bool	linkedStorage = false;

};
/*class storage : public Channel{

};

class tmpChannel : public Channel{

};*/
#endif
