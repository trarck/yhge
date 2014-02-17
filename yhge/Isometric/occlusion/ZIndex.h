//
//  ZIndex.

#ifndef YHGE_ISOMETRIC_ZINDEX_H_
#define YHGE_ISOMETRIC_ZINDEX_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ZIndexNode.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class ZIndex : public CCObject {

public:
    ZIndex();
    ~ZIndex();

    ZIndex* sharedZIndex();
    ZIndex* create(CCLayer* sortLayer);
    bool init();
    bool init(CCLayer* sortLayer);

    void insertStatic(ZIndexNode* node);
    void insertDynamic(ZIndexNode* node);
    void removeStatic(ZIndexNode* node);
    void removeDynamic(ZIndexNode* node);

    CCArray* insertSort(ZIndexNode* node ,CCArray* rects);
    CCArray* sort();
    void sortStatics();
    //动态指定。
    void start();
    void stop();
    int caculateSideFrom(CCRect* pFrom ,CCRect* pTo);

	void update(float delta);
    void setUpdate(SEL_SCHEDULE pfnUpdate);
public:
    
    typedef enum {
        ZIndex_Static,
        ZIndex_Dynamic
    } ZIndexType;
    
protected:
	CCArray *m_pStatics;
	CCArray *m_pDynamics;
	CCLayer *m_pSortLayer;
	bool m_bIsWorking;
	bool m_bStaticDirty;
    //弱引用
    SEL_SCHEDULE m_pfnUpdate;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ZINDEX_H_
