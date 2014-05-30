#include "AvatarSprite.h"
#include "AvatarFrame.h"
#include <yhge/CocosExt/CCDefaultTexture.h>

NS_CC_YHGE_BEGIN

AvatarSprite::AvatarSprite()
:m_animation(NULL)
,m_elements(NULL)
{
    
}

AvatarSprite::~AvatarSprite()
{
    CC_SAFE_RELEASE_NULL(m_animation);
    CC_SAFE_RELEASE_NULL(m_elements);
}

bool AvatarSprite::init()
{
    if (CCSpriteBatchNode::init()) {
        
        m_elements=new CCArray();
        
        return true;
    }
    
    return false;
}

void AvatarSprite::setAnimationFrame(Frame* frame)
{
    AvatarFrame* avatarFrame=static_cast<AvatarFrame*>(frame);
    
    CCArray* frameElements=avatarFrame->getElements();
    
    //update elements
    int i=0,j=0;
    
    int characterCount=m_elements->count();
    int dataCount=frameElements->count();
    
    CCSprite* character=NULL;
    FrameElement* frameElement=NULL;
    
    int characterZOrder=0;
    
    while (i<characterCount && j<dataCount) {
        //update property
        character= static_cast<CCSprite*>(m_elements->objectAtIndex(i));
        frameElement=static_cast<FrameElement*>(frameElements->objectAtIndex(j));
        
        //don't check character id
        
        characterZOrder=character->getZOrder();
        if (characterZOrder == frameElement->getZOrder()) {
            updateDisplayElement(character, frameElement->getDisplayProperty());
            
            ++i;
            ++j;
            
        }else if (characterZOrder<frameElement->getZOrder()){
            //don't display
            character->setVisible(false);
            ++i;
        }else{
            //add new element
            CCSprite* newCharacter=CCSprite::createWithTexture(CCDefaultTexture::getInstance()->createDefaultTexture());
            
            updateDisplayElement(newCharacter, frameElement->getDisplayProperty());
            
            newCharacter->setZOrder(frameElement->getZOrder());
            
            addChild(newCharacter);
            
            ++j;
        }
    }
    
    if (j<dataCount) {
        //add new element
        for (; j<dataCount; ++j) {
            frameElement=static_cast<FrameElement*>(frameElements->objectAtIndex(j));
            
            CCSprite* newCharacter=CCSprite::createWithTexture(CCDefaultTexture::getInstance()->createDefaultTexture());
            
            updateDisplayElement(newCharacter, frameElement->getDisplayProperty());
            
            newCharacter->setZOrder(frameElement->getZOrder());
            
            addChild(newCharacter);
        }
    }else if (i<characterCount) {
        //remove element
        for (; i<characterCount; ++i) {
            character= static_cast<CCSprite*>(m_elements->objectAtIndex(i));
            character->setVisible(false);
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


void AvatarSprite::updateDisplayElement(CCSprite* element,DisplayProperty* property)
{
    element->setDisplayFrame(property->getSpriteFrame());
    
    AnimationDataFlag flag=m_animation->getAnimationDataFlag();
    
    if(flag.haveTransform){
        element->setAdditionalTransform(property->getTransform());
    }
    
    if (flag.haveColor)
    {
        element->setColor(property->getColor());
    }
    
    if(flag.haveOpacity){
        element->setOpacity(property->getOpacity());
    }
}

NS_CC_YHGE_END