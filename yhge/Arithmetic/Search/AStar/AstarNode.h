//
//  AstarNode.h
//
#ifndef YHGE_ARITHMETIC_SEARCH_ASTAR_AstarNode_H_
#define YHGE_ARITHMETIC_SEARCH_ASTAR_AstarNode_H_

#include "cocos2d.h"
#include "YHGEMacros.h"

NS_CC_YHGE_BEGIN


class AstarNode : public CCObject 
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
	AstarNode* m_parent;
	int m_x;
	int m_y;
	int m_g;
	int m_h;
	int m_f;
};

NS_CC_YHGE_END

#endif //YHGE_ARITHMETIC_SEARCH_ASTAR_AstarNode_H_
