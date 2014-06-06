#ifndef YHGE_ANIMATION_ANIMATION_H_
#define YHGE_ANIMATION_ANIMATION_H_

#include "cocos2d.h"
#include "../YHGEMacros.h"
#include "AnimationInterface.h"
#include "Frame.h"

NS_CC_YHGE_BEGIN

typedef struct _AnimationDataFlag
{
    bool haveTransform;
    bool haveColor;
    bool haveOpacity;

} AnimationDataFlag;

class Animation:public CCObject
{
public:
    
    Animation();
    
    ~Animation();
    
    bool init();
    
    bool init(float duration);
    
    /**
     * 开始
     */
    void play();
    
    /**
     * 停止。
     * 不会修改状态，类似暂停
     */
    void stop();
    
    /**
     * 显示下一帧，并停止。
     */
    void nextFrame();
    
    /**
     * 显示上一帧，并停止
     */
    void prevFrame();
    
    /**
     * 转到某一帧，并播放
     */
    void gotoAndPlay(int index);
    
    /**
     * 转成某一帧，并停止。
     */
    void gotoAndStop(int index);
    
    /**
     * 加入一个帧数据
     */
    void appendFrame(Frame* frame);
    
    /**
     * 插入一个帧数据
     */
    void insertFrame(Frame* frame,int index);
    
    /**
     * 移除一帧
     */
    void removeFrame(Frame* frame);
    
    /**
     * 根据索引移除一帧
     */
    void removeFrameByIndex(int index);
    
    /**
     * 取得帧数据
     */
    Frame* getFrame(int index);
    
    /**
     * 取得当前帧数据
     */
    Frame* getCurrentFrame();
    
    /**
     * 更新器
     */
    void update(float delta);
    
    /**
     * 更新器。用于帧率一定的动画。
     */
    void update(float delta,int deltaFrame);
    
public:
    
    inline void setEnable(bool enable)
    {
        m_enable = enable;
    }
    
    inline bool isEnable()
    {
        return m_enable;
    }
    
    inline void setCurrentFrameIndex(int currentFrameIndex)
    {
        m_currentFrameIndex = currentFrameIndex<0?0:(currentFrameIndex>=m_frameCount?m_frameCount-1:currentFrameIndex);
    }
    
    inline int getCurrentFrameIndex()
    {
        return m_currentFrameIndex;
    }
    
    inline void setFrameCount(int frameCount)
    {
        m_frameCount = frameCount;
    }
    
    inline int getFrameCount()
    {
        return m_frameCount;
    }
    
//    inline void setTotalDuration(float totalDuration)
//    {
//        m_totalDuration = totalDuration;
//    }
    
    inline float getTotalDuration()
    {
        return m_frames?m_frames->count()*m_duration:0;
    }
    
    inline void setDuration(float duration)
    {
        m_duration = duration;
    }
    
    inline float getDuration()
    {
        return m_duration;
    }
    
    inline void setElapsed(float elapsed)
    {
        m_elapsed = elapsed;
    }
    
    inline float getElapsed()
    {
        return m_elapsed;
    }
    
    inline void setFrames(CCArray* frames)
    {
        CC_SAFE_RETAIN(frames);
        CC_SAFE_RELEASE(m_frames);
        m_frames = frames;
        
        setFrameInfo();
    }
    
    inline CCArray* getFrames()
    {
        return m_frames;
    }

    inline AnimationDataFlag getAnimationDataFlag()
    {
        return m_animationDataFlag;
    }
    
    inline void setAnimationDataFlag(AnimationDataFlag animationDataFlag)
    {
        m_animationDataFlag=animationDataFlag;
    }

    inline bool haveTransform()
    {
        return m_animationDataFlag.haveTransform;
    }
    
    inline void setHaveTransform(bool value)
    {
        m_animationDataFlag.haveTransform=value;
    }

    inline bool haveColor()
    {
        return m_animationDataFlag.haveColor;
    }
    
    inline void setHaveColor(bool value)
    {
        m_animationDataFlag.haveColor=value;
    }

    inline bool haveOpacity()
    {
        return m_animationDataFlag.haveOpacity;
    }
    
    inline void setHaveOpacity(bool value)
    {
        m_animationDataFlag.haveOpacity=value;
    }

    void setAnimationSprite(IAnimationSprite* animationSprite)
    {
        m_animationSprite = animationSprite;
    }

    IAnimationSprite* getAnimationSprite()
    {
        return m_animationSprite;
    }

protected:
    
    inline void setFrameInfo()
    {
        if (m_frames) {
            m_frameCount=m_frames->count();
//            m_totalDuration=m_duration* m_frameCount;
        }else{
            m_frameCount=0;
        }
    }

protected:
    
    //动画是否可用
    bool m_enable;
    
    //当前帧索引
    int m_currentFrameIndex;
    
    //总的帧数
    int m_frameCount;
    
//    //总的时间
//    float m_totalDuration;
    
    //每帧时间
    float m_duration;
    
    //计时
    float m_elapsed;
    
    //帧对象。frame使用对象。因为动画中的相同帧，可以使用同一个对象，节省空间。
    CCArray* m_frames;
    
    //frame中使用的数据标志。一个animation的所有frame使用统一的标志，所以放在animation里，而不是Frame中。
    AnimationDataFlag m_animationDataFlag;

    IAnimationSprite* m_animationSprite;
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_ANIMATION_H_