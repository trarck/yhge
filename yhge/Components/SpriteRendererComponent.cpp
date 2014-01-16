#include "SpriteRendererComponent.h"
#include <yhge/message.h>
#include <yhge/CocosExt/CCDefaultTexture.h>
#include "ComponentMessageDefine.h"
#include "Entity.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN

static const int kEightDirectionAction=1001;

SpriteRendererComponent::SpriteRendererComponent()
:m_spriteRenderer(NULL)
{
    CCLOG("SpriteRendererComponent create");
    m_name="SpriteRendererComponent";
}

SpriteRendererComponent::~SpriteRendererComponent()
{
    CCLOG("SpriteRendererComponent destroy");
}

bool SpriteRendererComponent::init()
{
    CCLOG("SpriteRendererComponent init");
    if (Component::init()) {
        m_spriteRenderer=new CCSprite();
        m_spriteRenderer->initWithTexture(CCDefaultTexture::getInstance()->getTexture());
        
        setRenderer(m_spriteRenderer);
        
        m_spriteRenderer->release();
    }
    return true;
}

bool SpriteRendererComponent::registerMessages()
{
    CCLOG("SpriteRendererComponent::registerMessages");
    
    if(RendererComponent::registerMessages()){
        return true;
    }
    return false;
}

void SpriteRendererComponent::cleanupMessages()
{
	CCLOG("SpriteRendererComponent::cleanupMessages");
    
    RendererComponent::cleanupMessages();
}

NS_CC_YHGE_END

