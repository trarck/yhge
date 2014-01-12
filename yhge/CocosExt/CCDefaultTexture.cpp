#include "CCDefaultTexture.h"

USING_NS_CC;

NS_CC_YHGE_BEGIN
   
static unsigned char cc_2x2_white_image[] = {
    // RGBA8888
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF
};

#define CC_YH_2x2_WHITE_IMAGE_KEY  "cc_2x2_white_image"

static CCDefaultTexture* s_defaultTexture=NULL;

CCDefaultTexture::CCDefaultTexture()
    :m_texture(NULL)
{

}

CCDefaultTexture::~CCDefaultTexture()
{
    CC_SAFE_RELEASE_NULL(m_texture);
}

CCDefaultTexture* CCDefaultTexture::getInstance()
{
    if (!s_defaultTexture)
    {
        s_defaultTexture=new CCDefaultTexture();
    }
    return s_defaultTexture;
}

CCTexture2D* CCDefaultTexture::createDefaultTexture()
{
    if (!m_texture)
    {
        CCImage* image = new CCImage();
        bool isOK = image->initWithImageData(cc_2x2_white_image, sizeof(cc_2x2_white_image), CCImage::kFmtRawData, 2, 2, 8);
        CCAssert(isOK, "The 2x2 empty texture was created unsuccessfully.");

        CCTexture2D* texture = CCTextureCache::sharedTextureCache()->addUIImage(image, CC_YH_2x2_WHITE_IMAGE_KEY);
        CC_SAFE_RELEASE(image);
        setTexture(texture);
    }

    return m_texture;
}

CCTexture2D* CCDefaultTexture::getTexture()
{
    return m_texture?m_texture:this->createDefaultTexture();
}


NS_CC_YHGE_END
