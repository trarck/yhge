#include "SpriteRendererComponent.h"
#include <yhge/message.h>
#include <yhge/CocosExt/CCDefaultTexture.h>
#include "ComponentMessageDefine.h"
#include <yhge/EntityComponent/Entity.h>

USING_NS_CC;

NS_CC_YHGE_BEGIN

static const int kEightDirectionAction=1001;

SpriteRendererComponent::SpriteRendererComponent()
:m_spriteRenderer(NULL)
{

}

SpriteRendererComponent::~SpriteRendererComponent()
{

}

bool SpriteRendererComponent::init()
{
    if (Component::init()) {
        m_spriteRenderer=new CCSprite();
        m_spriteRenderer->initWithTexture(CCDefaultTexture::getInstance()->getTexture());
        m_spriteRenderer->setAnchorPoint(ccp(0.5,0));

        setRenderer(m_spriteRenderer);
        
        m_spriteRenderer->release();
    }
    return true;
}

/**
 * 执行action
 */
void SpriteRendererComponent::runAnimate(CCAction* animate)
{
    if (animate->getTag()) {
        m_spriteRenderer->stopActionByTag(animate->getTag());
    }
    m_spriteRenderer->runAction(animate);
    
}

/**
 * 停止action
 */
void SpriteRendererComponent::stopAnimate(CCAction* animate)
{
    m_spriteRenderer->stopAction(animate);
}

/**
 * 停止action by tag
 */
void SpriteRendererComponent::stopAnimateByTag(int tag)
{
    m_spriteRenderer->stopActionByTag(tag);
}

NS_CC_YHGE_END

