//
//  DamageFormula.h
//
#ifndef YHGE_ARITHMETIC_FORMULA_DAMAGEFORMULA_H_
#define YHGE_ARITHMETIC_FORMULA_DAMAGEFORMULA_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN


class DamageFormula : public CCObject 
{

public:

    /**
     * 计算伤害值
     DR:伤害减免，AC:护甲,PAM1:系数1,DAM:伤害值,ATK:攻击力
     DR=AC/(AC+PAM1)
     
     DAM=ATK*(1-DR)=ATK*(1-AC/(AC+PAM1))=ATK*PAM1/(AC+PAM1)
     
     */
    inline static int calcDamage(float attack,float defence,float param1)
    {
        return (int)(attack*param1/(defence+param1));
    }
    
};

NS_CC_YHGE_END

#endif //YHGE_ARITHMETIC_FORMULA_DAMAGEFORMULA_H_
