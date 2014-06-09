#include "AvatarSprite.h"
#include <yhge/CocosExt/CCDefaultTexture.h>
#include "AvatarFrame.h"
#include "Character.h"
#include "Resource.h"

NS_CC_YHGE_BEGIN

AvatarComponent* AvatarComponent::create()
{
    AvatarComponent* avatarComponent=new AvatarComponent();
    if (avatarComponent && avatarComponent->init())
    {
        avatarComponent->autorelease();
        return avatarComponent;
    }

    CC_SAFE_DELETE(avatarComponent);
    return NULL;
}

AvatarComponent* AvatarComponent::create(const char *pszFileName)
{
    AvatarComponent* avatarComponent=new AvatarComponent();
    if (avatarComponent && avatarComponent->initWithFile(pszFileName))
    {
        avatarComponent->autorelease();
        return avatarComponent;
    }

    CC_SAFE_DELETE(avatarComponent);
    return NULL;
}

AvatarComponent* AvatarComponent::create(const char *pszFileName, const CCRect& rect)
{
    AvatarComponent* avatarComponent=new AvatarComponent();
    if (avatarComponent && avatarComponent->initWithFile(pszFileName,rect))
    {
        avatarComponent->autorelease();
        return avatarComponent;
    }

    CC_SAFE_DELETE(avatarComponent);
    return NULL;
}

AvatarComponent* AvatarComponent::createWithTexture(CCTexture2D *pTexture)
{
    AvatarComponent* avatarComponent=new AvatarComponent();
    if (avatarComponent && avatarComponent->initWithTexture(pTexture))
    {
        avatarComponent->autorelease();
        return avatarComponent;
    }

    CC_SAFE_DELETE(avatarComponent);
    return NULL;
}

AvatarComponent* AvatarComponent::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    AvatarComponent* avatarComponent=new AvatarComponent();
    if (avatarComponent && avatarComponent->initWithTexture(pTexture,rect))
    {
        avatarComponent->autorelease();
        return avatarComponent;
    }

    CC_SAFE_DELETE(avatarComponent);
    return NULL;
}

AvatarComponent* AvatarComponent::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    AvatarComponent* avatarComponent=new AvatarComponent();
    if (avatarComponent && avatarComponent->initWithSpriteFrame(pSpriteFrame))
    {
        avatarComponent->autorelease();
        return avatarComponent;
    }

    CC_SAFE_DELETE(avatarComponent);
    return NULL;
}

AvatarComponent* AvatarComponent::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    AvatarComponent* avatarComponent=new AvatarComponent();
    if (avatarComponent && avatarComponent->initWithSpriteFrameName(pszSpriteFrameName))
    {
        avatarComponent->autorelease();
        return avatarComponent;
    }

    CC_SAFE_DELETE(avatarComponent);
    return NULL;
}

 void AvatarComponent::setTransform(const CCAffineTransform& transform)
{
    m_sTransform=transform;
    m_bTransformDirty=false;
}

AvatarSprite::AvatarSprite()
:m_animation(NULL)
,m_components(NULL)
{
    
}

AvatarSprite::~AvatarSprite()
{
    CC_SAFE_RELEASE_NULL(m_animation);
    CC_SAFE_RELEASE_NULL(m_components);
}

bool AvatarSprite::init()
{
    if (CCSpriteBatchNode::init()) {
        
        m_components=new CCArray();
        
        return true;
    }
    
    return false;
}

bool AvatarSprite::initWithTexture(CCTexture2D *tex, unsigned int capacity)
{
    if (CCSpriteBatchNode::initWithTexture(tex, capacity)) {
        
        m_components=new CCArray();
        
        return true;
    }
    
    return false;
}

bool AvatarSprite::initWithFile(const char* fileImage, unsigned int capacity)
{
    if (CCSpriteBatchNode::initWithFile(fileImage, capacity)) {
        
        m_components=new CCArray();
        
        return true;
    }
    
    return false;
}

void AvatarSprite::setAnimationFrame(Frame* frame)
{
    
//    CCLOG("frame:%d",m_animation->getCurrentFrameIndex());
    
    AvatarFrame* avatarFrame=static_cast<AvatarFrame*>(frame);
    
    CCDictionary* frameElements=avatarFrame->getElements();
    
    //update components
    CCObject* obj=NULL;
    AvatarComponent* component=NULL;
    FrameElement* frameElement=NULL;
    int characterId=0;
    
    CCARRAY_FOREACH(m_components, obj){
        component=static_cast<AvatarComponent*>(obj);
        
        characterId=component->getTag();
        
        obj=frameElements->objectForKey(characterId);
        
        if (obj) {
            component->setVisible(true);
            frameElement=static_cast<FrameElement*>(obj);
            
            updateDisplayElement(component, frameElement->getDisplayProperty());
            
        }else{
            component->setVisible(false);
        }
    }
}

void AvatarSprite::updateCurrentAnimationFrame()
{
    //set current frame
    if (m_animation)
    {
        Frame* frame=m_animation->getCurrentFrame();
        if (frame)
        {
            setAnimationFrame(frame);
        }
    }
}

void AvatarSprite::setupComponets(CCArray* characters)
{
    CCObject* obj=NULL;
    Character* character=NULL;
    Resource* res=NULL;
    
    CCARRAY_FOREACH(characters, obj){
        character=static_cast<Character*>(obj);
        res=character->getResource();
        
        AvatarComponent* component=AvatarComponent::createWithTexture(CCDefaultTexture::getInstance()->createDefaultTexture());
        
        switch (res->getType()) {
            case Resource::kPackTexture:
                component->setDisplayFrame(res->getSpriteFrame());
                break;
                
            case Resource::kFileTexture:
                component->setTexture(res->getTexture());
            default:
                break;
        }
        
        component->setTag(character->getId());
        component->setAnchorPoint(character->getAnchor());
        
        m_components->addObject(component);
        
        addChild(component);
    }
}

void AvatarSprite::clearComponents()
{
    removeAllChildren();
    
    m_components->removeAllObjects();
}


void AvatarSprite::updateDisplayElement(AvatarComponent* component,DisplayProperty* property)
{
    
    if (property->haveCharacter()) {
        component->setDisplayFrame(property->getSpriteFrame());
    }
    
    AnimationDataFlag flag=m_animation->getAnimationDataFlag();
    
    if(flag.haveTransform && property->haveTransform()){
        component->setTransform(property->getTransform());
    }
    
    if (flag.haveColor && property->haveColor())
    {
        component->setColor(property->getColor());
    }
    
    if(flag.haveOpacity && property->haveOpacity()){
        component->setOpacity(property->getOpacity());
    }
    
    if (property->haveZOrder()) {
        if(component->getParent())
            component->getParent()->reorderChild(component, property->getZOrder());
    }
}

NS_CC_YHGE_END