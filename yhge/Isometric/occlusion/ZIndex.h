//
//  ZIndex.

#ifndef YHGE_ISOMETRIC_ZINDEX_H_
#define YHGE_ISOMETRIC_ZINDEX_H_

#include "cocos2d.h"
#include <yhge/Isometric/IsometricMacros.h>
#include "ZIndexNode.h"

NS_CC_YHGE_ISOMETRIC_BEGIN

class ZIndex : public Ref {

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
	CCArray *_statics;
	CCArray *_dynamics;
	CCLayer *_sortLayer;
	bool _isWorking;
	bool _staticDirty;
    //弱引用
    SEL_SCHEDULE _pfnUpdate;
};


NS_CC_YHGE_ISOMETRIC_END

#endif //YHGE_ISOMETRIC_ZINDEX_H_
