#include "AvatarSprite.h"
#include <yhge/CocosExt/CCDefaultTexture.h>
#include "AvatarFrame.h"
#include "Character.h"
#include "Resource.h"

NS_CC_YHGE_BEGIN

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
    CCSprite* component=NULL;
    FrameElement* frameElement=NULL;
    int characterId=0;
    
    CCARRAY_FOREACH(m_components, obj){
        component=static_cast<CCSprite*>(obj);
        
        characterId=component->getTag();
        
        obj=frameElements->objectForKey(characterId);
        
        if (obj) {
            component->setVisible(true);
            frameElement=static_cast<FrameElement*>(obj);
            
            updateDisplayElement(component, frameElement->getDisplayProperty());
            
//            CCLOG("update:%d,%d,%d",frameElement->getCharacterId(),frameElement->getDisplayProperty()->getZOrder(),frameElement->getDisplayProperty()->haveZOrder());
        }else{
            component->setVisible(false);
        }
    }
//    int characterCount=m_components->count();
//    int dataCount=frameElements->count();
//    
//    CCSprite* character=NULL;
//    int i=0,j=0;
//    int characterZOrder=0;
//    
//    while (i<characterCount && j<dataCount) {
//        //update property
//        character= static_cast<CCSprite*>(m_components->objectAtIndex(i));
//        frameElement=static_cast<FrameElement*>(frameElements->objectAtIndex(j));
//        
//        //don't check character id
//        
//        characterZOrder=character->getZOrder();
//        if (characterZOrder == frameElement->getZOrder()) {
//            updateDisplayElement(character, frameElement->getDisplayProperty());
//            
//            ++i;
//            ++j;
//            
//        }else if (characterZOrder<frameElement->getZOrder()){
//            //don't display
//            character->setVisible(false);
//            ++i;
//        }else{
//            //add new element
//            CCSprite* newCharacter=CCSprite::createWithTexture(CCDefaultTexture::getInstance()->createDefaultTexture());
//            
//            updateDisplayElement(newCharacter, frameElement->getDisplayProperty());
//            
//            newCharacter->setZOrder(frameElement->getZOrder());
//            newCharacter->setAnchorPoint(ccp(0, 0));
//            
//            m_components->addObject(newCharacter);
//            
//            addChild(newCharacter);
//            
//            ++j;
//        }
//    }
//    
//    if (j<dataCount) {
//        //add new element
//        for (; j<dataCount; ++j) {
//            frameElement=static_cast<FrameElement*>(frameElements->objectAtIndex(j));
//            
//            CCSprite* newCharacter=CCSprite::createWithTexture(CCDefaultTexture::getInstance()->createDefaultTexture());
//            
//            updateDisplayElement(newCharacter, frameElement->getDisplayProperty());
//            
//            newCharacter->setZOrder(frameElement->getZOrder());
//            newCharacter->setAnchorPoint(ccp(0, 0));
//            
//            m_components->addObject(newCharacter);
//            
//            addChild(newCharacter);
//        }
//    }else if (i<characterCount) {
//        //remove element
//        for (; i<characterCount; ++i) {
//            character= static_cast<CCSprite*>(m_components->objectAtIndex(i));
//            character->setVisible(false);
//        }
//    }
    
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
        
        CCSprite* component=CCSprite::createWithTexture(CCDefaultTexture::getInstance()->createDefaultTexture());
        
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


void AvatarSprite::updateDisplayElement(CCSprite* element,DisplayProperty* property)
{
    
    if (property->haveCharacter()) {
        element->setDisplayFrame(property->getSpriteFrame());
    }
    
    AnimationDataFlag flag=m_animation->getAnimationDataFlag();
    
    if(flag.haveTransform && property->haveTransform()){
//        element->setAdditionalTransform(property->getTransform());
        element->setTransform(property->getTransform());
    }
    
    if (flag.haveColor && property->haveColor())
    {
        element->setColor(property->getColor());
    }
    
    if(flag.haveOpacity && property->haveOpacity()){
        element->setOpacity(property->getOpacity());
    }
    
    if (property->haveZOrder()) {
        element->getParent()->reorderChild(element, property->getZOrder());
    }
}

NS_CC_YHGE_END