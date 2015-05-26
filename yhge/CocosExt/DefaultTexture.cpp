#include "DefaultTexture.h"

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

static DefaultTexture* s_defaultTexture=NULL;

DefaultTexture::DefaultTexture()
    :_texture(NULL)
{

}

DefaultTexture::~DefaultTexture()
{
    CC_SAFE_RELEASE_NULL(_texture);
}

DefaultTexture* DefaultTexture::getInstance()
{
    if (!s_defaultTexture)
    {
        s_defaultTexture=new DefaultTexture();
    }
    return s_defaultTexture;
}

Texture2D* DefaultTexture::createDefaultTexture()
{
    if (!_texture)
    {
        Image* image = new Image();
		bool isOK = image->initWithRawData(cc_2x2_white_image, sizeof(cc_2x2_white_image), 2, 2, 8);
        CCAssert(isOK, "The 2x2 empty texture was created unsuccessfully.");

        Texture2D* texture = TextureCache::sharedTextureCache()->addUIImage(image, CC_YH_2x2_WHITE_IMAGE_KEY);
        CC_SAFE_RELEASE(image);
        setTexture(texture);
    }

    return _texture;
}

Texture2D* DefaultTexture::getTexture()
{
    return _texture?_texture:this->createDefaultTexture();
}


NS_CC_YHGE_END
