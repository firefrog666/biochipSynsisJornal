#ifndef FLOWPATH_H
#define FLOWPATH_H

using namespace std;
#include "../header/Node.h"
#include "../header/device.h"
#include "../header/channel.h"
#include <boost/shared_ptr.hpp>

#ifndef SHAREDPTR
#define SHAREDPTR
typedef boost::shared_ptr<Op> Op_ptr;
typedef boost::shared_ptr<Device> Dev_ptr;
typedef boost::shared_ptr<Channel> Channel_ptr;

#endif





class FlowPath : public Channel{
public:
	Channel_ptr linkedChannel;
	bool	linkedStorage = false;

};
/*class storage : public Channel{

};

class tmpChannel : public Channel{

};*/
#endif
