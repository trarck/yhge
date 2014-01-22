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

NS_CC_YHGE_END

