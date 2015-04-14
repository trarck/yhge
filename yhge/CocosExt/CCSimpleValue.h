#ifndef YHGE_COCOSEXT_SUPPORT_CCVALUEOBJECT_H_
#define YHGE_COCOSEXT_SUPPORT_CCVALUEOBJECT_H_

#include "cocos2d.h"
#include <yhge/YHGEMacros.h>

NS_CC_YHGE_BEGIN


#define SIMPLEVALUE_CREATE(type)\
static SimpleValue* create(type v)\
{\
SimpleValue* value=new SimpleValue(v);\
if (value) {\
value->autorelease();\
return value;\
}\
return NULL;\
}

class SimpleValue:public Ref
{
public:
    static const SimpleValue Null;
    
    SimpleValue();
    
    explicit SimpleValue(unsigned char v);
    explicit SimpleValue(int v);
    explicit SimpleValue(float v);
    explicit SimpleValue(double v);
    explicit SimpleValue(bool v);
    explicit SimpleValue(const char* v);
    explicit SimpleValue(const std::string& v);
    
    SimpleValue(const SimpleValue& other);
    ~SimpleValue();
    
    // assignment operator
    SimpleValue& operator= (const SimpleValue& other);
    
    SimpleValue& operator= (unsigned char v);
    SimpleValue& operator= (int v);
    SimpleValue& operator= (float v);
    SimpleValue& operator= (double v);
    SimpleValue& operator= (bool v);
    SimpleValue& operator= (const char* v);
    SimpleValue& operator= (const std::string& v);
    
    unsigned char asByte() const;
    int asInt() const;
    float asFloat() const;
    double asDouble() const;
    bool asBool() const;
    std::string asString() const;

    enum Type
    {
        NONE,
        BYTE,
        INTEGER,
        FLOAT,
        DOUBLE,
        BOOLEAN,
        STRING
    };
    
    inline bool isNull() const { return _type == NONE; }

    inline Type getType() const { return _type; };
    
    std::string getDescription();
    
    static SimpleValue* create()
    {
        SimpleValue* value=new SimpleValue();
        if (value) {
            value->autorelease();
            return value;
        }
        return NULL;
    }
    
    SIMPLEVALUE_CREATE(unsigned char);
    SIMPLEVALUE_CREATE(int);
    SIMPLEVALUE_CREATE(float);
    SIMPLEVALUE_CREATE(double);
    SIMPLEVALUE_CREATE(bool);
    SIMPLEVALUE_CREATE(const char*);
    SIMPLEVALUE_CREATE(const std::string&);
    
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
    } _baseData;

    Type _type;
};

NS_CC_YHGE_END


#endif /* defined(YHGE_COCOSEXT_SUPPORT_CCVALUEOBJECT_H_) */
