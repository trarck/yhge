#include "AvatarFrame.h"

NS_CC_YHGE_BEGIN

 FrameElement::FrameElement()
 :_displayProperty(NULL)
 ,_characterId(0)
{

}
 FrameElement::~FrameElement()
 {
     CC_SAFE_RELEASE_NULL(_displayProperty);
 }

AvatarFrame::AvatarFrame()
:_elements(NULL)
{
    
}

AvatarFrame::~AvatarFrame()
{
    CC_SAFE_RELEASE_NULL(_elements);
}
//
//bool AvatarFrame::init()
//{
//    if (Frame::init()) {
//        
//        _elements=new CCArray();
//        
//        return true;
//    }
//    
//    return false;
//}
//
//void AvatarFrame::addElement(FrameElement* element)
//{
//    Ref* pObj=NULL;
//    FrameElement* iter=NULL;
//    int index=0;
//    CCARRAY_FOREACH(_elements, pObj){
//        iter=static_cast<FrameElement*>(pObj);
//        if (element->getZOrder()<iter->getZOrder()) {
//            
//            _elements->insertObject(element, index);
//            
//            return;
//        }
//        
//        ++index;
//    }
//    
//    _elements->addObject(element);
//}
//
//void AvatarFrame::removeElement(FrameElement* element)
//{
//    _elements->removeObject(element);
//}
//
//void AvatarFrame::removeElementByZOrder(int zOrder)
//{
//    Ref* pObj=NULL;
//    FrameElement* iter=NULL;
//    int index=0;
//    CCARRAY_FOREACH(_elements, pObj){
//        iter=static_cast<FrameElement*>(pObj);
//        if (zOrder==iter->getZOrder()) {
//            _elements->removeObjectAtIndex(index);
//            break;
//        }
//        ++index;
//    }
//}


bool AvatarFrame::init()
{
    if (Frame::init()) {
        
        _elements=new CCDictionary();
        
        return true;
    }
    
    return false;
}

void AvatarFrame::addElement(FrameElement* element)
{
    _elements->setObject(element, element->getCharacterId());
}

void AvatarFrame::removeElement(FrameElement* element)
{
    _elements->removeObjectForKey(element->getCharacterId());
}

void AvatarFrame::removeElementByZOrder(int zOrder)
{
    CCDictElement* elem=NULL;
    FrameElement* iter=NULL;
    int index=0;
    CCDICT_FOREACH(_elements, elem){
        iter=static_cast<FrameElement*>(elem->getObject());
        if (zOrder==iter->getZOrder()) {
            _elements->removeObjectForElememt(elem);
            break;
        }
        ++index;
    }
}
NS_CC_YHGE_END