#include "AvatarFrame.h"

NS_CC_YHGE_BEGIN

 FrameElement::FrameElement()
 :m_displayProperty(NULL)
 ,m_characterId(0)
{

}
 FrameElement::~FrameElement()
 {
     CC_SAFE_RELEASE_NULL(m_displayProperty);
 }

AvatarFrame::AvatarFrame()
:m_elements(NULL)
{
    
}

AvatarFrame::~AvatarFrame()
{
    CC_SAFE_RELEASE_NULL(m_elements);
}
//
//bool AvatarFrame::init()
//{
//    if (Frame::init()) {
//        
//        m_elements=new CCArray();
//        
//        return true;
//    }
//    
//    return false;
//}
//
//void AvatarFrame::addElement(FrameElement* element)
//{
//    CCObject* pObj=NULL;
//    FrameElement* iter=NULL;
//    int index=0;
//    CCARRAY_FOREACH(m_elements, pObj){
//        iter=static_cast<FrameElement*>(pObj);
//        if (element->getZOrder()<iter->getZOrder()) {
//            
//            m_elements->insertObject(element, index);
//            
//            return;
//        }
//        
//        ++index;
//    }
//    
//    m_elements->addObject(element);
//}
//
//void AvatarFrame::removeElement(FrameElement* element)
//{
//    m_elements->removeObject(element);
//}
//
//void AvatarFrame::removeElementByZOrder(int zOrder)
//{
//    CCObject* pObj=NULL;
//    FrameElement* iter=NULL;
//    int index=0;
//    CCARRAY_FOREACH(m_elements, pObj){
//        iter=static_cast<FrameElement*>(pObj);
//        if (zOrder==iter->getZOrder()) {
//            m_elements->removeObjectAtIndex(index);
//            break;
//        }
//        ++index;
//    }
//}


bool AvatarFrame::init()
{
    if (Frame::init()) {
        
        m_elements=new CCDictionary();
        
        return true;
    }
    
    return false;
}

void AvatarFrame::addElement(FrameElement* element)
{
    m_elements->setObject(element, element->getCharacterId());
}

void AvatarFrame::removeElement(FrameElement* element)
{
    m_elements->removeObjectForKey(element->getCharacterId());
}

void AvatarFrame::removeElementByZOrder(int zOrder)
{
    CCDictElement* elem=NULL;
    FrameElement* iter=NULL;
    int index=0;
    CCDICT_FOREACH(m_elements, elem){
        iter=static_cast<FrameElement*>(elem->getObject());
        if (zOrder==iter->getZOrder()) {
            m_elements->removeObjectForElememt(elem);
            break;
        }
        ++index;
    }
}
NS_CC_YHGE_END