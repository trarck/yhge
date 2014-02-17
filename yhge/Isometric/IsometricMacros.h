#ifndef YHGE_ISOMETRIC_ISOMETRICMACROS_H_
#define YHGE_ISOMETRIC_ISOMETRICMACROS_H_

#define NS_CC_YHGE_ISOMETRIC_BEGIN                     namespace cocos2d { namespace yhge { namespace isometric {
#define NS_CC_YHGE_ISOMETRIC_END                       }}}
#define USING_NS_CC_YHGE_ISOMETRIC                     using namespace cocos2d::yhge::isometric


/* 
    对坐标转换的一个包装宏。
    主要的区别是一个把图块的大小用宏定义，一个是用类的静态变量存储。
    宏定义的方式在编译的时候就固定了，如果做成库的话，在具体的游戏就没法改变，但是有的时候为了性能(优势不是很大)，直接使用宏使得速度快些。
    使用静态变量，可以在运行的时候改变值，会有点性能损失，基本可以忽略。
    为了保持兼容就定义了个包装宏。
 */
#ifdef USE_ISO_MACRO_COORD
#define YHGE_ISO_COORD_TRANSLATE_WRAP(translate_fun) translate_fun
#else
#define YHGE_ISO_COORD_TRANSLATE_WRAP(translate_fun) yhge::isometric::ISOStaticCoordinate::translate_fun
#endif

#endif //YHGE_ISOMETRIC_ISOMETRICMACROS_H_