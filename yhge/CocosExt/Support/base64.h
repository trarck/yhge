#ifndef YHGE_COCOSEXT_SUPPORT_BASE64_H_
#define YHGE_COCOSEXT_SUPPORT_BASE64_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN

/** 
 * ��Ҫ����Ϊcocos2dû�п���base64��dll�����ӿڣ����Ա���ʹ��һ��
 */
int base64Decode(unsigned char *in, unsigned int inLength, unsigned char **out);

NS_CC_YHGE_END

#endif // YHGE_COCOSEXT_SUPPORT_BASE64_H_
