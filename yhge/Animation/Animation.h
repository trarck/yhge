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

class Animation:public Ref
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
        _enable = enable;
    }
    
    inline bool isEnable()
    {
        return _enable;
    }
    
    inline void setCurrentFrameIndex(int currentFrameIndex)
    {
        _currentFrameIndex = currentFrameIndex<0?0:(currentFrameIndex>=_frameCount?_frameCount-1:currentFrameIndex);
    }
    
    inline int getCurrentFrameIndex()
    {
        return _currentFrameIndex;
    }
    
    inline void setFrameCount(int frameCount)
    {
        _frameCount = frameCount;
    }
    
    inline int getFrameCount()
    {
        return _frameCount;
    }
    
//    inline void setTotalDuration(float totalDuration)
//    {
//        _totalDuration = totalDuration;
//    }
    
    inline float getTotalDuration()
    {
        return _frames?_frames->count()*_duration:0;
    }
    
    inline void setDuration(float duration)
    {
        _duration = duration;
    }
    
    inline float getDuration()
    {
        return _duration;
    }
    
    inline void setElapsed(float elapsed)
    {
        _elapsed = elapsed;
    }
    
    inline float getElapsed()
    {
        return _elapsed;
    }
    
    inline void setFrames(CCArray* frames)
    {
        CC_SAFE_RETAIN(frames);
        CC_SAFE_RELEASE(_frames);
        _frames = frames;
        
        setFrameInfo();
    }
    
    inline CCArray* getFrames()
    {
        return _frames;
    }

    inline AnimationDataFlag getAnimationDataFlag()
    {
        return _animationDataFlag;
    }
    
    inline void setAnimationDataFlag(AnimationDataFlag animationDataFlag)
    {
        _animationDataFlag=animationDataFlag;
    }

    inline bool haveTransform()
    {
        return _animationDataFlag.haveTransform;
    }
    
    inline void setHaveTransform(bool value)
    {
        _animationDataFlag.haveTransform=value;
    }

    inline bool haveColor()
    {
        return _animationDataFlag.haveColor;
    }
    
    inline void setHaveColor(bool value)
    {
        _animationDataFlag.haveColor=value;
    }

    inline bool haveOpacity()
    {
        return _animationDataFlag.haveOpacity;
    }
    
    inline void setHaveOpacity(bool value)
    {
        _animationDataFlag.haveOpacity=value;
    }

    void setAnimationSprite(IAnimationSprite* animationSprite)
    {
        _animationSprite = animationSprite;
    }

    IAnimationSprite* getAnimationSprite()
    {
        return _animationSprite;
    }

protected:
    
    inline void setFrameInfo()
    {
        if (_frames) {
            _frameCount=_frames->count();
//            _totalDuration=_duration* _frameCount;
        }else{
            _frameCount=0;
        }
    }

protected:
    
    //动画是否可用
    bool _enable;
    
    //当前帧索引
    int _currentFrameIndex;
    
    //总的帧数
    int _frameCount;
    
//    //总的时间
//    float _totalDuration;
    
    //每帧时间
    float _duration;
    
    //计时
    float _elapsed;
    
    //帧对象。frame使用对象。因为动画中的相同帧，可以使用同一个对象，节省空间。
    CCArray* _frames;
    
    //frame中使用的数据标志。一个animation的所有frame使用统一的标志，所以放在animation里，而不是Frame中。
    AnimationDataFlag _animationDataFlag;

    IAnimationSprite* _animationSprite;
};


NS_CC_YHGE_END

#endif //YHGE_ANIMATION_ANIMATION_H_