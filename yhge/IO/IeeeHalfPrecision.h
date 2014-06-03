#ifndef YHGE_IO_IEEEHALFPRECISION_H_
#define YHGE_IO_IEEEHALFPRECISION_H_

#include "../YHGEMacros.h"
#include <float.h>
#include <math.h>
#include <stdint.h>

NS_CC_YHGE_BEGIN


int singles2halfp(void *target, void *source);
int doubles2halfp(void *target, void *source,int next);
int halfp2singles(void *target, void *source);
int halfp2doubles(void *target, void *source,int next);

//使用具体的类型
int singles2halfpTyped(uint16_t* target, uint32_t* source);
int doubles2halfpTyped(uint16_t *target, uint64_t *source);
int halfp2singlesTyped(uint32_t *target, uint16_t *source);
int halfp2doublesTyped(uint64_t *target, uint16_t *source);

NS_CC_YHGE_END

#endif // YHGE_IO_IEEEHALFPRECISION_H_
