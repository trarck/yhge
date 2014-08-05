#include "Define.h"

NS_CC_YHGE_BEGIN

static Device* sDeviceInstance=NULL;

Device::Device()
{
    
}

Device::~Device()
{
    
}

Device* Device::getInstance()
{
	if(!sDeviceInstance){
		sDeviceInstance=new Device();
	}
	
	return sDeviceInstance;
}

void Device::destroyInstance()
{
	if(sDeviceInstance)
	{
		delete sDeviceInstance;
		sDeviceInstance=NULL;
	}
}

bool Device::enableWIFI()
{
    return m_networkType & kNetWIFI;
}

bool Device::enable3G()
{
    return m_networkType & kNetMobile;
}

NS_CC_YHGE_END