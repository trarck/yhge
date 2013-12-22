#ifndef YHGE_COMPONENTS_COMPONENTINTERFACE_H_
#define YHGE_COMPONENTS_COMPONENTINTERFACE_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN

class ComponentInterface : public CCObject
{
public:
	~ComponentInterface(){};
	virtual bool setup(void)=0;
	virtual bool cleanup(void)=0;
};

NS_CC_YHGE_END

#endif // YHGE_COMPONENTS_COMPONENTINTERFACE_H_
