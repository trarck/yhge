#ifndef YHGE_DEVICE_DEVICE_H_
#define YHGE_DEVICE_DEVICE_H_

#include "GameMacros.h"
#include "cocos2d.h"

NS_CC_YHGE_BEGIN

/**
 * 此类不涉及具体不同平台代码，只是保存信息
 */
class Device:public CCObject
{
public:
    
    enum {
        kNetNone=0,
        kNetWIFI=1,
        kNetMobile=2
    };
    
    Device();
    
    ~Device();
    
    bool enableWIFI();
    
    bool enable3G();
	
	static Device* getInstance();
	
	static void destroyInstance();
    
public:
    
    inline void setTarget(int target)
    {
        m_target = target;
    }
    
    inline int getTarget()
    {
        return m_target;
    }
    
    inline void setPlatform(const std::string& platform)
    {
        m_platform = platform;
    }
    
    inline const std::string& getPlatform()
    {
        return m_platform;
    }
    
    inline void setModel(const std::string& model)
    {
        m_model = model;
    }
    
    inline const std::string& getModel()
    {
        return m_model;
    }
    
    inline void setLanguage(const std::string& language)
    {
        m_language = language;
    }
    
    inline const std::string& getLanguage()
    {
        return m_language;
    }
    
    inline void setWritablePath(const std::string& writablePath)
    {
        m_writablePath = writablePath;
    }
    
    inline const std::string& getWritablePath()
    {
        return m_writablePath;
    }
    
    inline void setCachePath(const std::string& cachePath)
    {
        m_cachePath = cachePath;
    }
    
    inline const std::string& getCachePath()
    {
        return m_cachePath;
    }
    
    inline void setNetworkType(int networkType)
    {
        m_networkType = networkType;
    }
    
    inline int getNetworkType()
    {
        return m_networkType;
    }


protected:
    int m_target;
    std::string m_platform;
    std::string m_model;
    std::string m_language;
    std::string m_writablePath;
    std::string m_cachePath;
    int m_networkType;
};


NS_CC_YHGE_END



#endif //YHGE_DEVICE_DEVICE_H_
