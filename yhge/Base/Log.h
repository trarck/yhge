#ifndef YHGE_BASE_LOG_H_
#define YHGE_BASE_LOG_H_

#include "../YHGEMacros.h"

NS_CC_YHGE_BEGIN

#define __YHLOGWITHFUNCTION(s, ...) \
    cocos2d::CCLog("%s : " s ,__FUNCTION__,  ##__VA_ARGS__)

#define YH_LOG_LEVEL_DEBUG 4
#define YH_LOG_LEVEL_INFO 3
#define YH_LOG_LEVEL_WARN 2
#define YH_LOG_LEVEL_ERROR 1

#if !defined(YH_LOG_LEVEL) || YH_LOG_LEVEL ==0
#define YHDEBUG(...)       do {} while (0)
#define YHINFO(...)   do {} while (0)
#define YHWARN(...)   do {} while (0)
#define YHERROR(...)  do {} while (0)

#elif YH_LOG_LEVEL == 1
#define YHDEBUG(...)   do {} while (0)
#define YHINFO(...) do {} while (0)
#define YHWARN(...)  do {} while (0)
#define YHERROR(...) __YHLOGWITHFUNCTION(__VA_ARGS__)

#elif YH_LOG_LEVEL == 2
#define YHDEBUG(...)   do {} while (0)
#define YHINFO(...)  do {} while (0)
#define YHWARN(format,...) cocos2d::CCLog(format, ##__VA_ARGS__)
#define YHERROR(...)  __YHLOGWITHFUNCTION(__VA_ARGS__)

#elif YH_LOG_LEVEL == 3
#define YHDEBUG(...)   do {} while (0)
#define YHINFO(format, ...)  cocos2d::CCLog(format, ##__VA_ARGS__)
#define YHWARN(format,...) cocos2d::CCLog(format, ##__VA_ARGS__)
#define YHERROR(...)  __YHLOGWITHFUNCTION(__VA_ARGS__)

#elif YH_LOG_LEVEL > 3
#define YHDEBUG(format, ...)      cocos2d::CCLog(format, ##__VA_ARGS__)
#define YHINFO(format,...)   cocos2d::CCLog(format, ##__VA_ARGS__)
#define YHWARN(format,...) cocos2d::CCLog(format, ##__VA_ARGS__)
#define YHERROR(...)  __YHLOGWITHFUNCTION(__VA_ARGS__)
#endif // yh log

NS_CC_YHGE_END

#endif // YHGE_BASE_LOG_H_
