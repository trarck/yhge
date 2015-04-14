//
//  AstarNode.h
//
#ifndef YHGE_ARITHMETIC_SEARCH_ASTAR_AstarNode_H_
#define YHGE_ARITHMETIC_SEARCH_ASTAR_AstarNode_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN


class AstarNode : public Ref 
{

public:
	
	AstarNode();
	~AstarNode(void);
	
    bool init();
    bool init(int x,int y);
	bool init(int x ,int y ,int g ,int h);
    
	virtual void setX(int x);
	virtual int getX();
	virtual void setY(int y);
	virtual int getY();
	virtual void setG(int g);
	virtual int getG();
	virtual void setH(int h);
	virtual int getH();
	virtual void setF(int f);
	virtual int getF();
	virtual void setParent(AstarNode* parent);
	virtual AstarNode* getParent();

    
	

protected:
	AstarNode* _parent;
	int _x;
	int _y;
	int _g;
	int _h;
	int _f;
};

NS_CC_YHGE_END

#endif //YHGE_ARITHMETIC_SEARCH_ASTAR_AstarNode_H_
