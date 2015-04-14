#include "SpriteRendererComponent.h"
#include <yhge/message.h>
#include <yhge/CocosExt/CCDefaultTexture.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

static const int kEightDirectionAction=1001;

SpriteRendererComponent::SpriteRendererComponent()
:_spriteRenderer(NULL)
{

}

SpriteRendererComponent::~SpriteRendererComponent()
{

}

bool SpriteRendererComponent::init()
{
    if (RendererComponent::init()) {
        _spriteRenderer=new CCSprite();
        _spriteRenderer->initWithTexture(CCDefaultTexture::getInstance()->getTexture());
        _spriteRenderer->setAnchorPoint(ccp(0.5,0));

//        setRenderer(_spriteRenderer);
        _renderer->addChild(_spriteRenderer);
        
//        CCLayer* test=CCLayerColor::create(ccc4(128, 0, 0, 128), 100, 200);
//        
//        _renderer->addChild(test);
        
        _spriteRenderer->release();
    }
    return true;
}
//
///**
// * 执行action
// */
//void SpriteRendererComponent::runAnimate(CCAction* animate)
//{
//    if (animate->getTag()) {
//        _spriteRenderer->stopActionByTag(animate->getTag());
//    }
//    _spriteRenderer->runAction(animate);
//    
//}
//
///**
// * 停止action
// */
//void SpriteRendererComponent::stopAnimate(CCAction* animate)
//{
//    _spriteRenderer->stopAction(animate);
//}
//
///**
// * 停止action by tag
// */
//void SpriteRendererComponent::stopAnimateByTag(int tag)
//{
//    _spriteRenderer->stopActionByTag(tag);
//}

NS_CC_YHGE_END

