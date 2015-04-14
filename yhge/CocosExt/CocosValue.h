#ifndef YHGE_COCOSEXT_SUPPORT_CCCOCOSVALUE_H_
#define YHGE_COCOSEXT_SUPPORT_CCCOCOSVALUE_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>
#include "Support/Vector.h"
#include "Support/Map.h"

NS_CC_YHGE_BEGIN


#define COCOSVALUE_CREATE(type)\
static CocosValue* create(type v)\
{\
CocosValue* cocosValue=new CocosValue(v);\
if (cocosValue) {\
cocosValue->autorelease();\
return cocosValue;\
}\
return NULL;\
}

class CocosValue:public Ref
{
public:
    static const CocosValue Null;
    
    typedef Vector<CocosValue*> ValueVector;
    typedef Map<std::string,CocosValue*> 	  ValueMap;
    typedef Map<int,CocosValue*> 	  ValueMapIntKey;
    
    CocosValue();
    
    explicit CocosValue(unsigned char v);
    explicit CocosValue(int v);
    explicit CocosValue(float v);
    explicit CocosValue(double v);
    explicit CocosValue(bool v);
    explicit CocosValue(const char* v);
    explicit CocosValue(const std::string& v);
    
    explicit CocosValue(const ValueVector& v);
    
    explicit CocosValue(const ValueMap& v);
    
    explicit CocosValue(const ValueMapIntKey& v);
    
    CocosValue(const CocosValue& other);
    ~CocosValue();
    
    // assignment operator
    CocosValue& operator= (const CocosValue& other);
    
    CocosValue& operator= (unsigned char v);
    CocosValue& operator= (int v);
    CocosValue& operator= (float v);
    CocosValue& operator= (double v);
    CocosValue& operator= (bool v);
    CocosValue& operator= (const char* v);
    CocosValue& operator= (const std::string& v);
    
    CocosValue& operator= (const ValueVector& v);
    
    CocosValue& operator= (const ValueMap& v);
    
    CocosValue& operator= (const ValueMapIntKey& v);
    
    unsigned char asByte() const;
    int asInt() const;
    float asFloat() const;
    double asDouble() const;
    bool asBool() const;
    std::string asString() const;

    ValueVector& asValueVector();
    const ValueVector& asValueVector() const;
    
    ValueMap& asValueMap();
    const ValueMap& asValueMap() const;
    
    ValueMapIntKey& asIntKeyMap();
    const ValueMapIntKey& asIntKeyMap() const;
    
    enum Type
    {
        NONE,
        BYTE,
        INTEGER,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING,
		VECTOR,
		MAP,
		INT_KEY_MAP
    };
    
    inline bool isNull() const { return _type == NONE; }

    inline Type getType() const { return _type; };
    
    std::string getDescription();
    
    static CocosValue* create()
    {
        CocosValue* cocosValue=new CocosValue();
        if (cocosValue) {
            cocosValue->autorelease();
            return cocosValue;
        }
        return NULL;
    }
    
    COCOSVALUE_CREATE(unsigned char);
    COCOSVALUE_CREATE(int);
    COCOSVALUE_CREATE(float);
    COCOSVALUE_CREATE(double);
    COCOSVALUE_CREATE(bool);
    COCOSVALUE_CREATE(const char*);
    COCOSVALUE_CREATE(const std::string&);
    
private:
    
    void clear();
    
    union
    {
        unsigned char byteVal;
        int intVal;
        float floatVal;
        double doubleVal;
        bool boolVal;
        CCString* strVal;
		ValueVector* vectorVal;
		ValueMap* mapVal;
        ValueMapIntKey* intKeyMapVal;
        
    } _baseData;

    Type _type;
};

NS_CC_YHGE_END


#endif /* defined(YHGE_COCOSEXT_SUPPORT_CCCOCOSVALUE_H_) */
