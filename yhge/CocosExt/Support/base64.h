#ifndef YHGE_COCOSEXT_SUPPORT_BASE64_H_
#define YHGE_COCOSEXT_SUPPORT_BASE64_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/** 
 * 主要是因为cocos2d没有开放base64的dll导出接口，所以本地使用一份
 */
int base64Decode(unsigned char *in, unsigned int inLength, unsigned char **out);

NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_SUPPORT_BASE64_H_
